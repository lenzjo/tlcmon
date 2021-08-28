###############################################################################
#				ACIA stuff
###############################################################################

inizACIA          lda #ACIA_RESET       # Reset ACIA
                  sta ACIA_ControlRam   # Always save a copy of the register in RAM
                  sta ACIA_Control      # Set RAM copy first because hardware generates IRQs
                  lda #ACIA_INIT        # Set N-8-1, Div 16 (overwrite old control byte)
                  sta ACIA_ControlRam
                  sta ACIA_Control
                  lda ACIA_ControlRam   # Always load the control byte image from RAM
                  ora #ACIA_RXI_EN      # Also enable Rx interrupt (no Tx IRQ at this time)
                  sta ACIA_ControlRam
                  sta ACIA_Control
                  rts


#------------------------------------------------------------------------------
# Put a character to output (character in A)
#------------------------------------------------------------------------------

ACIA1_put_c       phy
OUTCH             ldy UART_OCNT
                  bmi OUTCH

                  ldy UART_OTAIL
                  sta UART_OBUF,y
                  inc UART_OTAIL
                  rmb7 UART_OTAIL
                  inc UART_OCNT

                  lda ACIA_ControlRam   # may interrupt immediately if tx isn't busy
                  ora #ACIA_TXI_EN      # Use "or"  to set the bits for the transmit IRQ
                  sta ACIA_ControlRam
                  sta ACIA_Control

                  ply
                  rts
#-------------------------------------------------------------------------------
# Wait until at least one character is available in the input queue, and return
# the first character in A
#-------------------------------------------------------------------------------

ACIA1_get_c       lda UART_ICNT
                  beq ACIA1_get_c       # Loop until atleast 1 ch in buffer

                  phy
                  ldy UART_IHEAD        # Get the buffer head pointer
                  lda UART_IBUF,Y       # Get the character from the buffer
                  inc UART_IHEAD        # Increment head pointer
                  rmb7 UART_IHEAD       # Strip off bit 7, 128 bytes only
                  DEC UART_ICNT         # Decrement the buffer count

                  ply                   # Restore Y Reg
                  rts                   # Return to caller with character in A Reg
