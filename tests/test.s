.global z,x
.extern b
.section text
iret
ret
.word a,b
.word 54
lala:
.skip 54
.section data
.word c,d
.equ a,5
ldr r7,q
.end
