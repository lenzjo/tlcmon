#*******************************************************************************
#                 Get a command line input
#*******************************************************************************

get_cmdline       stz BUFIDX            # CMDBUFF chr ptr
gecm_loop         jsr get_c             # Read a chr from STDIN
                  cmp #CR
                  beq gecm_exit         # If it's a CR then exit

                  cmp #BS
                  bne gecm_maxbuff      # If it's not a BackSpace go on

                  lda BUFIDX
                  beq gecm_loop

                  dec BUFIDX
                  jsr back_spc          # Do the BSread 0
                  jmp gecm_loop         #   and go get next chr

gecm_maxbuff      cpx #MAXCMD
                  bne gecm_svch         # If CMDBUFF not full jump

                  lda #BELL             # Else
                  jsr put_c             #   sound the bell
                  jmp gecm_loop         #   and go get next chr

gecm_svch         ldx BUFIDX
                  pha                   # save ch
                  cmp #$61              # Is it lowercase?
                  bcc gecm_uc           # No, so go save it
                  sbc #$20              # Yes, then convert to uppercase
gecm_uc           sta CMD_IBUF,x        # Save the char
                  pla                   # restore ch
                  jsr put_c             #   print it to STDOUT
                  inc BUFIDX
                  jmp gecm_loop         #   and go get next chr

gecm_exit         jsr pr_CRLF          # print a CRLF
                  lda #NULL
                  ldx BUFIDX
                  sta CMD_IBUF,x        # and store a NULL in the cmd buffer
                  cpx #$00              # Set flags on exit
                  rts


#====  Destructive BackSpace  ====
back_spc          jsr pr_BKSPC         # clear the ch from the scr.
                  jsr pr_SPC
                  jsr pr_BKSPC

                  ldx BUFIDX
                  lda #NULL
                  sta CMD_IBUF,x        # and put a null there
bs_exit           rts


#*******************************************************************************
#                 Break cmdline up into CMD and optional ARGs
#*******************************************************************************

parse_cmdline     stz ARGCNT
                  stz ARG1
                  stz ARG2
                  stz ARG3
                  stz ARG4

                  stz CMDXPTR

                  jsr get_cmd           # Is there a valid CMD present?
                  bcc pacm_bexit        #   No, go to err exit

                  jsr get_next_arg_ptr  # Is there an ARG1?
                  bcc pacm_gexit        #   No, go to clean exit

                  stx ARG1              #   Yes, then store index
                  inc ARGCNT            #   and increment arg counter

                  jsr get_next_arg_ptr  # Is there an ARG2?
                  bcc pacm_gexit        #   No, go to clean exit

                  stx ARG2              #   Yes, then store index
                  inc ARGCNT            #   and increment arg counter

                  jsr get_next_arg_ptr  # Is ther an ARG3?
                  bcc pacm_gexit        #   No, go to clean exit

                  stx ARG3              #   Yes, then store index
                  inc ARGCNT            #   and increment arg counter

                  jsr get_next_arg_ptr  # Is there an ARG4?
                  bcc pacm_gexit        #   No, go to clean exit

                  stx ARG4              #   Yes, then store index
                  inc ARGCNT            #   and increment arg counter
pacm_gexit        lda THISCMD           # Clean exit
                  sec                   # Set Carry flag
                  rts                   # and exit

pacm_bexit        lda THISCMD           # Error exit
                  clc                   # Clear Carry flag
                  rts                   # and exit



#*******************************************************************************
#                 Is there a cmd present?
#                   Success:	sec = Yes, y = ptr
#                   Faliure:	clc = No, y = NO_CMD
#*******************************************************************************

get_cmd           stz THISCMD           # Iniz cmd ptr
                  ldy #$00              # Iniz Cmd table ptr
                  ldx CMDXPTR           # Get start of cmd pos.
gc_loop           lda CMD_IBUF,x        # Get cmd line chr
                  beq gc_test_table     # found a NULL  - exit cmp loop

                  cmp #SPC              # Is it a space?
                  beq gc_test_table     #   Yes, go exit cmp loop

                  cmp VALID_CMDS,y      # is it in curr cmd word?
                  bne gc_next_cmd       #   No, go find next cmd word

                  inx                   #   inc ptrs
                  iny
                  bra gc_loop           #   and go test next chr
