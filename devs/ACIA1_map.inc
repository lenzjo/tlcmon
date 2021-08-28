#=====================================================================
# I/O starts at $A400.
# ACIA - 68B50
#=====================================================================

ACIA1             .EQ $A200

ACIABase          .EQ ACIA1
ACIA_Control      .EQ ACIABase+$0       # Control reg
ACIA_Status       .EQ ACIABase+$0       # Status reg
ACIA_Tx           .EQ ACIABase+$1       # Transmit buffer reg
ACIA_Rx           .EQ ACIABase+$1       # Receive buffer reg
