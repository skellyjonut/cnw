#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<time.h>
#include<arpa/inet.h>
#include<string.h>

#define port 9000

int main(){
    int sd;
    struct sockaddr_in ser,cli;
    socklen_t len = sizeof(ser);
    char buffr[200],fname[100];

    sd = socket(AF_INET,SOCK_DGRAM,0);
    ser.sin_family = AF_INET;
    ser.sin_port = htons(port);
    ser.sin_addr.s_addr = INADDR_ANY;

    bind(sd,(struct sockaddr *)&ser,len);
    printf("----------------------\n");
    printf("Server is Listening\n");

    while(1){
        memset(fname,0,sizeof(fname));
        recvfrom(sd,fname,sizeof(fname)-1,0,(struct sockaddr *)&cli,&len);
        if(fork() == 0){
            FILE *fp;
            fp = fopen(fname,"r");
            memset(buffr,0,sizeof(buffr));
            sprintf(buffr,"Handled by server PID: %d\n\n",getpid());
            if(fp == NULL){
                strcat(buffr,"Req file not found\n");
            }
            else{
                char line[256];
                while(fgets(line,sizeof(line),fp) != NULL){
                    strcat(buffr,line);
                }
                fclose(fp);
            }
            sendto(sd,buffr,strlen(buffr)+1,0,(struct sockaddr *)&cli,len);
            printf("Requet for %s server by PID:%d",fname,getpid());
            exit(0);
        }
    }
    close(sd);
    return 0;
}