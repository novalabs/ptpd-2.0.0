// TODO: Copyright & Credits

#ifndef PTPD_H_
#define PTPD_H_

//define PTPD_DBGVV
//#define PTPD_DBGV
//#define PTPD_DBG
//#define PTPD_ERR

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdint-gcc.h>
#include <stm32f4xx.h>
#include <limits.h>

#include "lwip/opt.h"
#include "lwip/api.h"
#include "lwip/inet.h"
#include "lwip/mem.h"
#include "lwip/udp.h"
#include "lwip/igmp.h"
#include "lwip/arch.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "constants.h"
#include "dep/constants_dep.h"
#include "dep/datatypes_dep.h"
#include "datatypes.h"
#include "dep/ptpd_dep.h"

typedef struct
{
    int32_t   state;
    int32_t   delay;
    int64_t   offset;
    int32_t   drift;
} PTPStats;


/** \name arith.c
 * -Timing management and arithmetic */
/**\{*/
/* arith.c */

/**
 * \brief Convert scaled nanoseconds into TimeInternal structure
 */
void scaledNanosecondsToInternalTime(const int64_t*, TimeInternal*);
/**
 * \brief Convert TimeInternal into Timestamp structure (defined by the spec)
 */
void fromInternalTime(const TimeInternal*, Timestamp*);

/**
 * \brief Convert Timestamp to TimeInternal structure (defined by the spec)
 */
void toInternalTime(TimeInternal*, const Timestamp*);

/**
 * \brief Add two TimeInternal structure and normalize
 */
void addTime(TimeInternal*, const TimeInternal*, const TimeInternal*);

/**
 * \brief Substract two TimeInternal structure and normalize
 */
void subTime(TimeInternal*, const TimeInternal*, const TimeInternal*);

/**
 * \brief Divide the TimeInternal by 2 and normalize
 */
void div2Time(TimeInternal*);

/**
 * \brief Returns the floor form of binary logarithm for a 32 bit integer.
 * -1 is returned if ''n'' is 0.
 */
int32_t floorLog2(uint32_t);

/**
 * \brief return maximum of two numbers
 */
static __INLINE int32_t max(int32_t a, int32_t b)
{
	return a > b ? a : b;
}

/**
 * \brief return minimum of two numbers
 */
static __INLINE int32_t min(int32_t a, int32_t b)
{
	return a > b ? b : a;
}

/** \}*/

/** \name bmc.c
 * -Best Master Clock Algorithm functions */
/**\{*/
/* bmc.c */
/**
 * \brief Compare data set of foreign masters and local data set
 * \return The recommended state for the port
 */
uint8_t bmc(PtpClock*);

/**
 * \brief When recommended state is Master, copy local data into parent and grandmaster dataset
 */
void m1(PtpClock*);

/**
 * \brief When recommended state is Passive
 */
void p1(PtpClock*);

/**
 * \brief When recommended state is Slave, copy dataset of master into parent and grandmaster dataset
 */
void s1(PtpClock*, const MsgHeader*, const MsgAnnounce*);

/**
 * \brief Initialize datas
 */
void initData(PtpClock*);

/**
 * \brief Compare two port identities
 */
bool  isSamePortIdentity(const PortIdentity*, const PortIdentity*);

/**
 * \brief Add foreign record defined by announce message
 */
void addForeign(PtpClock*, const MsgHeader*, const MsgAnnounce*);


/** \}*/


/** \name protocol.c
 * -Execute the protocol engine */
/**\{*/
/**
 * \brief Protocol engine
 */
/* protocol.c */

/**
 * \brief Run PTP stack in current state
 */
void doState(PtpClock*);

/**
 * \brief Change state of PTP stack
 */
void toState(PtpClock*, uint8_t);
/** \}*/

// Send an alert to the PTP daemon thread.
void ptpd_alert(void);

// Initialize PTP daemon thread.
void ptpd_init(void);


bool ptpd_isSlave();
void ptpd_getStats(PTPStats* stats);
void ptpd_printStats();

#ifdef __cplusplus
}
#endif

#endif /* PTPD_H_*/
