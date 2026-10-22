#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<arpa/inet.h>

#define port 1234

int main(){

    int sd,sock;
    struct sockaddr_in addr;
    int N,matrix[10][10];
    sd = socket(AF_INET,SOCK_STREAM,0);
    socklen_t addrlen = sizeof(addr);

    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(port);

    bind(sd,(struct sockaddr *)&addr,addrlen);
    listen(sd,3);
    printf("Server is listening...\n");
    sock = accept(sd,(struct sockaddr *)&addr,&addrlen);

    recv(sock,&N,sizeof(N),0);
    recv(sock,matrix,sizeof(matrix),0);

    int diag=1,upr=1,lwr=1;

    for(int i = 0 ; i < N;i++){
        for(int j = 0; j < N;j++){
            printf("%d ",matrix[i][j]);
        }
        printf("\n");
    }
    for(int i = 0 ; i < N;i++){
        for(int j = 0; j < N;j++){
            if(j > i && matrix[i][j] != 0)upr=0;
            if(j < i && matrix[i][j] != 0)lwr = 0;
            if(i != j && matrix[i][j] != 0)diag = 0;
        }
    }
    char res[50];
    if(diag){
        strcpy(res,"Diagonal\n");
    }
    else if(upr){
        strcpy(res,"Upper\n");
    }
    else if(lwr){
        strcpy(res,"Lower\n");
    }
    else{
        strcpy(res,"Not spcl");
    }
    send(sock,res,strlen(res)+1,0);
    close(sock);
    close(sd);
    return 0;
}