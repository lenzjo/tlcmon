#*******************************************************************************
#                 Table of cmds and their format
#*******************************************************************************

#====  Each cmd can be no more than 8 chr INCLUDING the NULL terminator  ====
#====  $		: prefix denotes a hex number otherwise it's a decimal number
#====  n		: a single digit 0-9 or letter A-F
#====  n..	: one or more digits
#====  x		: a single letter
#====  a		: a single letter or number
#====  ext	: xxx
#====  count,
#====  addr	: $n[n][n][n] | n[n..] in range 0-65535
#====  src,
#====  until,
#====  dest	: addr
#====  dbyte	: $n[n] | n[n..] in range 0-255


# COMMANDS FORMAT
VALID_CMDS
                  #==== Returns the DB at location addr
                  .DB "PEEK", NULL, NULL, NULL, NULL              # peek addr

                  #==== Writes DB at location addr
                  .DB "POKE", NULL, NULL, NULL, NULL              # poke addr,dbyte

                  #====  Display a hex dump of mem from addr for either count or 100 dbytes
                  .DB "DUMP", NULL, NULL, NULL, NULL              # dump addr[,count]

                  #====  Copy memory block src-until to dest
                  .DB "COPY", NULL, NULL, NULL, NULL              # copy src,until,dest

                  #====  Fill memory range src-until with DB
                  .DB "FILL", NULL, NULL, NULL, NULL              # fill src,until,dbyte

                  #====  Convert a number from one base to another
                  .DB "CONV", NULL, NULL, NULL, NULL              # hexnum [$]n[n..]

                  #====  Execute code at location addr
                  .DB "GO", NULL, NULL, NULL, NULL, NULL, NULL    # exec addr

                  #====  Dis-assemble memory from src to either until or 100 dbytes
                  .DB "DISM", NULL, NULL, NULL, NULL              # dism src[,until]

                  #====  Display help page
                  .DB "HELP", NULL, NULL, NULL, NULL              # help



                  .DB NULL                                        # Cmd-Table end-marker is a NULL

VALID_ARGCNT
                  .DB 1
                  .DB 1
                  .DB 2
                  .DB 3
                  .DB 3
                  .DB 2
                  .DB 1
                  .DB 2
                  .DB 1
