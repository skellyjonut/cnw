#include<stdio.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>

#define port 1234
#define SIZE 10
#define BUFFR 1024
#define NAME_SIZE 30

typedef struct{
    int socket;
    char name[30];
}Client;

Client cl[SIZE];

int main(){

    int sd,sock;
    struct sockaddr_in addr;
    socklen_t len = sizeof(addr);
    fd_set readfds;
    char buffer[1024];
    
    for(int i=0; i < SIZE;i++){
        strcpy(cl[i].name,"");
        cl[i].socket = 0;
    }
    sd = socket(AF_INET,SOCK_STREAM,0);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = INADDR_ANY;

    bind(sd,(struct sockaddr *)&addr,len);
    listen(sd,5);

    printf("-===============================-\n");
    printf("Multi User chat started");
    printf("-===============================-\n");

    while(1){
        FD_ZERO(&readfds);
        FD_SET(sd,&readfds);
        int max_sd = sd;
        for(int i = 0; i < SIZE; i++){
            if(cl[i].socket > 0){
                FD_SET(cl[i].socket,&readfds);
                if(cl[i].socket > max_sd)max_sd = cl[i].socket;
            }
        }
        select(max_sd+1,&readfds,NULL,NULL,NULL);
        if(FD_ISSET(sd,&readfds)){
            sock = accept(sd,(struct sockaddr *)&addr,&len);
            char name[30];
            recv(sock,name,sizeof(name),0);
            for(int i = 0; i < SIZE; i++){
                if(cl[i].socket == 0){
                    cl[i].socket = sock;
                    strcpy(cl[i].name,name);
                    printf("%s Connected\n",name);
                    break;
                }
            }   
        }
        for(int i = 0 ; i < SIZE; i++){
            int sd = cl[i].socket;
            if(sd > 0 && FD_ISSET(sd,&readfds)){
                int valread = recv(sd,buffer,sizeof(buffer)-1,0);
                if(valread <= 0){
                    printf("%s Disconnected",cl[i].name);
                    close(sd);
                    cl[i].socket = 0;
                    strcpy(cl[i].name,"");
                }
                else{
                    buffer[valread] = '\0';
                    char msg[1200];
                    sprintf(msg,"%s : %s",cl[i].name,buffer);
                    printf("%s",msg);
                    for(int j = 0; j < SIZE;j++){
                        if(cl[j].socket != 0 && cl[j].socket != sd){
                            send(cl[j].socket,msg,strlen(msg),0);
                        }
                    }
                }
            }
        }
    }
    close(sd);
    return 0;
}