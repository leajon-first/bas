/*
 * =====================================================================================
 *
 *       Filename:  hightlightAndSummary.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/03/2011 06:16:47 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  kangle.wang (mn), wangkangluo1@gmail.com
 *        Company:  APE-TECH
 *
 * =====================================================================================
 */
#include        <string.h>
#include        <math.h>
#include	"findPositionStruct.h"
#include          "stringsReplace.h"
#include          "hightlightAndSummary.h"
#include         "log4c.h"
#include	"findStringsWithoutCase.h"

    static char*
get_keywords ( char** pKeywords, size16_t* pkeySz, int num)
{
   char* back = (char*)malloc(pkeySz[num] + 1);
   strncpy(back, pKeywords[num], pkeySz[num]);
   back[pkeySz[num]] = '\0';
    return back;
}		/* -----  end of function get_keywords  ----- */


    static char*
get_dest ( char* p_keywords, int isBigSize )
{

    char* css_strings_head = NULL;
    if(isBigSize == 0)
    {
        css_strings_head = "<span class='news_title2'>";
    }
    else
    {
        css_strings_head = "<span class='news_title1'>";
    }
    int css_strings_head_lens = strlen(css_strings_head); 
    char* css_strings_end= "</span>";
    int css_strings_end_lens = strlen(css_strings_end); 
    int lens = strlen(p_keywords);
    char* back = (char*)malloc(css_strings_head_lens + css_strings_end_lens + lens + 1);
    memcpy(back, css_strings_head, css_strings_head_lens);
    memcpy(&back[css_strings_head_lens], p_keywords, lens);
    memcpy(&back[css_strings_head_lens + lens], css_strings_end, css_strings_end_lens);
    back[css_strings_head_lens + css_strings_end_lens + lens] = '\0';
    return back;
}		/* -----  end of function get_dest  ----- */


    PositionList* 
creat_new_node ( char* point, int lens )
{
    PositionList* new = (PositionList*)malloc(sizeof(PositionList));
    new->position = point;
    new->lens = lens;
    new->next = NULL;
    return new;
}		/* -----  end of function creat_new_node  ----- */


    static void
insert_position_exact ( PositionListPoint* pointInfo, char* point, PositionList* needsToInsert)
{
    PositionList* cursor = pointInfo->head_point;

    if((cursor->position) > point)
    {
        needsToInsert->next = cursor;
        pointInfo->head_point = needsToInsert;
        return ; 
    }

    if(cursor->next != NULL)
    {
        while(1)
        {
            if(cursor->next == NULL)
            {
                cursor->next = needsToInsert;
                pointInfo->last_point = needsToInsert;
                break;
            }
            if( point < (cursor->next->position))
            {
                needsToInsert->next = cursor->next; 
                cursor->next = needsToInsert;
                break;
            }
            cursor = cursor->next;
        }
    }
    else
    {
        if(cursor->position < point)
        {
            cursor->next = needsToInsert;
            pointInfo->last_point = needsToInsert;           
        }
        else
        {
            needsToInsert->next = cursor;
        }
    }
    return ;
}		/* -----  end of function insert_position_exact  ----- */

    static void 
insert_position ( PositionListPoint* pointInfo, char* point, int lens,  int isByOrder)
{
    if( pointInfo->head_point == NULL)
    {
        PositionList* new = creat_new_node(point, lens);
        pointInfo->head_point = new;
        pointInfo->last_point = new;
    }
    else
    {
        PositionList* last_point = creat_new_node(point, lens);
        if(isByOrder == 0)
        {
            pointInfo->last_point->next = last_point;
            pointInfo->last_point  = last_point; 
        }
        else
        {
            insert_position_exact(pointInfo, point, last_point);
        }
    }
    return ;
}		/* -----  end of function insert_position  ----- */

    static void 
