/*
 * =====================================================================================
 *
 *       Filename:  getTimeStrings.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  06/28/2011 05:31:54 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  kangle.wang (mn), wangkangluo1@gmail.com
 *        Company:  APE-TECH
 *
 * =====================================================================================
 */
#include       <ctype.h>
#include       <string.h>
#include       <stdlib.h>
#include       <time.h>
#include       <stdio.h>
#include	"getTimeStrings.h"


static char* calu(int i)
{
    char* str =(char *)malloc(3) ;                                                                                                                                               
    //    memset(str, 0, 30);
    char b[3];
    if(i < 10)
    {
        sprintf(b, "%u", i);
        str[0] = '0';
        str[1] = '\0';
        strcat(str,b);        
    }
    else
    {
        sprintf(b,"%u", i);
        str[0] = '\0';
        strcat(str,b);
    }
    str[2] = '\0';
    return  str;
}



    void
getTimeString(char* times, char* pCharA, char* pCharB)         
{
    //char buf[2];
    time_t timep;        
    struct tm *p;        
    time(&timep);        
    p=gmtime(&timep);    

    sprintf(pCharA, "%u-", (1900+p->tm_year));
    // strcat(a,"af");   
    char*  c = calu((1+p->tm_mon));
    strcat(pCharA,c);    
    free(c);
    strcat(pCharA,"-");  
    char*  c1 = calu(p->tm_mday + 1);
    strcat(pCharA,c1);
    free(c1);

    if(!strcmp(times, "day")) 
    {   
        sprintf(pCharB, "%u-", (1900+p->tm_year));
        char* c2 = calu((1+p->tm_mon));
        strcat(pCharB,c2);        
        free(c2);
        strcat(pCharB,"-");       
        char* c3 = calu((p->tm_mday));
        strcat(pCharB,c3);        
        free(c3);
    }   
    if(!strcmp(times, "week"))
    {
        char* c4;
        char* c5;        
        sprintf(pCharB, "%u-", (1900+p->tm_year));
        if (p->tm_mday < 7 )      
            c4 = calu((p->tm_mon));   
        else
            c4 = calu((1+p->tm_mon)); 
        strcat(pCharB,c4);        
        free(c4);        
        strcat(pCharB,"-");       

        if ( p->tm_mday < 7 )     
            c5 = calu((p->tm_mday+30-7));
        else
            c5 = calu((p->tm_mday-7));
        strcat(pCharB,c5);        
        free(c5);        
    }
    if(!strcmp(times, "mons"))
    { 
        sprintf(pCharB, "%u-", (1900+p->tm_year));
        char*  c6 = calu((p->tm_mon));
        strcat(pCharB,c6);        
        free(c6);
        strcat(pCharB,"-");       
        char* c7 = calu((p->tm_mday));
        strcat(pCharB,c7);        
        free(c7);
    }
    if(!strcmp(times, "year"))
    {
        sprintf(pCharB, "%u-", (1900+p->tm_year-1));
        char* c8 = calu((1+p->tm_mon)); 
        strcat(pCharB,c8);        
        free(c8);
        strcat(pCharB,"-");       
        char* c9 = calu((p->tm_mday));
        strcat(pCharB,c9);        
        free(c9);
    }
    if(!strcmp(times, "alltime"))
    {
        strncpy(pCharB, "1974-01-01", 10);
        pCharB[10] = '\0';
        //strcat(pCharB, "1974-00-00");
    }
}

