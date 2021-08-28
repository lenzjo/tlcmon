#*******************************************************************************
#                 Poke Cmd: poke [h]|addr,byte : Write byte to location addr
#*******************************************************************************

cmd_poke          lda ARGCNT            # How many args?
                  cmp #$02              # Expect two
                  beq cpo_arg1          #   Yes, go get 'em

                  cmp #$01              # Only one?
                  beq cpo_ishelp        #   Yes, go test for help

cpo_bexit         jsr pr_err_arwr       #   No, Show err msg
                  rts                   #   and exit

cpo_ishelp        ldx ARG1              # Get ptr to Arg
                  lda CMD_IBUF,x        # and the ch there
                  cmp #HELPME           # Is it cmdhelp?
                  bne cpo_bexit         #   No, go err exit

                  jsr pr_hlp_poke       #   Yes, show help for this cmd
                  rts                   #   and exit

cpo_arg1          ldx ARG1              # Get ptr to Arg1
                  jsr get_SRC_addr      # Attempt to get the addr
                  bcc cpo_bexit2        #   No, go err exit

                  lda SRC+1             #   Yes, so test for ROM addr ($8100-$FFFF)
                  cmp #$82
                  bcc cpo_arg2          #   In RAM, so go poke it ;)

                  jsr pr_err_rom
                  rts

cpo_bexit2        jsr pr_err_inadr      #   No, show err msg
                  rts                   #   and exit

cpo_arg2          ldx ARG2              # Get ptr to Arg2
                  jsr get_BYTE          # Attempt to get a byte
                  bcs cpo_poke          #   Yes, go do poke

                  jsr pr_err_lgn        #   No, print err msg
                  rts                   #   and exit

cpo_poke          lda BYTE              # Finally, do the poke!
                  sta (SRC)
                  rts
