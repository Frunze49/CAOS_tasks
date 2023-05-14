    .text
    .global process
process:
    push %ebp
    mov %esp, %ebp
    push %ebp
    mov %esp, %ebp
    mov $4, %eax
    mov %ebp, %esp
    pop %ebp
    ret
