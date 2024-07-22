#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void transform(int *buf, int **matrix, int n, int m);
void copy_matrix(int **matrix, int **result);
void tick(int **matrix);
int check_survive(int **matrix, int i, int j);
void draw(int **grid);
void clearScreen(void);
int input(int **matrix);
void message(void);

int main(void) {
    int speed = 5;
    int grid[25][80] = {0};
    int *pointer[25];
    char c = 53;
    transform(grid[0], pointer, 25, 80);
    message();
    if (input(pointer)) {
        system("stty -icanon min 0 time 1 -echo");
        while (c != 'q') {
            if (speed != 0) {
                draw(pointer);
                tick(pointer);
            }
            if (speed == 0) speed = 5;
            usleep(1000000 / pow(2, speed));
            read(STDIN_FILENO, &c, 1);
            if (c >= 48 && c <= 57) speed = (int)c - 48;
        }
        system("stty sane");
    } else {
        clearScreen();
        printf("n/a");
    }
    return 0;
}

void message(void) {
    clearScreen();
    printf(
        "Добро пожаловать в The game of life!\nСтандартная скорость игры: 5. Чтобы изменить скорость игры, "
        "введите цифру от 0 до 9, где 0 - скорость паузы, 9 - максимальная.\nВведите начальное "
        "состояние. Чтобы завершить игру, нажмите q.\n");
}

void clearScreen(void) { printf("\033[H\033[J"); }

int input(int **matrix) {
    int flag, res = 1;
    char ch = 10;
    for (int i = 0; i < 25; i++) {
        for (int j = 0; j < 80; j++) {
            flag = scanf("%1d", &matrix[i][j]);
            if (flag != 1 || matrix[i][j] < 0 || matrix[i][j] > 1) res = 0;
        }
        scanf("%c", &ch);
        if (ch != 10) res = 0;
    }
    return res;
}

void tick(int **matrix) {
    int temp[25][80];
    int *point[25];
    transform(temp[0], point, 25, 80);
    for (int i = 0; i < 25; i++)
        for (int j = 0; j < 80; j++) temp[i][j] = check_survive(matrix, i, j);
    copy_matrix(point, matrix);
}

void copy_matrix(int **matrix, int **result) {
    for (int i = 0; i < 25; i++)
        for (int j = 0; j < 80; j++) result[i][j] = matrix[i][j];
}

void transform(int *buf, int **matrix, int n, int m) {
    for (int i = 0; i < n; i++) {
        matrix[i] = buf + i * m;
    }
}

int check_survive(int **matrix, int i, int j) {
    int count = -matrix[i][j], res = 0;
    for (int k = i - 1; k < i + 2; k++)
        for (int l = j - 1; l < j + 2; l++) count += matrix[(25 + k) % 25][(80 + l) % 80];
    if (matrix[i][j] == 0 && count == 3)
        res = 1;
    else if (matrix[i][j] == 1 && (count == 2 || count == 3))
        res = 1;
    return res;
}

void draw(int **grid) {
    clearScreen();
    for (int i = 0; i < 25; i++) {
        for (int j = 0; j < 80; j++) {
            printf("%c", grid[i][j] ? 'O' : ' ');
        }
        printf("\n");
    }
}
