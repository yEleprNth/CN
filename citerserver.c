#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>

int main()
{
  int sockfd,newsockfd,clilen;
  struct sockaddr_in serv_addr,cli_addr;
  char a[50];
  sockfd=socket(AF_INET,SOCK_STREAM,0);
  if(sockfd<0)
  {
    printf("\nSocket failed");
    exit(0);
  }
  serv_addr.sin_family=AF_INET;
  serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
  if(serv_addr.sin_addr.s_addr<0)
  {
    printf("\nInvalid IP addres");
    exit(0);
  }
  serv_addr.sin_port=htons(4567);
  if(bind(sockfd,(struct sockaddr * )&serv_addr,sizeof(serv_addr))<0)
  {
    printf("\nBind Failed");
    exit(1);
  }
  if(liste(sockfd,5)<0)
  {
    printf("\nListen failed");
    exit(0);
  }
  clilen=sizeof(cli_addr);
  printf("\nWaiting for clients message:");
  while(1)
  {
    newsockfd=accept(sockfd,(struct sockaddr *)&cli_addr,(struct sockaddr *)&clilen);
    memset(a,0,sizeof(a));
    read(newsockfd,a,50);
    printf("\nServer received:%s",a);
    write(newsockfd,a,50)
    close(newsockfd);
    if(!strcmp(a,"exit"))
    {
      printf("\nExiting server");
    }
  }
  return 0;
}
