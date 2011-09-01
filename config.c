/*
 * =====================================================================================
 *
 *       Filename:  config.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/21/2011 04:54:13 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  kangle.wang (mn), wangkangluo1@gmail.com
 *        Company:  APE-TECH
 *
 * =====================================================================================
 */



#include "config.h"
#include <stdlib.h>
#include <string.h>

G_CONFIG* G = NULL;
               /* -----  数据库根节点  ----- */ 

    void
start_CONFIG (  )
{
    G = (G_CONFIG*)malloc(sizeof(G_CONFIG));
    memset(G, 0, sizeof(G_CONFIG));
    G->p_stu_spd = spdPostStorage_new("kvdb:tt://192.168.1.136:12704");
}		/* -----  end of function start_c  ----- */

    void
free_CONFIG (  )
{
    spdPostStorage_delete(G->p_stu_spd);
    free(G->op);
    free(G);
    G = NULL;
    return ;
}		/* -----  end of function free_config  ----- */