find_position_and_insert ( PositionListPoint* pointInfo, char* content, char* keywords, int lens,  int isByOrder )
{
    char* point  = NULL;
    char* point_head = content;
    int keywords_lens = strlen(keywords);

       
//    while( (point = strstr(point_head, keywords)) != NULL)
    char *exact = find_without_case(point_head, keywords);
    char *switch_point = NULL;
    if(exact == NULL)
    {
        switch_point = keywords;
    }
    else
    {
        switch_point = exact;
    }
     
    while( (point = strstr(point_head, switch_point)) != NULL)
    {
        insert_position(pointInfo, point, lens,  isByOrder);
        point_head = point + keywords_lens;
    }
    free(exact);

    return ;
}		/* -----  end of function find_position_and_insert  ----- */

	
    void
delete_position_list(PositionList* head )
{
    PositionList* point = head->next;
    while(head != NULL)
    {
        free(head);
        head = point;
        if(head != NULL)
        {
            point = head->next; 
        }
    }
    return ;
}		/* -----  end of function delete_postion_list  ----- */

    static  void
get_position_list (PositionListPoint* pointInfo, char* content, char** pKeywords, size16_t* pkeySz, count_t num )
{
    int i = 0;
    char* p_keywords = NULL;
    for(i = 0; i < num ; i++)
    {
        p_keywords = get_keywords(pKeywords, pkeySz, i);
        if(i == 0)
        {
            find_position_and_insert(pointInfo , content, p_keywords, pkeySz[i], 0);
        }
        else
        {
            find_position_and_insert(pointInfo , content, p_keywords, pkeySz[i], 1);
        }
        free(p_keywords);
    }
    return ;
} 	/* -----  end of function get_instead  ----- */



    static int
is_english ( const char *pkeywords )
{
    int back = 0;
    int lens = strlen(pkeywords);
    int i = 0;
    for(i = 0; i < lens ; i++)
    {
        if((unsigned char)pkeywords[i] > 0xe0 && (unsigned char)pkeywords[i] < 0xef) 
        {
            i = i + 2;
        }

        if((unsigned char)pkeywords[i] > 0x40 && (unsigned char)pkeywords[i] < 0x5b) 
        {
            back = 1;
        }   
        if((unsigned char)pkeywords[i] > 0x60 && (unsigned char)pkeywords[i] < 0x7b) 
        {
            back = 1;
        }
    }

    return back;
}		/* -----  end of function is_chinese  ----- */


    static char
is_anti ( const char key )
{
    char back = key;
    if((unsigned char)key > 0x40 && (unsigned char)key < 0x5b )
    {
        back = (unsigned char)key + 0x20;
    }
     if((unsigned char)key > 0x60 && (unsigned char)key < 0x7b )
    {
        back = (unsigned char)key - 0x20;
    }
   
    return back;
}		/* -----  end of function is_anti  ----- */

    static char*
get_strings_by_bit (const char *pkeywords, const long long int num )        //根据比特位对相应字符取反
{
    char *back = NULL;
    int lens = strlen(pkeywords);
    //    printf("%d ", lens);
    back = (char*)malloc(lens + 1);
    memset(back, '\0', lens + 1);
    int i = 0;
    for(i = 0; i < lens ; i++)
    {
       long long  int is_bit_true = pow(2, i);
       if((is_bit_true&num) != 0)
       {
          back[i] = is_anti(pkeywords[i]);
       }
       else
       {
          back[i] = pkeywords[i];
       }
       
    }
    back[lens] = '\0';
    return back;
}		/* -----  end of function get_strings_by_bit  ----- */

    static char*
