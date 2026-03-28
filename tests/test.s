.global z,x
.extern b
.section text
iret
ret
d:
.word a,b
.word 54
add r1, r2
.word 0
and r1, r2
.word 0
shl r1, r2
.word 1
ldr r1,r2
lala:
.skip 4
.word 33
.section data
.word c,d
c:
.equ a,5
.word 6
.end
