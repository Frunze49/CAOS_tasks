    .global main
main:
    call readi32
    movl %eax, %ebx
    call readi32
    movl %eax, %ecx
    call readi32
    movl %eax, %edx
    call readi32
    call writei32
    
    movl %edx, %eax 
    sall $4, %edx
    addl %eax, %edx

    sall $1, %ecx
    
    subl %ecx, %ebx
    addl %edx, %ebx
    
    movl %ebx, %eax
    call writei32
    
    call finish
