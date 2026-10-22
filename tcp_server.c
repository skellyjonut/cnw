#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<arpa/inet.h>

#define P 1234

int main(){
    int server_fd,new_socket;
    struct sockaddr_in addr;
    socklen_t addrlen = sizeof(addr);
    char buffer[1024];
    char *msg = "Hello from Server";

    server_fd = socket(AF_INET,SOCK_STREAM,0);
    if(server_fd < 0){
        perror("Error");
        exit(EXIT_FAILURE);
    }
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(P);

    if(bind(server_fd,(struct sockaddr *)&addr,sizeof(addr)) < 0){
        perror("Error");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    if(listen(server_fd,3) < 0){
        perror("Error");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Server listening...\n");

    new_socket = accept(server_fd,(struct sockaddr *)& addr,&addrlen);
    if(new_socket < 0){
        perror("Error");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    
    int bytes = recv(new_socket,buffer,sizeof(buffer)-1,0);
    if(bytes > 0){
        buffer[bytes] = '\0';
        printf("Client: %s\n",buffer);

        send(new_socket,msg,strlen(msg),0);
        printf("Message sent!\n");
    }
    close(new_socket);
    close(server_fd);

    return 0;
}