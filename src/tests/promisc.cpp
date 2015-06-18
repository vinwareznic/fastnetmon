#include <stdlib.h>
#include <stdio.h>
#include <string.h>     
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <arpa/inet.h>  
#include <unistd.h>
#include <linux/if.h>

int main() {
    // We need really any socket for ioctl

    int fd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

    struct ifreq ethreq;    
    memset(&ethreq, 0, sizeof(ethreq));
    strncpy(ethreq.ifr_name, "eth6", IFNAMSIZ);

    int ioctl_res = ioctl(fd, SIOCGIFFLAGS, &ethreq);

    if (ioctl_res == -1) {
        printf("Can't get interface flags");
        exit(1);
    }

    if (ethreq.ifr_flags & IFF_PROMISC) {
        printf("Interface in promisc mode already\n");

        printf("Switch it off\n");

        ethreq.ifr_flags &= ~IFF_PROMISC;

        int ioctl_res_set = ioctl(fd, SIOCSIFFLAGS, &ethreq);

        if (ioctl_res_set == -1) {
            printf("Can't set interface flags");
            exit(1);
        }   

        printf("promisc mode disabled correctly\n");
    } else {
        printf("Interface in non promisc mode now, switch it on\n");
       
        ethreq.ifr_flags |= IFF_PROMISC; 
        int ioctl_res_set = ioctl(fd, SIOCSIFFLAGS, &ethreq);

        if (ioctl_res_set == -1) {
            printf("Can't set interface flags");
            exit(1);
        }
            
        printf("promisc mode enabled\n");
    }

    close(fd);
}
