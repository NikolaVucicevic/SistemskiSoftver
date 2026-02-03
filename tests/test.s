.global a,b,c,d
.section text
iret
ret
.extern b
.word 54
.skip 54
.equ a,5
.end
