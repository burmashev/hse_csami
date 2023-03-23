|                      |       |
|----------------------|-------|
| **Time limit:**      | `1 s` |
| **Real time limit:** | `5 s` |
| **Memory limit:**    | `64M` |


### Problem sm18-1: asm/atomic/spinlock

Реализуйте спинлок.

Напишите на языке ассемблера x86 функции с такими сигнатурами:

    
    
    void spin_lock(volatile int *s);
    void spin_unlock(volatile int *s);

Пользователи будут вызывать эти функции, чтобы создать в коде критическую секцию с активным
ожиданием:

    
    
    int s;
    ...
    spin_lock(&s);
    // critical section here
    spin_unlock(&s);

Предполагается, что спинлок инициализируется значением 0.

