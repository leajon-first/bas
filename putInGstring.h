/*
 * =====================================================================================
 *
 *       Filename:  putInGstring.h
 *
 *    Description:      
 *
 *        Version:  1.0
 *        Created:  06/28/2011 09:27:01 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  kangle.wang (mn), wangkangluo1@gmail.com
 *        Company:  APE-TECH
 *
 * =====================================================================================
 */


#ifndef PUT_IN_GSTRING_H_
#define PUT_IN_GSTRING_H_
#include        <glib.h>
#include        "getCollector.h"

    void
put_in_gstring ( CollecotrAndHits* collector, GString*  pGstr, HEGGINDEXREADER hIndexReader, InputStruct* inputStruct, float time, const char *keywords);
#endif
