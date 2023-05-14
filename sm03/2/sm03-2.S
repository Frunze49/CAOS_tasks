    .text

f_s_xchg:
    xchgl %ebx, %ecx
    jmp second_cmp

f_t_xchg:
    xchgl %ebx, %edx
    jmp third_cmp
    
s_t_xchg:   
    xchgl %ecx, %edx
    jmp Find

print_foo:
    pushl $foo_tmp
    call puts
    addl $4, %esp

    movl (%ebp), %ebp

    jmp loop

print_bar:
    pushl $bar_tmp
    call puts
    addl $4, %esp

    movl (%ebp), %ebp

    jmp loop

print_main:
    pushl $main_tmp
    call puts
    addl $4, %esp

    movl (%esp), %esp

    jmp final



    .global print_tb
print_tb:

    pushl %ebp
    movl %esp, %ebp

    pushl $print_tb_tmp
    call puts
    addl $4, %esp

loop:
    movl %ebp, %eax
    addl $4, %eax
    movl (%eax), %eax

    movl $foo, %ebx
    movl $bar, %ecx
    movl $main, %edx

    subl %eax, %ebx
    subl %eax, %ecx
    subl %eax, %edx

    movl %ebx, foo_val
    movl %ecx, bar_val
    movl %edx, main_val


Cmp:
first_cmp:
    cmpl %ebx, %ecx
    jl f_s_xchg

second_cmp:
    cmpl %ebx, %edx
    jl f_t_xchg

third_cmp:
    cmpl %ecx, %edx
    jl s_t_xchg

  
Find:
    movl %ebx, last

second_find:
    cmpl $0, %ecx
    jge Print
    movl %ecx, last

third_find:
    cmpl $0, %edx
    jge Print
    movl %edx, last
    
Print:
    movl last, %eax

    cmpl %eax, foo_val
    jz print_foo 

    cmpl %eax, bar_val
    jz print_bar

    cmpl %eax, main_val
    jz print_main

final:
    
    xor %eax, %eax

    leave
    ret

    .data
foo_val: .skip 4
bar_val: .skip 4
main_val: .skip 4
last: .skip 4

    .section .rodata
print_tb_tmp: .asciz "print_tb"
foo_tmp: .asciz "foo"
bar_tmp: .asciz "bar"
main_tmp: .asciz "main"
