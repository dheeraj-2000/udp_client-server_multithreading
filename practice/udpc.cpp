#include<iostream>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include <unistd.h>
using namespace std;

struct buff{
  char msg[100];
};

int main(){

struct sockaddr_in client,server;
int fd = socket(AF_INET,SOCK_DGRAM,0);
 memset ((char*)&client, 0, sizeof (client));

client.sin_family = AF_INET;
client.sin_port = htons(1997);
client.sin_addr.s_addr = htonl(INADDR_ANY);

if (fd==-1)
        cout<<"failed to create socket\n";

        if(bind(fd, (sockaddr*)&client , sizeof(client))==-1)
                    cout<<"failed1\n";
server.sin_family = AF_INET;
server.sin_port = htons(2000);
server.sin_addr.s_addr = htonl(INADDR_ANY);


//cin>>msg;char msg[100] = "helooooooooooo";

buff buf;

// strcpy(msg,d.c_str());
socklen_t len = sizeof(server);




//std::cout << sizeof(msg) << '\n';
while(1){
cin.getline(buf.msg,100);
int chk = sendto(fd , buf.msg , sizeof(buf.msg), 0 , (struct sockaddr *)&server , len);
if(chk == -1)
    cout<<"failed\n";
int chk2 = recvfrom(fd , buf.msg , sizeof(buf.msg), 0 , (struct sockaddr *)&server , &len);
if(chk2 == -1)
    cout<<"failed\n";
  cout<<buf.msg;
  }
close(fd);
}



/*#include<iostream>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include <unistd.h>
using namespace std;



int main(){

struct sockaddr_in client,server;
int fd = socket(AF_INET,SOCK_DGRAM,0);

client.sin_family = AF_INET;
client.sin_port = htons(1999);
client.sin_addr.s_addr = htonl(INADDR_ANY);

if (fd==-1)
        cout<<"failed to create socket\n";

server.sin_family = AF_INET;
server.sin_port = htons(2000);
server.sin_addr.s_addr = htonl(INADDR_ANY);;

char msg[100] ;//= "helooooooooooo";
//cin>>msg;char msg[100] = "helooooooooooo";

string d;
getline(cin,d);
strcpy(msg,d.c_str());
socklen_t len = sizeof(client);
//std::cout << sizeof(msg) << '\n';
int chk = sendto(fd , msg , sizeof(msg), 0 , (struct sockaddr *)&server , len);
if(chk == -1)
    cout<<"failed\n";
close(fd);
}
*/
