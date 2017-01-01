#include "../lib/unp.h"

void
sig_child(int signo) {
	pid_t pid;
	int stat;
	while((pid = waitpid(-1, &stat, WNOHANG)) > 0) {//WNOHANG 在没有出现任何终止的子进程时不像wait那样阻塞在这儿
		printf("child process %d terminated\n",pid);
	}
	return;
}

int
main(int argc, char **argv) {
	int listenfd, connfd;
	pid_t childpid;
	socklen_t clilen;
	struct sockaddr_in cliaddr, servaddr;

	listenfd = socket(AF_INET, SOCK_STREAM, 0); //创建套接字，指定协议类型
	
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);//将主机字节序转化为网络字节序（大端），l代表long 
	servaddr.sin_port = htons(SERV_PORT);

	bind(listenfd, &servaddr, sizeof(servaddr));//把协议地址/端口号等与套接字绑定

	listen(listenfd, LISTENQ);//把默认为主动连接的套接字转为被动连接，并设置两个排队队列的大小
	signal(SIGCHLD, sig_child); //在父进程中注册信号处理函数
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
    }
}
