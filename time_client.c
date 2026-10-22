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
    char buffr[1024];

    sd = socket(AF_INET,SOCK_DGRAM,0);
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(port);

    strcpy(buffr,"TIME");
    sendto(sd,buffr,strlen(buffr)+1,0,(struct sockaddr *)&addr,len);
    recvfrom(sd,buffr,sizeof(buffr),0,NULL,NULL);

    printf("\nCurr Server Time\n");
    printf("%s\n",buffr);
    close(sd);
    return 0;
}