gc_test_table     lda VALID_CMDS,y      # Is it end of cmd?
                  bne gc_next_cmd       #   No, go find next cmd word

                  ldy THISCMD
                  sec                   # Found exit
                  rts

gc_next_cmd       ldx CMDXPTR           # Reset cmd-ptr
                  inc THISCMD           # inc to nxt cmd
                  lda THISCMD           # Get cmd ptr
                  >MULTAx8               #   mult by 8 - each cmd is max 7 chr long + NULL
                  tay                   #   transfer to y index
                  lda VALID_CMDS,y      # Is it end of VALID_CMDS table?
                  bne gc_loop           #   No, so go compare next cmd

gc_bad_exit       ldy #NO_CMD           # Cmd not Found exit
                  sty THISCMD
                  clc
                  rts


#*******************************************************************************
#                 Get a possible ARG ptr from CMDLINE
#                 On Exit:  Success:	sec
#                           Failure:	clc
#*******************************************************************************

get_next_arg_ptr  lda CMD_IBUF,x        # Get cmd line chr
                  beq gnap_bexit        # It's a NULL - EOL go exit

                  jsr find_next_SPC
                  bcc gnap_bexit

gnap_loop         lda CMD_IBUF,x        # Get cmd line chr
                  jsr is_seperator      # Is it a SPC, COMMA or COLON?
                  bcc gnap_isalpha      #   No, then go chk if it is AlphaNumeric?

                  inx
                  bra gnap_loop         #   Yes, then skip to next ch
gnap_isalpha      jsr is_alphanumeric   # Is it AlphaNumeric (A-Z, a-z, 0-9)?
                  bcs gnap_gexit        #   Yes, found 1st ch of ARG, go good exit

gnap_ishash       cmp #HASH             # Is it a # ?
                  beq gnap_gexit        #   Yes, go good exit

                  cmp #DOLLAR           # Is it a $ ?
                  beq gnap_gexit        #   Yes, go good exit

                  cmp #'?'              # Is it a ? ?
                  beq gnap_gexit        #   Yes, go good exit


gnap_bexit        clc                   # Anything that get's to here is an illegal ch
                  rts

gnap_gexit        sec                   # Good exit, ARG found
                  rts


find_next_SPC     lda CMD_IBUF,x						; Get cmd line chr
                  beq fis_bexit						; It's a NULL - EOL go exit

                  jsr is_seperator
                  bcs fis_gexit

                  inx
                  bra find_next_SPC
fis_bexit         clc
                  rts

fis_gexit         sec
                  rts





#*******************************************************************************
#                 Get SRC addr
#                 sec=Yes, clc=No
#*******************************************************************************

get_SRC_addr      jsr get_ASC_number    # Attempt to get a number
                  bcs gsa_mvnum         #   Yes, go move it

                  rts                   #   No, exit

gsa_mvnum         >CPYW HEX_RES,SRC     # Copy to SRC
                  sec
                  rts


#*******************************************************************************
#                 Get UNTIL addr
#                 sec=Yes, clc=No
#*******************************************************************************

get_UNTIL_addr    jsr get_ASC_number    # Attempt to get a number
                  bcs gua_mvnum         #   Yes, go move it

                  rts                   #   No, exit

gua_mvnum         >CPYW HEX_RES,UNTIL   # Copy to UNTIL
                  sec
                  rts


#*******************************************************************************
#                 Execute a command from the jumptable
#*******************************************************************************

exec_cmd          lda THISCMD           # Get the cmd index
                  clc
                  asl a                 # and double it
                  tax
                  jmp (CMD_JUMP_TABLE,x)




prline            ldx #0
                  ldy BUFIDX
prllp             lda CMD_IBUF,x
                  jsr put_c
                  inx
                  dey
                  bne prllp
                  rts

prasline          ldx #0
                  ldy #20
praslp            lda CMD_IBUF,x
                  jsr prbyte
                  jsr pr_SPC
                  inx
                  dey
                  bne praslp
                  rts
