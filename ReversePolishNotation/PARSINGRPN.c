#include "stack.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>

enum Precedence { LOW = 1, MEDIUM, HIGH, VERY_HIGH };

// Вспомогательная функция для добавления оператора в стек
void addOperator(struct st **operations, char symbol, int currentPoint,
                 char *output_str) {
  while (*operations != NULL && priority((*operations)->c) > priority(symbol)) {
    output_str[currentPoint++] = delete (operations);
  }
  *operations = push(*operations, symbol);
}

// Вспомогательная функция для обработки чисел и переменных
void handleNumberOrVariable(char ch, int *currentPoint, char *output_str) {
  output_str[(*currentPoint)++] = ch;
}

void parsing_in_polish_notation(struct st *operations, char *input_str,
                                char *output_str) {
  int currentPoint = 0;
  const char *trigFunctions[] = {"sin", "cos", "tan", "ctg", "sqrt", "ln"};
  const char trigSymbols[] = {'s', 'c', 't', 'g', 'q', 'l'};
  const size_t numTrigFunctions =
      sizeof(trigFunctions) / sizeof(trigFunctions[0]);

  for (int i = 0; input_str[i] != '\0'; ++i) {
    if (input_str[i] == ')') {
      while (operations->c != '(') {
        output_str[currentPoint++] = delete (&operations);
      }
      delete (&operations); // Удалить открывающую скобку
    } else if (isdigit(input_str[i]) || input_str[i] == 'x') {
      handleNumberOrVariable(input_str[i], &currentPoint, output_str);
    } else if (input_str[i] == '(') {
      operations = push(operations, '(');
    } else if (input_str[i] == '+' || input_str[i] == '-' ||
               input_str[i] == '/' || input_str[i] == '*') {
      addOperator(&operations, input_str[i], currentPoint, output_str);
    } else {
      // Проверка на тригонометрические функции
      for (size_t j = 0; j < numTrigFunctions; ++j) {
        if (strncmp(input_str + i, trigFunctions[j],
                    strlen(trigFunctions[j])) == 0) {
          addOperator(&operations, trigSymbols[j], currentPoint, output_str);
          i +=
              strlen(trigFunctions[j]) - 1; // Сдвинуть индекс, чтобы пропустить
                                            // обработанную последовательность
          break;
        }
      }
    }
  }

  // Вывод всех оставшихся операторов из стека
  while (operations != NULL) {
    output_str[currentPoint++] = delete (&operations);
  }
  output_str[currentPoint] = '\0';
}