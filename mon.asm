                  .CR 65c02
                  .TF tlcmon.bin,BIN
                  .LF tlcmon.list

###############################################################################
#
#	My monitor/os kernal for the modified RC6502 sbc
#
#	ACIA functionality                    - working 28/04/21 - v0.0.1
#	ACIA Int. & Int Vector Table          - working 29/04/21 - v0.0.2
# cmd input
#   v1 - cmd buff & edit                - working 24/08/21 - v0.0.3
#   v2 - parse cmds & args              - working 25/08/21 - v0.0.4
#   v3 - execute a cmd via table        - working 27/08/21 - v0.1.0
#
# Cmds:
#   peek                                - working 27/08/21 - v0.1.0
#   poke                                - working 27/08/21 - v0.1.0
#   dump                                - working 27/08/21 - v0.1.0
#   copy
#   fill
#   conv
#   memed
#   go
#   dism
#   help                                - working 27/08/21 - v0.1.0
#   xload
#   prog
#
###############################################################################

#=-=-=-= TLCmon Version number =-=-=-=
VerMaj            .EQ 0
VerMin            .EQ 0
VerMnt            .EQ 4


#=-=-=-= Memory starts & limits =-=-=-=
RAM_Base          .EQ $0000
RAM_End           .EQ RAM_Base + $7FFF

ROM_Base          .EQ $C000


###############################################################################
#                 Hardware constants
###############################################################################

#=-=-=-= 6850 ACIA - hardware & constants =-=-=-=

                  .IN devs/ACIA1_map.inc

                  .IN devs/ACIA1_con.inc

#=-=-=-= 6522 VIA - hardware =-=-=-=
                  .IN devs/VIA1_map.inc

###############################################################################
#                 Program constants
###############################################################################

#=-=-=-= ASCII codes =-=-=-=

                  .IN misc/ascii_con.inc

#=-=-=-= ASCII codes =-=-=-=



#=-=-=-= My Macros =-=-=-=
                  .IN misc/macros.inc

MAXCMD            .EQ $7F               # Maximum cmdline length
NO_CMD            .EQ $

ISHEX             .EQ $00
ISDEC             .EQ $01

###############################################################################
#                 Zero Page Registers
###############################################################################

#=-=-=-=  Interrupt Vectors  =-=-=-=

R01_PTR           .EQ $20

VEC_RTABLE        .EQ R01_PTR

NMI_VEC0          .EQ R01_PTR           # nmi vector 0
NMI_VEC1          .EQ R01_PTR+2         # nmi vector 1

IRQ_VEC0          .EQ R01_PTR+4         # irq vector 0
IRQ_VEC1          .EQ R01_PTR+6         # irq vector 1
IRQ_VEC2          .EQ R01_PTR+8         # irq vector 2
IRQ_VEC3          .EQ R01_PTR+10        # irq vector 3
IRQ_VEC4          .EQ R01_PTR+12        # irq vector 4

USER_VECTOR       .EQ R01_PTR+14


#=-=-=-= Buffer head/tail Ptrs =-=-=-=

BIOS_PG0           .EQ $80

#=-=-=-= 2691 IRQ handler pointers and status =-=-=-=
UART_ICNT         .EQ BIOS_PG0+01       # Input buffer count
UART_IHEAD        .EQ BIOS_PG0+02       # Input buffer head pointer
UART_ITAIL        .EQ BIOS_PG0+03       # Input buffer tail pointer

UART_OCNT         .EQ BIOS_PG0+04       # Output buffer count
UART_OHEAD        .EQ BIOS_PG0+05       # Output buffer head pointer
UART_OTAIL        .EQ BIOS_PG0+06       # Output buffer tail pointer

#=-=-=-= Keyboard Buffer Pointers =-=-=-=
KYBD_ICNT         .EQ BIOS_PG0+07       # Character count in buffer
KYBD_IHEAD        .EQ BIOS_PG0+08       # Rx head ptr
KYBD_ITAIL        .EQ BIOS_PG0+09       # Rx tail ptr

#=-=-=-= Misc Stuff =-=-=-=
ACIA_ControlRam   .EQ BIOS_PG0+10
ACIA_StatusRam    .EQ BIOS_PG0+11



PGZERO_ST         .EQ BIOS_PG0+14

#=-=-=-= 16-bit C02 Monitor variables required access for BIOS =-=-=-=
INDEXL            .EQ PGZERO_ST         # Index for address - multiple routines
INDEXH            .EQ PGZERO_ST+1

MSG_PTR           .EQ PGZERO_ST+2       # Message pointer for I/O functions (2)


#=-=-=-= RTC stuff =-=-=-=
JIFFIES           .EQ PGZERO_ST+4       # 100ths of seconds
SECONDS           .EQ PGZERO_ST+5       # cnt of secs.
MINUTES           .EQ PGZERO_ST+6       # cnt of mins.
HOURS             .EQ PGZERO_ST+7       # cnt of hours
SHOWTIME          .EQ PGZERO_ST+8       # display time flag

BUFLEN            .EQ PGZERO_ST+9
BUFIDX            .EQ PGZERO_ST+10


#=-=-=-= CMD_IBUFF regs =-=-=-=
THISCMD           .EQ PGZERO_ST+11      # cmd index ptr
ARG1              .EQ PGZERO_ST+12      # ptr to 1st arg on cmd line
ARG2              .EQ PGZERO_ST+13      # ptr to 2nd arg on cmd line
ARG3              .EQ PGZERO_ST+14      # ptr to 3rd arg on cmd line
ARG4              .EQ PGZERO_ST+15      # ptr to 4th arg on cmd line
ARGCNT            .EQ PGZERO_ST+16      # how many args on cmd line
CMDXPTR           .EQ PGZERO_ST+17      # Holds the x ptr for the CMD_IBUFF


