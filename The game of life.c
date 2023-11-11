//ИГРА В ЖИЗНЬ


#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <time.h>
#include <windows.h>


#define N 10;
#define H 10;

using Board= int[10][10];
//генерируем рвндомное поле
void fill_rand(Board board) {
    srand(time(NULL));

    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            if (rand() % 5 == 0) {
                board[i][j] = 1;
            }
            else {
                board[i][j] = 0;
            }
        }
    }
}
//визуализируем поле, обозначая живые и мёртвые клетки
void show(const Board board) {

    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            if (board[i][j]==1) {
                printf(" %c |", '0');
            }
            else {
                printf(" %c |", ' ');
            }
        }
        printf("%c \n", ' ');
    }
    printf("%c \n", ' ');
}


int get_x(int i) {
    return(10 + i) % 10; //закольцевали по ширине 
}
int get_y(int j) {
    return(10 + j) % 10; //закольцевали по ширине 
}

//сохраняем копию предыдущего поля
void copy(Board src, Board dst) {
    for (int i = 0; i < 10; ++i) {
        for (int  j = 0; j < 10; ++j) {
            dst[i][j] = src[i][j];
        }
    }
}

//меняем поле по правилам
void step(Board board) {
    Board prev;
    copy(board, prev);
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            //   (i-1,j-1)  (i-1,j)  (i-1,j+1)
            //    (i,j-1)    (i,j)    (i,j+1)    поле цекличное -конец провой связан с началом левой 
            //   (i+1,j-1)  (i+1,j)  (i+1,j+1)                      а низ с верхом
            int count_neib = 0;
            //соседи
            count_neib += prev[get_x(i - 1)][get_y(j - 1)];
            count_neib += prev[get_x(i - 1)][get_y(j)];
            count_neib += prev[get_x(i - 1)][get_y(j +1)];
            count_neib += prev[get_x(i)][get_y(j - 1)];
            count_neib += prev[get_x(i)][get_y(j + 1)]; 
            count_neib += prev[get_x(i + 1)][get_y(j - 1)];
            count_neib += prev[get_x(i + 1)][get_y(j)];
            count_neib += prev[get_x(i + 1)][get_y(j + 1)];

            //правила игры
            if ((prev[i][j] == 0) && (count_neib == 3)) {
                board[i][j] = 1;
           }
            else if ((count_neib < 2) || (count_neib > 3)) {
                board[i][j] = 0;
            
            }
        }
    }
}
//основная программа
int main() {
    Board board;

    fill_rand(board);//рандомное поле
    for (int k=0; k < 50; ++k) {//кол-во позиций
        show(board);//рисуем поле
        step(board);//выплняем команды
        Sleep(300);//задержка
        system("cls");;//очистка экрана
      
    }
}