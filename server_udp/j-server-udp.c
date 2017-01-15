#include "../lib/unp.h"

int
main(int argc, char **argv) {
    socklen_t clilen;
	int listenfd;
    struct sockaddr_in cliaddr, servaddr;
    if((listenfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) //创建套接字，指定协议类型为UDP
        err_sys("socket error");
    
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);//将主机字节序转化为网络字节序（大端），l代表long 
    servaddr.sin_port = htons(SERV_PORT);

    if(bind(listenfd, (SA *) &servaddr, sizeof(servaddr)) < 0)//把协议地址/端口号等与套接字绑定
        err_sys("bind error");

/* 不需要tcp中的这些东西
    if(listen(listenfd, LISTENQ))//把默认为主动连接的套接字转为被动连接，并设置两个排队队列的大小
        err_sys("listen error");

    for(;;) {
        clilen = sizeof(cliaddr);
        //阻塞等待从已连接队列头返回下一个已连>接套接字
        if((connfd = accept(listenfd, &cliaddr, &clilen)) < 0) {
            if(errno == EINTR)
                continue;
            else
            err_sys("accept error");
        }
        if((childpid = fork()) == 0) {
            close(listenfd);//子进程中不再监听
            str_echo(connfd);//子进程通过连接回射
            exit(0);
        }
        close(connfd);//父进程不应干预子进程的连接
    }*/
	str_echo_udp(listenfd, (SA *) &cliaddr, sizeof(cliaddr));
	
}

