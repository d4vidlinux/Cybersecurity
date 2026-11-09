#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <stdbool.h>


void print_help(void);
bool Connection(char *ip, char *proto_name, int proto_type, int port);
void PortScan(int argc, char **argv, char *ip);

#endif