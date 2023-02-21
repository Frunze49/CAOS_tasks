### Problem kr03-t5: tests/kr3/yabloko-5

Выберите все строки кода, при выполнении которых процессор переключится из кольца 3 в кольцо 0:

1) [cpu/swtch.S:13](https://github.com/hse-cs-ami/yabloko-public/blob/main/cpu/swtch.S#L13) “mov
%ecx, %esp”

2) [user/false.c:2](https://github.com/hse-cs-ami/yabloko-public/blob/main/user/false.c#L2) “return
1;”

3) [cpu/vectors.S:27](https://github.com/hse-cs-ami/yabloko-public/blob/main/cpu/vectors.S#L27)
“iret”

4) [user/div0.c:3](https://github.com/hse-cs-ami/yabloko-public/blob/main/user/div0.c#L3) “x /= 0;”

5) [cpu/gdt.c:51](https://github.com/hse-cs-ami/yabloko-public/blob/main/cpu/gdt.c#L51) “lgdt
gdt_desc”

6) [cpu/idt.c:165](https://github.com/hse-cs-ami/yabloko-public/blob/main/cpu/idt.c#L165) “lidt
idt_reg”

7) [cpu/idt.c:173](https://github.com/hse-cs-ami/yabloko-public/blob/main/cpu/idt.c#L173) “cli”

8) [user/crt.c:6](https://github.com/hse-cs-ami/yabloko-public/blob/main/user/crt.c#L6) “int $0x84”

### Notes

ВАЖНО! Строки учитываются только в контексте того кода где они расположены!

Внимание! Выпишите номера ответов через пробел в произвольном порядке.

Если вы считаете что верны ответы 1, 3 и 5 то введите 1 3 5

