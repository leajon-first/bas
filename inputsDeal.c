/*
 * =====================================================================================
 *
 *       Filename:  inputsDeal.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  06/27/2011 10:56:42 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  kangle.wang (mn), wangkangluo1@gmail.com
 *        Company:  APE-TECH
 *
 * =====================================================================================
 */

#include	"putInGstring.h"
#include        "getCollector.h"
#include	"getInputStruct.h"
#include         "inputsDeal.h"
#include         <string.h>
#include        <glib.h>
#include <sys/time.h>
#include <unistd.h>
#include        "config.h"
extern G_CONFIG* G;


    char* 
exchange_gstring_string (GString* gStr )
{
    char* back = (char*)malloc(gStr->len + 1);
    strncpy(back, gStr->str, gStr->len);
    back[gStr->len] = '\0';
    g_string_free(gStr, TRUE);
    return back;
}		/* -----  end of function exchange_gstring_string  ----- */


     EggStartNeeds*
egg_start (  )
{
    EggStartNeeds* egg_start_needs =(EggStartNeeds*)malloc(sizeof(EggStartNeeds));

    egg_start_needs->hDirectory_bas = eggDirectory_open("/ape/ImRoBot5/index/bas/k2d");
    egg_start_needs->hIndexReader_bas = eggIndexReader_open(egg_start_needs->hDirectory_bas);
    egg_start_needs->hIndexSearcher_bas = eggIndexSearcher_new(egg_start_needs->hIndexReader_bas);

    egg_start_needs->hDirectory_bbs = eggDirectory_open("/ape/ImRoBot5/index/bas/bbs");
    egg_start_needs->hIndexReader_bbs = eggIndexReader_open(egg_start_needs->hDirectory_bbs);
    egg_start_needs->hIndexSearcher_bbs = eggIndexSearcher_new(egg_start_needs->hIndexReader_bbs);

    return egg_start_needs;
}		/* -----  end of function egg_start  ----- */
 
    void
egg_delete ( EggStartNeeds* eggStartNeeds)
{
    eggIndexSearcher_delete(eggStartNeeds->hIndexSearcher_bas);
    eggIndexReader_close(eggStartNeeds->hIndexReader_bas);
    eggDirectory_close(eggStartNeeds->hDirectory_bas);

    eggIndexSearcher_delete(eggStartNeeds->hIndexSearcher_bbs);
    eggIndexReader_close(eggStartNeeds->hIndexReader_bbs);
    eggDirectory_close(eggStartNeeds->hDirectory_bbs);

    free(eggStartNeeds);
    eggStartNeeds = NULL;
    return ;
}		/* -----  end of function egg_delete  ----- */


    static int 
all_null ( char *strings )
{
    int back = 1;
    int lens = strlen(strings);
    int i = 0;
    for(i = 0; i < lens ; i++)
    {
       if(strings[i] != 0x20)
       {
          back = 0;
          break;
       } 
    }
    return back;
}		/* -----  end of function is_all_null  ----- */


    void
print_null (GString *p_gstr)
{
    g_string_sprintfa(p_gstr, "search_callback({          \"result\":0,          \"pageAct\":0,          \"useTime\":%d",0);
    g_string_sprintfa(p_gstr,",          \"body\":[{\"post_title\":\"\",\"post_summary\":\"\",\"post_url\":\"\",\"date\":\"\"}], \"err\":\"\"})"); 
    return ;
}		/* -----  end of function print_null  ----- */



    static  int 
is_legal (InputStruct* inputStruct)   //判断输入是否合法
{
    int back = 0;
    if(inputStruct->op != NULL && inputStruct->keywords != NULL && !all_null(inputStruct->keywords))
    {
        if(!strcmp(inputStruct->op, "search") || !strcmp(inputStruct->op, "bbs"))
            back = 1;
    }
    return back;
}		/* -----  end of function is_legal  ----- */


    static void
set_g_op (char *op)  //设置全局op
{
   int lens = strlen(op);
   G->op = (char*)malloc(lens + 1 );
   strncpy(G->op, op, lens);
   G->op[lens] = '\0';  
    return ;
}		/* -----  end of function set_g_op  ----- */

    char*
get_strings (char* inputStrings,EggStartNeeds* eggStartNeeds )
{
    char* back = NULL;
    InputStruct* input_struct = get_input_struct(inputStrings);    //获取输入
    GString * p_gstr = g_string_new(NULL);

   // if(input_struct->op != NULL && !strcmp(input_struct->op, "search") && !all_null(input_struct->keywords))
    if(is_legal(input_struct))
    {
        set_g_op(input_struct->op);
        struct timeval tv1, tv2;
        double sec = 0;
        gettimeofday(&tv1, 0);

        CollecotrAndHits* collector = NULL;                   
        if(!strcmp(input_struct->op, "search"))
        {
            collector = get_colloector ( input_struct, eggStartNeeds->hIndexSearcher_bas);   //获取容器
        }
        else
        {
            collector = get_colloector ( input_struct, eggStartNeeds->hIndexSearcher_bbs);   //获取容器
        }


        gettimeofday(&tv2, 0);
        sec = (double)(tv2.tv_sec - tv1.tv_sec) +  (double)(tv2.tv_usec - tv1.tv_usec) / 1000000;

        if (collector->cnt > 0)
        {
            if(!strcmp(input_struct->op, "search"))
            {
                put_in_gstring(collector, p_gstr, eggStartNeeds->hIndexReader_bas, input_struct, sec, input_struct->keywords);    //在容器内取数据
            }
            else
            {
                put_in_gstring(collector, p_gstr, eggStartNeeds->hIndexReader_bbs, input_struct, sec, input_struct->keywords);    //在容器内取数据
            }
        }
        else
        {
            print_null(p_gstr);
        }
        delete_colloector(collector);
    }
    else
    {
        print_null(p_gstr);
    }
    back = exchange_gstring_string (p_gstr );     //gstring数据转到char*

    free_input_struct(input_struct);
    return back;
}		/* -----  end of function get_strings  ----- */
