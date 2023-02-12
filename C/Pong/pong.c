#include <stdio.h>
#define TABLE_H 25  // высота поля (не меньше 7)
#define TABLE_W 80  // длина поля (не меньше 11)
#define SCORE_LIM 21  // количество очков для победы (не меньше 1)
int scorePlus(int PosBall, int hand);  // функция для проверки попадания в ворота
int keyHand(char a, int b, int hand);  // функция для перемещения ракетки
void drawer(int PosBallX, int PosBallY, int aScore, int bScore, int aHand, int bHand);  // функция для рисования поля
int main() {
  int xPosBall = TABLE_W / 2, yPosBall = TABLE_H / 2, xVar = 1, yVar = 1, scoreA = 0, scoreB = 0, handA = TABLE_H / 2, handB = handA, ballZeroY, ballZeroX;
  if (TABLE_H % 2 == 1) {yPosBall += 1;}  // проверки на четность для централизования мячика
  ballZeroX = xPosBall;
  if (TABLE_W % 2 == 1) {xPosBall += 1;}
  ballZeroY = yPosBall;
  char s1, s2;
  drawer(xPosBall, yPosBall, scoreA, scoreB, handA, handB);
  while (1) {
    while ((s1 = getchar()) != 'A' && s1 != 'a' && s1 != 'z' && s1 != 'Z' && s1 != ' ') {drawer(xPosBall, yPosBall, scoreA, scoreB, handA, handB);}  // ждем правильный ввод
    while ((s2 = getchar()) != 'k' && s2 != 'K' && s2 != 'm' && s2 != 'M' && s2 != ' ') {drawer(xPosBall, yPosBall, scoreA, scoreB, handA, handB);}
    handA += keyHand(s1, 1, handA);
    handB += keyHand(s2, 2, handB);
    if (xPosBall == 4 || xPosBall == TABLE_W - 3) {  // отражение по x
      xVar = xVar * -1;
      if (xPosBall == 4) {
        scoreA += scorePlus(yPosBall, handA);
        scorePlus(yPosBall, handA) == 1 ? yPosBall = ballZeroY, xPosBall = ballZeroX : 1;
      } else {
        scoreB += scorePlus(yPosBall, handB);
        scorePlus(yPosBall, handB) == 1 ? yPosBall = ballZeroY, xPosBall = ballZeroX : 1;
      }
    }
    if (yPosBall == 2 || yPosBall == TABLE_H - 1) {  // отражение по y
      yVar = yVar * -1;
    }
    xPosBall += xVar;  // шаги мячика
    yPosBall += yVar;
    if (scoreA == SCORE_LIM || scoreB == SCORE_LIM) {break;}  // окончание игры
    drawer(xPosBall, yPosBall, scoreA, scoreB, handA, handB);
  }
  printf("\033c\n");
  scoreA == SCORE_LIM ? printf(" Right") : printf(" Left");
  printf(" player WIN  Score %d:%d", scoreB, scoreA);  // вывод того кто выиграл
  return 0;
}
void drawer(int PosBallX, int PosBallY, int aScore, int bScore, int aHand, int bHand) {
  printf("\033c\n");  // отчистка консоли и защита от запуска без консоли
  for (int i = 1; i < TABLE_H + 1; i++) {
    for (int j = 1; j < TABLE_W + 1; j++) {
      if (i == 1 || i == TABLE_H || j == 1 || j == TABLE_W) {
        printf("%c", 178);  // цифры это аски символы чисто для графики
      } else if (PosBallX == j && PosBallY == i) {
        printf("%c", 254);
      } else if ((aHand == i && j == 3) || (aHand + 1 == i && j == 3) || (aHand + 2 == i && j == 3)) {
        printf("%c", 221);
      } else if ((bHand == i && j == TABLE_W - 2) || (bHand + 1 == i && j == TABLE_W - 2) || (bHand + 2 == i && j == TABLE_W - 2)) {
        printf("%c", 222);
      } else {
        printf("%c", ' ');
      }
    }
    printf("%c", '\n');
  }
  printf(" Score %d:%d\n", bScore, aScore);
}
int scorePlus(int PosBall, int hand) {
  int res = 1;
  if (PosBall == hand || PosBall == hand + 1 || PosBall == hand + 2) {res = 0;}  // проверка на отбитие ракеткой
  return res;
}
int keyHand(char a, int b, int hand) {
  int res = 0;
  if (b == 1) {  // проверка на ракетку
    if (a == 'a' || a == 'A') {  // проверка на ввод
      if (hand != 2) {  // проверка на край поля
        res = -1;  // сдвиг поля
      }
    }
    if (a == 'z' || a == 'Z') {
      if (hand != TABLE_H - 3) {
        res = 1;
      }
    }
  }
  if (b == 2) {
    if (a == 'k' || a == 'K') {
      if (hand != 2) {
        res = -1;
      }
    }
    if (a == 'm' || a == 'M') {
      if (hand != TABLE_H - 3) {
        res = 1;
      }
    }
  }
  return res;
}
