#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<stdlib.h>

#define port 1234


int main(){
    int sd,sock;
    struct sockaddr_in saddr,caddr;
    socklen_t len = sizeof(caddr);
    char buffer[1024];

    sd = socket(AF_INET,SOCK_DGRAM,0);
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(port);
    saddr.sin_addr.s_addr = INADDR_ANY;

    bind(sd,(struct sockaddr *)&saddr,len);
    printf("UDP Server is runnnig ...\n");
    recvfrom(sd,buffer,sizeof(buffer),0,(struct sockaddr *)&caddr,&len);
    printf("Client: %s",buffer);

    char *msg = "Hello from UDP server";
    sendto(sd,msg,strlen(msg)+1,0,(struct sockaddr *)&caddr,len);
    close(sd);
    return 0;
}