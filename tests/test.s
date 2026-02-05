.global z,x
.section text
iret
ret
.word a,b,c,d
.extern b
.word 54
.skip 54
.equ a,5
ldr r7,q
.end
