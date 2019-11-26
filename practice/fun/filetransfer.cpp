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
#include<fstream>

using namespace std;
#define PORT 4561

struct msg {
  char filename[100];
  char file[1000];
};

struct sockaddr_in serveraddr ,client;

void *function(void *arg)
{     int fd = *((int*)arg);
      struct msg buff;
      while(1)
      {

        bzero(&buff,sizeof(buff));
        read(fd,&buff,sizeof(buff));
        cout<<"File : "<<buff.filename<<endl;
        cout<<"contents : "<<buff.file<<endl;
        fstream f;
        char name[100];
        cout<<"Enter file name : ";
        cin>>name;
        cout<<endl;
        f.open(name,ios::out);
        if(!f)
        {
          cout<<"error"<<endl;
        }
        int i=0;
        string d(buff.file);
        cout<<d<<endl;
        f << d;

        f.close();
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
