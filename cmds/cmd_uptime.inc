
cmd_uptime        lda HOURS
                  jsr hex8asc
                  lda #COLON
                  jsr put_c
                  lda MINUTES
                  jsr hex8asc
                  lda #COLON
                  jsr put_c
                  lda SECONDS
                  jsr hex8asc
                  jsr pr_CRLF
                  rts
