/*
 * =====================================================================================
 *
 *       Filename:  getCollector.h
 *
 *    Description:      
 *
 *        Version:  1.0
 *        Created:  06/28/2011 08:02:35 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  kangle.wang (mn), wangkangluo1@gmail.com
 *        Company:  APE-TECH
 *
 * =====================================================================================
 */


#ifndef GET_COLLECTOR_H_
#define GET_COLLECTOR_H_
typedef struct _CollecotrAndHits CollecotrAndHits;


#include <egg2/Egg2.h>
#include <scholar/ImLexAnalyzer.h>
#include <scholar/ImTokenList.h>
#include <scholar/ImCnLexAnalyzer.h>
#include <scholar/ImCwsLexAnalyzer.h>
#include         "addQueryToEgg.h"

struct _CollecotrAndHits
{
    HEGGTOPCOLLECTOR hTopCollector;
    HEGGSCOREDOC lp_score_doc;
    count_t cnt;
};

    CollecotrAndHits*
get_colloector ( InputStruct* inputStruct, HEGGINDEXSEARCHER  hIndexSearcher);

    void
delete_colloector ( CollecotrAndHits* collector );


#endif
