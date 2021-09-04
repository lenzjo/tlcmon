#*******************************************************************************
#                 Error Messages
#*******************************************************************************

ERR_LEADER        .DB "Err: ", NULL

ERR_GARBAGE       .DB "Huh?? Do not understand.. Try again..", CR, LF, NULL
ERR_WAR           .DB "Wrong number of Args.", CR, LF, NULL
ERR_INSADR        .DB "Invalid Start address.", CR, LF, NULL
ERR_ROM           .DB "Cannot change EEPROM.", CR, LF, NULL
ERR_LGN           .DB "Byte out of range (0-255).", CR, LF, NULL
ERR_INUADR        .DB "Invalid Until address.", CR, LF, NULL


ERR_DVN           .DB "Unknown device Name.", CR, LF, NULL
ERR_CHO           .DB "Channel is already open.", CR, LF, NULL
ERR_INDADR        .DB "Invalid Destination address.", CR, LF, NULL
ERR_INP           .DB "Blank line!!", CR, LF, NULL
ERR_TMA           .DB "Too many args.", CR, LF, NULL
ERR_INAR          .DB "Invalid Arg.", CR, LF, NULL
ERR_INFN          .DB "Invalid File Name (8.3).", CR, LF, NULL
ERR_INCN          .DB "Invalid Channel number (0-7).", CR, LF, NULL
ERR_INDDR         .DB "Invalid DDR (r, w or rw).", CR, LF, NULL
ERR_INNAN         .DB "Arg is not a number.", CR, LF, NULL
ERR_CHNOP         .DB "Not able to open a channel.", CR, LF, NULL


#*******************************************************************************
#                 System Messages
#*******************************************************************************

MonHeader         .DB 'TLCmon 6502 SBC by Clive Thomas (c) 2021 version '
                  .DB $30+VerMaj,'.',$30+VerMin,'.',$30+VerMnt
                  .DB CR, LF, CR, LF, NULL

MonPrompt         .DB 'tlc> ',NULL


#*******************************************************************************
#                 Print Functions
#*******************************************************************************

put_str           sta MSG_PTR
                  sty MSG_PTR+1
pr_str            ldy #$00
pes_loop          lda (MSG_PTR),y       # Get the next char in the string
                  beq pes_exit          #   NULL means the end

                  jsr put_c             #   Otherwise put the char
                  iny                   # Increment MSGPTR-lo
                  bne pes_loop          #   No roll-over? Loop back for next character

                  inc MSG_PTR+1         # MSGPTR-lo rolled over--carry hi byte
                  jmp pes_loop          # Now loop back

pes_exit          rts


pr_err_leader     >CPYMSPTR ERR_LEADER
                  jsr put_str
                  rts


pr_err_msg        pha
                  phy
                  jsr pr_err_leader     # Print 'Err: '
                  ply
                  pla
                  jsr put_str        # then the actual error msg
                  rts


#*******************************************************************************
#                 Print Error Messages
#*******************************************************************************

                  # Print Unkown Device Name Err msg
pr_err_nocmd      >CPYMSPTR ERR_GARBAGE
                  jsr pr_err_msg
                  rts


                  # Print Arg number Err msg
pr_err_arwr       >CPYMSPTR ERR_WAR
                  jsr pr_err_msg
                  rts


                  # Print Invalid Start Addr Err msg
pr_err_inadr      >CPYMSPTR ERR_INSADR
                  jsr pr_err_msg
                  rts


                  # Print Byte out of range Err msg
pr_err_rom        >CPYMSPTR ERR_ROM
                  jsr pr_err_msg
                  rts


                  # Print Byte out of range Err msg
pr_err_lgn        >CPYMSPTR ERR_LGN
                  jsr pr_err_msg
                  rts


                  # Print Invalid Until Addr Err msg
pr_err_inuadr     >CPYMSPTR ERR_INUADR
                  jsr pr_err_msg
                  rts

                  # Print Invalid Dest Addr Err msg
pr_err_indadr     >CPYMSPTR ERR_INDADR
                  jsr pr_err_msg
                  rts


#*******************************************************************************
#                 Print System Messages
#*******************************************************************************

                  # Print the Startup Banner
pr_MonHeader      >CPYMSPTR MonHeader
                  jsr put_str
                  rts


                  # Print the system prompt
pr_MonPrompt      >CPYMSPTR MonPrompt
                  jsr put_str
                  rts
