    .text
final:
    movl %eax, %edx
    pop %ebp
    pop %ecx
    pop %eax
    ret

    .global partition
partition:
    push %eax
    push %ecx
    push %ebp    

    xor %eax, %eax
    movl %esi, %ecx
    decl %ecx
Floop:
    cmpl %eax, %ecx
    jle final

Sloop:
    cmpl %eax, %esi
    jle Go

    cmpw (%ebx, %eax, 2), %di
    jle Go 

    incl %eax
    jmp Sloop

Go:
    cmpl $0, %ecx
    jl Last

    cmpw (%ebx, %ecx, 2), %di
    jg Last

    decl %ecx
    jmp Go

Last:
    cmpl %eax, %ecx
    jle final

    movw (%ebx, %ecx, 2), %bp
    xchgw (%ebx, %eax, 2), %bp
    movw %bp, (%ebx, %ecx, 2)

    jmp Floop
