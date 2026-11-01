#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <stdbool.h>

extern char *help;

bool Connection(char *ip, char *proto_name, int proto_type, int port);
void PortScan(int argc, char **argv, char *ip);

#endif