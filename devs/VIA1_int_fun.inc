#*******************************************************************************
# ISR detect for VIA1
#*******************************************************************************

VIA1_isr          bit VIA1_IFR          # Has the VIA caused the interrupt?
                  bmi VIA1_fun_isr      #   Yes, go do something
vc_next_irq       jmp (IRQ_VEC2)        #   No, then go to next cause of interrupt


#*******************************************************************************
# ISR function for VIA1
#*******************************************************************************

VIA1_fun_isr      bit VIA1_T1CL         # Clear the interrupt
                  inc JIFFIES
                  lda JIFFIES
                  cmp #100              # Have we reached a second yet?
vfi_exit          bne vc_next_irq       #   No, then exit

                  stz JIFFIES           # Reset JIFFIES ctr

                  lda LED_STATE
                  cmp #1                # Is led on?
                  bne ld_on             #   No, then go turn it on!

ld_off            stz LED_STATE         #   Yes, Turn off led
                  stz VIA1_ORB
                  bra update_time

ld_on             lda #1                # Turn it on
                  sta LED_STATE
                  sta VIA1_ORB
#                  bra update_time

update_time       inc SECONDS           # INC seconds
                  lda SECONDS
                  cmp #60               # Reached 1 min yet?
                  bne vc_next_irq       # If not, done for now

                  stz SECONDS           # Reset SECONDS
                  inc MINUTES           # INC minutes
                  lda MINUTES
                  cmp #60               # Reached 1 hour yet?
                  bne vc_next_irq

                  stz MINUTES           # Reset MINUTES
                  inc HOURS             # INC hours
                  lda HOURS
                  cmp #24               # Reached 24 hours yet?
                  bne vc_next_irq

                  stz HOURS             # Reset HOURS
                  >INCW DAYS
                  bra vc_next_irq
