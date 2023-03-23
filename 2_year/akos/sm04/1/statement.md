|                      |       |
|----------------------|-------|
| **Time limit:**      | `1 s` |
| **Real time limit:** | `5 s` |
| **Memory limit:**    | `64M` |


### Problem sm04-1: asm/mem/malloc

Напишите подпрограмму `alloc_mem`, которая аллоцирует память на куче.

Подпрограмма `alloc_mem`:

  * принимает один параметр `size` (32-битное беззнаковое число) — минимальный размер (в байтах) блока памяти, который нужно аллоцировать;
  * возвращает адрес блока памяти не менее чем требуемого размера либо 0.

В тестирующей программе будет определена глобальная переменная `freelist`, в которой хранится список
свободных блоков памяти:

![](https://caos.myltsev.ru/cgi-bin/new-
client?SID=df6483329ace2507&prob_id=16&action=194&file=image.png)

В каждом блоке первое машинное слово — размер блока в байтах минус 4, второе — адрес следующего
блока в списке. Если в списке есть блоки, у которых записанный размер не меньше size, `alloc_mem`
должна удалить первый такой блок из списка и вернуть вызывающей подпрограмме адрес тела этого блока
(адрес блока, увеличенный на 4).

Если в списке `freelist` подходящих блоков нет, то `alloc_mem` использует системный вызов `brk`,
чтобы запросить у системы `4 + actual_size` байт дополнительной памяти. `actual_size` вычисляется
как `max(4, align4(size))`, где align4 – операция округления вверх до числа, кратного 4.

Пример работы с системным вызовом `brk` приводился на лекции. Если `brk` отработал успешно, то
`alloc_mem` записывает `actual_size` в первое машинное слово полученного участка памяти и возвращает
адрес второго машинного слова.

В случае, если выделить память не удалось (результат `brk` не совпадает с его аргументом),
`alloc_mem` должна вернуть 0. При этом подпрограмма `alloc_mem` должна остаться работоспособной
(иметь возможность в дальнейшем выделить меньший объём памяти, если это возможно).
