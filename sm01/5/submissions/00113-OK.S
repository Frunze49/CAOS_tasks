    .global main  
final:
     movl %ecx, %eax
     call writei32
     call finish
one:
   inc %ecx
   
    sall $1, %ebx
    inc %edx
    jmp loop
main:
    movl $1, %ebx
    movl $0, %edx
    xor %ecx, %ecx
    call readi32
loop:

    cmpl $32, %edx
    jz final
    
    test %ebx, %eax
    jnz one
    
    sall $1, %ebx
    inc %edx
    jmp loop

