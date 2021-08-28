################################################################################
#                 Help menu functions and messages
################################################################################

HLP_HDR		.DB 'Available Commands:', CR, LF, NULL

HLP_PEEK          .DB 'peek addr              - Returns byte at addr.', CR, LF, NULL
HLP_POKE          .DB 'poke addr,byte         - Store byte at addr.', CR, LF, NULL
HLP_DUMP          .DB 'dump addr,dest         - Show hex-dump from addr, for 128bytes or to dest.', CR, LF, NULL


HLP_COPY          .DB 'copy addr,until dest   - Copy blk from-until to dest.', CR, LF, NULL
HLP_FILL          .DB 'fill addr,until byte   - Fill blk from-until with byte.', CR, LF, NULL
HLP_HEXDEC        .DB 'conv [$|%]n[,$|%]      - Convert num from one base to another.', CR, LF, NULL
HLP_MEMED         .DB 'memed addr             - Line edit mem from addr.', CR, LF, NULL
HLP_GO            .DB 'go addr                - Run code starting at addr.', CR, LF, NULL
HLP_DISM          .DB 'dism addr,until        - Disassemble mem blk addr-until.', CR, LF, NULL
HLP_HELP          .DB 'help                   - Show this help page.', CR, LF, NULL

HLP_CMDH          .DB 'cmd ?                  - Shows one line help for cmd.', CR, LF, NULL


HELP_MSG_TABLE    .DW HLP_PEEK
                  .DW HLP_POKE
                  .DW HLP_DUMP

                  .DW HLP_COPY
                  .DW HLP_FILL
                  .DW HLP_HEXDEC

                  .DW HLP_MEMED
                  .DW HLP_GO
                  .DW HLP_DISM

                  .DW HLP_HELP


cmd_help          >CPYMSPTR HLP_HDR
                  jsr put_str

                  >CPYMSPTR HLP_PEEK
                  jsr put_str
                  >CPYMSPTR HLP_POKE
                  jsr put_str
                  >CPYMSPTR HLP_DUMP
                  jsr put_str

                  >CPYMSPTR HLP_COPY
                  jsr put_str
                  >CPYMSPTR HLP_FILL
                  jsr put_str
                  >CPYMSPTR HLP_HEXDEC
                  jsr put_str

                  >CPYMSPTR HLP_MEMED
                  jsr put_str
                  >CPYMSPTR HLP_GO
                  jsr put_str
                  >CPYMSPTR HLP_DISM
                  jsr put_str

                  >CPYMSPTR HLP_HELP
                  jsr put_str
                  jsr pr_CRLF
                  rts

#*******************************************************************************
#                 Print a cmd's help line if needed
#                   On Entry: THISCMD holds cmd's index#
#                   On Exit: sec = done, clc = not done
#*******************************************************************************

pr_cmd_help       ldx ARG1
                  lda CMD_IBUF,x        # Get Arg1's 1st ch
                  cmp #HELPME           # Is the help?
                  bne prcm_bexit        #   No, then go exit

                  lda THISCMD           # Get cmd index
                  clc
                  asl a                 # double
                  tax
                  lda HELP_MSG_TABLE,x
                  sta MSG_PTR
                  inx
                  lda HELP_MSG_TABLE,x
                  sta MSG_PTR+1
                  jsr pr_str
                  jsr pr_CRLF
                  sec
                  rts

prcm_bexit        clc
                  rts
