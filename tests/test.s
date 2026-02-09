.global z,x
.extern b
.section text
iret
ret
.word a,b
.word 54
lala:
.skip 4
.section data
.word c,d
c:
.equ a,5
ldr r7,q
.word 6
.end
