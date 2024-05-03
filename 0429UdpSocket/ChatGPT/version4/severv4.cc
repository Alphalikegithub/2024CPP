#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <string.h>

int main() {
    // 创建套接字
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        std::cerr << "Error creating socket" << std::endl;
        return 1;
    }

    // 设置套接字为非阻塞模式
    int flags = fcntl(sockfd, F_GETFL, 0);
    fcntl(sockfd, F_SETFL, flags | O_NONBLOCK);

    // 绑定IP和端口
    struct sockaddr_in servaddr, cliaddr;
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(8888); // 选择一个未被占用的端口

    if (bind(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0) {
        std::cerr << "Bind failed" << std::endl;
        return 1;
    }

    char buffer[1024];
    socklen_t len = sizeof(cliaddr);

    while (true) {
        // 接收来自客户端的消息
        ssize_t n = recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)&cliaddr, &len);
        if (n >= 0) {
            buffer[n] = '\0';
            std::cout << "Received message from client: " << buffer << std::endl;

            // 发送回复到客户端
            std::string reply = "Message received!";
            ssize_t n_sent = sendto(sockfd, reply.c_str(), reply.length(), 0, (struct sockaddr*)&cliaddr, len);
            if (n_sent < 0) {
                std::cerr << "Error sending reply" << std::endl;
            }
        } else if (errno != EAGAIN && errno != EWOULDBLOCK) {
            std::cerr << "Error receiving message" << std::endl;
        }

        // 清空缓冲区
        memset(buffer, 0, sizeof(buffer));
        usleep(100000); // 等待一段时间，避免空循环
    }

    // 关闭套接字
    close(sockfd);

    return 0;
}
