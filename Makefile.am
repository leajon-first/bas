AUTOMAKE_OPTIONS=foreign

bin_PROGRAMS= bas.fcgi	     

bas_fcgi_SOURCES= main.c\
      inputsDeal.c\
      getInputStruct.c\
      addQueryToEgg.c\
      getTimeStrings.c\
      getCollector.c\
      putInGstring.c\
      stringsReplace.c\
      hightlightAndSummary.c\
      findPositionStruct.c\
      pKeywords.c\
      config.c\
      findStringsWithoutCase.c\
      mylog.c 

bas_fcgi_CFLAGS=$(glib_CFLAGS) -g -Wall -O0 -pg -I/usr/local/include/spdindex/ -L/usr/log4c/lib/ -I/usr/log4c/include /usr/local/log4c/lib/liblog4c.so 
bas_fcgi_LDADD=-lfcgi -lscholar -legg2 -lspdindex


