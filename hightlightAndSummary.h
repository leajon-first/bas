/*
 * =====================================================================================
 *
 *       Filename:  hightlightAndSummary.h
 *
 *    Description:      
 *
 *        Version:  1.0
 *        Created:  07/03/2011 06:16:49 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  kangle.wang (mn), wangkangluo1@gmail.com
 *        Company:  APE-TECH
 *
 * =====================================================================================
 */


#ifndef HIGHTLIGHT_AND_SUMMARY_H_
#define HIGHTLIGHT_AND_SUMMARY_H_
#include	"getCollector.h"

/*定义结构体*/
typedef struct _PositionList PositionList;
typedef struct _PositionListPoint PositionListPoint;

struct _PositionList
{
    char* position;
    int lens;
    PositionList* next;
};

struct _PositionListPoint
{
    PositionList* head_point;
    PositionList* last_point;
};

    char* 
hightlight_title(char* title, char** pKeywords, size16_t* pkeySz, count_t num, int isBigSize);

    char*
get_summary (char* content, char** pKeywords, size16_t* pkeySz, count_t num);

#endif
