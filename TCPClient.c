#include<stdio.h>
#include<stdlib.h>

#include<sys/types.h>
#include<sys/socket.h>

#include<netinet/in.h>

#include<string.h>

int main()
{
int network_socket=socket(AF_INET,SOCK_STREAM,0);
if(network_socket==0)
printf("Socket failure \n");

struct sockaddr_in server_address;
memset(&server_address, '\0' , sizeof(server_address));                           

server_address.sin_family=AF_INET;
server_address.sin_port=htons(9002);
server_address.sin_addr.s_addr=INADDR_ANY;

int connection_status=connect(network_socket, (struct sockaddr *) &server_address, sizeof(server_address));
if(connection_status==-1)
printf("Error connecting to remote socket \n");

int n,i=0,ack;
printf("Enter how many strings you want to send : ");
scanf("%d", &n);
char str[100][100];
while(i<n)
{
printf("Enter a string : ");
scanf("%s", str[i]);
i++;
}
printf("\n");

i=0;
while(i<n)
{
send(network_socket, str[i], sizeof(str[i]), 0);
recv(network_socket, &ack, 1024, 0);
printf("The server received the ack %d \n", ack);
}


return 0;
}




