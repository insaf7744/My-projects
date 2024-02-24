#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

#define WIDTH 80
#define HEIGHT 25

// Структура для клетки
typedef struct {
  int is_alive;
} Cell;

// Двумерный массив для поля
Cell field[HEIGHT][WIDTH];

// Инициализация ncurses
void initNcurses() {
  initscr(); // Инициализация экрана
  noecho(); // Отключение отображения вводимых символов
  cbreak(); // Получение клавиш без необходимости нажатия Enter
  timeout(0); // Таймаут для функции getch(), чтобы не блокировать программу
}

// Функция для завершения работы с ncurses
void endNcurses() {
  endwin(); // Завершение работы с экраном
}

// Функция для отображения состояния поля с использованием ncurses
void printField() {
  clear(); // Очистка экрана
  // Отрисовка верхней горизонтальной границы
  mvaddch(0, 0, '+'); // левый верхний угол
  mvhline(0, 1, '-', WIDTH);
  mvaddch(0, WIDTH + 1, '+'); // правый верхний угол

  for (int i = 0; i < HEIGHT; i++) {
    mvaddch(i + 1, 0, '|'); // левая вертикальная граница
    mvaddch(i + 1, WIDTH + 1, '|'); // правая вертикальная граница
    for (int j = 0; j < WIDTH; j++) {
      if (field[i][j].is_alive) {
        mvaddch(i + 1, j + 1, '#'); // Помещение символа в координаты i, j
      } else {
        mvaddch(i + 1, j + 1, ' '); // Пустое место в координатах i, j
      }
    }
  }

  // Отрисовка нижней горизонтальной границы
  mvaddch(HEIGHT + 1, 0, '+'); // левый нижний угол
  mvhline(HEIGHT + 1, 1, '-', WIDTH);
  mvaddch(HEIGHT + 1, WIDTH + 1, '+'); // правый нижний угол

  refresh(); // Обновление экрана
}

// Функция для подсчёта живых соседей клетки
int countNeighbors(int x, int y) {
  int count = 0;

  for (int i = -1; i <= 1; i++) {
    for (int j = -1; j <= 1; j++) {
      if ((i != 0 || j != 0) &&
          field[(x + i + HEIGHT) % HEIGHT][(y + j + WIDTH) % WIDTH].is_alive) {
        count++;
      }
    }
  }

  return count;
}

// Функция для обновления состояния поля
void updateField() {
  Cell newField[HEIGHT][WIDTH];

  for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      int neighbors = countNeighbors(i, j);
      newField[i][j].is_alive = field[i][j].is_alive;

      if (field[i][j].is_alive) {
        if (neighbors < 2 || neighbors > 3) {
          newField[i][j].is_alive = 0;
        }
      } else {
        if (neighbors == 3) {
          newField[i][j].is_alive = 1;
        }
      }
    }
  }

  for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      field[i][j].is_alive = newField[i][j].is_alive;
    }
  }
}

char *chooseFile(int choice) {
  char *filename;

  switch (choice) {
  case 1:
    filename = "initial_state_1.txt";
    break;
  case 2:
    filename = "initial_state_2.txt";
    break;
  case 3:
    filename = "initial_state_3.txt";
    break;
  case 4:
    filename = "initial_state_4.txt";
    break;
  case 5:
    filename = "initial_state_5.txt";
    break;
  case 6:
    system("chmod +x RNDM.sh"); // Добавляем права на исполнение скрипта RNDM.sh
    system("./RNDM.sh"); // Добавляем вызов скрипта RNDM.sh при выборе 6
    filename = "initial_state_6.txt";
    break;
  default:
    fprintf(stderr, "Неверный выбор\n");
    filename = NULL;
  }

  return filename;
}

int main() {
  int choice;
  int flag = 0;
  int speed = 300000; // Установка скорости по умолчанию в микросекундах

  printf("Выберите начальную конфигурацию (1, 2, 3, 4, 5 или 6 для random): ");
  scanf("%d", &choice);

  char *filename = chooseFile(choice);

  FILE *file = fopen(filename, "r");
  if (file == NULL) {
    fprintf(stderr, "Не удалось открыть выбранный файл\n");
    flag = 1;
  }

  // Инициализация поля через файл
  for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      // Считываем состояние клетки из файла
      char input;
      if (fscanf(file, " %c", &input) != 1) {
        fprintf(stderr, "Недостаточно данных в файле с начальным состоянием\n");
        fclose(file);
        flag = 1;
      }
      field[i][j].is_alive = (input == '#');
    }
  }

  fclose(file);

  // Инициализация ncurses
  initNcurses();

  while (1) {
    printField();
    updateField();

    int ch = getch(); // Получение введенной клавиши (без блокирования)
    if (ch == 'q' || ch == 'Q') {
      break; // Выход из цикла при нажатии q или Q
    } else if (ch == '+') {
      if (speed > 10000) { // Проверка на минимальную скорость
        speed -= 50000; // Уменьшаем скорость на 10000 микросекунд
      }
    } else if (ch == '-') {
      speed += 50000; // Увеличиваем скорость на 10000 микросекунд
    }
    void sleepscreen(int ms) {
      napms(ms);
    } // функция из библиотеки ncurses для замены usleep

    sleepscreen(speed / 1000); // установка скорости в микросекундах
  }

  endNcurses();

  return flag;
}
