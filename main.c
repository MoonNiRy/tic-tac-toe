#include <stdio.h>
#include <stdlib.h>

#define WINDOWS

#if defined(WINDOWS) 
    #define CLEAR system("cls")
#elif defined(UNIX) 
    #define CLEAR system("clear")
#endif

char area[3][3] = {
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
};

void output() {
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            switch (area[i][j])
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
}

void clear_area() {
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            area[i][j] = 0;
        }
    }   
}

void win(char player) {
    CLEAR;
    output();
    printf("Player %d win!\n", player);

    char inp;
    do {
        inp = getchar();
    } while (inp != 'e');
    
}
void draw() {
    CLEAR;
    output();
    printf("Draw!\n");  

    char inp; 
    do {
        inp = getchar();
    } while (inp != 'e');
}

int input(char *c, char *r) {
    while (1)
    {
        printf("Area: ");
        if(scanf("%hhd", &(*r)) != 1) {
            return -1;
        } 
        if (*r > 0 && *r < 4) {
            break;
        };
    }
    
    while (1)
    {
        printf("Column: ");
        if(scanf("%hhd", &(*c)) != 1) {
            return -1;
        }
        if (*c > 0 && *c < 4) {
            break;
        }
    }

    if(area[*r - 1][*c - 1] == 1 || area[*r - 1][*c - 1] == 2) {
        return -1;
    };

    return 0;
}

int check_win(char player) {
    //  Горизрнтали
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            if (area[i][j] != player) {
                break;
            } else if (j == 2) return 1;
        }
    }
    //  Вертикали
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            if (area[j][i] != player) {
                break;
            } else if (j == 2) return 1;
        }
    }
    //  Диагонали
    if(area[1][1] == player) {
        if(area[0][0] == player && area[2][2] == player) return 1;
        if(area[0][2] == player && area[2][0] == player) return 1;
    }

    //Проверка ничьи
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            if(area[i][j] == 0) {
                return 0;
            }
            if(i == 2 && j == 2) return 2;
        }
        
    }
    return 0;
} 

int process(char player, char c, char r) {
    area[r - 1][c - 1] = player; // add 

    int check = check_win(player);
    switch (check)
    {
    case 1:
        win(player);
        return 1;
    case 2:
        draw();
        return 1;    

    }
    return 0;
}

int main() {
    char col, row;
    char player = 1;
    
    while (1) {

        CLEAR;
        output();

        printf("Player %d:\n", player);
        if(input(&col, &row)) {
            return 0;
        }
 
        if (process(player, col, row)) {
            clear_area();
        };

        player++;
        if (player > 2) player = 1; 
    }
    return 0;
}