|                      |       |
|----------------------|-------|
| **Time limit:**      | `1 s` |
| **Real time limit:** | `5 s` |
| **Memory limit:**    | `64M` |


### Problem sm16-3: c/longjmp/exc

Напишите функции `try, endtry` и `throw`, реализующие механизм исключений на минималках. Сигнатуры
функций:

    
    
    jmp_buf* try(int exception);
    void endtry();
    void throw(int exception);

Синтаксис для пользователя такой:

    
    
    if (!setjmp(*try(42))) { // добавили обработчик
        puts("level 1");
        if (!setjmp(*try(1))) { // и ещё один
            puts("level 2");
            throw(42); // выбросили исключение
            puts("this string is not displayed");
            endtry();
        } else {
            puts("handle exception 1");
        }
        endtry();
    } else {
        puts("handle exception 42");
    }

Этот пример напечатает:

    
    
    level 1
    level 2
    handle exception 42

Используйте механизм `setjmp/longjmp`. Обработчики исключений образуют "параллельный стек", который
можно хранить в глобальной переменной. Гарантируется, что глубина этого стека не превышает 10.

Если для выброшенного исключения не нашлось обработчика, программа должна немедленно завершиться с
кодом 13.

