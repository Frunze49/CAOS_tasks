### Problem exam1-10: exam/module3/0x0A

В каких из этих фрагментов кода на Си НЕ МОЖЕТ возникнуть undefined behavior?

1) `auto void** ptr; *ptr = NULL;`

2) `char* msg = “hello world”; puts(msg + 6);`

3) `uint32_t x = 7; x <<= 31;`

4) `uint8_t a = 200, b = 200; a += b;`

5) `int32_t x = 0x76543210; x *= 2;`

6) `char* buf = malloc(100); strcpy(buf, “riders on the storm”);`

7) `int x; uintptr_t p = (uintptr_t)&x; *(int*)p = 3;`

### Notes

Внимание! Выпишите номера ответов через пробел в произвольном порядке.

Если вы считаете что верны ответы 1, 3 и 5 то введите 1 3 5

