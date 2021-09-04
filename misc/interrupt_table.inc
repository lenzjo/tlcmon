#=====================================================================
#  Vector table data for default ROM handlers
#=====================================================================

VEC_ETABLE        .DW NMI_vector        # NMI Location in ROM
                  .DW NMI_exit          # NMI return handler in ROM

                  .DW ACIA_isr          # UART isr Location in ROM
                  .DW VIA1_isr          # RTC isr Location in ROM
                  .DW IRQ_exit          # IRQ return handler in ROM
                  .DW IRQ_exit          # IRQ return handler in ROM
                  .DW IRQ_exit          # IRQ return handler in ROM
                  .DW IRQ_exit          # IRQ return handler in ROM
#                  .DW IRQ_exit          # IRQ return handler in ROM
