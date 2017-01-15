#include	"../lib/unp.h"
#include	"../lib/sum.h"


void
str_cli_udp(FILE *fp, int sockfd, SA *servaddr, socklen_t servlen)
{
	int n;
	char	sendline[MAXLINE], recvline[MAXLINE + 1];
	while (fgets(sendline, MAXLINE, fp) != NULL) {

		sendto(sockfd, &sendline, strlen(sendline), 0, servaddr, servlen);

		n = recvfrom(sockfd, &recvline, MAXLINE, 0, servaddr, servlen);
		
		recvline[n] = 0;

		fputs(recvline, stdout);

//		fputs(recvline, stdout);
	}

	
/*
	fd_set rset;
	int maxfdp1;
	int stdineof = 0;
	
	for(;;) {
		if(stdineof == 0)//只有当没检测到stdin的eof时才需要去读stdin
			FD_SET(fileno(fp), &rset);//在读集中添加文件的fd号(stdin)
		FD_SET(sockfd, &rset);//在读集中添加套接字的号
		maxfdp1 = max(sockfd, fileno(fp)) + 1; //注意要加一，号数从0开始的
		select(maxfdp1, &rset, NULL, NULL, NULL);

		if(FD_ISSET(fileno(fp), &rset)) {//select后发现可读了
			if((n = read(fileno(fp), sendline, MAXLINE)) == 0){//在可读的情况下读到eof返回0
				stdineof = 1;
//				shutdown(sockfd, SHUT_WR);//检测到eof说明不再有要发的数据，但可能还有来自server的应答需要从sockfd读数据
				FD_CLR(fileno(fp), &rset);//不再关心它
				continue;//继续回select处等着到来的数据，不过这次就只关心从server应答的数据了
			}
			
			sendto(sockfd, &sendline, n, 0, (SA *) &servaddr, servlen);
//			write(sockfd, sendline, n);//注意参数是地址，sendline可不加&
		}
		if(FD_ISSET(sockfd, &rset)) {
			if ((n = recvfrom(sockfd, &recvline, MAXLINE, 0, (SA *) &servaddr, servlen)) < 0) {
					err_quit("recvfrom error");
			}
			write(fileno(stdout), recvline, n);
		}
	}*/
/*注释下列语句是因为服务器终止的时候本进程不能立即处理该信息，因为阻塞在fget的函数上。
	while (fgets(sendline, MAXLINE, fp) != NULL) {
		if(sscanf(sendline, "%ld%ld", &args.arg1, &args.arg2) != 2) {
			printf("invalid input:%s", sendline);
			continue;
		}
		write(sockfd, &args, sizeof(args));//注意参数是地址，sendline可不加&

		if (read(sockfd, &result, sizeof(result)) == 0)
			err_quit("str_cli: server terminated prematurely");
		printf("%ld\n",result.sum);
//		fputs(recvline, stdout);
	}*/
}
