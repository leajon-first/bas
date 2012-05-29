/*
 * ======================================================================================
 *
 *       Filename:  getInputStruct.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  06/28/2011 11:20:00 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  kangle.wang (mn), wangkangluo1@gmail.com
 *        Company:  APE-TECH
 *
 * ======================================================================================
 */
#include       "stringsReplace.h"
#include       "inputsDeal.h"
#include       "getInputStruct.h"	
#include      <stdlib.h>
#include<string.h>
#include	<glib.h>

    static int 
is_position_legal (char* src, char* pointer)
{
    int back = 0;
    if(pointer == src)
    {
       back = 1;
    }
    else if(pointer[-1] == '&')
    {
       back = 1;
    }
    return back;
}		/* -----  end of function is_position_legal  ----- */

   static  char*
search_in_inputs (char* inputsStrings,  char* field )
{
    char* value = NULL;
    char* point_start;
    char* point_end;
    int lens = strlen(field)+1;
    char* needs_to_search = (char*)malloc(lens+1);
    strncpy(needs_to_search, field, lens);
    needs_to_search[lens-1] = '=';
    needs_to_search[lens] = '\0';
    if((point_start= strstr(inputsStrings, needs_to_search)) != NULL)
    {
        // if(point_start[-1] == '\0' || point_start[-1] == '&')
        if(is_position_legal(inputsStrings, point_start) == 1)
        {
            long long  int len = 0;
            if((point_end = strstr(point_start, "&")) != NULL)
            {
                len = (long long int)(point_end) - (long long int )(point_start) - lens;
            }
            else
            {
                len = strlen(point_start) -lens ;
            }
            if(len != 0)
            {
                value = (char*)malloc(len+1);
                strncpy(value, point_start+lens, len);
                value[len] = '\0';
            }
        }
    }
     
    free(needs_to_search); 
    return value;
}		/* -----  end of function search_in_inputs  ----- */


    int 
is_chinese ( char* head )
{
   int back = 0;
   if((head[3] == '%') && (head[6] == '%') && (head[1] == 0x45))
   {
     back = 1;
   }
    return back;
}		/* -----  end of function is_chinese  ----- */


    static char*
get_key (char* head)
{
    char* strings = (char*)malloc(3);
    strings[2] = '\0';

    char* strings_in_num = (char*)malloc(4);

    strncpy(strings, head+1, 2);
    strings_in_num[0] = strtol(strings, NULL, 16);

    strncpy(strings, head+4, 2);
    strings_in_num[1] = strtol(strings, NULL, 16);

    strncpy(strings, head+7, 2);
    strings_in_num[2] = strtol(strings, NULL, 16);
    strings_in_num[3] = '\0';

    free(strings);
    return strings_in_num;
}		/* -----  end of function getkey  ----- */

    char*
utf8_change (char* stringsInputs)
{
    char* strings ;
  //  char* strings = stringsInputs;

    if(stringsInputs != NULL)
    {
        strings = strings_replace_with_free(stringsInputs, "%20", " "); 
    }
    else
    {
        return NULL;
    }
   char* back = NULL;
   char* head = strings;
   if(strings != NULL)
   {
       GString * p_gstr_key = g_string_new(NULL);
       char* point ;
       back = strings;
       while((point = strstr(head, "%")) != NULL)
       {
           if(point != head)
           {
               int len = (long long int)(point) - (long long int)(head); 
               char* new = (char*)malloc(len + 1);
               strncpy(new, head, len);
               new[len] = '\0';
               g_string_sprintfa(p_gstr_key,"%s", new);
               free(new);
               head = head + len;
           }
   
          if(is_chinese(point))
          {
             char* chinese = get_key(point);
             g_string_sprintfa(p_gstr_key,"%s", chinese);
             free(chinese);
             head = head + 9;
          }
          else
          {
             char* is_head_out = head + 1;
             if(is_head_out != &strings[strlen(strings)])
             {
                 head = head + 1;
             }
          }
       }

       if(head != &strings[strlen(strings)])
       {
           g_string_sprintfa(p_gstr_key,"%s", head);
       }
       if(p_gstr_key->len != 0)
       {
           back = exchange_gstring_string(p_gstr_key);
       }
       else
       {
          g_string_free(p_gstr_key, TRUE); 
       }
   }
free(strings);
    return back;
}		/* -----  end of function utf8_change  ----- */

    InputStruct*
get_input_struct ( char* inputsStrings )
{
    InputStruct* input_struct = (InputStruct*)malloc(sizeof(InputStruct));
    input_struct->op = search_in_inputs(inputsStrings, "op");
    char* keywords = search_in_inputs(inputsStrings, "keywords"); 
    input_struct->keywords = utf8_change(keywords);
  //  free(keywords);

    char* category = search_in_inputs(inputsStrings, "category");
    input_struct->category = utf8_change(category);
 //    free(category);

    
    input_struct->orderby = search_in_inputs(inputsStrings, "orderby");
    input_struct->time = search_in_inputs(inputsStrings, "time");
    input_struct->pagesize = 10;
    char* pagesize = search_in_inputs(inputsStrings, "pagesize");
    if(pagesize != NULL)
    {
       int size = strtol(pagesize, NULL, 10);
       if( size < 100 && size > 0)
       {
          input_struct->pagesize = size;
       }
       free(pagesize);
    }

    input_struct->page = 1;
    char* page = search_in_inputs(inputsStrings, "page");
    if(page != NULL)
    {
       int size = strtol(page, NULL, 10);
       if(size < 100000 && size > 0)
       {
          input_struct->page = size;
       }
       free(page); 
    }
    return input_struct;
}		/* -----  end of function get_input_struct  ----- */

    void
free_input_struct ( InputStruct* inputsStrings)
{
    free(inputsStrings->op);
    free(inputsStrings->keywords);
    free(inputsStrings->category);
    free(inputsStrings->orderby);
    free(inputsStrings->time);
    free(inputsStrings);
    inputsStrings = NULL;
    return ;
}		/* -----  end of function free_input_struct  ----- */
