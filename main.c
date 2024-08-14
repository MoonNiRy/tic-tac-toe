#include <stdio.h>
#include <stdlib.h>

#define WINDOWS

#if defined(WINDOWS) 
    #define CLEAR system("cls")
#elif defined(UNIX) 
    #define CLEAR system("clear")
#endif

char field[3][3] = {
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
};
char player = 1;

void output_field() {
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            switch (field[i][j])
            {
                case 0:
                    printf(" - ");
                    break;
                case 1:
                    printf(" x ");
                    break;
                case 2:
                    printf(" o ");
                    break;
            }
            if (j < 2) {
                printf("|");
            }
        }
        printf("\n");
        if (i < 2) {
            printf("--- --- ---\n");
        }
    }
    printf("\n");
}

void clear_field() {
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            field[i][j] = 0;
        }
    }   
}

void win() {
    CLEAR;
    output_field();
    printf("Player %d win!\n", player);

    char inp;
    do {
        inp = getchar();
    } while (inp != 'e');
    
}
void draw() {
    CLEAR;
    output_field();
    printf("Draw!\n");  

    char inp; 
    do {
        inp = getchar();
    } while (inp != 'e');
}

void change_player() {
    if (player < 2) {
        player++;
    } else {
        player = 1;
    }
}
int input(char *c, char *r) {
    while(1){
        CLEAR;
        output_field();
        printf("Player %d:\n", player);
        printf("Row: ");

        if (scanf("%hhd", &(*r)) != 1) {
            while (getchar() != '\n');  // Очистка входного буффера
            continue;
        }
        if (*r > 0 && *r < 4) {
            break;
        };
    }
    while(1) {
        CLEAR;
        output_field();
        printf("Player %d:\n", player);
        printf("Column: ");

        if (scanf("%hhd", &(*c)) != 1) {
            while (getchar() != '\n');  // Очистка входного буффера
            continue;
        }
        if (*c > 0 && *c < 4) {
            break;
        }
    }

    if(field[*r - 1][*c - 1] == 1 || field[*r - 1][*c - 1] == 2) {
        return -1;
    };

    return 0;
}

int check_win() {
    //  Горизрнтали
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            if (field[i][j] != player) {
                break;
            } else if (j == 2) return 1;
        }
    }
    //  Вертикали
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            if (field[j][i] != player) {
                break;
            } else if (j == 2) return 1;
        }
    }
    //  Диагонали
    if(field[1][1] == player) {
        if(field[0][0] == player && field[2][2] == player) return 1;
        if(field[0][2] == player && field[2][0] == player) return 1;
    }

    //Проверка ничьи
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            if(field[i][j] == 0) {
                return 0;
            }
            if(i == 2 && j == 2) return 2;
        }
        
    }
    return 0;
} 

int process(char c, char r) {   
    field[r - 1][c - 1] = player;   //  Добавление хода на карту

    int check = check_win();    // return:  1 - победа, 2 - ничья, иначе - 0 
    switch (check)
    {
    case 1:
        win();
        return 1;
    case 2:
        draw();
        return 1;    
    }
    change_player();

    return 0;
}

int main() {
    char col, row;
    while (1) {
        CLEAR;
        output_field();

        if(input(&col, &row)) {
            return 0;
        }
 
        if (process(col, row)) {
            clear_field();
            change_player();
        }; 
    }
    return 0;
}