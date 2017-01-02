#include	"../lib/unp.h"
#include	"../lib/sum.h"

void
str_cli(FILE *fp, int sockfd)
{
	char	sendline[MAXLINE];
	struct args	args; //参数类型的对象(不要忘了struct,与cpp不同)
	struct result result;//结果类型的对象
	fd_set rset;
	int maxfdp1;

	for(;;) {
		FD_SET(fileno(fp), &rset);//在读集中添加文件的fd号(stdin)
		FD_SET(sockfd, &rset);//在读集中添加套接字的号
		maxfdp1 = max(sockfd, fileno(fp)) + 1; //注意要加一，号数从0开始的
		select(maxfdp1, &rset, NULL, NULL, NULL);

		if(FD_ISSET(fileno(fp), &rset)) {//select后发现可读了
			if(fgets(sendline, MAXLINE, fp) != NULL){
				printf("invalid input:%s", sendline);
				continue;
			}
			write(sockfd, &args, sizeof(args));//注意参数是地址，sendline可不加&
		}
		if(FD_ISSET(sockfd, &rset)) {
			if (read(sockfd, &result, sizeof(result)) == 0)
				err_quit("str_cli: server terminated prematurely");
			printf("%ld\n",result.sum);
		}
	}
/*
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
