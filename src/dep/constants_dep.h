#ifndef CONSTANTS_DEP_H_
#define CONSTANTS_DEP_H_

#define IF_NAMESIZE        2
#ifndef INET_ADDRSTRLEN
#define INET_ADDRSTRLEN    16
#endif
#define IFACE_NAME_LENGTH  IF_NAMESIZE
#define NET_ADDRESS_LENGTH INET_ADDRSTRLEN

#if BYTE_ORDER == LITTLE_ENDIAN
#define PTPD_LSBF
#elif BYTE_ORDER == BIG_ENDIAN
#define PTPD_MSBF
#endif

#define pow2ms(a) (((a)>0) ? (1000 << (a)) : (1000 >>(-(a))))

#define ADJ_FREQ_MAX  512000

/* UDP/IPv4 dependent */
#define SUBDOMAIN_ADDRESS_LENGTH  4
#define PORT_ADDRESS_LENGTH       2
#define PTP_UUID_LENGTH           NETIF_MAX_HWADDR_LEN
#define CLOCK_IDENTITY_LENGTH     8
#define FLAG_FIELD_LENGTH         2

#define PACKET_SIZE  300 /* ptpdv1 value kept because of use of TLV... */

#define PTP_EVENT_PORT    319
#define PTP_GENERAL_PORT  320

#define DEFAULT_PTP_DOMAIN_ADDRESS  "224.0.1.129"
#define PEER_PTP_DOMAIN_ADDRESS     "224.0.0.107"

/* Must be a power of 2 */
#define PBUF_QUEUE_SIZE 4
#define PBUF_QUEUE_MASK (PBUF_QUEUE_SIZE - 1)

#endif /* CONSTANTS_DEP_H_*/

