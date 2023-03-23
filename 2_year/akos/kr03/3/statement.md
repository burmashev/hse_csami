|                      |       |
|----------------------|-------|
| **Time limit:**      | `1 s` |
| **Real time limit:** | `5 s` |
| **Memory limit:**    | `64M` |


### Problem kr03-3: kr3/parent_arg

Напишите функцию `void print_parent_arg()`, которая печатает на stdout первый аргумент вызывающей её
функции как беззнаковое целое 32-битное число в шестнадцатеричной системе счисления и перевод
строки. Например, если определена функция `void calling_fun(int xyzzy) { print_parent_arg(); }`, то
`calling_fun(17)` напечатает на stdout 3 байта "11\n". Все функции поддерживают стандартный стековый
кадр и пользуются обычным соглашением о вызовах cdecl.
