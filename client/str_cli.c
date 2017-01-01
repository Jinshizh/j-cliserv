#include	"../lib/unp.h"
#include	"../lib/sum.h"

void
str_cli(FILE *fp, int sockfd)
{
	char	sendline[MAXLINE];
	struct args	args; //参数类型的对象(不要忘了struct,与cpp不同)
	struct result result;//结果类型的对象
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
	}
}
