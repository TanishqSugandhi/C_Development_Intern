// tic_tac_toe.c
#include <stdio.h>

char board[3][3];

void init_board() { for (int i=0;i<3;i++) for (int j=0;j<3;j++) board[i][j] = ' '; }

void print_board() {
    printf("\n");
    for (int i=0;i<3;i++){
        printf(" %c | %c | %c \n", board[i][0], board[i][1], board[i][2]);
        if (i<2) printf("---+---+---\n");
    }
    printf("\n");
}

int check_win(char p) {
    for (int i=0;i<3;i++) if (board[i][0]==p && board[i][1]==p && board[i][2]==p) return 1;
    for (int j=0;j<3;j++) if (board[0][j]==p && board[1][j]==p && board[2][j]==p) return 1;
    if (board[0][0]==p && board[1][1]==p && board[2][2]==p) return 1;
    if (board[0][2]==p && board[1][1]==p && board[2][0]==p) return 1;
    return 0;
}

int full() {
    for (int i=0;i<3;i++) for (int j=0;j<3;j++) if (board[i][j]==' ') return 0;
    return 1;
}

int main() {
    init_board();
    char player = 'X';
    int r,c;
    printf("Tic-Tac-Toe: enter row and column as 1 1 for top-left, 3 3 for bottom-right.\n");
    while (1) {
        print_board();
        printf("Player %c move (row col): ", player);
        if (scanf("%d %d", &r, &c)!=2) break;
        if (r<1||r>3||c<1||c>3) { printf("Invalid.\n"); continue; }
        if (board[r-1][c-1] != ' ') { printf("Cell occupied.\n"); continue; }
        board[r-1][c-1] = player;
        if (check_win(player)) { print_board(); printf("Player %c wins!\n", player); break; }
        if (full()) { print_board(); printf("It's a draw.\n"); break; }
        player = (player=='X') ? 'O' : 'X';
    }
    return 0;
}
