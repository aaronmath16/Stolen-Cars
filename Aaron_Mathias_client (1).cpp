#include <iostream>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
using namespace std;

int main(){
  string userName;
  int portNum;
  string license;
  cout << "Enter the server host name: ";
  cin >> userName;
  cout << "Enter the server port number: ";
  cin >> portNum;
  cout << "Enter a car license plate number: ";
  cin >> license;
  
    
  int clientSocket, nBytes;
  char buffer[1024];
  struct sockaddr_in serverAddr;
  socklen_t addr_size;

  /*Create UDP socket*/
  clientSocket = socket(PF_INET, SOCK_DGRAM, 0);

  /*Configure settings in address struct*/
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(portNum);
  serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  

  /*Initialize size variable to be used later on*/
  addr_size = sizeof serverAddr;

  
  sendto(clientSocket,license.c_str(),8,0,(struct sockaddr *)&serverAddr,addr_size);
  recvfrom(clientSocket,buffer,1024,0,NULL, NULL);

  if(license == "killsvc"){
    cout << buffer << endl;
  }
  else{
    cout << license << ": " << buffer << endl;  
  }
  

  return 0;
}