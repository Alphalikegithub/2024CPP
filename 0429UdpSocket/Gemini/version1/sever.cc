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
        cerr << "Usage: server <port> <message>" << endl;
        return 1;
    }

    int port = atoi(argv[1]);
    const char *message = argv[2];

    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("socket");
        return 1;
    }

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(sockfd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("bind");
        close(sockfd);
        return 1;
    }

    struct sockaddr_in clientAddr;
    socklen_t clientAddrLen = sizeof(clientAddr);

    while (true) {
        char buf[1024];
        int len = recvfrom(sockfd, buf, sizeof(buf), 0, (struct sockaddr *)&clientAddr, &clientAddrLen);
        if (len < 0) {
            perror("recvfrom");
            continue;
        }

        cout << "Received message from " << inet_ntoa(clientAddr.sin_addr) << ":" << ntohs(clientAddr.sin_port) << ": " << buf << endl;

        sendto(sockfd, message, strlen(message), 0, (struct sockaddr *)&clientAddr, clientAddrLen);
        if (len < 0) {
            perror("sendto");
            continue;
        }

        cout << "Sent message to " << inet_ntoa(clientAddr.sin_addr) << ":" << ntohs(clientAddr.sin_port) << endl;
    }

    close(sockfd);

    return 0;
}
