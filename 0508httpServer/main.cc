#include "httpServer.h"

int main(){
    
    //HttpServer server("172.31.94.231","8089");
    HttpServer server("172.16.4.132","8089");
    //HttpServer server("47.120.23.204","8089");
    server.Start();//开始监听
    while(1){
        server.RecvAndShow();
    }

    return 0;

}