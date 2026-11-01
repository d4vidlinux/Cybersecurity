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
#include "functions.h"




int main(int argc, char **argv){


    if(argc < 2){
        printf("%s", help);
        exit(1);
    }


    PortScan(argc, argv, argv[1]);

    return 0;
}
