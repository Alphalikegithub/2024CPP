#include "unixHeader.h"
#include <memory>
class HttpServer
{
private:
    const char *_ip;//127.0.0.1
    const char *_port;//8089
    int _sockfd;
public:
    HttpServer(const char *ip,const char *port):
    _ip(ip),
    _port(port)
    {}
    

    void Start(){
        _sockfd = socket(AF_INET,SOCK_STREAM,0);//监听socket
        struct sockaddr_in addr;
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = inet_addr(_ip);
        addr.sin_port = htons(atoi(_port));

        int reuse = 1;//允许复用端口
        setsockopt(_sockfd,SOL_SOCKET,SO_REUSEADDR,&reuse,sizeof(int));

        bind(_sockfd,(struct sockaddr*)&addr,sizeof(addr));

        listen(_sockfd,10);//最大监听数量为10
    }

    void RecvAndShow(){
        int netFd = accept(_sockfd,NULL,NULL);

        //智能指针 使用RAII管理缓冲区
        std::unique_ptr<char[]> buf(new char[4096]);//buf.get()
        bzero(buf.get(),4096);//清空

        //读取请求的内容，直接显示在stderr中
        recv(netFd,buf.get(),4096,0);
        fprintf(stderr,"%s\n",buf.get());//打印缓冲区中的内容

        //回应客户端
        //发送火车头
        std::string firstLine = "HTTP/1.1 200 OK\r\n";
        send(netFd,firstLine.c_str(),firstLine.size(),0);
        std::string headers = "Content-Type:test/plain\r\n"
                              "Content-Length:5\r\n";
        send(netFd,headers.c_str(),headers.size(),0);
        std::string emptyLine = "\r\n";
        send(netFd,emptyLine.c_str(),headers.size(),0);
        //----------------到此为止，火车头已经发送完毕

        //----------------接下来是车厢
        //发送火车车厢
        std::string body = "hello";
        send(netFd,body.c_str(),body.size(),0);

        close(netFd);
        fprintf(stderr,"connection closed\n");

        //RAII的思想，把accept放到构造函数里面，把close函数放到析构函数里面
    }
    
};

