/*
 * =====================================================================================
 *
 *       Filename:  inputsDeal.h
 *
 *    Description:      
 *
 *        Version:  1.0
 *        Created:  06/27/2011 10:56:50 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  kangle.wang (mn), wangkangluo1@gmail.com
 *        Company:  APE-TECH
 *
 * =====================================================================================
 */


#ifndef INPUTS_DEAL_H_
#define INPUTS_DEAL_H_

#include <egg2/Egg2.h>
#include <scholar/ImLexAnalyzer.h>
#include <scholar/ImTokenList.h>
#include <scholar/ImCnLexAnalyzer.h>
#include <scholar/ImCwsLexAnalyzer.h>



typedef struct _EggStartNeeds EggStartNeeds;

   struct _EggStartNeeds
{
    HEGGDIRECTORY hDirectory_bas;
    HEGGINDEXREADER hIndexReader_bas;
    HEGGINDEXSEARCHER hIndexSearcher_bas;

    HEGGDIRECTORY hDirectory_bbs;
    HEGGINDEXREADER hIndexReader_bbs;
    HEGGINDEXSEARCHER hIndexSearcher_bbs;
   
};
    char* 
exchange_gstring_string (GString* gStr );

     EggStartNeeds*
egg_start (  );

    void
egg_delete ( EggStartNeeds* eggStartNeeds);

    char*
get_strings (char* inputStrings,EggStartNeeds* eggStartNeeds );
#endif
