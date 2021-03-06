/***************************************************************************************************************************
  Author: Dheeraj Chaudhary
  Udp server for interacting with different client at a time using socket programming
  
  Here I'll receive a file name from the client and check whether it is present on the present directory or not
***************************************************************************************************************************/

#include<bits/stdc++.h>
#include <iostream>
#include <sys/socket.h>
#include <cstring>
#include <netdb.h>
#include <unistd.h>
#include <stdio.h>
#include <arpa/inet.h>
//#include <boost/filesystem.hpp>
#include <pthread.h>

//using boost::filesystem;
using namespace std;
void* search_file (void*);
#define BUFSIZE 2048

struct req {                              //Structure to get various parameter from client for each client
	int des;
	char str[2048];
	socklen_t addlen;
	sockaddr_in clientaddr;
};

int main(int argc, char **argv){
		struct sockaddr_in myaddr;	/* my address */
		struct sockaddr_in remaddr;	/* remote address */
		socklen_t addrlen = sizeof(remaddr);		/* length of addresses */
		int recvlen, fd, msgcnt = 0;			/* number of bytes received , socket descriptor , count # of messages we received  */
		char buf[BUFSIZE];	/* receive buffer */
  	pthread_t thread[50];
	
		/* create a UDP socket */

		if ((fd = socket (AF_INET, SOCK_DGRAM, 0)) ==-1 ) {                         //Creating Socket
	 		 std::cout << "\n\t Socket creation failed...\n\t Exiting..." << '\n';
	 		 return 0;
	  }

    cout<< "Socket created..."<<endl;

		memset((char *)&myaddr, 0, sizeof(myaddr));
		myaddr.sin_family = AF_INET;
		myaddr.sin_addr.s_addr = htonl(INADDR_ANY);
		myaddr.sin_port = htons(2052);

  	if (bind(fd, (sockaddr*) &myaddr, sizeof (myaddr)) < 0) {                   //Binding to create the socket
      	std::cout << "\n\t Bind failed...\n\t Exiting..." << '\n';
      	return 0;
      }

		cout<<"Binding succesful..."<<endl;

	 int i = 0;

   while(true){
		cout<<"waiting on port: "<<myaddr.sin_port<<"\t"<<inet_ntoa (remaddr.sin_addr)<<endl;
		recvlen = recvfrom(fd, buf, BUFSIZE, 0, (struct sockaddr *)&remaddr, &addrlen);
		req *r = new req;
		r->des = fd;
		r->addlen = addrlen;
		r->clientaddr = remaddr;
		strcpy (r->str, buf);
  	pthread_create(&thread[i++], NULL, search_file,(void*) r);
		if (i == 50)
			 i = 0;

		 bzero (buf, 2048);
	}
 	//	for(int i=0; i<=50; i++){
  	//		pthread_join(thread[i], NULL);
     //}
}


void* search_file(void* r) {
  /* code */
	req rq = *((req*)r);
	std::cout << "\n\tsearching file.. " << rq.str << '\n';

/*  if ( !boost::filesystem::exists( rq.str ) ){
			bzero(rq.str, strlen (rq.str));
      strcpy( rq.str, "Can't find the file!  \n" );
     }

  else {
	    bzero(rq.str, strlen (rq.str));
	    strcpy( rq.str, "File found  \n" );
		}*/

		ifstream file(rq.str);
		if(!file){
			bzero(rq.str, strlen (rq.str));
			strcpy( rq.str, "Can't find the file!  \n" );}
		 // return false;
		else{
			bzero(rq.str, strlen (rq.str));
			strcpy( rq.str, "File found  \n" );
		}

  sendto (rq.des, rq.str, strlen (rq.str), 0, (sockaddr*) &rq.clientaddr, rq.addlen);

  return 0;
}
