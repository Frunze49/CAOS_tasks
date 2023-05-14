    .global main  
final:
     call finish
out:
   cmpl $0, %ebx
   jz final
   decl %ebx
   pop %eax
   call writei32
   jmp out
main:
    xor %ebx, %ebx
loop:
    call readi32
    jc out
    push %eax
    incl %ebx
    jmp loop
    
