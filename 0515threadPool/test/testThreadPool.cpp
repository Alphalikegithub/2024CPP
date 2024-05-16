#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <functional>
#include <queue>

class ThreadPool {
public:
    ThreadPool(int minThreads, int maxThreads, int queueCapacity)
        : minNum(minThreads), maxNum(maxThreads), queueCapacity(queueCapacity), 
          queueSize(0), shutdown(false) {
        threadID.reserve(maxThreads);
        taskQ.reserve(queueCapacity);

        // Create worker threads
        for (int i = 0; i < minNum; ++i) {
            threadID.emplace_back(std::thread(&ThreadPool::worker, this));
        }

        // Start manager thread
        managerThread = std::thread(&ThreadPool::manager, this);
    }

    ~ThreadPool() {
        {
            std::unique_lock<std::mutex> lock(mutexPool);
            shutdown = true;
        }
        cvNotEmpty.notify_all();
        cvNotFull.notify_all();

        for (auto& thread : threadID) {
            thread.join();
        }

        managerThread.join();
    }

    void addTask(std::function<void()> task) {
        std::unique_lock<std::mutex> lock(mutexPool);
        cvNotFull.wait(lock, [this] { return queueSize < queueCapacity || shutdown; });
        if (shutdown) return;
        taskQ.push(std::move(task));
        ++queueSize;
        cvNotEmpty.notify_one();
    }

private:
    void worker() {
        while (true) {
            std::function<void()> task;
            {
                std::unique_lock<std::mutex> lock(mutexPool);
                cvNotEmpty.wait(lock, [this] { return !taskQ.empty() || shutdown; });
                if (shutdown) return;
                task = std::move(taskQ.front());
                taskQ.pop();
                --queueSize;
                cvNotFull.notify_one();
            }
            task();
        }
    }

    void manager() {
        while (true) {
            std::this_thread::sleep_for(std::chrono::seconds(3));

            std::unique_lock<std::mutex> lock(mutexPool);
            int queueSize = this->queueSize;
            int liveNum = threadID.size();
            lock.unlock();

            if (queueSize > liveNum && liveNum < maxNum) {
                int num = std::min(maxNum - liveNum, NUMBER);
                for (int i = 0; i < num; ++i) {
                    threadID.emplace_back(std::thread(&ThreadPool::worker, this));
                }
            }

            if (liveNum > minNum && queueSize * 2 < liveNum) {
                int exitNum = std::min(liveNum - minNum, NUMBER);
                for (int i = 0; i < exitNum; ++i) {
                    cvNotEmpty.notify_one();
                }
            }
        }
    }

private:
    const int NUMBER = 2;
    int minNum;
    int maxNum;
    int queueCapacity;
    int queueSize;
    bool shutdown;

    std::mutex mutexPool;
    std::condition_variable cvNotEmpty;
    std::condition_variable cvNotFull;

    std::vector<std::thread> threadID;
    std::queue<std::function<void()>> taskQ;
    std::thread managerThread;
};

int main() {
    ThreadPool pool(3, 10, 100);

    for (int i = 0; i < 100; ++i) {
        pool.addTask([i] {
            std::cout << "Thread " << std::this_thread::get_id() << " is working, number = " << i + 100 << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
        });
    }

    std::this_thread::sleep_for(std::chrono::seconds(30));

    return 0;
}
