#include <sys/types.h>
#include <netinet/in.h>
#include <inttypes.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <strings.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

void printsin(struct sockaddr_in *sin, char *pname, char* msg){

  printf("%s\n", pname);
  printf("%s ", msg);
  printf("ip= %s , port= %d", inet_ntoa(sin->sin_addr), sin->sin_port);
  printf("\n");
}
int main(int argc, char *argv[])
{
/*Defining a Structure	variable*/
  int socket_fd;
 socklen_t fsize;
  struct sockaddr_in  s_in, from;
  struct { char head; char  body[10]; char tail;} msg,msgbuf;
/*Define socket IPv4 protocol in the Domain ,UDP in the type, and protocol because it 0 it default */
  socket_fd = socket (AF_INET, SOCK_DGRAM, 0);
/*set all the byts in s_in with 0*/
  bzero((char *) &s_in, sizeof(s_in));  /* They say you must do this    */

  s_in.sin_family = (short)AF_INET; /*set the protocol*/
  s_in.sin_addr.s_addr = htonl(INADDR_ANY);  /* set sender any IP number */
  s_in.sin_port = htons((u_short)0x3333);/* set sender port number */

/*create the messege he send*/
  char myname[8] = "Pikalov";
  msgbuf.head = '<';
  strncpy(msgbuf.body,myname,sizeof(myname)); /* Insert what we wrote */
  msgbuf.tail = '>';

  printsin( &s_in, "RECV_UDP", "Local socket is:"); 

/*Connection between the Socket and the client(by ip and port)*/
  bind(socket_fd, (struct sockaddr *)&s_in, sizeof(s_in));

for (;;) {

    fsize = sizeof(from);
    recvfrom(socket_fd,&msg,sizeof(msg),0,(struct sockaddr *)&from,&fsize);
/*transfer the data between the client and the server*/
	    /*socket_fd sendung the data,msg pointer to data he sending,sizeof max length of buufer in bits,0 is the flag,
	     * (struct sockaddr *)&from pointer to  the struck that contain ip and port,frsize pointer to the local variable that contain the length of sockadrr*/
    printsin( &from, "recv_udp: ", "Packet from:");
	    /*print data we got,but first we need to convert it from byte network order to host order so we use ntohl*/
    printf("Got data ::%c%s%c\n",msg.head,msg.body,msg.tail); 
    fflush(stdout);
/*export the message*/
    sendto(socket_fd,&msgbuf,sizeof(msgbuf),0,(struct sockaddr *)&from,
                  sizeof(from));

  }
  
  return 0;
}

