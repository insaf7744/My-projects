#include <stdio.h>
#include "calculations.h"
#include "stack.h"

int main(void) {
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

  // Значение x для вычисления функции
  int x =  5;

  // Вычисляем значение функции для заданного x
  double y = counter(output_string, &head, x);

  // Выводим результат вычисления функции
  printf("%lf", y);

  // Завершаем программу
  return  0;
}