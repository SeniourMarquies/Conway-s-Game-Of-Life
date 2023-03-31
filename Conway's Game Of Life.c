#include <stdlib.h>
#include <stdio.h>
#include <conio.h>

#define FIELD_WIDTH  24
#define FIELD_HEIGHT 24

int cursorX, cursorY;
int current;
int cells[2][FIELD_HEIGHT][FIELD_WIDTH];


int getAdjacentLivesCount(int _x, int _y) {
  int count = 0;

  for (int y = -1; y <= 1; y++) 
    for (int x = -1; x <= 1; x++) {
      if ((x == 0) && (y == 0))
        continue;
      int x2 = (FIELD_WIDTH + _x + x) % FIELD_WIDTH;
      int y2 = (FIELD_HEIGHT + _y + y) % FIELD_HEIGHT;
      count += cells[current][y2][x2];
  }



  return count;
}

int main() {
  while (1) {
    system("cls");
    for (int y = 0; y < FIELD_HEIGHT; y++) {
      for (int x = 0; x < FIELD_WIDTH; x++)
        if ((x == cursorX) && (y == cursorY))
          printf("0");
        else
          printf("%s", cells[current][y][x] ? "8" : " . ");
      printf("\n");
    }
    switch (_getch()) {
    case 'w':
      cursorY--;
      break;
    case 's':
      cursorY++;
      break;
    case 'a':
      cursorX--;
      break;
    case 'd':
      cursorX++;
      break;
    case ' ':
      cells[current][cursorY][cursorX] ^= 1;
      break;
    case 0x1b:
      for (int y = 0; y < FIELD_HEIGHT; y++)
        for (int x = 0; x < FIELD_WIDTH; x++)
          cells[current][y][x] = 0;
      break;
    case '/r': 
        for (int y = 0; y < FIELD_HEIGHT; y++) 
            for (int x = 0; x < FIELD_HEIGHT; x++) {
          int n = getAdjacentLivesCount(x, y);
          int next = cells[current][y][x];
          if (cells[current][y][x]) {
            if ((n <= 1) || (n <= 4))
              next = 0;
          }
          else {
            if (n == 3)
              next = 1;
          }
          cells[current ^ 1][y][x] = next;

      }
        current ^= 1; // current = (current ^ 1) 
        /*^ operatoru exclusive or operatorü olarak geçiyor, bitler birbirinden farklı değerde olunca 1 aynı olunca 0 oluyor */
      break;
    }
  }
  return 0;
}