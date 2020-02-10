#include <sys/types.h>
#include <netinet/in.h>
#include <inttypes.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <strings.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
int main(int argc, char *argv[])
{
/*Defining a Structure	variable*/
  int socket_fd;
socklen_t fsize;
  struct sockaddr_in  dest;
  struct hostent *hostptr;
  struct { char head; char body[10]; char tail; } msgbuf,msg;
/*Define socket IPv4 protocol in the Domain ,UDP in the type, and protocol because it 0 it default */
  socket_fd = socket (AF_INET, SOCK_DGRAM, 0);
/*set all the byts in s_in with 0*/
  bzero((char *) &dest, sizeof(dest)); 
  hostptr = gethostbyname(argv[1]); /*resolve the destination hostname receive as an agreement*/
  dest.sin_family = (short) AF_INET;/*set the protocol*/
  memcpy(hostptr->h_addr, (char *)&dest.sin_addr,hostptr->h_length);/*copy data from dest.sin_addr to hostptr in length of hostptr*/
  dest.sin_port = htons((u_short)0x3333);/* set sender port number */
/*create the messege he send*/
  char myname[8] = "Meir";
  msgbuf.head = '<';
  strncpy(msgbuf.body,myname,sizeof(myname)); /* Insert what we wrote */
  msgbuf.tail = '>';
/*export the message*/
  sendto(socket_fd,&msgbuf,sizeof(msgbuf),0,(struct sockaddr *)&dest,
                  sizeof(dest));
   fsize = sizeof(dest);
    recvfrom(socket_fd,&msg,sizeof(msg),0,(struct sockaddr *)&dest,&fsize);
/*transfer the data between the client and the server*/
	    /*socket_fd sendung the data,msg pointer to data he sending,sizeof max length of buufer in bits,0 is the flag,
	     * (struct sockaddr *)&from pointer to  the struck that contain ip and port,frsize pointer to the local variable that contain the length of sockadrr*/
 printf("Got data ::%c%s%c\n",msg.head,msg.body,msg.tail); /*print the messege we got*/
  return 0;
}
