    .data
    .global A
A: .skip 4

    .global B
B: .skip 4

    .global R
R: .skip 4

    .text
    .global process
process:
    push %ebp
    movl %esp, %ebp

    movl A, %eax
    movl B, %ecx

    sall $1, %eax
    jo overflow

    movl A, %edx
    sarl $4, %ecx
    subl %ecx, %edx

    addl %edx, %eax
    jo overflow

    movl %eax, R
    
overflow:    
    xor %eax, %eax
    leave
    ret

    .section .rodata
scanf_tmp: .asciz "%d"
printf_tmp: .asciz "%d\n"
