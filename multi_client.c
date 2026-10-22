#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<arpa/inet.h>


#define port 1234

int main(){
    int sock;
    struct sockaddr_in addr;
    socklen_t len = sizeof(addr);
    sock = socket(AF_INET,SOCK_STREAM,0);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);

    if(connect(sock,(struct sockaddr *)&addr,len) < 0){
        printf("Connection failed\n");
        return 0;
    }
    char name[30];
    printf("Enter name");
    fgets(name,sizeof(name),stdin);
    name[strcspn(name,"\n")] = '\0';
    send(sock,name,sizeof(name),0);
    printf("Connected to Chat Server\n");
    printf("Type your msg\n");

    if(fork() == 0){
        char msg[1024];
        while(1){
            fgets(msg,sizeof(msg),stdin);
            send(sock,msg,strlen(msg),0);
        }
    }
    else{
        char buffr[1024];
        while(1){
            int n = recv(sock,buffr,sizeof(buffr)-1,0);
            if(n <= 0){
                printf("Disconnected\n");
                break;
            }
            buffr[n] = '\0';
            printf("%s",buffr);
        }
    }
    close(sock);
    return 0;
}