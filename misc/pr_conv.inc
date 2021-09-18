################################################################################
#                 Print numbers from CMD_IBUF
################################################################################

;====  Print byte in A from ASCBYTE ====
pr_HEX_byte       phy
                  jsr byt_2_ASC         # Convert byte to ASCII
                  lda ASCBYTE           # get Hi-nyb
                  jsr put_c             # and print it
                  lda ASCBYTE+1         # Get Lo-nyb
                  jsr put_c             # and print it
                  ply
                  rts


;====  Convert a byte to an ASCII char in ASCBYTE & ASCBYTE+1  ====
byt_2_ASC         pha                   # Save byte
                  lsr a
                  lsr a
                  lsr a
                  lsr a                 # move to lower nybble
                  tay
                  lda HEXNUM,y
                  sta ASCBYTE           # and store it
                  pla                   # get the byte back
                  and #$0F              # get lower nybble
                  tay
                  lda HEXNUM,y
                  sta ASCBYTE+1         # and store it
                  rts


HEXNUM            .DB '0123456789ABCDEF'


################################################################################
#                 Get numbers from CMD_IBUF
################################################################################

#*******************************************************************************
#                 Get an ASCII number from the cmdline
#                 On Exit:
#                   Result in HEX_RES and HEX_RES+1
#                   sec = Success, clc = Failure
#*******************************************************************************

get_ASC_number    lda CMD_IBUF,x        # Get a chr
                  cmp #DOLLAR           # Is it HEX?
                  beq gan_getHEX        #   Yes, go get a Hex num

                  jmp get_ASC_dec       #   No, go get a DEC number

gan_getHEX        jmp get_ASC_hex


********************************************************************************
#                 Convert an ASCII decimal number on the cmd line to binary
#                 On Exit:
#                   Result in HEX_RES and HEX_RES+1
#                   sec = Success, clc = Failure
#*******************************************************************************

get_ASC_dec       stz HEX_RES           # Clear result regs
                  stz HEX_RES+1
                  dex

gad_next_digit    inx
                  lda CMD_IBUF,x        # Get a chr
                  cmp #SPC              # End of #?
                  beq gad_gexit         #   Yes, then exit

                  cmp #COMMA            # End of #?
                  beq gad_gexit         #   Yes, then exit

                  cmp #NULL             # End of cmd?
                  beq gad_gexit         #   Yes, then exit

                  jsr is_numeric        # Is it numeric?
                  bcc gad_bexit         #   No, then err exit

                  and #$0F              # Convert to binary
                  jsr multx10           # mult HEX_RES x 10

                  clc
                  adc HEX_RES           # and add new number to HEX_RES
                  sta HEX_RES
                  bcc gad_next_digit    # If no carry go get next digit

                  inc HEX_RES+1         # There's a carry so add 1 to hi-byte
                  jmp gad_next_digit

gad_gexit         sec                   # sec = success
                  rts

gad_bexit         clc                   # clc = failure
                  rts


#*******************************************************************************
#                 Multiply HEX_RES by 10
#*******************************************************************************

multx10           php
                  pha
                  asl HEX_RES           # Mult by 2
                  rol HEX_RES+1
                  lda HEX_RES+1         # Save a copy of HEX_RES
                  pha                   # multiplied by 2
                  lda HEX_RES
                  asl HEX_RES           # Now mult by 8
                  rol HEX_RES+1         # since HEX_RES has already
                  asl HEX_RES           # been mult by 2
                  rol HEX_RES+1         # A simple mult by 4 gives
                  clc
                  adc HEX_RES           # Add in 2x to 8x
                  sta HEX_RES           # to get 10x
                  pla
                  adc HEX_RES+1
                  sta HEX_RES+1
                  pla
                  plp
                  rts


#*******************************************************************************
#                 Get a number in range 0-255
#*******************************************************************************

get_BYTE          jsr get_ASC_number    # Get a number
                  bcc gby_bexit         # If invalid go exit

                  lda HEX_RES+1         # Is hi-byte == 0
                  bne gby_bexit         #   No, go err exit

