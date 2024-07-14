#include <stdio.h>
#include <termios.h>  //библиотеки интерактива
#include <unistd.h>
#define WIDTH 80
#define HEIGHT 25
#define PADDLE_SIZE 3
#define WIN_SCORE 21
int ball_x = WIDTH / 2, ball_y = HEIGHT / 2;
int ball_dir_x = 1, ball_dir_y = 1;
int paddle1_y = HEIGHT / 2, paddle2_y = HEIGHT / 2;
int score1 = 0, score2 = 0;
void print_score(void) { printf("Score: Player 1: %d | Player 2: %d\n", score1, score2); }
void clear_screen(void) {
    for (int i = 0; i < 30; i++) {
        printf("\n");
    }
}
void draw(void) {
    clear_screen();  // Очистка экрана
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (x == 0) {
                if (y >= paddle1_y && y < paddle1_y + PADDLE_SIZE) {
                    printf("|");
                } else {
                    printf(" ");
                }
            } else if (x == WIDTH - 1) {
                if (y >= paddle2_y && y < paddle2_y + PADDLE_SIZE) {
                    printf("|");
                } else {
                    printf(" ");
                }
            } else if (x == ball_x && y == ball_y) {
                printf("O");
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
    print_score();
}
void update(void) {
    ball_x += ball_dir_x;
    ball_y += ball_dir_y;
    if (ball_y <= 0 || ball_y >= HEIGHT - 1) {
        ball_dir_y = -ball_dir_y;  // Отскок от верхней и нижней стен
    }
    if (ball_x == 1 && ball_y >= paddle1_y && ball_y < paddle1_y + PADDLE_SIZE) {
        ball_dir_x = 1;  // Отскок от первой ракетки
    } else if (ball_x == WIDTH - 2 && ball_y >= paddle2_y && ball_y < paddle2_y + PADDLE_SIZE) {
        ball_dir_x = -1;  // Отскок от второй ракетки
    } else if (ball_x < 0) {
        score2++;  // Очко для второго игрока
        ball_x = WIDTH / 2;
        ball_y = HEIGHT / 2;  // Перезапуск мяча
    } else if (ball_x >= WIDTH) {
        score1++;  // Очко для первого игрока
        ball_x = WIDTH / 2;
        ball_y = HEIGHT / 2;  // Перезапуск мяча
    }
}
void move_paddles(char input) {
    if ((input == 'A' || input == 'a') && paddle1_y > 0) {
        paddle1_y--;  // Движение первой ракетки вверх
    } else if ((input == 'Z' || input == 'z') && paddle1_y < HEIGHT - PADDLE_SIZE) {
        paddle1_y++;  // Движение первой ракетки вниз
    }
    if ((input == 'K' || input == 'k') && paddle2_y > 0) {
        paddle2_y--;  // Движение второй ракетки вверх
    } else if ((input == 'M' || input == 'm') && paddle2_y < HEIGHT - PADDLE_SIZE) {
        paddle2_y++;  // Движение второй ракетки вниз
    }
}
int main(void) {
    struct termios old, new;  //реализация функций ввода без enter:
    tcgetattr(0, &old);
    new = old;
    new.c_lflag &= ~ICANON;
    new.c_lflag &= ~ECHO;
    tcsetattr(0, TCSANOW, &new);
    while (score1 < WIN_SCORE && score2 < WIN_SCORE) {
        char input;
        draw();
        input = getchar();
        if (input == ' ') {  // Пропустить шаг
        } else {
            move_paddles(input);
        }
        update();
    }
    draw();
    if (score1 == WIN_SCORE) {
        printf("Player 1 wins!\n");
    } else {
        printf("Player 2 wins!\n");
    }
    tcsetattr(0, TCSANOW, &old);
    return 0;
}
