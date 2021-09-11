

cmd_fill          >CPYMSPTR FILLMSG
                  jsr put_str
                  rts

FILLMSG           .DB "FILL: not yet ready.", CR, LF, NULL
