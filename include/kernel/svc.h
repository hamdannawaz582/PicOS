/* svc.h - dispatch_svcall */

#ifndef SVC_H
#define SVC_H

/*----------------------------------------------------------------------
 * dispatch_svcall   -   dispatcher for svcalls
 * Input:
 *  uint32_t*   -   start of arguments of caller
 * Output:
 *
 ----------------------------------------------------------------------*/
void dispatch_svcall(uint32_t * args);

#endif