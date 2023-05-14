    .text
    .global main
main:

    pushl %ebp
    movl %esp, %ebp    

    pushl $continue    
    pushl %ebp
    movl %esp, %ebp    
    jmp process

continue:
    pushl %eax
    pushl $print_tmp
    call printf
    
    addl $8, %esp

    xor %eax, %eax
    leave
    ret

    .section .rodata
print_tmp: .asciz "%d\n"
