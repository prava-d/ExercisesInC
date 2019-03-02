#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <time.h>
#include <netinet/in.h>
#include <netinet/in_systm.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <netinet/udp.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <sys/un.h>
#include <stdarg.h>
#include <syslog.h>

#define BUFSIZE 1500

typedef struct rec {                /* outgoing UDP data */
  u_short seq;          /* sequence number */
} Rec;

typedef struct timeval Timeval;
typedef struct sockaddr Sockaddr;

#define max(a,b) ((a) > (b) ? (a) : (b))


// variables in trout.c
extern int max_ttl;
extern int nprobes;
extern int seq;
extern char recvbuf[BUFSIZE];
extern char sendbuf[BUFSIZE];
extern Rec *rec;
extern int sendfd, recvfd;
extern int pipefd[2];      
extern Sockaddr *sasend;   
extern Sockaddr *sarecv;
extern Sockaddr *salast;
extern Sockaddr *sabind;
extern socklen_t salen;       
extern int datalen;     
extern u_short sport;                 
extern u_short dport; 
extern Timeval sendtv[1];
extern Timeval recvtv[1];
extern Timeval difftv[1];

// functions in trout.c
void sig_alrm (int signo);
int process_ip (struct ip *ip, int len);
int recv_dgram ();
void sub_tv (Timeval *plus, Timeval *minus, Timeval *res);
double time_to_double (Timeval *time);
void print_report ();
void send_dgram (int ttl);
int send_probes (int ttl);
void loop_ttl ();