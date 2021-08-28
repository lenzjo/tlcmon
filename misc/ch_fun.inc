#*******************************************************************************
#                 Print a byte as two Ascii characters
#*******************************************************************************
prbyte            pha
                  phy
prbyt2            jsr bin2asc
                  jsr put_c
                  tya
                  jsr put_c
                  ply
                  pla
                  rts

#*******************************************************************************
#                 Convert a single binary digit (0-9,A-F) to an Ascii character
#*******************************************************************************
bin2asc           pha
                  and #$0F
                  jsr con_ascii
                  tay
                  pla
                  lsr a
                  lsr a
                  lsr a
                  lsr a

con_ascii         cmp #$0A
                  bcc ascok
                  adc #$06
ascok             adc #$30
                  rts
