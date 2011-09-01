/*
 * =====================================================================================
 *
 *       Filename:  putInGstring.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  06/28/2011 09:26:58 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  kangle.wang (mn), wangkangluo1@gmail.com
 *        Company:  APE-TECH
 *
 * =====================================================================================
 */


#include	"hightlightAndSummary.h"
#include        "stringsReplace.h"
#include	"putInGstring.h"
#include        "pKeywords.h"
#include        <spdPostStorage.h>
#include        "config.h"

extern G_CONFIG* G;


typedef struct _Element  Element;
struct _Element
{
    char* title;
    char* url;
    char* content;
    char* datetime;
};


typedef struct _Pageinfo Pageinfo;
struct _Pageinfo
{
    int start;
    int end;
};



    static void
print_head (  GString*  pGstr, count_t cnt, InputStruct* inputStruct, float time)
{
    long int page = (cnt%inputStruct->pagesize == 0)
        ? (cnt/inputStruct->pagesize)
        : (cnt/inputStruct->pagesize + 1);

    g_string_sprintfa(pGstr, "search_callback({ \
        \"result\":%d, \
            \"pageAct\":%ld, \
            \"useTime\":%f, \
            \"body\":[", cnt, page, time);
    return ;
}		/* -----  end of function print_head  ----- */


    static void
print_end ( GString*  pGstr)
{
    g_string_sprintfa(pGstr, "], \"err\":\"\"})");
    return ;
}		/* -----  end of function print_end  ----- */


    static char*
get_strings_from_doc ( HEGGDOCUMENT lpEggDocument, char* field )
{
    HEGGFIELD lp_field = eggDocument_get_field(lpEggDocument, field);
    unsigned len = 0;
    char* val = eggField_get_value(lp_field, &len);
    lp_field = 0;
    return val;
}		/* -----  end of function get_strings_from_doc  ----- */


    static char*
replace_special_strings ( char* strings )
{
    char* back = NULL;
    char* exchange = NULL;
    exchange = strings_replace_without_free(strings, "\n", "");
    back = strings_replace_with_free(exchange, "\"", "\\\"");
    back = strings_replace_with_free(back, "\r", "");
   
return back;
}		/* -----  end of function replace_special_strings  ----- */


    static char*
delete_no_needs (char * content )
{
    content = strings_replace_without_free(content, "<", "");
    content = strings_replace_with_free(content, ">", "");
    content = strings_replace_with_free(content, "commenttime", "");
    content = strings_replace_with_free(content, "comment", "");
    content = strings_replace_with_free(content, "content", "");
    content = strings_replace_with_free(content, "CDATA", "");
    content = strings_replace_with_free(content, "[", "");
    content = strings_replace_with_free(content, "]", "");
    content = strings_replace_with_free(content, "time", "");
    content = strings_replace_with_free(content, "\"", "");

    return content ;
}		/* -----  end of function delete_no_needs  ----- */

    static void  
get_element ( Element* element, HEGGDOCUMENT lpEggDocument, char** pKeywords, size16_t* pkeySz, count_t num)
{
    char* title = get_strings_from_doc ( lpEggDocument, "title" );
    element->title = replace_special_strings(title);
    element->title = hightlight_title(element->title, pKeywords, pkeySz, num, 1);
    title = element->title;
    element->title = replace_special_strings(element->title);
    free(title);

    element->url = get_strings_from_doc ( lpEggDocument, "url" );
  
  char* content = NULL;

/*
    if(!strcmp(G->op, "search"))
    {
*/
        content = get_strings_from_doc ( lpEggDocument, "content" );
/*  
  }
    else 
    {

        spdPostStorage_get_focus(G->p_stu_spd, element->url);
        content = spdPostStorage_get_comments(G->p_stu_spd);
    }

*/
    if(!strcmp(G->op, "bbs"))
    {
        content = delete_no_needs(content);      
    } 

    element->content = get_summary (content, pKeywords, pkeySz, num);


    if(!strcmp(G->op, "bbs"))
    {

        free(content);
    }

    char* point = element->content;
    element->content = replace_special_strings(element->content);
    free(point);
    point = NULL;
    element->content = hightlight_title(element->content, pKeywords, pkeySz, num, 0);

    point = element->content;
    element->content = replace_special_strings(element->content);
    free(point);

    element->datetime = get_strings_from_doc ( lpEggDocument, "datetime" );
    return ;
}		/* -----  end of function get_element  ----- */


    static void
