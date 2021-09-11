
cmd_conv          >CPYMSPTR CONVMSG
                  jsr put_str
                  rts

CONVMSG           .DB "CONV: not yet ready.", CR, LF, NULL
