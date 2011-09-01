/*
 * =====================================================================================
 *
 *       Filename:  config.h
 *
 *    Description:      
 *
 *        Version:  1.0
 *        Created:  07/21/2011 04:54:43 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  kangle.wang (mn), wangkangluo1@gmail.com
 *        Company:  APE-TECH
 *
 * =====================================================================================
 */



#ifndef _CONFIG_H
#define _CONFIG_H
#include        <spdPostStorage.h>

typedef struct _G_CONFIG G_CONFIG;


/*定义结构体*/

struct _G_CONFIG
/*-----------------------------------------------------------------------------
 * \brief     数据库结构
 *-----------------------------------------------------------------------------*/
{
    spdPostStorage* p_stu_spd;
    char *op;
};

    void
start_CONFIG ( );

/*-----------------------------------------------------------------------------
 * \brief    初始化数据库
 * \param[in]         
 * \param[out]   G
 * \return                                                                                                                                        
 * \free  free_CONFIG()
 *-----------------------------------------------------------------------------*/

    void
free_CONFIG (  );

/*-----------------------------------------------------------------------------
 * \brief    删除数据库
 * \param[in]    G   
 * \param[out]   
 * \return                                                                                                                                         
 * \free  
 *-----------------------------------------------------------------------------*/

#endif
