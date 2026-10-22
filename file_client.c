#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<time.h>
#include<arpa/inet.h>
#include<string.h>

#define port 9000

int main(){

    int sd;
    struct sockaddr_in addr;
    socklen_t len = sizeof(addr);
    char buffr[200],fname[100];
    sd = socket(AF_INET,SOCK_DGRAM,0);

    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    printf("Enter file name:");
    scanf("%s",fname);

    sendto(sd,fname,sizeof(fname),0,(struct sockaddr *)&addr,len);
    recvfrom(sd,buffr,sizeof(buffr),0,NULL,NULL);

    printf("Response Received\n");
    printf("-%s",buffr);
    close(sd);
    return 0;
}