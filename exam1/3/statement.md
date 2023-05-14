|                      |       |
|----------------------|-------|
| **Time limit:**      | `1 s` |
| **Real time limit:** | `5 s` |
| **Memory limit:**    | `64M` |


### Problem exam1-3: exam/module3/0x03

Напишите функцию

    
    
    int count_glyphs(const char* utf8_text)

Функция считает количество codepoints в нуль-терминированной строке без учёта combining
диакритических знаков из диапазона Combining Diacritical Marks (0300–036F).

### Examples

#### Input

    
    
    text текст

#### Output

    
    
    10

#### Input

    
    
    H̸̡̪̯ͨ͊̽̅̾̎Ȩ̬̩̾͛ͪ̈́̀́͘ ̶̧̨̱̹̭̯ͧ̾ͬC̷̙̲̝͖ͭ̏ͥͮ͟Oͮ͏̮̪̝͍M̲̖͊̒ͪͩͬ̚̚͜Ȇ̴̟̟͙̞ͩ͌͝S̨̥̫͎̭ͯ̿̔̀ͅ

#### Output

    
    
    8

