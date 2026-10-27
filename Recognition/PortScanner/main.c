#include <stdio.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>


struct sockaddr_in target;


void PortScan(char *ip){

    int all_ports = 1;

    int sockfd;

    while(1){

        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        memset(&target, 0, sizeof(target));
        
        target.sin_family = AF_INET;
        target.sin_port = htons(all_ports);

        inet_pton(AF_INET, ip, &target.sin_addr);

        if(all_ports > 65535) break;

        if ( connect(sockfd, (struct sockaddr *)&target, sizeof(target)) == 0){

            switch (all_ports){
            
            case 20:
                printf("Port Opened: %d - FTP\n", all_ports);

            case 21:
                printf("Port Opened: %d - FTP\n", all_ports);

            case 22:
                printf("Port Opened: %d - SSH\n", all_ports);

            case 23:
                printf("Port Opened: %d - TELNET\n", all_ports);

            case 25:
                printf("Port Opened: %d - SMTP\n", all_ports);
            
            case 53:
                printf("Port Opened: %d - DNS\n", all_ports);

            case 69:
                printf("Port Opened: %d - TFTP\n", all_ports);

            case 80:
                printf("Port Opened: %d - HTTP\n", all_ports);

            case 110:
                printf("Port Opened: %d - POP3\n", all_ports);

            case 143:
                printf("Port Opened: %d - IMAP\n", all_ports);

            case 443:
                printf("Port Opened: %d - HTTPS", all_ports);

            case 445:
                printf("Port Opened: %d - SMB\n", all_ports);
            
            case 3389:
                printf("Port Opened: %d - RDP\n", all_ports);

            case 465:
                printf("Port Opened: %d - SMTPS\n", all_ports);

            case 587:
                printf("Port Opened: %d - SMTPS\n", all_ports);

            case 8080:
                printf("Port Opened: %d - HTTP\n", all_ports);

            default:
                printf("Port Opened: %d - Unknown\n", all_ports);
        }

        }
        all_ports++;



    }

    close(sockfd);

}



int main(int *argc, char **argv){

    PortScan(argv[1]);

    return 0;
}
