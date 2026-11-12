#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>

#include<linux/if_packet.h>
#include<net/ethernet.h>

#include<netinet/ip.h>
#include<netinet/tcp.h>
#include<netinet/udp.h>
#include<netinet/ip_icmp.h>

#define buffr_size 65536

void printMAC(unsigned char *mac){
    printf("%02X:%02X:%02X:%02X:%02X:%02X",mac[0],mac[1],mac[2],mac[3],mac[4],mac[5]);
}

int main(){
    int sd;
    unsigned char *buffr;
    int data_size;

    struct sockaddr_in addr;
    socklen_t len = sizeof(addr);

    buffr = (unsigned char *)malloc(buffr_size);

    sd = socket(AF_PACKET,SOCK_RAW,htons(ETH_P_ALL));

    if(sd < 0){
        perror("Error");
        return 0;
    }

    printf("\n==============================================\n");
    printf("        RAW SOCKET PACKET CAPTURE\n");
    printf("==============================================\n");
    printf("Press Ctrl+C to stop...\n\n");

    while(1){
        data_size = recvfrom(sd,buffr,buffr_size,0,(struct sockaddr *)&addr,&len);
        if(data_size < 0){
            perror("recvfrom");
            break;
        }

        struct ethhdr *eth = (struct ethhdr *)buffr;
        printf("\n==============================================\n");
        printf("Packet Length : %d Bytes\n",data_size);

        printf("Destination:");
        printMAC(eth->h_dest);
        printf("\nSource:");
        printMAC(eth->h_source);
        printf("\nProtocol: 0x%04X\n",ntohs(eth->h_proto));

        if(ntohs(eth->h_proto) == ETH_P_IP){
            struct iphdr *iph = (struct iphdr *)(buffr+sizeof(struct ethhdr));
            struct sockaddr_in src,dst;

            memset(&src,0,sizeof(src));
            memset(&dst,0,sizeof(dst));

            src.sin_addr.s_addr = iph->saddr;
            dst.sin_addr.s_addr = iph->daddr;

            printf("\nIP Header\n");
            printf("------------------\n");

            printf("Source ip: %s\n",inet_ntoa(src.sin_addr));
            printf("Dest ip: %s\n",inet_ntoa(dst.sin_addr));
            printf("TTL   :%d\n",iph->ttl);
            printf("Protocol:   %d",iph->protocol);

            if(iph->protocol == IPPROTO_TCP){
                struct tcphdr *tcp = (struct tcphdr *)(buffr+sizeof(struct ethhdr)+iph->ihl*4);
                printf("TCP Header\n");
                printf("Source port: %u\n",ntohs(tcp->source));
                printf("Destination port: %u\n",ntohs(tcp->dest));
            }
            else if(iph->protocol == IPPROTO_UDP){
                struct udphdr *udp = (struct udphdr *)(buffr+sizeof(struct ethhdr)+iph->ihl*4);
                printf("UDP Header\n");
                printf("Source port: %u\n",ntohs(udp->source));
                printf("Destination port: %u\n",ntohs(udp->dest));
            }
            else if(iph->protocol == IPPROTO_ICMP){
                struct icmphdr *icmp = (struct icmphdr *)(buffr+sizeof(struct ethhdr)+iph->ihl*4);
                printf("ICMP Header\n");
                printf("Type : %d\n",icmp->type);
                printf("Code: %d\n",icmp->code);
            }
            else{
                printf("\nOther proto");
            }

        }
    }
    close(sd);
    free(buffr);
    return 0;
}