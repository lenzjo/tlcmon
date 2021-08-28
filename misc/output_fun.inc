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
