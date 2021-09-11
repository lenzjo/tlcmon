

cmd_copy          lda ARGCNT            # How many args?
                  cmp #$03              # Expect three
                  beq cco_arg1          #   Yes, go get 'em

cco_bexit         jsr pr_err_arwr       #   No, Show err msg
                  rts                   #   and exit

cco_arg1          ldx ARG1              # Get ptr to Arg1
                  jsr get_SRC_addr      # Attempt to get the addr
                  bcs cco_arg2          #   Yes, go get arg2

                  jsr pr_err_inadr      #   No, show err msg
                  rts                   #   and exit

cco_arg2          ldx ARG2              # Get ptr to Arg2
                  jsr get_UNTIL_addr    # Attempt to get the addr
                  bcs cco_arg3          #   Yes, go get arg3

                  jsr pr_err_inuadr     #   No, show err msg
                  rts                   #   and exit

cco_arg3          ldx ARG3              # Get ptr to Arg3
                  jsr get_DEST_addr     # Attempt to get the addr
                  bcs copy_start        #   Yes, go do it

                  jsr pr_err_indadr     #   No, show err msg
                  rts                   #   and exit

#*******************************************************************************
# Alternate Entry Point: If SRC, UNTIL and DEST addr's are set up already
#*******************************************************************************

copy_start        lda DEST+1            # Test 1: dest=src
                  cmp SRC+1
                  bne cpydir            #   Not equal so go to next test
                  lda DEST
                  cmp SRC
                  bne cpydir            #   Not equal so go to next test

                  jsr pr_err_eqadr      # Error: they're equal!!
                  rts

cpydir            lda DEST+1            # Is dest > src?
                  cmp SRC+1
                  bcc copyFW            #   No, it's less so go to copyfw
                  lda DEST
                  cmp SRC
                  bcc copyFW            #   No, it's less so go to copyfw

                  lda UNTIL+1           # Is until >= dest?
                  cmp DEST+1
                  bcc copyFW            #   No, it's less so go to copyfw
                  lda UNTIL
                  cmp DEST
                  bcc copyFW            #   No, it's less so go to copyfw

                  # If you got here then both comparisons are true so copyBW

                  sec                   # how many bytes to copy?
                  lda UNTIL             # len = until-src
                  sbc SRC
                  sta LEN
                  lda UNTIL+1
                  sbc SRC+1
                  sta LEN+1

                  clc                   # Now add len to dest
                  lda DEST+1            # dest = dest+len
                  adc LEN+1
                  sta DEST+1
                  lda DEST
                  adc LEN
                  sta DEST

                  >INCW LEN

copyBW            lda LEN+1             # Is until < src?
                  bne cpbw_cpy          #   No, then go copy byte
                  lda LEN
                  beq cpbw_exit         #   Yes, then go exit

cpbw_cpy          lda (UNTIL)           # copy byte
                  sta (DEST)

                  >DECW UNTIL           # decrement the ptrs
                  >DECW DEST
                  >DECW LEN

                  bra copyBW            # Go copy the next byte
cpbw_exit         rts


copyFW            lda UNTIL+1           # Is until < src?
                  cmp SRC+1
                  bne cpfw_cpy          #   No, then go copy byte
                  lda UNTIL
                  cmp SRC
                  bcc cpfw_exit         #   Yes, then go exit

cpfw_cpy          lda (SRC)             # copy byte
                  sta (DEST)

                  >INCW SRC             # increment the ptrs
                  >INCW DEST
                  bra copyFW            # Go copy the next byte
cpfw_exit         rts

#-------------------------------------------------------------------------------
pr_addrs          jsr pr_SRC_addr
                  jsr pr_SPC
                  jsr pr_UNTIL_addr
                  jsr pr_SPC
                  jsr pr_DEST_addr
                  jsr pr_CRLF
                  rts
