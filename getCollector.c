/*
 * =====================================================================================
 *
 *       Filename:  getCollector.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  06/28/2011 08:02:32 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  kangle.wang (mn), wangkangluo1@gmail.com
 *        Company:  APE-TECH
 *
 * =====================================================================================
 */

#include        "getTimeStrings.h"
#include        "getCollector.h"
#include        <stdlib.h>
#include        <stdio.h>

    static  HEGGQUERY        
egg2Searcher_get_query(char* key)  
{
    HEGGQUERY new_hQuery = NULL; 
    char* startTime = (char *)malloc(11);
    char* endTime = (char *)malloc(11);
    getTimeString(key,endTime,startTime);
    new_hQuery = eggQuery_new_stringRange("date", startTime, endTime);
    free(startTime);     
    free(endTime);
    return new_hQuery;      
}

    static int
is_in_array ( char* key )
{
    int back = 0;
    if(key != NULL)
    {
        if(!strcmp(key, "day") ||
                !strcmp(key, "week") || 
                !strcmp(key, "mons") ||
                !strcmp(key, "year") )
        {
            back = 1;
        }
    }
    return back;
}		/* -----  end of function is_in_array  ----- */

    CollecotrAndHits*
get_colloector ( InputStruct* inputStruct, HEGGINDEXSEARCHER  hIndexSearcher)
{
    HEGGQUERY egg_query = get_query(inputStruct);    //造query
    int lens = sizeof(CollecotrAndHits);
    CollecotrAndHits* collector = (CollecotrAndHits*)malloc(lens);  
    memset(collector, '\0', lens); 
    collector->hTopCollector = eggTopCollector_new(0);
    int ret = eggIndexSearcher_search_with_query(hIndexSearcher, collector->hTopCollector, egg_query);
    if (ret == EGG_TRUE)
    {
        HEGGQUERY hQuery_tmp = 0;
        hQuery_tmp = egg2Searcher_get_query("alltime");
        if((inputStruct->time != NULL) && (is_in_array(inputStruct->time) == 1))
        {
            hQuery_tmp = egg2Searcher_get_query(inputStruct->time);
        }

        eggTopCollector_normalized(collector->hTopCollector,EGG_TOPSORT_SCORE);    //按时间排序

        eggIndexSearcher_filter(hIndexSearcher, collector->hTopCollector, hQuery_tmp, 1);

        if((inputStruct->orderby == NULL) || (strcmp(inputStruct->orderby, "time")))
        {
            eggTopCollector_sort_with_score(collector->hTopCollector);    //按相关度排序
        }

        eggQuery_delete(hQuery_tmp);
        collector->lp_score_doc = eggTopCollector_top_docs(collector->hTopCollector);
        collector->cnt =  eggTopCollector_total_hits(collector->hTopCollector);
    }
    eggQuery_delete(egg_query);
    return collector;
}		/* -----  end of function get_colloector  ----- */

    void
delete_colloector ( CollecotrAndHits* collector )
{
    eggTopCollector_delete(collector->hTopCollector);
    free(collector);
    collector = NULL; 
    return ;
}		/* -----  end of function get_colloector  ----- */
