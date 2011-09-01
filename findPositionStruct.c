/*
 * =====================================================================================
 *
 *       Filename:  findPositionStruct.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/04/2011 01:17:50 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  kangle.wang (mn), wangkangluo1@gmail.com
 *        Company:  APE-TECH
 *
 * =====================================================================================
 */


#include	"findPositionStruct.h"

    static int
is_chinese ( char val )
{

    //sprintf(str,"%s",val);
    int result = val & 0xf0;
    if(result == 224)
    {
        return 1;
    }
    else
    {
        return 0;
    }

return 1;
}		/* -----  end of function is_chinese  ----- */

    static int 
get_utf_strings (char* start, char* content, int isFront)
{
if(isFront == 1)
{
  long long int start_lens = strlen(start);
  if(start_lens < 210)
  {
      return 0;
  }
  else
  {
      if(is_chinese(start[209]))
      {
          return 209;
      } 
      if(is_chinese(start[208]))
      {
          return 208;
      }
      if(is_chinese(start[207]))
      {
          return 207;
      }
      return 210;
  } 
}
else
{
    long long int lens = strlen(content);
    char* point;
    point = &content[lens] - 209;
    if(is_chinese(point[0]))
    {
        return 209;
    }
    point = &content[lens] - 208;
    if(is_chinese(point[0]))
    {
        return 208;
    } 
    point = &content[lens] - 207;
    if(is_chinese(point[0]))
    {
        return 207;
    }
    return 210;
}
}		/* -----  end of function get_utf_strings  ----- */

    int 
calu_list_lens (  PositionList* head )
{
    int counts = 0;
    PositionList* point = head;
    while(point != NULL)
    {
        point = point->next;
        counts++;
    } 
    return counts;
}		/* -----  end of function calu_list_lens  ----- */


    static char*
get_precise_position_char (PositionList* head, int num)
{
    PositionList* point = head; 
    int i = 0;
    for(i = 0; i < num ; i++)
    {
        point = point->next;
    }
    return point->position;
}		/* -----  end of function get_Precise_position  ----- */

    static int
get_precise_position_lens (PositionList* head, int num)
{
    PositionList* point = head; 
    int i = 0;
    for(i = 0; i < num ; i++)
    {
        point = point->next;
    }
    return point->lens;
}		/* -----  end of function get_Precise_position  ----- */


    static void
get_result (PositionStruct* positionStruct, PositionList* head, char* content)
{
    char* point = head->position;
    int i = 0;
    long long int lens_between_max = -1;
    int lens = calu_list_lens(head);
    for(i = 0; i < lens - 1 ; i++)
    {
       char* point_next =  get_precise_position_char (head, i + 1 );
       char* point_this =  get_precise_position_char (head, i);       
       long long int lens_between = (long long int)(point_next) - (long long int)(point_this) - get_precise_position_lens(head, i);
       if(lens_between_max == -1)
       {
           lens_between_max = lens_between;
           point = point_this;
       }
       else
       {
           if(lens_between < lens_between_max)
           {
               lens_between_max = lens_between;
               point = point_this;
           }
       }      
    }
    positionStruct->position = point;

    positionStruct->lens = get_utf_strings(positionStruct->position, content, 1);
    if(positionStruct->lens == 0)
    {
        int content_lens = strlen(content);
        if(content_lens <= 250 )
        {
            positionStruct->position = content;
            positionStruct->lens = get_utf_strings(positionStruct->position, content, 1);
        }
        else
        {
            positionStruct->lens = get_utf_strings(positionStruct->position, content, 0);
            long long int point_position = (long long int)(point) - (long long int)(content) - positionStruct->lens;
            positionStruct->position = content + point_position + strlen(positionStruct->position);
            positionStruct->lens = positionStruct->lens - 2 ;
        }
    }
    return ;
}		/* -----  end of function get_result  ----- */

    PositionStruct*
 get_position_struct(PositionList* head, char* content)
{
    PositionStruct* position_struct = (PositionStruct*)malloc(sizeof(PositionStruct));
    if(head == NULL)
    {
        position_struct->position = content;
        position_struct->lens = get_utf_strings(content, content, 1);
    }
    else
    {
        get_result(position_struct, head, content); 
    }
    return position_struct;
}
