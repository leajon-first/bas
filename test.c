/*
 1;2305;0c* =====================================================================================
 1;2305;0c*
 *       Filename:  test.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/02/2011 10:09:57 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  kangle.wang (mn), wangkangluo1@gmail.com
 *        Company:  APE-TECH
 *
 * =====================================================================================
 */

   #include <egg2/Egg2.h>
   #include <scholar/ImLexAnalyzer.h>
   #include <scholar/ImTokenList.h>
   #include <scholar/ImCnLexAnalyzer.h>
   #include <scholar/ImCwsLexAnalyzer.h>
   int main()
{
   HEGGDIRECTORY hDirectory = eggDirectory_open("/ape/ImRoBot5/index/bas/bbs");
   HEGGINDEXREADER hIndexReader = eggIndexReader_open(hDirectory);
   HEGGINDEXSEARCHER hIndexSearcher = eggIndexSearcher_new(hIndexReader);
   HEGGQUERY h1, h2, h3;
   h1 = eggQuery_new_string("content_index", "kds", 3, ANALYZER_CWSLEX);
   h2 = eggQuery_new_string("title", "kds", 3, ANALYZER_CWSLEX);
   //:h3 = eggQuery_new_string("date", "2011-08-11", 10 , NULL);
   h3 = eggQuery_new_stringRange("date", "2011-08-11", "2011-08-12");
 //  h2 = eggQuery_new_string("content", "苹果", 6, ANALYZER_CWSLEX);
   // h2 = eggQuery_new_string("body", "some description", 16, p_la);
   // h3 = eggQuery_new_int32("price", 199);
   // h2 = eggQuery_and(h3, h2);
   h1 = eggQuery_or(h2, h1);
   h1 = eggQuery_and(h3, h1);

   // h3 = h2 = 0;
   HEGGTOPCOLLECTOR hTopCollector = eggTopCollector_new(0);
   int ret = eggIndexSearcher_search_with_query(hIndexSearcher, hTopCollector, h1);
   if (ret == EGG_TRUE)
   {
        eggTopCollector_normalized(hTopCollector, EGG_TOPSORT_SCORE);
        eggTopCollector_normalized(hTopCollector, EGG_TOPSORT_WEIGHT);
        eggIndexSearcher_filter(hIndexSearcher, hTopCollector, h3, 1);
        // eggTopCollector_normalized(hTopCollector, EGG_TOPSORT_NOT);
        HEGGSCOREDOC lp_score_doc = eggTopCollector_top_docs(hTopCollector);
        count_t cnt =  eggTopCollector_total_hits(hTopCollector);
        printf("have hit %u documents\n", cnt);
        
        if (cnt > 0)
        {
             printf("last document: id[%llu]\n", lp_score_doc[cnt-1].idDoc);
             HEGGDOCUMENT lp_eggDocument = EGG_NULL;
             eggIndexReader_get_document(hIndexReader,
                                lp_score_doc[cnt-1].idDoc, &lp_eggDocument);
             HEGGFIELD lp_field = eggDocument_get_field(lp_eggDocument, "date");
             unsigned len = 0;
             char *val = eggField_get_value(lp_field, &len);
             printf("%s\n", val);
             lp_field = 0;
             eggDocument_delete(lp_eggDocument);
        }
   }

   eggTopCollector_delete(hTopCollector);
   eggQuery_delete(h1);
   eggIndexSearcher_delete(hIndexSearcher);
   eggIndexReader_close(hIndexReader);
   eggDirectory_close(hDirectory);
}
