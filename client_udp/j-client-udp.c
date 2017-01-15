#include "../lib/unp.h"

int
main(int argc, char **argv) {
	int sockfd;
	struct sockaddr_in servaddr;
	if(argc != 2)
		err_quit("usage: j-client <IPaddress>");
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERV_PORT);
	inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

//	connect(sockfd, &servaddr, sizeof(servaddr));

	str_cli_udp(stdin, sockfd, (SA *) &servaddr, (socklen_t)sizeof(servaddr));
	exit(0);
}
