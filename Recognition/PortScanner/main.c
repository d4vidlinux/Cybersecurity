#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>


struct sockaddr_in target;


void PortScan(char *ip){

    int all_ports = 1;
    int sockfd;

    struct servent *service;

    while(1){

        service = getservbyport(htons(all_ports), "tcp");
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        memset(&target, 0, sizeof(target));
        
        target.sin_family = AF_INET;
        target.sin_port = htons(all_ports);

        inet_pton(AF_INET, ip, &target.sin_addr);

        if(all_ports > 65535) break;

        if ( connect(sockfd, (struct sockaddr *)&target, sizeof(target)) == 0){

            if (service != NULL) {
                printf("Port Opened: %d\t", all_ports);
                printf("Service: %s\n", service->s_name);
            } else {
                printf("Port Opened: %d\t", all_ports);
                printf("Service: Unknown\n");
            }

        }

        close(sockfd);
        all_ports++;

    }

}


int main(int argc, char **argv){

    if(argc < 2){
        printf("Use the %s <IP> format.\n", argv[0]);
        exit(1);
    }

    PortScan(argv[1]);

    return 0;
}
