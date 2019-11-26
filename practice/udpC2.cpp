#include<iostream>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/socket.h>

using namespace std;

int main(){
      int sockfd  = socket(AF_INET, SOCK_DGRAM,0);
      if(sockfd == -1){
            cout<<"socket not created: ";
            exit(EXIT_FAILURE);
      }

      struct sockaddr_in  server, client;
      client.sin_family =  AF_INET;
      client.sin_port = htons(6000);
      client.sin_addr.s_addr= inet_addr("127.0.0.1");

      int b = bind (sockfd, (sockaddr*)&client, sizeof(client));
      if(b == -1){
            cout<<"bind failed...";
            close(sockfd);
            exit(EXIT_FAILURE);
      }
      for (;;) {

      char str[80];
      socklen_t size = sizeof(server);
      //cout<<sizeof(str);
      int len = recvfrom(sockfd, str, sizeof(str), 0, ( struct sockaddr*)&server, &size);
//      str[len] = '\0';
      cout<<"Received msg form server: ";
      cout<<str;
      cout<<"\n";
      
      //while(t--){
      cout<<"Enter the string to send to the server: ";
      cin.getline(str,80);
      int len2 = sendto(sockfd, str, sizeof(str), 0, (const struct sockaddr*)&server, sizeof(server));
      if(len2 == -1){
            cout << "failed to send"<<endl;
            exit(EXIT_FAILURE);
      }}
      close(sockfd);
      return 0;


}
