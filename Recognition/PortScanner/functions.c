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
#include <pthread.h>


static char *help = "Usage: ./main <IP> [options]\n\nBasic options:\n-h\thelp screen\n-p\tspecifies a port to scan\n-s\tconfigure a start port. (Default: 0)\n-l\tconfigue a limit port. (Default: 65535)\n";

char *target_ip;
int port = 0;
int limit = 65535;
int num_threads = 10;
pthread_t *t;
pthread_mutex_t mutex;


void *ThreadFunc(void *arg){

    int current_port;

    while(1){

        pthread_mutex_lock(&mutex);
        if (port > limit){
            pthread_mutex_unlock(&mutex);
            break;
        }

        current_port = port;
        port++;
        pthread_mutex_unlock(&mutex);

        Connection(target_ip, current_port);
    }

    return NULL;
}



void print_help(void){
    printf("%s", help);
}

bool Connection(char *ip, int port){

    int sockfd;

    struct sockaddr_in target;
    struct servent *service;

    if(port < 0 || port > limit) return false;


    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) return false;


    memset(&target, 0, sizeof(target));
    
    target.sin_family = AF_INET;
    target.sin_port = htons(port);

    inet_pton(AF_INET, ip, &target.sin_addr);

    if ( connect(sockfd, (struct sockaddr *) &target, sizeof(target)) == 0){

        pthread_mutex_lock(&mutex);

        service = getservbyport(htons(port), "tcp");

        if (service != NULL) {
            printf("Port Opened: %d\t", port);
            printf("Service: %s - Protocol: %s\n", service->s_name, service->s_proto);
        } else {
            printf("Port Opened: %d\t", port);
            printf("Service: Unknown - Protocol: tcp\n");
        }
        pthread_mutex_unlock(&mutex);

        close(sockfd);
        return true;
    }
    close(sockfd);
    return false;
}


void PortScan(int argc, char **argv, char *ip){

    int opt;
    target_ip = ip;

    while ((opt = getopt(argc, argv, "p:hs:l:t:")) != -1){
    
        switch (opt){

            case 'h':
                printf("%s", help);
                exit(1);

        
            case 'p':
                port = atoi(optarg);
                if (!Connection(ip, port)) printf("Port Closed: %d\n", port);
                exit(1);


            case 's':
                port = atoi(optarg);
                break;
            
            
            case 'l':
                limit = atoi(optarg);
                break;
            
            case 't':
                num_threads = atoi(optarg);
                if (num_threads <= 0) num_threads = 1;
                break;

            default:
                break;
        }

    }
    
    t = malloc(sizeof(pthread_t) * num_threads);
    if (t == NULL){
        perror("Error allocating threads!");
        exit(1);
    }

    pthread_mutex_init(&mutex, NULL);

    for (int i = 0; i < num_threads; i++){
        pthread_create(&t[i], NULL, ThreadFunc, NULL);
    }
    for (int i = 0; i < num_threads; i++){
        pthread_join(t[i], NULL);
    }
    pthread_mutex_destroy(&mutex);
    free(t);
}



