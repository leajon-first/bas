/*
 * =====================================================================================
 *
 *       Filename:  stringsReplace.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/03/2011 04:21:52 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  kangle.wang (mn), wangkangluo1@gmail.com
 *        Company:  APE-TECH
 *
 * =====================================================================================
 */

#include <stdlib.h>
#include <string.h>
#include "stringsReplace.h"


    char*
strings_replace_with_free (char* pStrings, char* pNeedReplace, char* pNew )
{
    char* strings = strings_replace_without_free (pStrings, pNeedReplace, pNew );
    free(pStrings);
    pStrings = NULL;
    return strings;
}

    char*
strings_replace_without_free (char* pStrings, char* pNeedReplace, char* pNew )
{
    long int counts = find_strings_count(pStrings, pNeedReplace);
    int len = strlen(pNew) - strlen(pNeedReplace);
    int strings_len = strlen(pStrings);
    long int malloc_len = strings_len + counts*len + 1;
    char* p_back = (char*)malloc(malloc_len);
    p_back[malloc_len -1] = '\0';
    p_back = strings_replace(pStrings, p_back, pNeedReplace, pNew);
    return p_back;
} /* ----- end of function strings_replace ----- */

    long int
find_strings_count ( char* pStrings, char* pFindStrings )
{
    long int n_counts = 0;
    if(pStrings != NULL && pFindStrings && strcmp(pStrings, "") && strcmp(pFindStrings, ""))
    {
        long int n_lengs = strlen(pFindStrings);
        char* p_head = pStrings ;
        char* p_point = pStrings;
        while(1)
        {
            p_point = strstr(p_head, pFindStrings);
            if(p_point != NULL)
            {
                n_counts++;
            }
            else
            {
                break;
            }
            p_head = p_point + n_lengs;
        }
    }
    return n_counts;
} /* ----- end of function calu_strings_num ----- */

    char*
strings_replace(char *pInput, char *pOutput, char *pSrc, char *pDst)
{
    char* point = NULL;
    char* input_head = pInput;
    char* output_head = pOutput;
    long long int lens = 0;
    int src_lens = strlen(pSrc);
    int dst_lens = strlen(pDst);
    while(1)
    {
        point = strstr(input_head, pSrc);
        if(point != NULL)
        {
            lens =(long long int)(point) - (long long int)(input_head);
        }
        else
        {
            int len = (int)(&pInput[strlen(pInput)] - input_head);
            memcpy(output_head, input_head , len);
            break;
        }
        memcpy(output_head, input_head, lens);
        input_head = input_head + lens + src_lens;
        output_head = output_head + lens;
        memcpy(output_head, pDst, dst_lens);
        output_head = output_head + dst_lens;
    }
    return pOutput;
}


