/*
 * =====================================================================================
 *
 *       Filename:  addQueryToEgg.h
 *
 *    Description:      
 *
 *        Version:  1.0
 *        Created:  06/28/2011 02:48:14 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  kangle.wang (mn), wangkangluo1@gmail.com
 *        Company:  APE-TECH
 *
 * =====================================================================================
 */

#ifndef ADD_QUERY_TO_EGG_H_
#define ADD_QUERY_TO_EGG_H_
#include <egg2/Egg2.h>
#include <scholar/ImLexAnalyzer.h>
#include <scholar/ImTokenList.h>
#include <scholar/ImCnLexAnalyzer.h>
#include <scholar/ImCwsLexAnalyzer.h>
#include "getInputStruct.h"

    HEGGQUERY
get_query (InputStruct* inputStruct);
    HEGGQUERY
add_query (HEGGQUERY eggQuery, char* field, char* key);

#endif
