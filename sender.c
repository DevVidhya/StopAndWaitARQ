//SENDER.C
// ARQ - client server
// sender.c
//connection if he ready to receive else wait
// till he does not ready or timeout fails .
/*server.c and client.c - implementation of go-back-n ARQ in C
Server.c implements a reliable data transfer over UDP in C
client.c implements a reliable data transfer client over UDP in C
Both of these programs use the go-back-n ARQ, that is lost data is
automatically resent. These programs are hardcoded to transfer
to compile:
gcc -o server server.c
gcc -o client client.c
*/
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#define MAXLINE 80
char buffer[255] ;
#define SERVER_ADDR "127.0.0.1"
#define SERVER_PORT_NUM 6000
#define t_max_retransmission 3
typedef int bit_32_var ;
typedef char bit_8_var ;

typedef struct pdu_field
{
bit_32_var SN ;
bit_8_var data[MAXLINE] ;
bit_8_var status ;
}PDU_FIELD;
void str_cli ( FILE *fp , bit_32_var sfd )

{

bit_32_var no_of_data , counter_1 , counter_2 ;
static bit_32_var retransmission_counter , intial_readycheck_counter ;
PDU_FIELD send_data[MAXLINE] ,recv_data[MAXLINE] ;
printf ( "enter how many data you have to send : " ) ;
scanf ( "%d", &no_of_data ) ;
for ( counter_1 = 0 ; counter_1 < no_of_data ; counter_1++ )
{
printf ( "enter %d'th data : ",counter_1 ) ;
scanf ( "%s", send_data[counter_1].data ) ;
send_data[counter_1].SN = counter_1 ;
send_data[counter_1].status = 0 ;
}

for ( counter_1 = 0 ; counter_1 < no_of_data ; counter_1++ )
{
write ( sfd , &send_data[counter_1] , sizeof ( send_data[counter_1] ) ) ;
read ( sfd , &recv_data[counter_1] , sizeof ( recv_data[counter_1] ) ) ;

 if ( counter_1 == 0 && ( strcmp ( recv_data[counter_1].data , "yes" ) != 0 ) )
 { 
   if ( intial_readycheck_counter == t_max_retransmission ) 
   {
   printf ( "client : receiver not there , better to exit : \n" ) ;
   exit ( 1 ) ;
   }
   intial_readycheck_counter++ ;
   printf ( "client : receiver is not ready : wait 10sec... \n" ) ;
   sleep ( 10 ) ;
   counter_1 = counter_1- 1 ;
 }

 if ( counter_1 > 0 ) 
 {
 if ( recv_data[counter_1].SN == send_data[counter_1].SN + 1 ) 
    printf ( "\n server responding = %s ", recv_data[counter_1].data ) ;
 else
  {
  if ( retransmission_counter < t_max_retransmission ) 
    {
  printf ( "incorrect ack - sending the same data - \n" ) ;
  counter_1 -= 1 ;
  retransmission_counter++ ;
    }
  else 
    {
     printf ( "Time out : sending next data \n " ) ;
retransmission_counter = 0 ;
    }
    
   }
}
}

write ( sfd , "Nothingtotransmit:\n" , 10 ) ;
printf ( "Transmission finished : \n" ) ;
exit ( 1 ) ;
}

int main ()

{

bit_32_var socket_fd ;
struct sockaddr_in config_client ;

socket_fd = socket ( AF_INET , SOCK_STREAM , 0 ) ;

if ( socket_fd < 0 )
{
printf ( "client : failed to create socket \n" ) ;
exit ( 1 ) ;
}

 memset ( &config_client , 0 , sizeof ( struct sockaddr_in )) ;
 config_client.sin_family = AF_INET ;
 config_client.sin_port = htons ( SERVER_PORT_NUM ) ;
 inet_aton ( SERVER_ADDR , &config_client.sin_addr ) ;
 connect ( socket_fd , (struct sockaddr *)&config_client , sizeof ( config_client ) ) ;
 printf ( "connect successfully\n" ) ;
 system ( "clear" ) ;
 str_cli ( stdin , socket_fd ) ;
 exit ( 0 );
}








