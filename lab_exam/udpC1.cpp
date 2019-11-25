#include<iostream>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>

using namespace std;
int main(){
      char * hello = "hello from clint";
      struct sockaddr_in servaddr = {0};

      int sockfd = socket(AF_INET, SOCK_DGRAM, 0);

      if(sockfd == -1){
            cout << "failed to create socket..."<<endl;
            exit(EXIT_FAILURE);
      }
      //memset(servaddr, '\0', sizeof(servaddr));
      servaddr.sin_family = AF_INET;
      servaddr.sin_port = htons(12345);
      servaddr.sin_addr.s_addr = INADDR_ANY;

      int len = sendto(sockfd, (const char *)hello, strlen(hello), 0, (const struct sockaddr *)&servaddr, sizeof(servaddr));
      if(len == -1){
            cout << "failed to send"<<endl;
            exit(EXIT_FAILURE);
      }
      close(sockfd);
}
