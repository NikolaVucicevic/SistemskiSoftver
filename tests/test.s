.global z,x
.extern b
.section text
iret
ret
d:
.word a,b
.word 54
add r1, r2
and r1, r2
shl r1, r2
lala:
.skip 4
.word 33
.section data
.word c,d
c:
.equ a,5
.word 6
.end
