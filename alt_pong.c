// I WANT TO PLAY WITH YOU
//         YOUR FRIEND, AI
#include <stdio.h>  // размер игрового поля:
#define WIDTH 80
#define HEIGHT 25
#define PADDLE_SIZE 3  //размер лопаток
#define WIN_SCORE 21   // количество очков для победы
int main(void) {       //ввод переменных:
    int score1 = 0, score2 = 0, ball_x = WIDTH / 2, ball_y = HEIGHT / 2, ball_dir_x = 1, ball_dir_y = 1,
        paddle1_y = HEIGHT / 2, paddle2_y = HEIGHT / 2;
    while (score1 < WIN_SCORE && score2 < WIN_SCORE) {  // цикл игры:
        for (int i = 0; i < 30; i++) printf("\n");  // очистка экрана; отрисовка кадра:
        for (int y = 0; y < HEIGHT; y++) {
            for (int x = 0; x < WIDTH; x++) {
                if (x == 0 && y >= paddle1_y && y < paddle1_y + PADDLE_SIZE) {
                    printf("|");
                } else if (x == WIDTH - 1 && y >= paddle2_y && y < paddle2_y + PADDLE_SIZE) {
                    printf("|");
                } else if (x == ball_x && y == ball_y) {
                    printf("O");
                } else {
                    printf(" ");
                }
            }
            printf("\n");
        }
        printf("Score: Player 1: %d | Player 2: %d\n", score1, score2);  // вывод очков обновляемых очков.
        char input = getchar();  //ввод символов управления; условия ввода:
        if (input == 'A' || input == 'a') paddle1_y = paddle1_y > 0 ? paddle1_y - 1 : paddle1_y;
        if (input == 'Z' || input == 'z')
            paddle1_y = paddle1_y < HEIGHT - PADDLE_SIZE ? paddle1_y + 1 : paddle1_y;
        if (input == 'K' || input == 'k') paddle2_y = paddle2_y > 0 ? paddle2_y - 1 : paddle2_y;
        if (input == 'M' || input == 'm')
            paddle2_y = paddle2_y < HEIGHT - PADDLE_SIZE ? paddle2_y + 1 : paddle2_y;
        ball_x += ball_dir_x;  //физика шарика:
        ball_y += ball_dir_y;
        if (ball_y == 0 || ball_y == HEIGHT - 1) ball_dir_y = -ball_dir_y;
        if (ball_x == 1 && ball_y >= paddle1_y && ball_y < paddle1_y + PADDLE_SIZE) ball_dir_x = 1;
        if (ball_x == WIDTH - 2 && ball_y >= paddle2_y && ball_y < paddle2_y + PADDLE_SIZE) ball_dir_x = -1;
        if (ball_x < 0) {  //регистрация гола:
            score2++;
            ball_x = WIDTH / 2, ball_y = HEIGHT / 2;
        }
        if (ball_x >= WIDTH) {
            score1++;
            ball_x = WIDTH / 2, ball_y = HEIGHT / 2;
        }
    }  // вывод результа:
    printf(score1 == WIN_SCORE ? "Player 1 wins!\n" : "Player 2 wins!\n");
    return 0;
}
