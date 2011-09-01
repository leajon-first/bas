/*
 * =====================================================================================
 *
 *       Filename:  findPositionStruct.h
 *
 *    Description:      
 *
 *        Version:  1.0
 *        Created:  07/04/2011 01:17:54 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  kangle.wang (mn), wangkangluo1@gmail.com
 *        Company:  APE-TECH
 *
 * =====================================================================================
 */


#ifndef FIND_POSITION_STRUCT_H_
#define FIND_POSITION_STRUCT_H_
typedef struct _PositionStruct PositionStruct;

#include	"hightlightAndSummary.h"


/*定义结构体*/

struct _PositionStruct
{
    char* position;
    int lens;
};


    PositionStruct*
 get_position_struct(PositionList* head, char* content);

#endif
