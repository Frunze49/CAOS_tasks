    .text
    .global my.args.forward
my.args.forward:
    pushl %ebp
    movl %esp, %ebp
    
    # read
    movl 8(%ebp), %ecx
    movl %ecx, first
    
    movl 12(%ebp), %eax
    movl 16(%ebp), %edx    

    movl 20(%ebp), %ecx
    movl %ecx, third
 
    # write
    pushl %edx
    pushl %eax

    movl first, %ecx
    pushl %ecx

    movl third, %ecx
    pushl %ecx

    call process

    imull $-1, %eax
    
    leave
    ret


    .data
first: .skip 4
third: .skip 4
