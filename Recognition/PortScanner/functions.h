#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <stdbool.h>

void *ThreadFunc(void *arg);
void print_help(void);
bool Connection(char *ip, int port);
void PortScan(int argc, char **argv, char *ip);


#endif