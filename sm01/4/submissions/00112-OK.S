    .global main  
final:
   movl %ebx, %eax
   call writei32
    
   movl %ecx, %eax
   call writei32
    
   call finish
even:
    addl %eax, %ebx
    jmp loop
    
odd:
    addl %eax, %ecx
    jmp loop

main:
    xor %eax, %eax
    xor %ebx, %ebx
    xor %ecx, %ecx
    xor %edx, %edx
loop:
    call readi32    
    jb	 final
    
    test $1, %eax
    jz   even
    
    jmp  odd
    

