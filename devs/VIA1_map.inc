#=====================================================================
# I/O starts at $A220.
# VIA - W65c22
#=====================================================================

VIA1              .EQ $A220

VIA1Base          .EQ VIA1

VIA1_IRB          .EQ VIA1Base+$0       # Input/output Register Port B
VIA1_ORB          .EQ VIA1Base+$0       # Input/output Register Port B
VIA1_IRA          .EQ VIA1Base+$1       # Input/output Register Port A
VIA1_ORA          .EQ VIA1Base+$1       # Input/output Register Port A
VIA1_DDRB         .EQ VIA1Base+$2       # Data Direction Register Port B
VIA1_DDRA         .EQ VIA1Base+$3       # Data Direction Register Port A
VIA1_T1CL         .EQ VIA1Base+$4       # T1 Low Order Latches & Counter
VIA1_T1CH         .EQ VIA1Base+$5       # T1 High Order Counter
VIA1_T1LL         .EQ VIA1Base+$6       # T1 Low Order Latches
VIA1_T1LH         .EQ VIA1Base+$7       # T1 High Order Latches
VIA1_T2CL         .EQ VIA1Base+$8       # T2 Low Order Latches & Counter
VIA1_T2CH         .EQ VIA1Base+$9       # T2 High Order Counter
VIA1_SR           .EQ VIA1Base+$A       # Shift Register
VIA1_ACR          .EQ VIA1Base+$B       # Auxillary Control Register
VIA1_PCR          .EQ VIA1Base+$C       # Peripheral Control Register
VIA1_IFR          .EQ VIA1Base+$D       # Interrupt Flag Register
VIA1_IER          .EQ VIA1Base+$E       # Interrupt Enable Register
VIA1_IRA_NHS      .EQ VIA1Base+$F       # Same as VIA1_IORA except no "Handshake"
VIA1_ORA_NHS      .EQ VIA1Base+$F       # Same as VIA1_IORA except no "Handshake"
