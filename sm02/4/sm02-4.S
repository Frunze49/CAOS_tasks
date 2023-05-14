    .bss
arr: .skip 8 * 1001


    .text
final:
    call finish

bruh:
    movl $-1, %eax
    call writei32
    jmp loop

push:
    call readi32
    movl %eax, (%esi, %ebx, 4)
    incl %ebx

    call readi32
    movl %eax, (%esi, %ebx, 4)
    incl %ebx

    jmp loop
    
pop:
    call readi32    

    movl (%esi, %eax, 8), %ecx
    cmpl $-1, %ecx
    je bruh    

    movl 4(%esi, %eax, 8), %ecx

    xchgl %ecx, %eax
    call writei32
    xchgl %ecx, %eax    

    movl (%esi, %eax, 8), %ecx

    movl 4(%esi, %ecx, 8), %eax
    movl (%esi, %ecx, 8), %ecx

    //AAA

    movl %ecx, (%esi, %ebx, 4)
    incl %ebx

    movl %eax, (%esi, %ebx, 4)
    incl %ebx

    jmp loop
    

    .global main
main:
    xor %eax, %eax
    xor %ebx, %ebx
    xor %ecx, %ecx
    movl $arr, %esi
    
    movl $-1, (%esi, %ebx, 4)
    incl %ebx

    movl $0, (%esi, %ebx, 4)
    incl %ebx

loop:
    call readi32
    jc final

    test %eax, %eax
    jz push

    test %eax, %eax
    jnz pop
