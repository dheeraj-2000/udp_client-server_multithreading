#include<iostream>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<unistd.h>
#include<pthread.h>
using namespace std;
struct req{
//  int reqno;
  int fdd;
  char str[100];
  socklen_t len;
  sockaddr_in client;
};
struct buff{
  char msg[100];
};
pthread_t id[50];
void* fun(void *r){
  req re = *((req *)r);
  cout<< "Received the word: "<<re.str<<endl;
 // char *str = "rcvd";
 bzero(re.str, sizeof(re.str));
 strcpy(re.str, "recieved the file: \n");
  sendto(re.fdd, re.str , strlen(re.str) ,0, (sockaddr*) &re.client ,re.len );
  //sendto(re.fdd, (char *)str , strlen(str) ,0, (sockaddr*) &re.client ,re.len );

}


int main(){
  //string msg;
  int fd  = socket(AF_INET , SOCK_DGRAM , 0);
  struct sockaddr_in server, client;
  server.sin_family = AF_INET;
  server.sin_port = htons(2000);
  server.sin_addr.s_addr = htonl(INADDR_ANY);
  //socklen_t len = sizeof(server);
  if(bind(fd, (sockaddr*)&server , sizeof(server))==-1)
              cout<<"failed1\n";
  socklen_t len = sizeof(client);



buff buf;
int i=0;
  while(1){

    if(recvfrom(fd,buf.msg,sizeof(buf.msg),0,(sockaddr*)&client,&len)==-1)
          cout<<"failed\n";
    req *r = new req;
    bzero(r,sizeof(r));
    r->fdd = fd;
    r->client = client;
    r->len = len;
    strcpy(r->str,buf.msg);

    pthread_create(&id[i] , NULL ,fun , (void*)r);

    bzero(buf.msg,sizeof(buf.msg));
i++;
  }
}













/*#include<iostream>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<unistd.h>
using namespace std;

int main(){
  cout<<"chk";
  char msg[100];
  //string msg;
  int fd  = socket(AF_INET , SOCK_DGRAM , 0);
  struct sockaddr_in server, client;
  server.sin_family = AF_INET;
  server.sin_port = htons(2000);
  server.sin_addr.s_addr = htonl(INADDR_ANY);
  //socklen_t len = sizeof(server);
  if(bind(fd, (sockaddr*)&server , sizeof(server))==-1)
              cout<<"failed1\n";
  socklen_t len = sizeof(client);
  int chk = recvfrom(fd , msg , sizeof(msg) ,0 ,(sockaddr*)&client , &len);
  if(chk==-1)
    cout<<"failed2\n";
  cout<<"msg recieved "<<msg<<endl;
  string d(msg);
  cout<<"string"<<d;
  close(fd);
  cout<<"chk";


}
*/
