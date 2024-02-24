#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "calculations.h"
#include "draw.h"
#include "stack.h"

int main() {
  // Выделяем память под двумерный массив для графика
  char **graph = calloc_matrix(HEIGHT, WIDTH +  1);

  // Инициализируем стек операций
  struct st *operations = NULL;

  // Буферы для ввода и вывода
  char input_string[80], output_string[80];

  // Очищаем буфер ввода
  fflush(stdin);

  // Читаем строку ввода пользователя
  fgets(input_string,  80, stdin);

  // Преобразуем введенное пользователем выражение в постфиксную форму
  parsing_in_polish_notation(operations, input_string, output_string);

  // Выводим результат преобразования
  printf("\n%s\n", output_string);

  // Очищаем буфер ввода
  fflush(stdin);

  // Инициализируем структуру для работы со стеком
  HEAD head;
  init(&head);

  // Инициализируем график
  init_graph(graph, HEIGHT, WIDTH);

  // Добавляем график функции на график
  add_func_for_graph(graph, HEIGHT, WIDTH, output_string, &head);

  // Рисуем график
  draw_graph(graph, HEIGHT);

  // Освобождаем память, занятую двумерным массивом графика
  free_matrix(graph, HEIGHT);

  // Завершаем программу
  return  0;
}
