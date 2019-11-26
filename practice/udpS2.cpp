#include<iostream>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/socket.h>

using namespace std;
#define MSGS 5
int main(){
      int sockfd  = socket(AF_INET, SOCK_DGRAM,0);
      if(sockfd == -1){
            cout<<"socket not created: ";
            exit(EXIT_FAILURE);
      }

      struct sockaddr_in sockaddr, server, client;
      server.sin_family =  AF_INET;
      server.sin_port = htons(5000);
      server.sin_addr.s_addr= inet_addr("127.0.0.1");

      int b = bind (sockfd, (struct sockaddr*)&server, sizeof(server));
      if(b == -1){
            cout<<"bind failed...";
            close(sockfd);
            exit(EXIT_FAILURE);
      }

      client.sin_family =  AF_INET;
      client.sin_port = htons(6000);
      client.sin_addr.s_addr= inet_addr("127.0.0.1");

      
      for (int i=0; i < MSGS; i++) {
      char str[80];
      cout<<"Enter the string to send to the client: ";
      cin.getline(str,80);
      //cout<<sizeof(str);
      int len = sendto(sockfd, str, sizeof(str), 0, (const struct sockaddr*)&client, sizeof(client));
      if(len == -1){
            cout << "failed to send"<<endl;
            exit(EXIT_FAILURE);
      }
      socklen_t size = sizeof(client);
      recvfrom(sockfd, str, sizeof(str), 0, ( struct sockaddr*)&client, &size);
      cout<<"Received msg form client: ";
      cout<<str;}
      close(sockfd);

}
