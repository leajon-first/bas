/*
 * =====================================================================================
 *
 *       Filename:  pKeywords.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/18/2011 09:59:21 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  kangle.wang (mn), wangkangluo1@gmail.com
 *        Company:  APE-TECH
 *
 * =====================================================================================
 */

#include   "pKeywords.h"


typedef struct _KeywordsList KeywordsList;
struct _KeywordsList
{
    char* strings;
    int strings_lens;
    long long int position;
    int defy_pos;
};

    static GSList*
get_list ( char **pkeywords, size16_t *pkeySz, count_t num, const char *keywords)      //获取关键字链表
{  
    GSList* list = NULL;
    KeywordsList* fred = NULL;
    int i = 0;
    for(i = 0; i < num ; i++)
    {
       fred = (KeywordsList*)malloc(sizeof(KeywordsList));

       fred->strings = (char*)malloc(pkeySz[i] + 1);
       strncpy(fred->strings, pkeywords[i], pkeySz[i]);
       fred->strings[pkeySz[i]] =  '\0';
      
       fred->strings_lens = pkeySz[i];
       fred->position = (long long int)strstr(keywords, fred->strings);

       fred->defy_pos = i;
       list = g_slist_append(list, fred);
    }
     return list;
}		/* -----  end of function get_list  ----- */


    static void
free_list (GSList *list)
{
    GSList *iterator = NULL;
    for (iterator = list; iterator; iterator = iterator->next) { 
        free(((KeywordsList*)iterator->data)->strings);
        free(iterator->data); 
    } 
    g_slist_free(list); 
}		/* -----  end of function free_list  ----- */

    static gint  
my_comparator(gconstpointer item1, gconstpointer item2) {
    if(((KeywordsList*)item1)->position > ((KeywordsList*)item2)->position)
    {
        return 1;
    }
    else
    {
        return 0;
    }    
   //  return g_ascii_strcasecmp(((Person*)item1)->name, ((Person*)item2)->name); 
}


    static void
sort_pkeywords ( char **pkeywords, size16_t *pkeySz, count_t num, GSList *list)
{
    int i = 0;
    GSList *iterator = list;
    for(i = 0; i < num ; i++)
    {
        int point = ((KeywordsList*)iterator->data)->defy_pos;
        if(i != point)
        {
           free(pkeywords[i]); 
           char *strings = ((KeywordsList*)iterator->data)->strings;
           int lens = strlen(strings);
           pkeywords[i] = (char*)malloc(lens + 1);
           strncpy(pkeywords[i], strings, lens);
           (pkeywords[i])[lens] = '\0';
           pkeySz[i] = ((KeywordsList*)iterator->data)->strings_lens;
        }
        iterator = iterator->next;
    }
    return ;
}		/* -----  end of function sort_pkeywords  ----- */
    void
get_order ( char **pkeywords, size16_t *pkeySz, count_t num, const char *keywords )    //对关键字排序
{
    GSList *list = get_list( pkeywords, pkeySz, num, keywords);
    list = g_slist_sort(list, (GCompareFunc)my_comparator);
    sort_pkeywords(pkeywords, pkeySz,  num, list ); 
    free_list(list); 
    return ;
}		/* -----  end of function get_order  ----- */

