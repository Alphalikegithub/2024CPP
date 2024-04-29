#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

void ARGS_CHECK(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <IP address>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
}

int main(int argc,char* argv[]){
    ARGS_CHECK(argc,2);
    struct in_addr addr;
    inet_aton(argv[1],&addr);
    printf("addr = %08x\n",addr.s_addr);
    return 0;
}

