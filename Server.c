#include <sys/types.h>
#include <netinet/in.h>
#include <inttypes.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <strings.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

int main(int argc, char *argv[])
{
  int socket_fd,cc;
   bool check= true;
  char msg_get[500];
  char msg_snd[500];
  
  struct sockaddr_in  dest,s_in,from;
  struct hostent *hostptr;
  
  memset(&msg_get,0,sizeof(msg_get));
  socket_fd = socket (AF_INET, SOCK_DGRAM, 0);
  

  memset((char *) &dest,0, sizeof(dest)); 
  hostptr = gethostbyname(argv[1]);
  dest.sin_family = (short) AF_INET;
  memcpy(hostptr->h_addr, (char *)&dest.sin_addr,hostptr->h_length);
  dest.sin_port = htons((u_short)0x3333);


  s_in.sin_family = (short)AF_INET;
  s_in.sin_addr.s_addr = htonl(INADDR_ANY);   
  s_in.sin_port = htons((u_short)0x3311);
  bind(socket_fd, (struct sockaddr *)&s_in, sizeof(s_in));
  

 
while(strcmp(msg_snd,"exit")!=0){
  
  if(check){
    sendto(socket_fd,msg_snd,sizeof(msg_snd),0,(struct sockaddr *)&dest,sizeof(dest));
    check= false;
  }
  else
  {
	  socklen_t  size = sizeof(from);
	  cc = recvfrom(socket_fd,&msg_get,sizeof(msg_get),0,(struct sockaddr *)&from,&size);
	  msg_get[cc] = '\0';
          if(strcmp(msg_get,"dontwrite")!= 0)printf("\nThe messege you got is: %s ",msg_get);
          check= true;
  }

  if(check){
  printf("\nPlease write a messege: ");
  scanf("%s",msg_snd);
  }
}
  return 0;
}
