|                      |       |
|----------------------|-------|
| **Time limit:**      | `2 s` |
| **Real time limit:** | `2 s` |
| **Memory limit:**    | `64M` |


### Problem ku08-4: kr08-4 (дореш)

Напишите функцию `void std_accumulate(void* result, const void* begin, size_t size, size_t n, void*
init_state, void (*binary_op)(void* state, const void* element_or_state)) `, которая работает
аналогично std::accumulate, а именно: по заданному массиву begin, в котором лежит n элементов
размера size, применить функцию binary_op и записать результат в указатель result. binary_op - это
некоторая коммутативная и ассоциативная бинарная операция, например, сложение. Соответственно, если
пользователь передаст в std_accumulate функцию сложения, то в result должен быть записан результат
сложения всех элементов массива.

Функция, переданная аргументом *binary_op, возвращает void и принимает два аргумента:

  * void* state - текущее состояние оператора. Например, для оператора суммы - это сумма уже обработанных элементов. Это объект, занимающий size байт, память для которого должны выделить вы в функции std_accumulate. Гарантируется, что state имеет тот же тип данных, что и элементы массива.
  * void* element_or_state - текущий элемент, передаваемый на обработку, или какое-то значение state, полученное ранее.

Таким образом, после обработки всех элементов массива, переданных функции binary_op, результат будет
записан по адресу, соответствующему указателю state. Для первого вызова binary_op следует передать
ей state, в котором будет записано значение init_state. Для копирования результата из этой
переменной в result используйте функцию memcpy. Гарантируется, что по указателю result доступно size
байт памяти.

Гарантируется, что результат binary_op не зависит от порядка выбора элементов. Гарантируется, что 4
потоков достаточно для достаточно быстрой работы функции.

### Examples

#### Input

    
    
    std_accumulate((void*)(&result), &{1, 2, 3, 4}, sizeof(int), 4, &int_zero, summator)

#### Output

    
    
    printf("%d\n", *result);
    10
    
