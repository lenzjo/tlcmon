#=====================================================================
# My Macros to make coding more readable
#=====================================================================

#====  Move an address into regs A & Y  ====
CPYMSPTR          .MA	ADDR
                  lda #]1
                  ldy /]1
                  .EM


;====  Multiply Acc by 16  ====
MULTAx16          .MA
                  clc
                  asl a
                  asl a
                  asl a
                  asl a
                  .EM


;====  Multiply Acc by 8  ====
MULTAx8           .MA
                  clc
                  asl a
                  asl a
                  asl a
                  .EM


;====  Multiply a word by 2
MULTW2            .MA WORD
                  asl ]1
                  rol	]1+1
                  .EM


;====  Add two mem regs together and save in 1st
ADDW              .MA WORDA, WORDB
                  clc
                  lda ]1
                  adc ]2
                  sta ]1
                  lda ]1+1
                  adc ]2+1
                  sta ]1+1
                  .EM


;==== Copy a Word
CPYW              .MA WORDA, WORDB
                  lda ]1
                  sta ]2
                  lda ]1+1
                  sta ]2+1
                  .EM


;====  Copy addr into ptr
CPYA2P            .MA ADDR, PTR
                  lda #]1
                  sta ]2
                  lda /]1
                  sta ]2+1
                  .EM


;====  Compare two numbers  ===
CMPAD             .MA MEMA, MEMB
                  lda ]1+1
                  cmp ]2+1
                  bne :CA_EXIT
                  lda ]1
                  cmp ]2
:CA_EXIT
                .EM


;====  Compare two numbers  ===
CMPVAL            .MA ADDR, VAL
                  lda ]1
                  cmp #]2
                  bne :CV_EXIT
                  lda ]1
                  cmp /]2
:CV_EXIT
                  .EM


;==== Increment a Word
INCW              .MA VAL
                  inc ]1
                  bne :IW_EXIT
                  inc ]1+1
:IW_EXIT
                  .EM


;==== Decrement a Word
DECW              .MA WORD
                  lda ]1
                  bne :DW
                  dec ]1+1
:DW               dec ]1
                  .EM


;====  Add A reg to a ptr
ADDA              .MA ADDR
                  clc
                  adc ]1
                  sta ]1
                  lda #0
                  adc ]1+1
                  sta ]1+1
                  .EM


;====  Subtract A reg from a ptr
SUBA              .MA ADDR,VAL
                  sec
                  lda ]1
                  sbc ]2
                  sta ]2
                  lda ]1+1
                  sbc #0
                  sta ]1+1
                  .EM


;====  Subtract two mem regs and save in 1st
SUBW              .MA MEMA,MEMB
                  sec
                  lda ]1
                  sbc ]2
                  sta ]1
                  lda ]1+1
                  sbc ]2+1
                  sta ]1+1
