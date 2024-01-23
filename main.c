#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/epoll.h>

#define MAX_EVENTS 10
#define MAX_BUFFER_SIZE 1024

int main() {
    int serverSocket, clientSocket, epollfd;
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t clientAddrLen = sizeof(clientAddr);
    
    // 创建 TCP 套接字
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    
    // 设置服务器地址
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddr.sin_port = htons(8080);
    
    // 绑定套接字
    bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    
    // 监听
    listen(serverSocket, 5);
    
    // 创建 epoll 实例
    epollfd = epoll_create(MAX_EVENTS);
    if (epollfd == -1) {
        perror("epoll_create");
        exit(EXIT_FAILURE);
    }
    
    // 添加服务器套接字到 epoll 实例中
    struct epoll_event event;
    event.events = EPOLLIN;
    event.data.fd = serverSocket;
    epoll_ctl(epollfd, EPOLL_CTL_ADD, serverSocket, &event);
    
    struct epoll_event events[MAX_EVENTS];
    
    while (1) {
        // 等待事件发生
        int numEvents = epoll_wait(epollfd, events, MAX_EVENTS, -1);
        
        for (int i = 0; i < numEvents; ++i) {
            if (events[i].data.fd == serverSocket) {
                // 有新的连接
                clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &clientAddrLen);
                event.events = EPOLLIN | EPOLLET;
                event.data.fd = clientSocket;
                epoll_ctl(epollfd, EPOLL_CTL_ADD, clientSocket, &event);
            } else {
                // 处理客户端消息
                char buffer[MAX_BUFFER_SIZE];
                memset(buffer, 0, MAX_BUFFER_SIZE);
                int bytesRead = read(events[i].data.fd, buffer, MAX_BUFFER_SIZE - 1);
                if (bytesRead <= 0) {
                    // 客户端断开连接
                    epoll_ctl(epollfd, EPOLL_CTL_DEL, events[i].data.fd, NULL);
                    close(events[i].data.fd);
                } else {
                    // 处理接收到的消息
                    printf("Received: %s", buffer);
                }
            }
        }
    }
    
    // 关闭套接字和 epoll 实例
    close(serverSocket);
    close(epollfd);

    return 0;
}
