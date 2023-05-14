    .global process
process:
    pushl %ebp
    movl %esp, %ebp
    
    movl $4, %eax
    
    leave
    ret
