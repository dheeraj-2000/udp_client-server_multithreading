#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <pthread.h>
#include <unistd.h>
#include <fcntl.h>
#include <math.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>


#define MAX 80
#define PORT 5011
#define SA struct sockaddr

struct msg {
  char word[20];
  char fname[30];
  int a;
};
void func(int sockfd)
{

	struct msg buffer;

	//int n;
	for (;;) {
		bzero(buffer.word,sizeof(buffer.word));
    bzero(buffer.fname , sizeof(buffer.fname));
    buffer.a=0;
		printf("Enter the word : ");
		scanf("%s",buffer.word);
    printf("Enter the File name : ");
    scanf("%s", buffer.fname);
		write(sockfd,&buffer, sizeof(buffer));
    bzero(buffer.word,sizeof(buffer.word));
    bzero(buffer.fname , sizeof(buffer.fname));
    buffer.a=0;
    read(sockfd,&buffer, sizeof(buffer));
		printf("From server :\n");
    if(buffer.a==1)
            printf("YES\n");
    else
            printf("NO\n");
    buffer.a=0;

    bzero(buffer.word,sizeof(buffer.word));
    bzero(buffer.fname , sizeof(buffer.fname));
	}
}

int main()
{
	int sockfd, connfd;
	struct sockaddr_in servaddr, cli;

	// socket create and varification
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1) {
		printf("socket creation failed...\n");
		exit(0);
	}
	else
		printf("Socket successfully created..\n");
	bzero(&servaddr, sizeof(servaddr));

	// assign IP, PORT
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	servaddr.sin_port = htons(PORT);

	// connect the client socket to server socket
	if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) {
		printf("connection with the server failed...\n");
		exit(0);
	}
	else
		printf("connected to the server..\n");
	func(sockfd);
	close(sockfd);
}
