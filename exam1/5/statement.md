|                      |       |
|----------------------|-------|
| **Time limit:**      | `1 s` |
| **Real time limit:** | `5 s` |
| **Memory limit:**    | `64M` |


### Problem exam1-5: exam/module3/0x05

Напишите программу `LSF`, которая запускается с одним аргументом командной строки: `./LSF DIR` и
печатает (в произвольном порядке) содержимое директории `DIR`. Имя каждого файла должно выводиться
на отдельной строке.

* После имени поддиректорий должен выводиться символ '/'.
* После имени обычных (regular) файлов, исполнимых для их владельца, должен выводиться символ '*'.
* После имени символических ссылок должен выводиться символ '@'.

Скрытые файлы (наподобие .config) должны выводиться в общем порядке, а вот ссылка на текущую и
родительскую директорию выводиться не должны. Например:

    
    
    $ ./LSF .
    subdir/
    symlink@
    LSF*
    LSF.c
    .clang-format

