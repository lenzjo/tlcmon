COUNT             .EQ $4E1E             # 100hz sample rate (10msec ints.) assuming 2Mhz clk




# Iniz the T1 interrupt timer
iniz_VIA1         lda  VIA1_ACR         # Clear the ACR's bit that
                  and  #%01111111       # tells T1 to toggle PB7 upon time-out, and
                  ora  #%01000000       # set the bit that tells T1 to automatically
                  sta  VIA1_ACR         # produce an interrupt at every time-out and
                                        # just reload from the latches and keep going.
                  lda  #%11000000
                  sta  VIA1_IER         # Enable the T1 interrupt in the VIA.


                  lda #$1E
                  sta VIA1_T1CL         # Set low byte of count
                  lda #$4E
                  sta VIA1_T1CH         # Set high byte of count

# This is for the LED on PB0
                  lda #%00000001
                  sta VIA1_DDRB         # Make PB0 an output
                  sta VIA1_ORB          # Turn on LED
                  sta LED_STATE         # Remember if LED is on/off

# This is for the clock
                  stz SECONDS
                  stz MINUTES
                  stz HOURS
                  rts
