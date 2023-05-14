|                      |       |
|----------------------|-------|
| **Time limit:**      | `1 s` |
| **Real time limit:** | `5 s` |
| **Memory limit:**    | `64M` |


### Problem exam1-6: exam/module3/0x06

Напишите функцию

    
    
    int eval_poly(int A, int B, int C, int x, jmp_buf overflow)

Функция вычисляет значение многочлена `(A * x + B) * x + C` в точке x (операции выполняются именно в
таком порядке). В случае возникновения целочисленного переполнения в результате любой операции
необходимо передать управление на обработчик overflow.

Можно пользоваться непортабельными встроенными функциями компилятора GCC.
