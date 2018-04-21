/*************************************************************************
	> File Name: convercli.c
	> Author: 
	> Mail: 
	> Created Time: 2018年03月22日 星期四 14时17分14秒
 ************************************************************************/

#include<stdio.h>
#include<unp.h>

void str_cli(FILE* const fp, int sockfd)
{
    char buff[MAXLINE];
    while(Fgets(buff, MAXLINE, fp) != NULL)
    {
        Writen(sockfd, buff, strlen(buff));
        if(Readline(sockfd, buff, MAXLINE) == 0)
        {
            err_quit("str_cli:server terminated permaturely");
        }
        Fputs(buff, stdout);
    }
}

int main(int argc, char **argv)
{
	int					sockfd;
	struct sockaddr_in	servaddr;

	if(argc != 2)
		err_quit("usage: a.out <IPaddress>");

	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		err_sys("socket error");

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port   = htons(4399);	/* daytime server */
	if(inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0)
		err_quit("inet_pton error for %s", argv[1]);

	if(connect(sockfd, (SA *) &servaddr, sizeof(servaddr)) < 0)
		err_sys("connect error");

    str_cli(stdin, sockfd);

    exit(0);
}