ASCBYTE           .EQ PGZERO_ST+20      # 2 BYTEs
HEX_RES           .EQ PGZERO_ST+22      # 2 BYTEs for hex results
TEMP              .EQ PGZERO_ST+24      # 2 BYTEs
BYTECNT           .EQ PGZERO_ST+26
NUMBASE           .EQ PGZERO_ST+26


SRC               .EQ PGZERO_ST+40
UNTIL             .EQ PGZERO_ST+42
DEST              .EQ PGZERO_ST+44
BYTE              .EQ PGZERO_ST+46

###############################################################################
#                 Buffers
###############################################################################

#=-=-=-= UART =-=-=-=
UART_IBUF         .EQ $0200             # Console Input Buffer - 128 bytes
UART_OBUF         .EQ $0280             # Console Output Buffer - 128 bytes

#=-=-=-= KYBD =-=-=-=
KYBD_IBUF         .EQ $300              # KYBD Input Buffer - 128 bytes

#=-=-=-= CMD LINES =-=-=-=
CMD_IBUF          .EQ $380              # cmdline buffer

ASCIIDUMP         .EQ $400              # text formatting area for dump cmd.

###############################################################################
###############################################################################
#                 Start of rom - (Using only top half of 32K EEPROM)
###############################################################################
                  .OR $8000
                  .DW $1234

###############################################################################
#                 Start of TLCmon
###############################################################################

                  .NO ROM_Base

RESET_Ptr         cld                   # Clear decimal mode
                  sei                   # and disable interrupts
                  ldx #$00
pgz_lp            stz $00,x             # clr page zero
                  dex
                  bne pgz_lp            # loop til done
                  dex                   # $ff - ready for stack ptr
                  txs

                  jsr iniz_intvec       # Setup interrupt vector table
                  jsr inizACIA          # Setup uart

                  cli                   # clear interrupts

                  jsr pr_MonHeader     # Show Header

cmd_loop          jsr pr_MonPrompt     # Show Prompt

                  jsr get_cmdline       # Read in a cmd line
                  beq cmd_loop          # If empty then retry

                  jsr parse_cmdline     # Is it a valid cmd?
                  bcs cmd_doit          #   Yes, then go do it.

cmd_bad           jsr pr_err_nocmd      #   Else, show error msg
                  bra cmd_loop          #   and go retry.

cmd_doit
                  jsr pr_cmd_help       # Was 1st arg = help?
                  bcs cmd_loop          #   Yes, then go get next cmd

                  jsr exec_cmd          # Execute the cmd line

                  bra cmd_loop          # then go get the next cmd line.


###############################################################################
#                 Command line stuff
###############################################################################

                  .IN cmdline/cmds_fun.inc


                  .IN misc/ch_fun.inc


###############################################################################
#                 ACIA stuff
###############################################################################

                  .IN devs/ACIA1_fun.inc


#-------------------------------------------------------------------------------
# Send a character to output (character in A)
#-------------------------------------------------------------------------------

put_c             jsr ACIA1_put_c
                  rts


#-------------------------------------------------------------------------------
# Wait until at least one character is available in the input queue, and return
# the first character in A
#-------------------------------------------------------------------------------

get_c             jsr ACIA1_get_c
                  rts


#                  .IN misc/output_fun.inc

###############################################################################
#               Interrupt stuff
###############################################################################

                  .IN misc/interrupt_fun.inc


                  .IN misc/interrupt_table.inc


###############################################################################
#               Device ISR stuff
###############################################################################

                  .IN devs/ACIA1_int_fun.inc


###############################################################################
#               Character tests
###############################################################################

                .IN misc/ch_tests.inc


###############################################################################
#                 Print various characters
###############################################################################

pr_CRLF           lda #CR
                  jsr put_c
                  lda #LF
                  jmp put_c


pr_SPC            lda #SPC
                  jmp put_c


#====  Print X Spaces  ====
pr_XSPC           lda #SPC
                  jsr put_c
                  dex
                  bne pr_XSPC

                  rts


pr_STAR           lda #STAR
                  jmp put_c


pr_IBUF           >CPYMSPTR CMD_IBUF
                  jmp put_str


pr_BKSPC          lda #BS
                  jmp put_c


pr_EQUALS         lda #EQUALS
                  jmp put_c


pr_DOLLAR         lda #DOLLAR
                  jmp put_c


pr_COLON          lda #COLON
                  jmp put_c



# Print system messages stuff

                  .IN misc/sys_msgs.inc


                  .IN misc/pr_conv.inc


###############################################################################
#                 COMMANDS functions
###############################################################################


                  .IN cmds/cmd_peek.inc
                  .IN cmds/cmd_poke.inc
                  .IN cmds/cmd_dump.inc

                  .IN cmds/cmd_help.inc


cmd_copy          rts
cmd_fill          rts
cmd_hexdec        rts
cmd_memed         rts
cmd_go            rts
cmd_dism          rts


###############################################################################
#                 System Data Tables and other config stuff
###############################################################################

                  .IN cmdline/cmds_table.inc


                  .IN cmdline/cmds_jmp_table.inc


###############################################################################
#                 System vectors
###############################################################################

                  .NO $FFFA
                  .DW NMI_vector        # NMI vector
                  .DW RESET_Ptr         # RESET vector
                  .DW IRQ_vector        # IRQ vector
