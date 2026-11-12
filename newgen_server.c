#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<arpa/inet.h>


#define port 1234

void translate(char *str){
    struct { char *abbr, *full; } dict[] = {
        {"tbh", "to be honest"},
        {"ig", "I guess"},
        {"tbf", "to be fair"},
        {"atm", "at the moment"},
        {"irl", "in real life"},
        {"lol", "laughing out loud"},
        {"asap", "as soon as possible"},
        {"omg", "oh my God"},
        {"ttyl", "talk to you later"},
        {"idk", "I don't know"},
        {"nvm", "never mind"},
        {"idc", "I don't care"}
    };

    char res[1024] = "";
    char temp[100];
    int i =0,j;
    while(sscanf(str+i,"%s",temp) == 1){
        int fnd = 0;
        for(j = 0; j < 12; j++){
            if(strcmp(temp,dict[j].abbr) == 0){
                strcat(res,dict[j].full);
                fnd = 1;
                break;
            }
        }
        if(!fnd){
            strcat(res,temp);
        }
        strcat(res," ");
        i += strlen(temp)+1;
    }
    strcpy(str,res);
}

int main(){
    int sd;
    struct sockaddr_in saddr,caddr;
    socklen_t len = sizeof(caddr);
    char buffr[2048];

    sd = socket(AF_INET,SOCK_DGRAM,0);
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(port);
    saddr.sin_addr.s_addr = INADDR_ANY;
    bind(sd,(struct sockaddr *)&saddr,len);

    recvfrom(sd,buffr,sizeof(buffr),0,(struct sockaddr *)&caddr,&len);
    printf("Recieved:%s",buffr);
    translate(buffr);
    sendto(sd,buffr,strlen(buffr)+1,0,(struct sockaddr *)&caddr,len);
    close(sd);
    return 0;
}