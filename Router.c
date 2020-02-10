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
#include <time.h>
#include <stdlib.h>



int main(int argc, char *argv[])
{
  int socket_fd, cc;
  socklen_t fsize;
  struct sockaddr_in  s_in, from,client,server;
  

  socket_fd = socket (AF_INET, SOCK_DGRAM, 0);
 
  memset((char *) &s_in,0, sizeof(s_in));  /* They say you must do this    */
  memset((char *) &client,0, sizeof(client));
  memset((char *) &server,0, sizeof(server));

  s_in.sin_family = (short)AF_INET;
  s_in.sin_addr.s_addr = htonl(INADDR_ANY);    
  s_in.sin_port = htons((u_short)0x3333);
  
  
  server.sin_family = (short) AF_INET;
  server.sin_addr.s_addr = htonl(INADDR_ANY);
  server.sin_port = htons((u_short)0x3311);
  
  
  client.sin_family = (short) AF_INET;
  client.sin_addr.s_addr = htonl(INADDR_ANY);
  client.sin_port = htons((u_short)0x3322);  

  bind(socket_fd, (struct sockaddr *)&s_in, sizeof(s_in));
    

  char msg_get[500];
  memset(&msg_get,0,sizeof(msg_get));
  while(1) {
    fsize = sizeof(from);
    cc = recvfrom(socket_fd,&msg_get,sizeof(msg_get),0,(struct sockaddr *)&from,&fsize);
    msg_get[cc] = '\0';

    if(from.sin_port==client.sin_port){
		     
	double rnd = rand() % 2;
	double x = atof(argv[1]);
	if(rnd > x){
		
                
		sendto(socket_fd, msg_get, strlen(msg_get) , 0, (struct sockaddr *)&server,sizeof(server));
	}
	else
           sendto(socket_fd, "dontwrite", strlen("dontwrite") , 0, (struct sockaddr *)&server,sizeof(server));

    }
    else{
		       
	sendto(socket_fd, msg_get , strlen(msg_get) , 0, (struct sockaddr *)&client,sizeof(client));       
     }

    
    memset(&msg_get,0,sizeof(msg_get));
  }
  
  return 0;
}
