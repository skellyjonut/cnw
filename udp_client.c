#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<arpa/inet.h>

#define port 1234

int main(){

    int sd,sock;
    struct sockaddr_in saddr,caddr;
    socklen_t len = sizeof(saddr);
    char buffer[1024];

    sd = socket(AF_INET,SOCK_DGRAM,0);
    
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(port);
    saddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    char *msg = "Msg from client";
    sendto(sd,msg,strlen(msg)+1,0,(struct sockaddr *)&saddr,len);
    recvfrom(sd,buffer,sizeof(buffer),0,(struct sockaddr *)&saddr,&len);

    printf("Server:%s",buffer);
    close(sd);
    return 1;
}