#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>
#include <thread>
#include <chrono>
#include <signal.h>
#define MAX 80
#define PORT 5011
#define SA struct sockaddr
struct msg{
  char word[20];
  char fname[30];
  int a;
};

int sockfd;
void sig_handler(int signo)
{
  if (signo == SIGINT)
  {
		std::cout<<"Server is shutting down...";
		close(sockfd);
		exit(0);
	}
  if (signo == SIGTSTP)
  {
    std::cout<<"Server is shutting down...";
    close(sockfd);
    exit(0);
  }
}

void *func(void *arg)
{

  int sockfd = *((int *)arg);
  struct msg buff;

std::cout.flush();

  for(;;){
    std::fstream fpt;
		bzero(buff.word, sizeof(buff.word));
    bzero(buff.fname, sizeof(buff.fname));
    buff.a=0;
		read(sockfd, &buff, sizeof(buff));
    int count =0;
	  //bzero(buff.arr, sizeof(buff.arr));
    std::cout<<"From client find word : " <<buff.word<<" in file name : " <<buff.fname<<"\n";
    fpt.open(buff.fname);
    std::string word;
    fpt.seekg(0);
    while(fpt >> word ){
            count++;
            std::cout<<word<<"\n";
            if(word==buff.word){
                buff.a=1;


              }}

     write(sockfd, &buff, sizeof(buff));
     buff.a=0;
     bzero(buff.word, sizeof(buff.word));
     bzero(buff.fname, sizeof(buff.fname));

  }


}


int main()
{
	int  confd, len;
	struct sockaddr_in servaddr, cli;

  // if (signal(SIGINT, sig_handler) == SIG_ERR)
  //     printf("\ncan't catch SIGINT\n");
  // if (signal(SIGTSTP, sig_handler) == SIG_ERR)
  //     printf("\ncan't catch SIGINT\n");
	// // socket create and verification
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
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(PORT);

	// Binding newly created socket to given IP and verification
	if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) {
		printf("socket bind failed...\n");
		exit(0);
	}
	else
		printf("Socket successfully binded..\n");

	// Now server is ready to listen and verification
	if ((listen(sockfd, 15)) != 0) {
		printf("Listen failed...\n");
		exit(0);
	}
	else
		printf("Server listening..\n");

    pthread_t id[40];
  int i=0;
    while(1)
    {

      len = sizeof(cli);
      confd = accept(sockfd,(SA*)&cli,(socklen_t*)&len);
      char* str;
      printf("%s",&cli.sin_addr);
      printf("\nREQUEST FROM %s PORT %d\n",inet_ntoa(cli.sin_addr),ntohs(cli.sin_port));

      if(confd < 0)
        std::cout<<"Server accept failed....\n";
      else
        std::cout<<"Server accept the client....\n";
        std::cout<<"Connection accepted!!!"<<"\n";


      if(pthread_create(&id[i++],NULL,func,&confd) != 0)
        std::cout<<"Failed to create thread..."<<"\n";
      else
        std::cout<<"Thread created ...\n";
    }




}