// https://www.youtube.com/watch?v=tPzoRLCX-Ps
// https://stackoverflow.com/questions/33141614/implementing-stop-and-wait-with-c-udp-and-what-does-cause-resource-temporari
// https://gangof1994.wordpress.com/2015/08/11/stop-and-wait-protocol-using-socket-program/
// https://gist.github.com/ankurdinge/1202643



// explaining saw arq :     https://www.geeksforgeeks.org/stop-and-wait-arq/
// https://www.geeksforgeeks.org/efficiency-of-stop-and-wait-protocol/
// https://www.geeksforgeeks.org/difference-between-stop-and-wait-gobackn-and-selective-repeat/
// https://www.geeksforgeeks.org/difference-between-stop-and-wait-protocol-and-sliding-window-protocol/

// https://www.youtube.com/watch?v=pxMa0HxeurY



// explaining ns3 :     https://www.geeksforgeeks.org/network-simulator-3/
// https://www.nsnam.org/docs/release/3.10/tutorial/html/building-topologies.html
// https://www.youtube.com/watch?v=3n0M-7-6IMM&list=PLRAV69dS1uWQEbcHnKbLldvzrjdOcOIdY&index=8&t=0s
// https://www.youtube.com/watch?v=P-E2Om5dxJ8&list=PLRAV69dS1uWQEbcHnKbLldvzrjdOcOIdY&index=9&t=0s



// video tutorial for ns3 :     https://www.youtube.com/watch?v=FLttSa45_MI




// video algorithm :    https://www.youtube.com/watch?v=i5UzpsLeuo4
// code :    https://www.isi.edu/nsnam/DIRECTED_RESEARCH/DR_HYUNAH/D-Research/stop-ns.html




// install :         https://www.nsnam.org/bugzilla/show_bug.cgi?id=2667#c1



// ns3 installation
// https://www.youtube.com/watch?v=4FCaQ_rh9bw
// https://www.nsnam.com/2018/03/ns3-installation-in-ubuntu-1604.html
// https://www.nsnam.org/wiki/Installation#Installation




















// https://www.google.com/search?q=ns3+stop+and+wait+arq+code&sxsrf=ACYBGNT3H4HhDG7Bxdd2ZPZrbt7m30Ujqw:1569156052849&source=lnms&tbm=vid&sa=X&ved=0ahUKEwjj74HpueTkAhXYfCsKHfL3BTEQ_AUIEigB&biw=1853&bih=932

// https://www.google.com/search?q=dll+protocol+implemented+in+ns3&sxsrf=ACYBGNTKQ2Dh6-HGZYgH6ZnVKFK0S3HsCw:1569160016346&source=lnms&tbm=vid&sa=X&ved=0ahUKEwiIuPrKyOTkAhVNfH0KHRX9DJ4Q_AUIEigB&biw=1853&bih=932

// https://www.youtube.com/watch?v=vTKe2cAUPuY

// https://www.google.com/search?q=how+to+sed+data+between+2+nodes+using+ns3&oq=how+to+sed+data+between+2+nodes+using+ns3&aqs=chrome..69i57.9627j0j8&sourceid=chrome&ie=UTF-8

// https://github.com/wakwanza/leach/blob/master/model/const.h

// https://www.google.com/search?q=ns3+implementation+code+of+a+protocol&oq=ns3+implementation+code+of+a+protocol&aqs=chrome..69i57.15068j0j7&sourceid=chrome&ie=UTF-8

// https://www.nsnam.org/doxygen/olsr-routing-protocol_8cc_source.html

// https://www.nsnam.org/docs/dce/release/1.1/manual/html/dce-user-newapps.html

// https://www.google.com/search?q=protocol+implemented+in+ns3&oq=protocol+implemented+in+ns3&aqs=chrome..69i57j69i61j69i60l2.8093j0j8&sourceid=chrome&ie=UTF-8

// https://www.google.com/search?q=how+to+send+data+from+one+to+another+in+ns3&oq=how+to+send+data+from+one+to+another+in+ns3&aqs=chrome..69i57.9281j0j8&sourceid=chrome&ie=UTF-8

// https://www.nsnam.org/docs/release/3.9/tutorial/tutorial_31.html

// 

