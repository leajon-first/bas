/*
 * =====================================================================================
 *
 *       Filename:  stringsReplace.h
 *
 *    Description:      
 *
 *        Version:  1.0
 *        Created:  07/03/2011 04:22:39 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  kangle.wang (mn), wangkangluo1@gmail.com
 *        Company:  APE-TECH
 *
 * =====================================================================================
 */

#ifndef STRINGS_REPLACE_H_
#define STRINGS_REPLACE_H_



    char* 
strings_replace_with_free (char* pStrings, char* pNeedReplace, char* pNew );

    char* 
strings_replace_without_free (char* pStrings, char* pNeedReplace, char* pNew );
/*-----------------------------------------------------------------------------
 * \brief    字符串替换
 * \param[in]    pStrings    输入字符串    
 *               pNeedReplace    需要被替换的字符串
 *               pNew     目的字符串
 *
 * \param[out]   
 * \return    char* p_back        
 * \free   yes
 *-----------------------------------------------------------------------------*/
    long int 
find_strings_count ( char* pStrings, char* pFindStrings );
/*-----------------------------------------------------------------------------
 * \brief    计算字符串中指定字符串出现的次数
 * \param[in]    pStrings    输入字符串
 *               pFindStrings    需要查找的字符串
 *
 * \param[out]   
 * \return    int n_counts   查询到的次数                                                                                                                                 
 * \free    no 
 *-----------------------------------------------------------------------------*/

    char* 
strings_replace(char *pInput, char *pOutput, char *pSrc, char *pDst);
/*-----------------------------------------------------------------------------
 * \brief     字符串替换
 * \param[in]    pInput    输入字符串     
 *               pOutput    输出字符串
 *               pSrc    被替换字符串
 *               pDst  目的字符串
 *
 * \param[out]   
 * \return    char* pOutput   输出字符串
 * \free   no 
 *-----------------------------------------------------------------------------*/

#endif