gby_gexit         lda HEX_RES
                  sta BYTE
                  sec
                  rts

gby_bexit         clc
                  rts



#*******************************************************************************
#                 Convert an ASCII Hex number on the cmd line to binary
#                 On Exit:
#                   Result in HEX_RES and HEX_RES+1
#                   sec = Success, clc = Failure
#*******************************************************************************

get_ASC_hex       stz HEX_RES           # clear the result regs
                  stz HEX_RES+1
                  lda #ISHEX
                  sta NUMBASE
gah_loop          inx                   # inc line ptr
                  lda CMD_IBUF,x        # Get a chr
                  cmp #SPC              # End of #?
                  beq gah_gexit         #   Yes, then exit

                  cmp #COMMA            # End of #?
                  beq gah_gexit         #   Yes, then exit

                  cmp #NULL             # End of cmd?
                  beq gah_gexit         #   Yes, then exit

                  jsr get_ASC_nybl      # Is it valid # ?
                  bcc gah_bexit         #   No, go to err exit

                  >MULTW2 HEX_RES       #   Yes, so shift left the result 4 times
                  >MULTW2 HEX_RES
                  >MULTW2 HEX_RES
                  >MULTW2 HEX_RES

                  ora HEX_RES           # Add in the new nybble
                  sta HEX_RES
                  bra gah_loop

gah_gexit         sec                   # sec = success
                  rts

gah_bexit         clc                   # clc = failure
                  rts


#*******************************************************************************
#                 Conv ASC to hex nibble.
#                 On Exit:
#                   clc = ERR, sec = Valid
#                   A = number
#*******************************************************************************

get_ASC_nybl      sec
                  sbc #$30              # Subtract  ASCII '0'
                  cmp #$0A              # Is it a number?
                  bcc gan_gexit         #   Yes, then go good exit

                  sbc #$07              # Subtract diff '9' - 'A'
                  cmp #$10              # Is it 'A' - 'F'?
                  bcc gan_gexit         #   Yes, then go good exit

                  sbc #$20              # Must be lowercase, subtract diff
                  cmp #$10              # Is it less than 16?
                  bcc gan_gexit         #   Yes, then go good exit

gan_bexit         clc                   #   No, bad ch err exi
                  rts

gan_gexit         sec
                  rts



pr_SRC_addr       jsr pr_DOLLAR         ; Format is $xxxx
                  lda SRC+1
                  jsr pr_HEX_byte
                  lda SRC
                  jsr pr_HEX_byte
                  rts

pr_UNTIL_addr     jsr pr_DOLLAR         ; Format is $xxxx
                  lda UNTIL+1
                  jsr pr_HEX_byte
                  lda UNTIL
                  jsr pr_HEX_byte
                  rts

pr_DEST_addr      jsr pr_DOLLAR         ; Format is $xxxx
                  lda DEST+1
                  jsr pr_HEX_byte
                  lda DEST
                  jsr pr_HEX_byte
                  rts


# HEX8ASC - Accepts 8-bit Hexadecimal value (00-99 decimal) and converts to ASCII numeric values.
#  A register contain the single byte value on entry and outputs the two ASCII numeric values.
#  leading zero is output as it is used for showing hundredths of a second after a decimal point.
hex8asc         ldy #$FF                # Load Y reg with "-1"
                sec                     # Set carry for subtraction
hex8lp1         iny                     # Increment 10's count (starts at zero)
                sbc #10                 # Subtract 10 decimal
                bcs hex8lp1             # Branch back if >10
                adc #$3A                # Add the last 10 back plus $30 (ASCII "0")
                pha                     # Save 1's count to the Stack
                tya                     # Get the 10's count
                clc                     # Clear carry for add
                adc #$30                # Add $30 for ASCII digit
                jsr put_c               # Print the first digit (10's)
                pla                     # Get 1's count from the Stack
                jmp put_c               # Print the second digit, return
