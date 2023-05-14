    .text
    .global main
main:
    call readi64

    cmpl $-1, %edx
    jz minus_one_case

    cmpl $0, %edx
    jz zero_case

    jg max

    jl min
    

max:
    movl $2147483647, %eax
    jmp print

min:
    movl $-2147483648, %eax
    jmp print

zero_case:
    cmpl $0, %eax
    jge print

    jl max

minus_one_case:
   cmpl $0, %eax
    
    jle print
    jg min

print:
    call writei32
    call finish
 
