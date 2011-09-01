/*
 * =====================================================================================
 *
 *       Filename:  addQueryToEgg.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  06/28/2011 02:48:08 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  kangle.wang (mn), wangkangluo1@gmail.com
 *        Company:  APE-TECH
 *
 * =====================================================================================
 */


#include	"addQueryToEgg.h"
#include        "stdio.h"
#include       <time.h>
#include	<string.h>

#include        "config.h"

extern G_CONFIG* G;


    static char*
addSpace(char* str,int len);


    static char*
addSpace(char* str,int len)
{
    int i;               
    int a = strlen(str); 
    char* str1 = (char *) malloc(len+1);
    str1 = strcpy(str1,str);  
    for(i = a;i < len; i++)   
    {
        str1[i] = ' ';   
    }
    str1[len] = '\0';    
    return str1;         
}
    
    HEGGQUERY
add_query (HEGGQUERY eggQuery, char* field, char* key)
{
    HEGGQUERY new_query = NULL;

    if(!strcmp(field, "keywords"))
    {
        new_query = eggQuery_new_string("title", key,strlen(key),ANALYZER_CWSLEX);
        HEGGQUERY new_query_two = NULL;
        if(!strcmp(G->op, "search"))
        {

            new_query_two = eggQuery_new_string("content", key,strlen(key),ANALYZER_CWSLEX);
        }
        else
        {
            new_query_two = eggQuery_new_string("content_index", key,strlen(key),ANALYZER_CWSLEX);
        }

        new_query = eggQuery_or(new_query,new_query_two);
    }

 
    if(!strcmp(field, "category"))
    {

        new_query = eggQuery_new_string("category", key, strlen(key), NULL);

/*
        if(!strcmp(G->op, "search"))
        {
            // char* key_with_space = addSpace(key,30);
            new_query = eggQuery_new_string("category", key, strlen(key), NULL);
           // free(key_with_space);        
        }
        else
        {
            new_query = eggQuery_new_string("category", key, strlen(key), NULL);
        }
*/
    }


    if(new_query != NULL)  
    {
        if(eggQuery == NULL) 
        {
            eggQuery = new_query;  
        }
        else
        {
            eggQuery = eggQuery_and(eggQuery,new_query);

        }
    }
    return eggQuery;
}		/* -----  end of function get_queryadd_query  ----- */

    HEGGQUERY
get_query (InputStruct* inputStruct)
{
    HEGGQUERY egg_query = NULL;
    if(inputStruct->keywords != NULL)
    {
        egg_query = add_query(egg_query, "keywords", inputStruct->keywords);
    }
    if(inputStruct->category != NULL)
    {
        egg_query = add_query(egg_query, "category", inputStruct->category);
    }
    return egg_query;
}		/* -----  end of function get_query  ----- */

