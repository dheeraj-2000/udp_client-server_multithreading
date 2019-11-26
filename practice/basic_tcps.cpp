#include<iostream>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<unistd.h>
#include<cstring>
#include<pthread.h>

using namespace std;
#define PORT 4556

struct msg {
  char text[100];
};

struct sockaddr_in serveraddr ,client;

void *function(void *arg)
{     int fd = *((int*)arg);
      struct msg buff;
      while(1)
      {

        bzero(&buff,sizeof(buff));
        read(fd,&buff,sizeof(buff));
        cout<<"Client port number: "<<htons(client.sin_port)<<endl;
        cout<<"Client address : "<<inet_ntoa(client.sin_addr)<<endl;
        cout<<"Message from client "<<buff.text<<endl;
        bzero(&buff,sizeof(buff));

        cout<<"Enter message : ";
        int n = 0;
        while ((buff.text[n++] = getchar()) != '\n');
        cout<<endl;
        write(fd,&buff,sizeof(buff));

        bzero(&buff,sizeof(buff));
      }

}


int main()
{
  int sockfd ,connfd;


  sockfd = socket(AF_INET,SOCK_STREAM,0);
  if(sockfd == -1)
  {
    cout<<"Socket creation failed :"<<endl;
    exit(0);
  }
  else
    cout<<"Socket created successfully...."<<endl;

  bzero(&serveraddr,sizeof(serveraddr));

  serveraddr.sin_family = AF_INET;
  serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
  serveraddr.sin_port = htons(PORT);

  if(bind(sockfd,(const struct sockaddr *)&serveraddr,sizeof(serveraddr)) != 0)
  {
    cout<<"Binding unsuccessfull....."<<endl;
    exit(0);
  }
  else
    cout<<"Binding successfull...."<<endl;

  if(listen(sockfd,5) != 0)
  {
    cout<<"listen failed..."<<endl;
    exit(0);
  }
  else
    cout<<"Server listening...."<<endl;



  pthread_t id[100];
  int i= 0;
  for(i=0;i<10;i++)
  {
    int len;
    len = sizeof(client);
    connfd = accept(sockfd,(struct sockaddr*)&client,(socklen_t*)&len);
    
    if(connfd < 0)
      cout<<"Server Accept Failed..."<<endl;
    else
      cout<<"Connection accepted..."<<endl;

    if(pthread_create(&id[i],NULL,function,&connfd) != 0)
      cout<<"Thread created unsuccessfull...."<<endl;
    else
      cout<<"Thread creation successfully...."<<endl;
  }

  close(sockfd);

  return 0;
}
