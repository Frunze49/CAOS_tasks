    .text
    .global okay
okay:
    push %ebp
    mov %esp, %ebp

    movsd   8(%ebp), %xmm0
    movsd   8(%ebp), %xmm3

    mulsd   %xmm3, %xmm0
    mulsd   %xmm3, %xmm0
    mulsd   %xmm3, %xmm0

    movsd   16(%ebp), %xmm1
    movsd   16(%ebp), %xmm3

    mulsd   %xmm3, %xmm1
    mulsd   %xmm3, %xmm1
    mulsd   %xmm3, %xmm1

    mov 24(%ebp), %eax

    addsd %xmm1, %xmm0
    sqrtsd %xmm0, %xmm1

    sub     $8, %esp
    movsd   %xmm1, (%esp)
    fldl    (%esp)
    add     $8, %esp

    fstl   (%eax)

    leave
    ret