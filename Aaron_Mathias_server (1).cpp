#include <iostream>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <fstream>
#include <ctype.h>
#include <arpa/inet.h>
#include <cstring>
using namespace std;


int main(){
cout <<  "Enter today's stolen car DB name: ";
string filename, line;
cin >> filename;
ifstream fin;
string stolen[1000];
fin.open(filename);
int z=0;
while (getline(fin, line)){
  stolen[z] = line;
  z++;
}

  //server code
    int udpSocket, nBytes;
  char buffer[1024];
  struct sockaddr_in serverAddr, clientAddr;
  struct sockaddr_storage serverStorage;
  socklen_t addr_size, client_addr_size;

  /*Create UDP socket*/
  int portnum;
udpSocket = socket(PF_INET, SOCK_DGRAM, 0);
  
cout << "Enter server port number: ";
cin>> portnum;
//Configure settings in address struct
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(portnum);
  serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);
bind(udpSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));
addr_size = sizeof serverStorage;
int counter=1;
bool ifstolen = false;
while(counter == 1){
    // Try to receive any incoming UDP datagram. Address and port of 
      //requesting client will be stored on serverStorage variable 
    nBytes = recvfrom(udpSocket,buffer,1024,0,(struct sockaddr*)&serverStorage, &addr_size);
  
    if(strcmp(buffer,"killsvc")==0){
        cout << "Received request to terminate the service" << endl;
        cout << "Bye" << endl;
    sendto(udpSocket,"Client terminates. Bye!",23,0,(struct sockaddr *)&serverStorage,addr_size);
      counter++;
      return 100;
    }
  
    for(int i= 0; i < z; i++){
      string compare = stolen[i];
      if(compare == buffer){
        ifstolen = true;
        cout << buffer << ": Reported as stolen" << endl;
    sendto(udpSocket,"Reported as stolen",18,0,(struct sockaddr *)&serverStorage,addr_size);
      }
    }

    //Send uppercase message back to client, using serverStorage as the address/
    //if(buffer != "killsvc"){
      if(ifstolen == false){
      cout << buffer << ": Not in the database" << endl;
      sendto(udpSocket,"Not in Database",15,0,(struct sockaddr *)&serverStorage,addr_size);
    }
    
    ifstolen=false;
  }
  

  
  return 0;
}
