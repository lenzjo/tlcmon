################################################################################
#                 Help menu functions and messages
################################################################################

HLP_HDR		.DB 'Available Commands:', CR, LF, NULL

HLP_PEEK          .DB 'peek addr              - Returns byte at addr.', CR, LF, NULL
HLP_POKE          .DB 'poke addr,byte         - Store byte at addr.', CR, LF, NULL
HLP_DUMP          .DB 'dump addr,dest         - Show hex-dump from addr, for 128bytes or to dest.', CR, LF, NULL


HLP_COPY          .DB 'copy addr,until dest   - Copy blk from-until to dest.', CR, LF, NULL
HLP_FILL          .DB 'fill addr,until byte   - Fill blk from-until with byte.', CR, LF, NULL
HLP_HEXDEC        .DB 'hexdec [$]n[n..]       - Convert num from one base to another.', CR, LF, NULL
HLP_MEMED         .DB 'memed addr             - Line edit mem from addr.', CR, LF, NULL
HLP_EXEC          .DB 'exec addr              - Run code starting at addr.', CR, LF, NULL
HLP_DISM          .DB 'dism addr,until        - Disassemble mem blk addr-until.', CR, LF, NULL
HLP_HELP          .DB 'help                   - Show this help page.', CR, LF, NULL

HLP_CMDH          .DB 'cmd ?                  - Shows help for cmd.', CR, LF, NULL


pr_hlp_hdr        >CPYMSPTR HLP_HDR
                  jsr put_str
                  rts


pr_hlp_peek       >CPYMSPTR HLP_PEEK
                  jsr put_str
                  rts


pr_hlp_poke       >CPYMSPTR HLP_POKE
                  jsr put_str
                  rts


pr_hlp_dump       >CPYMSPTR HLP_DUMP
                  jsr put_str
                  rts
