

cmd_dism          >CPYMSPTR DISMMSG
                  jsr put_str
                  rts

DISMMSG           .DB "DISM: not yet ready.", CR, LF, NULL
