#include<stdio.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>


#define P 1234

int main(){
    int sock;
    struct sockaddr_in saddr = {0};
    char *msg = "Hello From client";
    char buffer[1024] = {0};

    sock = socket(AF_INET,SOCK_STREAM,0);
    if(sock < 0){
        perror("Error");
        return 1;
    }
    saddr.sin_family = AF_INET;
    saddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    saddr.sin_port = htons(P);

    if(connect(sock,(struct sockaddr *)&saddr,sizeof(saddr)) < 0){
        perror("Error");
        close(sock);
        return 1;
    }
    send(sock,msg,strlen(msg),0);
    printf("Msg sent to server\n");

    auto bytes = read(sock,buffer,sizeof(buffer)-1);
    if(bytes > 0){
        buffer[bytes] = '\0';
        printf("Server:%s",buffer);
    }
    close(sock);
    return 0;
}
