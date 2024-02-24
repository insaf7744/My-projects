#!/ bin / bash

#Создаем пустой файл
> initial_state_6.txt

#Задаем количество столбцов и строк
        columns = 80 lines = 25

#Генерируем содержание файла
    for ((i = 0; i < lines; i++));
do
  line = "" for ((j = 0; j < columns; j++));
do
  if ((RANDOM % 4))
    ;
then line += "." else line +=
    "#" fi done echo $line >> initial_state_6.txt #записываем строку в файл done
