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
	int listenfd, connfd, sockfd;
	int client[FD_SETSIZE];//客户连接信息表，元素既是连接对应的fd号
	int maxi;//client[]表中的已连接元素的最大下标index
	fd_set rset;//读集
	fd_set allset;//用于创建和修改读集
	int maxfd;//读集中的最大fd号
	int i;//用于遍历
	int nready;//用于select统计有多少个描述符准备好了

	//原str_echo中的逻辑
	ssize_t n;
	char buf[MAXLINE];

//	pid_t childpid;
	socklen_t clilen;
	struct sockaddr_in cliaddr, servaddr;

	if((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) //创建套接字，指定协议类型
		err_sys("socket error");
	
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);//将主机字节序转化为网络字节序（大端），l代表long 
	servaddr.sin_port = htons(SERV_PORT);

	if(bind(listenfd, &servaddr, sizeof(servaddr)) < 0)//把协议地址/端口号等与套接字绑定
		err_sys("bind error");

	if(listen(listenfd, LISTENQ))//把默认为主动连接的套接字转为被动连接，并设置两个排队队列的大小
		err_sys("listen error");

	
	for(i = 0; i < FD_SETSIZE; ++i)//初始化client[]表
		client[i] = -1;

    FD_ZERO(&allset);//初始化读集
    FD_SET(listenfd, &allset);

	maxfd = listenfd;
	maxi = -1;

//	signal(SIGCHLD, sig_child); //在父进程中注册信号处理函数
	for( ; ;) {
		rset = allset;
		nready = select(maxfd+1, &rset, NULL, NULL, NULL);

		if(FD_ISSET(listenfd, &rset)){ //新的连接到了
			clilen = sizeof(cliaddr);
        	//阻塞等待从已连接队列头返回下一个已连>接套接字
			if((connfd = accept(listenfd, &cliaddr, &clilen)) < 0) {
				if(errno == EINTR)
					continue;
	    		else
					err_sys("accept error");
			}
			
			FD_SET(connfd, &allset); //加入读集，下一次select会监控

			//连接建立
            printf("new client: %s, port %d\n",
                    inet_ntop(AF_INET, &cliaddr.sin_addr, 4, NULL),
                    ntohs(cliaddr.sin_port));

//			 printf("new client: port %d\n",ntohs(cliaddr.sin_port));

			
//两个易错点！！client[]表不一定是连续的（中间可能有一些之前关闭了的连接为-1），读集的fd值也不一定是连续的
//			client[++maxi] = connfd;//更新client[]表中的index——直接这样的话之前一些已被clean的元素就再也不能用了，只能不断增大，浪费了空间
			for(i = 0; i < FD_SETSIZE; ++i) {
				if(client[i] < 0) {
					client[i] = connfd;
					break;
				}
			}
            if (i == FD_SETSIZE)
                err_quit("too many clients");//对客户数量有限制
			if(i > maxi)
				maxi = i;

//			maxfd = connfd;//更新读集中的maxfd——新的fd不一定比旧的大
			if(connfd > maxfd)//更新读集中的maxfd
				maxfd = connfd;

			if(--nready <= 0)//只有一个监听套接字可读的情况，也就没必要有之后的处理了
				continue;
		}
		for(i = 0; i <= maxi; ++i){//对所有client[]表中的元素检查是否可读
			if(client[i] < 0)//说明是未连接的
				continue;
			if(FD_ISSET(client[i], &rset)){
				if((n = read(client[i], buf, MAXLINE)) == 0){//读到buffer的惯用操作，注意检测eof
					close(client[i]);//读到了eof
					FD_CLR(client[i], &rset);
					client[i] = -1;
				} else {
					write(client[i], buf, n);//回射
				}
				if(--nready <= 0)//避免过多的循环次数，最多处理nready次
					break;
			}
		}
    }
}
