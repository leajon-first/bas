/*
 * =====================================================================================
 *
 *       Filename:  getInputStruct.h
 *
 *    Description:      
 *
 *        Version:  1.0
 *        Created:  06/28/2011 11:20:05 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  kangle.wang (mn), wangkangluo1@gmail.com
 *        Company:  APE-TECH
 *
 * =====================================================================================
 */


#ifndef GET_INPUT_STRUCT_H_
#define GET_INPUT_STRUCT_H_

typedef struct _InputStruct InputStruct;

struct _InputStruct
{
    char* op;
    char* keywords;
    char* category;
    char* orderby;
    char* time;
    int pagesize;
    int page; 
};

    InputStruct*
get_input_struct ( char* inputsStrings );
    void
free_input_struct ( InputStruct* inputsStrings);
#endif
