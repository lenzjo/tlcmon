#*******************************************************************************
#                 Peek Cmd: peek h|addr : Show byte at addr
#*******************************************************************************


cmd_peek          lda ARGCNT            # How many args?
                  cmp #$01              # Expect only one
                  beq cpe_args          #   Yes, go get 'em

                  jsr pr_err_arwr       #   No, Show err msg
                  rts                   #   and exit

cpe_args          ldx ARG1              # Get ptr to Arg
                  lda CMD_IBUF,x        # and the ch there
                  cmp #HELPME           # Is it cmdhelp?
                  bne cpe_num           #   No, go test for an addr

                  jsr pr_hlp_peek       #   Yes, show help for this cmd
                  rts                   #   and exit

cpe_num           jsr get_SRC_addr      # Attempt to get the addr
                  bcs cpe_peek          #   Yes, go do cmd

cpe_bexit         jsr pr_err_inadr      #   No, show err msg
                  rts                   #   and exit

cpe_peek          jsr pr_SRC_addr       # Print SRC addr
                  jsr pr_SPC
                  jsr pr_EQUALS
                  jsr pr_SPC
                  jsr pr_DOLLAR
                  lda (SRC)						; Get data
                  jsr pr_HEX_byte
                  jsr pr_CRLF
                  rts