insert_to_gstring (Element* element,  GString*  pGstr, int isLastOne)
{
    g_string_sprintfa(pGstr,"{\"post_title\":\"%s\",", element->title);
    free(element->title);


    g_string_sprintfa(pGstr,"\"post_summary\":\"%s\",", element->content);
    free(element->content);


    g_string_sprintfa(pGstr,"\"post_url\":\"%s\",", element->url);
    if(isLastOne == 1)
    {
        g_string_sprintfa(pGstr,"\"date\":\"%s\"}", element->datetime);
    }
    else
    {
        g_string_sprintfa(pGstr,"\"date\":\"%s\"},", element->datetime);
    }
    return ;
}		/* -----  end of function insert_to_gstring  ----- */

    static void
get_page_info (Pageinfo* pageInfo,  InputStruct* inputStruct,  count_t cnt)
{
    pageInfo->start = inputStruct->pagesize * (inputStruct->page - 1);
    if((inputStruct->page * inputStruct->pagesize) > cnt)
    {
        pageInfo->end = cnt - pageInfo->start;  
    }
    else
    { 
        pageInfo->end = pageInfo->start + inputStruct->pagesize;     
    }
}		/* -----  end of function page_info  ----- */




    static void
get_document (CollecotrAndHits* collector, HEGGINDEXREADER hIndexReader, int nums, int isLastOne, Element* element, GString*  pGstr, const char *keywords)
{
    HEGGDOCUMENT lp_eggDocument = EGG_NULL;
    eggIndexReader_get_document(hIndexReader,
            collector->lp_score_doc[nums].idDoc, &lp_eggDocument);

            char **pkeywords;
            size16_t *pkeySz;
            count_t num;

            if(!strcmp(G->op, "bbs"))
            {
                eggTopCollector_get_keyPosition(collector->hTopCollector, 
                        collector->lp_score_doc[nums].idDoc,
                        "content_index", &pkeywords, &pkeySz,
                        NULL, &num);

            }
            else
            {
                eggTopCollector_get_keyPosition(collector->hTopCollector, 
                        collector->lp_score_doc[nums].idDoc,
                        "content", &pkeywords, &pkeySz,
                        NULL, &num);
            }
   get_order(pkeywords, pkeySz, num, keywords);
/*
            int i;
            for (i = 0; i < num; i++)
            {
                printf("Key[%.*s]\n", pkeySz[i], pkeywords[i]);
            }
*/

    get_element(element, lp_eggDocument, pkeywords, pkeySz, num);
    free(pkeySz);
    int i  = 0;
    for (i = 0; i < num; i++)
    {
        free(pkeywords[i]);
    }
    free(pkeywords);


    insert_to_gstring (element, pGstr, isLastOne);
    eggDocument_delete(lp_eggDocument);
    return ;
}		/* -----  end of function get_document  ----- */



    void
put_in_gstring ( CollecotrAndHits* collector, GString*  pGstr, HEGGINDEXREADER hIndexReader, InputStruct* inputStruct, float time, const char *keywords)

{
    print_head ( pGstr, collector->cnt , inputStruct,  time);

    Element* element = (Element*)malloc(sizeof(Element));
    memset(element, '0', sizeof(Element)); 
    Pageinfo page_info;

    get_page_info(&page_info, inputStruct, collector->cnt);
    int i = 0;
    for(i = page_info.start; i < page_info.end ; i++)
    {
        if(i == page_info.end - 1)
        {
            get_document(collector, hIndexReader, i, 1, element, pGstr, keywords);
        }
        else
        {
            get_document(collector, hIndexReader, i, 0, element, pGstr, keywords);
        }
    }

    free(element);
    element = NULL;
    print_end(pGstr);
    return ;
}		/* -----  end of function put_in_gstring  ----- */
