#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<time.h>
#include<arpa/inet.h>
#include<string.h>

#define port 9000

int main(){

    int sd;
    struct sockaddr_in saddr,caddr;
    char buffer[100];
    socklen_t len = sizeof(caddr);

    sd = socket(AF_INET,SOCK_DGRAM,0);
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(port);
    saddr.sin_addr.s_addr = INADDR_ANY;

    bind(sd,(struct sockaddr *)&saddr,len);
    printf("Server Started\n");

    while(1){
        recvfrom(sd,buffer,sizeof(buffer),0,(struct sockaddr *)&caddr,&len);
        time_t curt;
        time(&curt);
        char *tstr = ctime(&curt);
        sendto(sd,tstr,strlen(tstr)+1,0,(struct sockaddr *)&caddr,len);
        printf("Time served!\n");
    }
    close(sd);
    return 0;
}