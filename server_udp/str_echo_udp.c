#include	"../lib/unp.h"
void str_echo_udp(int sockfd, SA *cliaddr, socklen_t clilen)
{
	ssize_t		n;
	char		buf[MAXLINE];
	socklen_t len;

	for(;;) {
		len = clilen;
		if((n = recvfrom(sockfd, &buf, MAXLINE, 0, cliaddr, &len)) < 0)//第二个和最后两个参数是值-结果参数,返回的结果是接收到的字节数。
			err_sys("recvfrom error");
		if(sendto(sockfd, &buf, n, 0, cliaddr, clilen) < 0)//不是&cliaddr
			err_sys("sendto error");
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
