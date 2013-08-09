#include <string.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char* argv[])
{
    int inet_sock;
    struct ifreq ifr;
    FILE *net_devs;
    char buf[1024];
    char interface[32];

    net_devs = fopen("/proc/net/dev", "r");
    if(net_devs == NULL){
        perror("Can't open /proc/net/dev for reading");
        _exit(1);
    }

    inet_sock = socket(AF_INET, SOCK_DGRAM, 0);
    while (1)
    {
        if(fscanf(net_devs, "%32s %1024[^\n]", interface, buf) <= 0){
            break;
        }
        if(interface[strlen(interface) - 1] != ':'){
            continue; // skip the comment
        }
        else
        {
            interface[strlen(interface) - 1] = '\0';
        }
        strcpy(ifr.ifr_name, interface);
        if (ioctl(inet_sock, SIOCGIFADDR, &ifr) < 0)
        {
            perror(interface);
        }
        else
        {
            printf("%s:%s\n", interface,
                inet_ntoa(((struct sockaddr_in*)&(ifr.ifr_addr))->sin_addr));
        }
    }
    close(inet_sock);

    return 0;
}

