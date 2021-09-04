

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
                  bcs copy_blk          #   Yes, go do it

                  jsr pr_err_indadr     #   No, show err msg
                  rts                   #   and exit

#*******************************************************************************
# Alternate Entry Point: If SRC, UNTIL and DEST addr's are set up already
#*******************************************************************************

copy_blk

                  rts
