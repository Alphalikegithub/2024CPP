#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>

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

    struct sockaddr_in servaddr;
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(8888); // 服务端端口
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // 服务端IP地址

    while (true) {
        // 发送消息到服务端
        std::string message;
        std::cout << "Enter message to send: ";
        std::getline(std::cin, message);
        ssize_t n = sendto(sockfd, message.c_str(), message.length(), 0, (struct sockaddr*)&servaddr, sizeof(servaddr));
        if (n < 0 && errno != EAGAIN && errno != EWOULDBLOCK) {
            std::cerr << "Error sending message" << std::endl;
            break;
        }

        // 接收服务端的回复
        char buffer[1024];
        ssize_t n_recv = recvfrom(sockfd, buffer, sizeof(buffer), 0, nullptr, nullptr);
        if (n_recv >= 0) {
            buffer[n_recv] = '\0';
            std::cout << "Received reply from server: " << buffer << std::endl;
        } else if (errno != EAGAIN && errno != EWOULDBLOCK) {
            std::cerr << "Error receiving reply" << std::endl;
            break;
        }

        usleep(100000); // 等待一段时间，避免空循环
    }

    // 关闭套接字
    close(sockfd);

    return 0;
}
