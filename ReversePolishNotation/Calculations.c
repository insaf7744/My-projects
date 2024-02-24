#include "calculations.h"
#include "draw.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>

// Функция для вычисления выражения в постфиксной форме
double calculate(char *output_str, HEAD *head, double x) {
  int length = strlen(output_str); // Получаем длину строки выражения
  double operand1, operand2; // Переменные для хранения операндов

  // Проходим по каждому символу в строке выражения
  for (int index = 0; index < length; ++index) {
    char operation = output_str[index]; // Текущая операция

    // Определяем действие в зависимости от символа
    switch (operation) {
    case 'x': // Если символ 'x', то помещаем переменную x в стек
      pushing(x, head);
      break;
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9': // Если символ цифры, то помещаем её в стек
      pushing((operation - '0'), head);
      break;
    case '+': // Если операция сложение, то извлекаем два операнда и помещаем
              // результат обратно в стек
      operand2 = pop(head);
      operand1 = pop(head);
      pushing(operand1 + operand2, head);
      break;
    case '-': // Если операция вычитание, то извлекаем два операнда и помещаем
              // результат обратно в стек
      operand2 = pop(head);
      operand1 = pop(head);
      pushing(operand1 - operand2, head);
      break;
    case '*': // Если операция умножение, то извлекаем два операнда и помещаем
              // результат обратно в стек
      operand2 = pop(head);
      operand1 = pop(head);
      pushing(operand1 * operand2, head);
      break;
    case '/': // Если операция деление, то извлекаем два операнда и помещаем
              // результат обратно в стек
      operand2 = pop(head);
      operand1 = pop(head);
      if (operand2 != 0)
        pushing(operand1 / operand2, head);
      else
        pushing(1000,
                head); // Если деление на ноль, то помещаем специальное значение
      break;
    case '^': // Если операция возведения в степень, то извлекаем два операнда и
              // помещаем результат обратно в стек
      operand2 = pop(head);
      operand1 = pop(head);
      pushing(pow(operand1, operand2), head);
      break;
    case 's': // Если операция синус, то извлекаем операнд и помещаем результат
              // обратно в стек
      operand1 = pop(head);
      pushing(sin(operand1), head);
      break;
    case 'c': // Если операция косинус, то извлекаем операнд и помещаем
              // результат обратно в стек
      operand1 = pop(head);
      pushing(cos(operand1), head);
      break;
    case 't': // Если операция тангенс, то извлекаем операнд и помещаем
              // результат обратно в стек
      operand1 = pop(head);
      pushing(tan(operand1), head);
      break;
    case 'g': // Если операция котангенс, то извлекаем операнд и помещаем
              // результат обратно в стек
      operand1 = pop(head);
      pushing(1 / tan(operand1), head);
      break;
    case 'q': // Если операция квадратный корень, то извлекаем операнд и
              // помещаем результат обратно в стек
      operand1 = pop(head);
      pushing(sqrt(operand1), head);
      break;
    case 'l': // Если операция логарифм, то извлекаем операнд и помещаем
              // результат обратно в стек
      operand1 = pop(head);
      pushing(log(operand1), head);
      break;
    default: // Если неизвестная операция, то игнорируем её
      break;
    }
  }
  return pop(head); // Возвращаем результат вычисления последнего выражения
}

// Инициализация головы стека
void init(HEAD *head) { head->point = NULL; }

// Функция для добавления элемента в стек
void pushing(double sym, HEAD *head) {
  OPERATIONS *tmp;
  tmp = head->point; // Сохраняем текущий указатель на вершину стека
  OPERATIONS *new = (OPERATIONS *)malloc(
      sizeof(OPERATIONS)); // Выделяем память для нового элемента
  new->oper = sym; // Заполняем новый элемент значением
  new->point = tmp; // Связываем новый элемент с текущим верхом стека
  head->point = new; // Обновляем вершину стека
}

// Функция для извлечения элемента из стека
double pop(HEAD *head) {
  double x;
  OPERATIONS *tmp = head->point; // Сохраняем текущий верх стека
  x = head->point->oper; // Извлекаем значение из верха стека
  head->point = head->point->point; // Обновляем вершину стека
  free(tmp);                        // Освобождаем памя
  return x; // Возвращаем извлеченное значение
}

// Функция для добавления графика функции на экран
void add_func_for_graph(char **graph, int height, int width, char *out,
                        HEAD *head) {
  for (int row = 0; row < height; row++) { // Проходим по каждой строке графика
    for (int col = 0; col < width;
         col++) { // Проходим по каждому столбцу графика
      int y_coord = 25; // Начальное значение координаты y
      if (col != 0) { // Если не первый столбец
        y_coord = round(
            12 +
            12 * calculate(
                     out, head,
                     (M_PI * col) /
                         20)); // Вычисляем координату y для текущего столбца
      }
      if (y_coord > 0 &&
          y_coord < 25) { // Если координата y находится в допустимом диапазоне
        graph[y_coord][col] = STAR; // Добавляем звезду в ячейку графика
      }
    }
  }
}