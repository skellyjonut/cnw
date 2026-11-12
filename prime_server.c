#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<string.h>

#define port 12345

int main(){

    int sd,ns;
    struct sockaddr_in addr;
    socklen_t len = sizeof(addr);
    char buffr[1024];

    sd = socket(AF_INET,SOCK_STREAM,0);

    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = INADDR_ANY;

    bind(sd,(struct sockaddr *)&addr,len);
    listen(sd,3);
    printf("Server is Listening:\n");

    ns = accept(sd,(struct sockaddr *)&addr,&len);
    int n;
    recv(ns,&n,sizeof(n),0);

    int prim = 1;
    for(int i = 2; i <= n/2; i++){
        if(n%i == 0)prim = 0;
    }
    if(prim){
        strcpy(buffr,"prime");
    }
    else{
        strcpy(buffr,"not prime");
    }
    send(ns,buffr,strlen(buffr)+1,0);
    close(ns);
    close(sd);
    return 0;
}