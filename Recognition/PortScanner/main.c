#include <stdio.h>
#include <stdlib.h>
#include "functions.h"


int main(int argc, char **argv){


    if(argc < 2){
        print_help();
        exit(1);
    }


    PortScan(argc, argv, argv[1]);
    exit(1);

    return 0;
}
