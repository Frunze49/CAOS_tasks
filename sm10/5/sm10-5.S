    .text
    .global product
product:
    push %ebp
    mov %esp, %ebp

    vxorps %xmm0, %xmm0, %xmm0
    vxorps %xmm1, %xmm1, %xmm1
    vxorps %xmm2, %xmm2, %xmm2

    mov 8(%ebp), %eax
    mov %eax, num
    mov 12(%ebp), %ecx
    mov 16(%ebp), %edx
    mov $0, %eax
loop:
    cmp num, %eax
    jz print

    mov %eax, current
    mov num, %eax
    sub current, %eax

    cmp $4, %eax
    jl scalar

vector:

    mov current, %eax

    vmovups (%ecx), %xmm1
    vmovups (%edx), %xmm2
    mulps %xmm2, %xmm1

    hsubps %xmm2, %xmm1
    haddps %xmm2, %xmm1

    addss %xmm1, %xmm0

end_vector:

    add $4, %eax
    add $16, %ecx
    add $16, %edx

    jmp loop


scalar:
    mov current, %eax

    movss (%ecx), %xmm1
    movss (%edx), %xmm2

    mulss %xmm2, %xmm1
    test $1, %eax
    jnz sub
add:
    addss %xmm1, %xmm0
    jmp end_loop
sub:
    subss %xmm1, %xmm0

end_loop:

    add $1, %eax
    add $4, %ecx
    add $4, %edx

    jmp loop

print:

    mov 20(%ebp), %eax

    sub     $4, %esp
    movss   %xmm0, (%esp)
    fld    (%esp)
    add     $4, %esp

    fst   (%eax)

    leave
    ret

    .data
num: .int 1
current: .int 1
arr: .skip 16