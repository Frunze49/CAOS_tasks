|                      |       |
|----------------------|-------|
| **Time limit:**      | `1 s` |
| **Real time limit:** | `5 s` |
| **Memory limit:**    | `64M` |


### Problem sm03-5: asm/algorithms/anagram

Программе на стандартный вход подаются две текстовые строки в кодировке ASCII, обе из которых
завершаются символом перевода строки (`'\n'`, код 10). Строки имеют длину не более 200 символов.
Программа должна проверить, являются ли строки анаграммами друг друга (то есть можно ли одну из них
получить перестановкой символов в другой), и напечатать ответ `YES` или `NO`, завершив вывод
символом перевода строки.

При проверке учитывать все символы, кроме пробела (`' '`, код 32), регистр латинских букв
игнорировать.

Для считывания строк используйте функцию getchar

### Examples

#### Input

    
    
    Anagram.
    Nag a ram.

#### Output

    
    
    YES

#### Input

    
    
    Go?
    Go!

#### Output

    
    
    NO
