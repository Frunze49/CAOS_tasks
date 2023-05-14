    .data
    .global A
A: .skip 4
    .global B
B: .skip 4
    .global R
R: .skip 4

     .text
     
final:
     movl %eax, R
     pop %edx
     pop %ecx
     pop %ebx
     pop %eax
     ret

add:
   addl %edx, %eax
   
   sall $1, %ebx 
   sall $1, %edx
   inc %ecx
   jmp loop
   
   .global process
process:
     push %eax
     push %ebx
     push %ecx
     push %edx
     
     movl $0, %eax
     movl $1, %ebx
     movl $0, %ecx
     movl A, %edx

loop:
     cmpl $32, %ecx
     jz final

     test %ebx, B
     jnz add
     
     
     sall $1, %ebx 
     sall $1, %edx
     inc %ecx
     jmp loop

