# Решение

[Файл](../task_i.cpp) с решением на языке C++.

# Описание задания

    Ограничение времени	1 секунда
    Ограничение памяти	512Mb
    Ввод	стандартный ввод или input.txt
    Вывод	стандартный вывод или output.txt

Перед вами журнал результативных бросков в баскетбольном матче. Ваша задача — определить итоговый результат матча.
Правила начисления очков в баскетболе таковы:

за заброшенный со штрафного броска мяч команда получает 1 очко;
за заброшенный с близкой дистанции мяч команда получает 2 очка;
за заброшенный с дальней дистанции мяч команда получает 3 очка.
Если расстояние до корзины во время броска было не более 
6 метров, то дистанция считается близкой, в противном случае — дальней. Конечно, это несколько упрощённые правила игры в баскетбол.

Формат ввода:
В первой строке записано целое число 
n — количество заброшенных мячей (1≤n≤1000). В следующих n строках содержатся сведения о заброшенных мячах. Каждая строка содержит два целых числа t_i и d_i (1≤t_i≤2, −1≤d_i≤20). Если d_i≥0, то это означает, что игрок из команды t_i забросил мяч с расстояния d_i метров до корзины. Если d_i=−1, то это означает, что игрок из команды t_i забросил мяч со штрафного броска.

Формат вывода:
Выведите результат матча — количества очков, набранных первой и второй командой, записанные через двоеточие.
Пример 1
Ввод:
3
1 2
2 5
1 10

Вывод:
5:2

Пример 2
Ввод:
4
1 2
1 -1
1 20
1 20

Вывод:
9:0

Пример 3
Ввод:
10
1 -1
1 -1
2 -1
2 -1
1 1
1 5
2 6
2 7
1 11
1 12

Вывод:
12:7