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

char str[100];

while(1)
{


//send(network_socket, str, sizeof(str), 0);

recv(network_socket, str, 1024, 0);
if(strcmp(str,"exit")==0)
{
printf("\n Disconnected ");
break;
}
else
printf("The server sent the data %s \n", str);
}

//close(network_socket);

return 0;
}




