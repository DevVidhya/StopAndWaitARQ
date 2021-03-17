#include"stdio.h"    
#include"stdlib.h"    
#include"sys/types.h"    
#include"sys/socket.h"    
#include"string.h"    
#include"netinet/in.h"    
#include <arpa/inet.h>
#include"netdb.h"  
    
#define PORT 4444   
#define BUF_SIZE 2000   
    
int main() {    
 struct sockaddr_in addr, cl_addr;    
 int sockfd, ret;    
 //char *buffer=(char *)(BUF_SIZE*2*sizeof(char));    
int buffer[100]; 
struct hostent * server;  
 char * serverAddr;  
  
// if (argc < 2) {  
//  printf("usage: client < ip address >\n");  
//  exit(1);    
// }  
  
// serverAddr = argv[1];   
   
 sockfd = socket(AF_INET, SOCK_STREAM, 0);    
 if (sockfd < 0) {    
  printf("Error creating socket!\n");    
  exit(1);    
 }    
 printf("Socket created...\n");     
  
 memset(&addr, 0, sizeof(addr));    
 addr.sin_family = AF_INET;    
 addr.sin_addr.s_addr = INADDR_ANY;  
 addr.sin_port = PORT;       
  
 ret = connect(sockfd, (struct sockaddr *) &addr, sizeof(addr));    
 if (ret < 0) {    
  printf("Error connecting to the server!\n");    
  exit(1);    
 }    
 printf("Connected to the server...\n");    
  
 
  
   

int n,i=0,ack[100],temp,tmp;
printf("Enter how many strings you want to send : ");
scanf("%d", &n);

//for(i=0;i<n;i++)
//memset(buffer[i], 0, 2);

/*char s1[10],s2[10];
s1[0]=a+'0';
s1[1]='\0';
s2[0]=b+'0';
s2[1]='\0';
*/

for(i=0;i<n;i++)
{
if(i%2==0)
buffer[i]=0;
else
buffer[i]=1;
}

for(i=0;i<n;i++)
printf(" %d ",buffer[i]);

//printf("Enter your message(s): \n");
 while (i<n) {  
//if(fgets(buffer[i], BUF_SIZE, stdin) != NULL)
//scanf("%d", buffer[i]);
  temp=htonl(buffer[i]);
  ret = sendto(sockfd, &temp, sizeof(temp), 0, (struct sockaddr *) &addr, sizeof(addr));    
  if (ret < 0) {    
   printf("Error sending data!\n\t-%d", temp);    
  }  
  ret = recvfrom(sockfd, &tmp, sizeof(tmp), 0, NULL, NULL);
  ack[i]=ntohl(tmp);    
  if (ret < 0) {    
   printf("Error receiving data!\n");      
  } else {  
   printf("Received: %d",ack[i]);  
   //printf(buffer[i], stdout);  
   printf("\n");  
  }    
i++;
 }  
   
 return 0;      
}    

