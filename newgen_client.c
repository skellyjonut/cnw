#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<arpa/inet.h>


#define port 1234

int main(){
    int sd;
    char buffr[1024];
    struct sockaddr_in addr;
    socklen_t len = sizeof(addr);
    
    sd = socket(AF_INET,SOCK_DGRAM,0);

    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    printf("Enter sentence");
    fgets(buffr,sizeof(buffr),stdin);

    sendto(sd,buffr,sizeof(buffr),0,(struct sockaddr *)&addr,len);
    recvfrom(sd,buffr,sizeof(buffr),0,(struct sockaddr *)&addr,&len);

    printf("Translated:%s",buffr);
    close(sd);
    return 0;
}