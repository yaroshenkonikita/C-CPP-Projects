#include <time.h>
#include <stdio.h>
#include <curses.h>
#include <unistd.h>
#define _WORLD_WIDTH_ 80  // Ширина игрового поля
#define _WORLD_HEIGHT_ 25  // Высота игрового поля

void input(int* field);
int check_input(int argc, int speed);
void draw(int field[][_WORLD_WIDTH_]);
void life(int* field);
void speed_acceleration(int* acceleration, int* count_when_to_switch_speed, int* switch_speed);
void incorrect_result();

int main(int argc, char* argv[]) {
    int field[_WORLD_HEIGHT_][_WORLD_WIDTH_];
    int acceleration = 0;
    int count_when_to_switch_speed = 0;
    int switch_speed = 0;
    int speed = argv[1][0] - '0';
    if (check_input(argc, speed) == 0) {
        input(&field[0][0]);
        printf("\e[H\e[2J\e[3J");
        draw(field);
        while (1) {
            usleep(100000 * speed - acceleration);
            printf("\e[H\e[2J\e[3J");
            speed_acceleration(&acceleration, &count_when_to_switch_speed, &switch_speed);
            life(&field[0][0]);
            draw(field);
            }
    } else {
        incorrect_result();
    }
    return 0;
}

void input(int* field) {
    int initial_setup_count = 0;
    while (initial_setup_count < (_WORLD_HEIGHT_ * _WORLD_WIDTH_)) {
        for (int HEIGHT = 0; HEIGHT < _WORLD_HEIGHT_; HEIGHT++) {
            for (int WIDTH = 0; WIDTH < _WORLD_WIDTH_; WIDTH++) {
                scanf("%d", &field[HEIGHT * _WORLD_WIDTH_ +  WIDTH]);
                initial_setup_count += 1;
            }
        }
    }
}

int check_input(int argc, int speed) {
    int result = 0;
    if ((argc < 0) || (argc > 2) || (speed > 9) || (speed < 1)) {
        result = 1;
    }
    return result;
}

void incorrect_result() {
    printf("n/a");
}

void speed_acceleration(int* acceleration, int* count_when_to_switch_speed, int* switch_speed) {
    if ((*count_when_to_switch_speed < 100) && (*switch_speed == 0)) {
        *acceleration += 500;
        *count_when_to_switch_speed += 1;
        if (*count_when_to_switch_speed == 100) {
            *switch_speed = 1;
        }
    } else {
        *acceleration -= 500;
        *count_when_to_switch_speed -= 1;
        if (*count_when_to_switch_speed == 0) {
            *switch_speed = 0;
        }
    }
}

void life(int* field) {
    int field_temp[_WORLD_HEIGHT_][_WORLD_WIDTH_];
    for (int HEIGHT = 0; HEIGHT < _WORLD_HEIGHT_; HEIGHT++)  {
        for (int WIDTH = 0; WIDTH < _WORLD_WIDTH_; WIDTH++) {
            field_temp[HEIGHT][WIDTH] = field[HEIGHT * _WORLD_WIDTH_ +  WIDTH];
        }
    }
int ScoreOfLife = 0, LeftExWidth, RightExWidth, HighExHeight, LowExHeight;
  for (int HEIGHT = 0; HEIGHT < _WORLD_HEIGHT_; HEIGHT++) {
    for (int WIDTH = 0; WIDTH < _WORLD_WIDTH_; WIDTH++) {
      LeftExWidth = 1; RightExWidth = 1; HighExHeight = 1; LowExHeight = 1;
      if (WIDTH == 0) {LeftExWidth = 1 - _WORLD_WIDTH_;}
      if (WIDTH == _WORLD_WIDTH_ - 1) {RightExWidth = 1 - _WORLD_WIDTH_;}
      if (HEIGHT == 0) {HighExHeight = 1 - _WORLD_HEIGHT_;}
      if (HEIGHT == _WORLD_HEIGHT_ - 1) {LowExHeight = 1 - _WORLD_HEIGHT_;}
      ScoreOfLife += field_temp[HEIGHT - HighExHeight][WIDTH - LeftExWidth] +
      field_temp[HEIGHT - HighExHeight][WIDTH] +
      field_temp[HEIGHT - HighExHeight][WIDTH + RightExWidth] +
      field_temp[HEIGHT][WIDTH - LeftExWidth] +
      field_temp[HEIGHT][WIDTH + RightExWidth] +
      field_temp[HEIGHT + LowExHeight][WIDTH - LeftExWidth] +
      field_temp[HEIGHT + LowExHeight][WIDTH] +
      field_temp[HEIGHT + LowExHeight][WIDTH + RightExWidth];
      field[HEIGHT * _WORLD_WIDTH_ +  WIDTH] = ((ScoreOfLife == 2) &&
      (field_temp[HEIGHT][WIDTH] == 1)) ||
      (ScoreOfLife == 3);
      ScoreOfLife = 0;
    }
  }
}

void draw(int field[][_WORLD_WIDTH_]) {
    for (int HEIGHT = 0; HEIGHT < _WORLD_HEIGHT_; HEIGHT++) {
        for (int WIDTH = 0; WIDTH < _WORLD_WIDTH_; WIDTH++) {
            if (field[HEIGHT][WIDTH] == 1) {
                printf("#");
            } else {
                printf(".");
            }
        }
    printf("\n");
    }
}
