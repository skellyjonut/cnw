#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<string.h>

#define port 12345

int main(){
    int sd,n;
    struct sockaddr_in addr;
    socklen_t len = sizeof(addr);
    char buffr[1024];
    char *msg = "Hi Serv";

    sd = socket(AF_INET,SOCK_STREAM,0);

    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(sd,(struct sockaddr *)&addr,len);
    printf("Enter No:");
    scanf("%d",&n);
    send(sd,&n,sizeof(n),0);
    int val = recv(sd,buffr,sizeof(buffr)-1,0);
    if(val > 0){
        buffr[val] = '\0';
        printf("%s",buffr);
    }

    close(sd);
    return 0;
}