|                      |       |
|----------------------|-------|
| **Time limit:**      | `1 s` |
| **Real time limit:** | `5 s` |
| **Memory limit:**    | `64M` |


### Problem sm16-1: unix/mplex/chat

Напишите чат-сервер, который принимает подключения по протоколу TCP/IPv6 и через Unix domain сокеты,
а затем пересылает данные, полученные из любого сокета, во все остальные. При получении сигнала
SIGTERM сервер должен успешно завершить работу.

Сервер запускается так:

    
    
    ./chat_server TCP_PORT UNIX_SOCKET_FILENAME

Если порт или файл заняты (там уже есть сервер), программа должна завершиться с кодом 1.

Используйте любой механизм мультиплексирования (select, poll или epoll). Считайте, что все клиенты
быстро читают данные от сервера, так что при отправке данных системный вызов write не заблокируется.
Не порождайте дополнительных процессов или потоков исполнения.

Помните, что при попытке записи в сокет, который клиент успел закрыть, будет порождён сигнал
SIGPIPE. Это не должно привести к завершению работы сервера. Если обнаружилось, что клиент закрыл
соединение, то пытаться отправлять в него данные больше не нужно.

Тестировать сервер можно, запустив одновременно несколько команд `nc ::1 _TCP_PORT_` или `nc -U
_UNIX_SOCKET_FILENAME_`.
