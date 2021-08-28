#==============================================================================
#                 6850 Interrupt Service Routine
#==============================================================================

ACIA_isr          lda ACIA_Status       # Get status from 6850
                  bpl ai_next_irq       # No interrupt, so go try the next device

                  sta ACIA_StatusRam    # Store in MOS variable in RAM

                  lda #ACIA_RDRF
                  bit ACIA_StatusRam    # Check receiver full flag
                  beq CheckXmt          # Branch to next check if flag not set

                  bra ACIA_isr_rx       # Receive character into buffer

CheckXmt          lda #ACIA_TDRE
                  bit ACIA_StatusRam    # Check transmitter empty flag
                  beq ai_next_irq       # Branch to next check if flag not set

                  bra ACIA_isr_tx       # Handle transmitter

ai_next_irq       jmp (IRQ_VEC1)


#==============================================================================
#                 ACIA Transmit ISR
#==============================================================================

ACIA_isr_tx       lda UART_OCNT
                  beq actr_exit

                  ldy UART_OHEAD
                  lda UART_OBUF,y
                  sta ACIA_Tx
                  inc UART_OHEAD
                  rmb7 UART_OHEAD
                  dec UART_OCNT
                  bra ai_next_irq

actr_exit         lda ACIA_ControlRam   # No more chars in the buf turn off the tx-empty IRQ.
                  and #ACIA_TXI_DS      # Use "and" to clear the bits for the transmit IRQ
                  sta ACIA_ControlRam
                  sta ACIA_Control
                  bra ai_next_irq


#==============================================================================
#                 ACIA Receive ISR
#==============================================================================

ACIA_isr_rx       ldy UART_ICNT
                  bmi ai_next_irq
                  lda ACIA_Rx

                  ldy UART_ITAIL
                  sta UART_IBUF,y
                  inc UART_ITAIL
                  rmb7 UART_ITAIL
                  inc UART_ICNT

                  bra ai_next_irq