get_exact_whatis ( const char *content, const char *pkeywords )    //根据原文中出现的英文单词 确定大小写
{
    char *back = NULL;
    int lens = strlen(pkeywords);
    int counts = pow(2, lens);
    long long int i = 0;
    for(i = 0; i < counts ; i++)
    {
        char *strings = get_strings_by_bit(pkeywords, i);
        char *point = NULL;

/* Explicitly call the log4c cleanup routine */ 

        point =  strstr(content, strings);
        if( point != NULL)
        {
           back = (char*)malloc(lens + 1);
           strncpy(back, strings, lens);
           back[lens] = '\0';
           free(strings);
           return back;
        }
        free(strings);
        strings = NULL;
    }
    back = (char*)malloc(lens + 1);
    strncpy(back, pkeywords, lens);
    back[lens] = '\0';
   
    return back ;
}		/* -----  end of function get_exact_whatis  ----- */

    static char*
get_change_by_case (const char *content, const char *pkeywords)    //如果是中文，原样输出 英文 则查找其在原文中到底具体字符的大小写
{
    char *back = NULL;
    int lens = strlen(pkeywords);
    if((is_english(pkeywords)))
    {
        back = get_exact_whatis(content, pkeywords);
    }
    else
    {
        back = (char*)malloc(lens + 1);
        strncpy(back, pkeywords, lens);
        back[lens] = '\0';
    }
    return back;
}		/* -----  end of function get_change_by_case  ----- */


    static char*
get_instead ( char *pKeywords, int couts)
{
    int keywords_len = strlen(pKeywords);
    char *back = (char*)malloc(keywords_len + couts +1);
    memset(back, '\n', couts);
    strncpy(back + couts, pKeywords, keywords_len);  
    back[keywords_len + couts] = '\0';
    return back;
}	
		/* -----  end of function get_position_list  ----- */
    char* 
hightlight_title(char* title, char** pKeywords, size16_t* pkeySz, count_t num, int isBigSize)
{
    int i = 0;
    for(i = 0; i < num ; i++)
    {
//  char *p_keywords = get_keywords(pKeywords, pkeySz, i);

        char *p_change_by_case = get_keywords(pKeywords, pkeySz, i);
          
        char *p_keywords = get_change_by_case(title, p_change_by_case);

/*
        char *p_instead = get_instead(p_change_by_case, i + 1);

        title = strings_replace_with_free(title, p_change_by_case, p_instead);
*/
        char *p_instead = get_instead(p_keywords, i + 1);

        title = strings_replace_with_free(title, p_keywords, p_instead);

        free(p_change_by_case);
        free(p_keywords);
        free(p_instead);             
    }

    for(i = num - 1; i >= 0 ; i--)
    {
        char *p_change_by_case = get_keywords(pKeywords, pkeySz, i);
          
        char *p_keywords = get_change_by_case(title, p_change_by_case);


//        char *p_keywords = get_keywords(pKeywords, pkeySz, i);
        char *p_instead = get_instead(p_keywords, i + 1);     
        char *p_dest = NULL; 
        if(isBigSize == 0) 
        {
            p_dest = get_dest(p_keywords, 0);
        } 
        else
        {
            p_dest = get_dest(p_keywords, 1);

        }
        title = strings_replace_with_free(title, p_instead, p_dest); 
        free(p_change_by_case); 
        free(p_keywords);
        free(p_instead);
        free(p_dest);
    }
    return title;
}		/* -----  end of function hightlight_title  ----- */

    char*
get_summary (char* content, char** pKeywords, size16_t* pkeySz, count_t num)
{
    PositionListPoint* pointInfo = (PositionListPoint*)malloc(sizeof(PositionListPoint));
    pointInfo->head_point = NULL;
    pointInfo->last_point = NULL; 

    get_position_list(pointInfo, content, pKeywords, pkeySz, num);

    PositionStruct* position = get_position_struct(pointInfo->head_point, content);
    char* back = (char*)malloc(position->lens + 4);
    strncpy(back, position->position, position->lens);
    strncpy(back + position->lens, "...", 3);
    back[position->lens + 3] = '\0'; 
    if(pointInfo->head_point != NULL)
    {
        delete_position_list(pointInfo->head_point);
    }
    free(pointInfo);
    free(position);
    return  back;
}		/* -----  end of function get_summary  ----- */
