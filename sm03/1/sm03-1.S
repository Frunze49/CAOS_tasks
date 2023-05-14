    .global main
    .text
main:
    pushl %ebp
    movl %esp, %ebp

continue:

    pushl $cur
    pushl $scanf_tmp

    call scanf
    addl $8, %esp
    
    mov cur, %ecx
    add %ecx, sum
    movl $0, cur
    jo overflow_case

    cmpl $1, %eax
    je continue

    pushl sum
    pushl $printf_tmp
    call printf
    addl $8, %esp
    xor %eax, %eax

    leave
    ret

overflow_case:
    pushl $overflow_tmp
    call printf

    xor %eax, %eax

    leave
    ret

    .data
cur:    .int 0
sum:    .int 0

    .section .rodata
scanf_tmp: .asciz "%d"
printf_tmp: .asciz "%d\n"
overflow_tmp: .asciz "Overflow\n"

     
