#include<iostream>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<fcntl.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

using namespace std;
#define PORT 4556

struct msg{
  char text[100];
};

void function(int fd)
{
      struct msg buff;
      while(1)
      {

        bzero(&buff,sizeof(buff));
        cout<<"Enter Message : ";
        int n = 0;
        while ((buff.text[n++] = getchar()) != '\n');
        cout<<endl;
        write(fd,&buff,sizeof(buff));
        bzero(&buff,sizeof(buff));

        read(fd,&buff,sizeof(buff));
        cout<<"Message from server : "<< buff.text <<endl;
        bzero(&buff,sizeof(buff));
      }
}

int main()
{
  int sockfd;
  struct sockaddr_in serveraddr;
  sockfd = socket(AF_INET,SOCK_STREAM,0);
  if(sockfd == -1)
  {
    cout<<"socket creation failed..."<<endl;
    exit(0);
  }
  else
    cout<<"socket created successfully..."<<endl;

  bzero(&serveraddr, sizeof(serveraddr));

  serveraddr.sin_family = AF_INET;
  serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
  serveraddr.sin_port = htons(PORT);

  if(connect(sockfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr)) !=0 )
  {
    cout<<"connection failed..."<<endl;
    exit(0);
  }
  else
    cout<<"conneted to the server ..."<<endl;

  function(sockfd);

  close(sockfd);

  return 0;
}
