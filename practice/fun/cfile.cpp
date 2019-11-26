#include<iostream>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<fcntl.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<fstream>

using namespace std;
#define PORT 4561

struct msg{
  char filename[100];
  char file[1000];
};

void function(int fd)
{
      struct msg buff;
      while(1)
      {

        bzero(&buff,sizeof(buff));
        cout<<"Enter filename : ";
        cin>>buff.filename;
        cout<<endl;
        fstream f;
        f.open(buff.filename);
        char c;
        int i=0;
        f.seekg(0,ios::beg);
        while(!f.eof())
        {
          f.get(c);
          buff.file[i] = c;
          i++;
        }
        buff.file[i] = '\0';
        cout<<buff.file<<endl;
        cout<<buff.filename<<endl;
        f.close();
        write(fd,&buff,sizeof(buff));
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
