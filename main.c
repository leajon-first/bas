#include <stdio.h>  
#include <stdlib.h>  
#include <fcgiapp.h>
#include <sys/time.h>
#include <unistd.h>
#include <glib.h> 
#include "inputsDeal.h" 
#include        "config.h"

#include	<log4c.h>
#include        <sys/time.h>
#include        <unistd.h>
extern G_CONFIG* G;

 
#define fprintf(...) FCGX_FPrintF(request->out, __VA_ARGS__)  
#define get_param(KEY) FCGX_GetParam(KEY, request->envp)  

  
void handle_request(FCGX_Request *request, EggStartNeeds* eggStartNeeds) 
{ 
    char* input_strings = NULL;
    char* result_from_db = NULL;
    
    if ((input_strings = get_param("QUERY_STRING")) != NULL) 
    {  
       result_from_db = get_strings(input_strings, eggStartNeeds); 
    }

    fprintf("Content-Type: text/plain\r\n\r\n");
    
    if(result_from_db != NULL)
    {
        fprintf("%s",result_from_db);
        free(result_from_db);
        result_from_db = NULL;
    }

}  


    int 
main ( int argc, char *argv[] )
 {
     start_CONFIG();

    EggStartNeeds* egg_start_needs = egg_start();

#ifdef DEBUG
    char* result_from_db = NULL;
    if(argv[1] != NULL)
    {
        result_from_db = get_strings(argv[1], egg_start_needs);
    }
    if(result_from_db != NULL)
    {
        printf("%s",result_from_db);
        free(result_from_db);
        result_from_db = NULL;
    }
#else
    FCGX_Request request;  
    FCGX_Init();   
    FCGX_InitRequest(&request, 0, 0);  
    while (FCGX_Accept_r(&request) >= 0) 
    { 
        handle_request(&request, egg_start_needs); 
        FCGX_Finish_r(&request);  
    }
#endif
    egg_delete( egg_start_needs);

     free_CONFIG();

    return EXIT_SUCCESS;  
}























