
/***************************************************************************************************************************
  Author: Dheeraj Chaudhary
  Udp client for interacting with multithreaded server using socket programming
  
  Here I'm taking a filename as input which will be send to the server to check whether it's present on server or not
***************************************************************************************************************************/


#include <iostream>
#include <sys/socket.h>
#include <cstring>
#include <netdb.h>
#include <unistd.h>
#include <stdio.h>
#include <arpa/inet.h>

 int main(int argc, char const *argv[]) {

     sockaddr_in myaddr,remaddr;
     int fd, slen = sizeof (remaddr), recvlen;
     char buf [2048];
     int rcvlen;
     char *server = "127.0.0.1";

     if ((fd = socket (AF_INET, SOCK_DGRAM, 0)) == -1 ) {                            //creating socket
         std::cout << "\n\t Socket creation failed...\n\t Exiting..." << '\n';
         return 0;
     }

  
     std::cout << "\n\t Socket created..." << '\n';

     memset ((char*)&myaddr, 0, sizeof (myaddr));
     myaddr.sin_family = AF_INET;
     myaddr.sin_addr.s_addr = htonl (INADDR_ANY);
     myaddr.sin_port = htons (0);

     //bind
     if (bind(fd, (sockaddr*) &myaddr, sizeof (myaddr)) < 0) {
         std::cout << "\n\t Bind failed...\n\t Exiting..." << '\n';
         return 0;
     }

     std::cout << "\n\t Bind succesful..." << '\n';

     memset ((char*) &remaddr, 0, sizeof (remaddr));
     remaddr.sin_family = AF_INET;
     remaddr.sin_port = htons (2052);
     if (inet_aton (server, &remaddr.sin_addr) == 0) {
         std::cout << "\n\t inet_aton() failed...\n\t Exiting..." << '\n';
         return 0;
     }

     for (int i = 0; i < 5; i++) {
         //std::cin >> buf;
         //getline (std::cin, buf);
         std::cout << "\n\t Enter the string  : ";
         std::cin.getline (buf, 2048);
         std::cout << "\n\t Sending data " << i << " to " << server << " on port " << remaddr.sin_port << '\n';
         sendto (fd, buf, strlen (buf), 0, (sockaddr*) &remaddr, slen);

         memset (buf, 0, sizeof (buf));
         socklen_t len;
          recvlen = recvfrom (fd, buf, 2048, 0, (sockaddr*) &remaddr, &len);
         std::cout << "\n\t recieved: " << buf << '\n';
         memset (buf, 0, sizeof (buf));
     }

     close (fd);

     return 0;
 }
