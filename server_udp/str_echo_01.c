#include	"../lib/unp.h"
#include	"../lib/sum.h"
void str_echo(int sockfd)
{
	ssize_t		n;
//	char		buf[MAXLINE];
	struct args args;
	struct result result;

	for(;;) {
		if((n = read(sockfd, &args, sizeof(args))) == 0) {
//			printf("%d", n);
			return;
		}
		
		result.sum = args.arg1 + args.arg2;
//		printf("%ld",result.sum);
		write(sockfd, &result, sizeof(result));
	}
/*
again:
	while ( (n = readline(sockfd, &args, MAXLINE)) > 0)
		write(sockfd, buf, n);
	if (n < 0 && errno == EINTR)
		goto again;
	else if (n < 0)
		err_sys("str_echo: read error");
*/
}
