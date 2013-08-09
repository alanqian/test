#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <net/if.h>
#include <arpa/inet.h>

#define BOOL int
#define FALSE  0
#define TRUE   1

#define MAX_NET_CARDS   16
#define MAC_ADDR_LEN    32
/* local loopback interface name */
#define LOOPBACK_IF_NAME "lo"

/*
UINT_PTR WINAPI SetTimer(
  __in_opt  HWND hWnd,
  __in      UINT_PTR nIDEvent,
  __in      UINT uElapse,
  __in_opt  TIMERPROC lpTimerFunc
);

BOOL WINAPI KillTimer(
  __in_opt  HWND hWnd,
  __in      UINT_PTR uIDEvent
);
*/

int GetNicInfoForLinux()
{
    int skfd = -1, if_cnt = 0, if_idx = 0;;
    struct ifreq if_buf[MAX_NET_CARDS];
    struct ifconf ifc;
    u_int8_t mac_addr[MAC_ADDR_LEN];
    u_int32_t ip = 0, netmask = 0;
    BOOL ip_get = FALSE, netmask_get = FALSE;
    struct list_head *ip_info_list = NULL;
    if ((skfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        fprintf(stderr, "Get NIC info, Create socket error");
        return FALSE;
    }
    ifc.ifc_len = sizeof(if_buf);
    ifc.ifc_buf = (char *)if_buf;
    if (!ioctl(skfd, SIOCGIFCONF, (char *)&ifc))
    {
        if_cnt = (ifc.ifc_len) / (sizeof(struct ifreq));
        for (if_idx = 0; if_idx < if_cnt; ++if_idx)
        {
            /* ignore local loopback interface */
            if (strcmp(LOOPBACK_IF_NAME, if_buf[if_idx].ifr_name) == 0)
                continue;
            /* get interface flags */
            if (!(ioctl(skfd, SIOCGIFFLAGS, (char *)(&if_buf[if_idx]))))
            {
                /* this interface is up and running */
                if ((if_buf[if_idx].ifr_flags & IFF_UP) &&
                    (if_buf[if_idx].ifr_flags & IFF_RUNNING))
                {
                    if (!(ioctl(skfd, SIOCGIFHWADDR, (char *)(&if_buf[if_idx]))))
                    {
                        memcpy(mac_addr, (char *)(&(if_buf[if_idx].ifr_hwaddr.sa_data)), MAC_ADDR_LEN);
                        /* add new NIC */
                        //ip_info_list = AddNicToNewNicInfoList(mac_addr, MAC_ADDR_LEN, &g_newNicInfoList);
                        printf("mac: %.*s\n", MAC_ADDR_LEN, mac_addr);
                    }
                    /* get ip address of this NIC */
                    if (!(ioctl(skfd, SIOCGIFADDR, (char *)(&if_buf[if_idx]))))
                    {
                        ip = ((struct sockaddr_in *)(&(if_buf[if_idx].ifr_addr)))->sin_addr.s_addr;

                        ip_get = TRUE;
                    }
                    /* get ip netmask */
                    if (!(ioctl(skfd, SIOCGIFNETMASK, (char *)(&if_buf[if_idx]))))
                    {
                        netmask = ((struct sockaddr_in *)(&(if_buf[if_idx].ifr_netmask)))->sin_addr.s_addr;
                        netmask_get = TRUE;
                    }
                    /* insert ip to ip list */
                    if ((TRUE == ip_get) && (TRUE == netmask_get))
                    {
                        //AddIpToIpList(ip, netmask, ip_info_list);
                        printf("ip: %d.%d.%d.%d, mask:%d.%d.%d.%d\n",
                            ip >> 24, (ip >> 16) & 0xff, (ip >> 8) & 0xff, ip & 0xff,
                            netmask >> 24, (netmask >> 16) & 0xff, (netmask >> 8) & 0xff, netmask & 0xff);
                        ip_get = FALSE;
                        netmask_get = FALSE;
                    }
                }
            }
        }   /* end of for (if_idx = 0; if_idx < if_cnt; ++if_idx) */
    }
    close(skfd);
    return TRUE;
}

int main(int argc, const char *argv[])
{
    GetNicInfoForLinux();
    return 0;
}
