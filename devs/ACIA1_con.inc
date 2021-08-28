#=====================================================================
#                 ACIA CONSTANTS
#=====================================================================

# Control register bit fields
ACIA_RXI_EN       .EQ %1000.0000        # Receive interrupt enable
ACIA_TXI_EN       .EQ %0010.0000        # Transmit interrupt enable, /rts low
ACIA_TXI_DS       .EQ %1001.1111        # Transmit interrupt disable, /rts low (AND)
ACIA_N_8_1        .EQ %0001.0100        # No parity, 8 bit data, 1 stop (see docs)
ACIA_DIV_16       .EQ %0000.0001        # Divide tx & rx clock by 16, sample middle
ACIA_RESET        .EQ %0000.0011        # Master reset
ACIA_INIT         .EQ %0001.0101        # No parity, 8 bit data, 1 stop, Divide by 16

# Status register bit fields
ACIA_RDRF         .EQ %00000001         # Receive Data Register Full
ACIA_TDRE         .EQ %00000010         # Transmit Data Register Empty
ACIA_DCD          .EQ %00000100         # Data Carrier Detect line
ACIA_CTS          .EQ %00001000         # Clear To Send line
ACIA_ER_F         .EQ %00010000         # Error- Framing
ACIA_ER_O         .EQ %00100000         # Error- Overrun
ACIA_ER_P         .EQ %01000000         # Error- Parity
ACIA_IRQ          .EQ %10000000         # Interrupt Request
