/*
 * =====================================================================================
 *
 *       Filename:  z.c
 *
 *    Description:  i
 *
 *        Version:  1.0
 *        Created:  08/02/2011 04:31:14 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  kangle.wang (mn), wangkangluo1@gmail.com
 *        Company:  APE-TECH
 *
 * =====================================================================================
 */

#include <time.h>
int
main()
{
    time_t t;
    time(&t);
    struct tm *plocalTime;
    plocalTime = localtime(&t);
    printf("%f\n", (double)t);
}
