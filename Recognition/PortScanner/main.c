#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <getopt.h>
#include <stdbool.h>

int port = 0;
int proto_type = SOCK_STREAM;
char *proto_name = "tcp";
int sockfd; 
int opt;

struct sockaddr_in target;
struct servent *service;

bool Connection(char *ip, char *proto_name, int proto_type, int port){

   

    if(port < 0 || port > 65535) exit(1);

    service = getservbyport(htons(port), proto_name);
    sockfd = socket(AF_INET, proto_type, 0);
    memset(&target, 0, sizeof(target));
    
    target.sin_family = AF_INET;
    target.sin_port = htons(port);

    inet_pton(AF_INET, ip, &target.sin_addr);

    if ( connect(sockfd, (struct sockaddr *) &target, sizeof(target)) == 0){

        if (service != NULL) {
            printf("Port Opened: %d\t", port);
            printf("Service: %s - Protocol: %s\n", service->s_name, service->s_proto);
        } else {
            printf("Port Opened: %d\t", port);
            printf("Service: Unknown - Protocol: %s\n", proto_name);
        }

        return true;
    }
}

void PortScan(int argc, char **argv, char *ip){


    while(1){


        while ((opt = getopt(argc, argv, "p:")) != -1){
        
            switch (opt){
            
                case 'p':
                    port = atoi(optarg);
                    if (!Connection(ip, proto_name, proto_type, port)) printf("Port Closed: %d\n", port);
                    exit(1);


                default:
                    break;
            }

        }

    Connection(ip, proto_name, proto_type, port);
    close(sockfd);
    port++;
    }
}


int main(int argc, char **argv){


    if(argc < 2){
        printf("Use the %s <IP> format.\n", argv[0]);
        exit(1);
    }


    PortScan(argc, argv, argv[1]);

    return 0;
}
