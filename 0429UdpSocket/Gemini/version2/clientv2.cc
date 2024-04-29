#include <iostream>
#include <stdio.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

using namespace std;

int main(int argc, char **argv) {
    if (argc != 3) {
        cerr << "Usage: client <server_ip> <port>" << endl;
        return 1;
    }

    const char *serverIp = argv[1];
    int port = atoi(argv[2]);

    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("socket");
        return 1;
    }

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr(serverIp);

    while (true) {
        string message;
        cout << "Enter message to send: ";
        getline(cin, message);

        if (message == "exit") {
            break;
        }

        int len = sendto(sockfd, message.c_str(), message.size(), 0, (struct sockaddr *)&addr, sizeof(addr));
        if (len < 0) {
            perror("sendto");
            close(sockfd);
            return 1;
        }

        cout << "Sent message: " << message << endl;

        char buf[1024];
        socklen_t addrLen = sizeof(addr);

        int recvLen = recvfrom(sockfd, buf, sizeof(buf), 0, (struct sockaddr *)&addr, &addrLen);
        if (recvLen < 0) {
            perror("recvfrom");
            close(sockfd);
            return 1;
        }

        cout << "Received message from " << inet_ntoa(addr.sin_addr) << ":" << ntohs(addr.sin_port) << ": " << buf << endl;
    }

    close(sockfd);

    return 0;
}
