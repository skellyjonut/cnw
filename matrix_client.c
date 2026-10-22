#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<strings.h>
#include<arpa/inet.h>
#include<time.h>

#define port 1234


int main(){
    int sock;
    struct sockaddr_in addr;
    int N,matrix[10][10];
    socklen_t addrlen = sizeof(addr);
    sock = socket(AF_INET,SOCK_STREAM,0);

    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(port);

    // srand(time(0));

    connect(sock,(struct sockaddr *)&addr,addrlen);
    printf("Enter order of Matrix");
    scanf("%d",&N);
    for(int i = 0; i < N;i++){
        for(int j = 0; j < N;j++){
            scanf("%d",&matrix[i][j]);
            // matrix[i][j] = rand()%51;
        }
    }

    send(sock,&N,sizeof(N),0);
    send(sock,matrix,sizeof(matrix),0);
    char res[50];
    recv(sock,res,sizeof(res),0);
    printf("\nMAtrix Type:%s\n",res);
    close(sock);
    return 0;
}
