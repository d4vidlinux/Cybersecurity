#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <getopt.h>


#define BUFFER_SIZE 1024

int port = 0;
int limit = 65535;
int proto_type = SOCK_STREAM;
int sockfd; 
int opt;
char buffer[BUFFER_SIZE];
char *proto_name = "tcp";
char *help = "Usage: ./main <IP> [options]\n\nBasic options:\n-h\thelp screen\n-p\tspecifies a port to scan\n-s\tconfigure a start port. (Default: 0)\n-l\tconfigue a limit port. (Default: 65535)\n";



struct sockaddr_in target;
struct servent *service;


bool Connection(char *ip, char *proto_name, int proto_type, int port){

   

    if(port < 0 || port > limit) exit(1);

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


        while ((opt = getopt(argc, argv, "p:hs:l:")) != -1){
        
            switch (opt){

                case 'h':
                    printf("%s", help);
                    exit(1);

            
                case 'p':
                    port = atoi(optarg);
                    if (!Connection(ip, proto_name, proto_type, port)) printf("Port Closed: %d\n", port);
                    exit(1);


                case 's':
                    port = atoi(optarg);
                
                
                case 'l':
                    limit = atoi(optarg);


                default:
                    break;
            }

        }

    Connection(ip, proto_name, proto_type, port);
    close(sockfd);
    port++;
    }
}