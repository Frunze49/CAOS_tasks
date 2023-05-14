    .text

mul_first:
    imulw $-1, %ax
    jmp bruh    

mul_second:
    imulw $-1, %dx
    jmp bruh_two

comparator:

    pushl %ebp
    movl %esp, %ebp

    xor %eax, %eax

    movl 8(%ebp), %ecx
    movw (%ecx), %ax

    movl 12(%ebp), %ecx
    movw (%ecx), %dx
    
    cmpw $0, %ax
    jl mul_first

bruh:
    cmpw $0, %dx
    jl mul_second

bruh_two:

    subw %dx, %ax
    movswl %ax, %eax 

    leave
    ret

    .global sort_by_abs
sort_by_abs:    
    
    pushl %ebp
    movl %esp, %ebp

    movl 8(%ebp), %eax
    movl 12(%ebp), %ecx

    pushl $comparator
    pushl $2
    pushl %ecx
    pushl %eax

    call qsort

    
    
    xor %eax, %eax
    leave
    ret
