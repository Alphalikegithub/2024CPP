#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main() {
    // 创建套接字
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        std::cerr << "Error creating socket" << std::endl;
        return 1;
    }

    // 绑定IP和端口
    struct sockaddr_in servaddr;
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(8888); // 选择一个未被占用的端口

    if (bind(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0) {
        std::cerr << "Bind failed" << std::endl;
        return 1;
    }

    char buffer[1024];
    struct sockaddr_in cliaddr;
    socklen_t len = sizeof(cliaddr);

    // 接收来自客户端的消息
    ssize_t n = recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)&cliaddr, &len);
    if (n < 0) {
        std::cerr << "Error receiving message" << std::endl;
    } else {
        buffer[n] = '\0';
        std::cout << "Received message from client: " << buffer << std::endl;
    }

    // 关闭套接字
    close(sockfd);

    return 0;
}
