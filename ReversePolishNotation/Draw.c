#include "draw.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// Функция для выделения памяти под двумерный массив
char **calloc_matrix(int height, int width) {
  char **matrix;
  matrix = (char **)calloc(
      height, sizeof(char *)); // Выделяем память под массив указателей
  for (int y = 0; y < height; y++)
    matrix[y] = (char *)calloc(
        width, sizeof(char)); // Выделяем память под каждую строку массива
  return matrix; // Возвращаем указатель на массив
}

// Функция для инициализации графика
void init_graph(char **graph, int height, int width) {
  for (int y = 0; y < height; y++) { // Проходим по каждой строке графика
    for (int x = 0; x < width; x++) { // Проходим по каждому столбцу графика
      graph[y][x] = POINT; // Заполняем каждую ячейку символом точки
    }
  }
  for (int y = 0; y < HEIGHT; y++) { // Проходим по каждой строке графика
    graph[y][width + 1] =
        '\0'; // Заполняем ячейку после последнего столбца нулевым символом
  }
}

// Функция для отрисовки графика
void draw_graph(char **graph, int height) {
  printf("\e[1;1H\e[2J"); // Очищаем экран и перемещаем курсор в начало экрана
  for (int y = 0; y < height; y++) { // Проходим по каждой строке графика
    printf("%s\n", graph[y]); // Выводим строку графика
  }
}

// Функция для освобождения памяти, занятой двумерным массивом
void free_matrix(char **graph, int height) {
  for (int y = 0; y < height; y++)
    free(graph[y]); // Освобождаем память каждой строки массива
  free(graph); // Освобождаем память самого массива
}