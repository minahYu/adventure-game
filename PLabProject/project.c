#include <stdio.h>
#include <conio.h>
#include <Windows.h>

#define BLACK   0
#define BLUE1   1
#define GREEN1   2
#define CYAN1   3
#define RED1   4
#define MAGENTA1 5
#define YELLOW1   6
#define GRAY1   7
#define GRAY2   8
#define BLUE2   9
#define GREEN2   10
#define CYAN2   11
#define RED2   12
#define MAGENTA2 13
#define YELLOW2   14
#define WHITE   15

#define ESC 0x1b
#define SPACE 0x20
#define U 0x75

#define UP  0x48 // Up key는 0xe0 + 0x48 두개의 값이 들어온다.
#define DOWN 0x50
#define LEFT 0x4b
#define RIGHT 0x4d

#define UP2     'w'
#define DOWN2   's'
#define LEFT2   'a'
#define RIGHT2  'd'

#define SPECIAL1 0xe0 // 특수키는 0xe0 + key 값으로 구성된다.
#define SPECIAL2 0x00 // keypad 경우 0x00 + key 로 구성된다.

#define WIDTH 80
#define HEIGHT 24

#define XSIZE 16
#define YSIZE 16

void stage1();
void stage2();
int score[2] = { 0, 0 };
int life[2] = { 3, 3 };
int stage = 0;
int time_out = 20;

//stage1
int newx1, newx2;
int x1, x2;
int newy1, newy2;
int y1, y2;
int lr_1_1 = 1, ud_1_1 = 1; //1P용 -> lr : 1은 오른쪽, 2는 왼쪽 / ud : 1은 위쪽, 2는 아래쪽
int lr_2_1 = 1, ud_2_1 = 1; //2P용 -> lr : 3은 오른쪽, 4는 왼쪽 / ud : 3은 위쪽, 4는 아래쪽

//stage2
int newx1_2, newx2_2;
int x1_2, x2_2;
int newy1_2, newy2_2;
int y1_2, y2_2;
int lr_1_2 = 1, ud_1_2 = 1; //1P용 -> lr : 1은 오른쪽, 2는 왼쪽 / ud : 1은 위쪽, 2는 아래쪽
int lr_2_2 = 1, ud_2_2 = 1; //2P용 -> lr : 3은 오른쪽, 4는 왼쪽 / ud : 3은 위쪽, 4는 아래쪽

//stage3
int newx1_3, newx2_3;
int x1_3, x2_3;
int newy1_3, newy2_3;
int y1_3, y2_3;
int lr_1_3 = 1, ud_1_3 = 1; //1P용 -> lr : 1은 오른쪽, 2는 왼쪽 / ud : 1은 위쪽, 2는 아래쪽
int lr_2_3 = 1, ud_2_3 = 1; //2P용 -> lr : 3은 오른쪽, 4는 왼쪽 / ud : 3은 위쪽, 4는 아래쪽

//stage4
int newx1_4, newx2_4;
int x1_4, x2_4;
int newy1_4, newy2_4;
int y1_4, y2_4;
int lr_1_4 = 1, ud_1_4 = 1; //1P용 -> lr : 1은 오른쪽, 2는 왼쪽 / ud : 1은 위쪽, 2는 아래쪽
int lr_2_4 = 1, ud_2_4 = 1; //2P용 -> lr : 3은 오른쪽, 4는 왼쪽 / ud : 3은 위쪽, 4는 아래쪽

//stage5
int newx1_5, newx2_5;
int x1_5, x2_5;
int newy1_5, newy2_5;
int y1_5, y2_5;
int lr_1_5 = 1, ud_1_5 = 1; //1P용 -> lr : 1은 오른쪽, 2는 왼쪽 / ud : 1은 위쪽, 2는 아래쪽
int lr_2_5 = 1, ud_2_5 = 1; //2P용 -> lr : 3은 오른쪽, 4는 왼쪽 / ud : 3은 위쪽, 4는 아래쪽

int map1[XSIZE][YSIZE] = {
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1},
    {1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,4,0,0,0,0,0,0,1,1,1,1},
    {1,0,0,1,1,0,0,0,0,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,1,1,1,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,1,1,1,0,0,0,0,0,1},
    {1,0,0,0,1,1,1,1,1,1,0,0,0,0,0,1},
    {1,0,0,0,1,1,1,1,1,1,0,0,1,1,0,1},
    {1,0,0,0,1,1,0,0,0,0,0,0,1,1,0,1},
    {1,0,0,0,1,1,0,0,0,0,0,0,1,1,0,1},
    {1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,1},
    {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,0,0,0,1,1,0,0,0,0,0,1},
    {1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,1},
    {1,1,0,0,0,0,5,0,1,1,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,0,3,1}
};
int map1_[XSIZE][YSIZE] = {
   1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,
   1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,1,
   1,0,0,0,0,4,0,0,0,0,0,0,1,1,1,1,
   1,0,0,1,1,0,0,0,0,1,1,1,1,1,1,1,
   1,0,0,0,0,0,0,1,1,1,0,0,0,0,0,1,
   1,0,0,0,0,0,0,1,1,1,0,0,0,0,0,1,
   1,0,0,0,1,1,1,1,1,1,0,0,0,0,0,1,
   1,0,0,0,1,1,1,1,1,1,0,0,1,1,0,1,
   1,0,0,0,1,1,0,0,0,0,0,0,1,1,0,1,
   1,0,0,0,1,1,0,0,0,0,0,0,1,1,0,1,
   1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,1,
   1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
   1,1,1,1,1,0,0,0,1,1,0,0,0,0,0,1,
   1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,1,
   1,1,0,0,0,0,5,0,1,1,0,0,0,0,0,1,
   1,1,1,1,1,1,1,1,1,1,1,1,1,0,3,1
};

int map2[XSIZE][YSIZE] = {
   1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,
   1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,1,
   1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,1,
   1,1,0,0,1,1,0,0,1,1,0,0,0,0,0,1,
   1,1,0,0,4,0,0,1,1,1,1,1,1,1,1,1,
   1,1,0,0,0,0,0,1,1,1,1,1,1,1,1,1,
   1,0,0,5,1,1,1,1,1,1,0,0,0,0,0,1,
   1,0,0,0,1,1,1,1,1,1,0,0,0,0,0,1,
   1,1,0,0,1,1,0,0,0,0,0,0,1,1,0,1,
   1,1,0,0,1,1,0,0,0,0,0,0,1,1,0,1,
   1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,1,
   1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,1,
   1,1,1,1,0,0,0,0,1,1,0,0,1,1,0,1,
   1,1,0,0,0,0,0,0,1,1,0,0,1,1,0,1,
   1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,1,
   1,1,1,1,1,1,1,1,1,1,1,1,1,0,3,1
};
int map2_[XSIZE][YSIZE] = {
   1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,
   1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,1,
   1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,1,
   1,1,0,0,1,1,0,0,1,1,0,0,0,0,0,1,
   1,1,0,0,4,0,0,1,1,1,1,1,1,1,1,1,
   1,1,0,0,0,0,0,1,1,1,1,1,1,1,1,1,
   1,0,0,5,1,1,1,1,1,1,0,0,0,0,0,1,
   1,0,0,0,1,1,1,1,1,1,0,0,0,0,0,1,
   1,1,0,0,1,1,0,0,0,0,0,0,1,1,0,1,
   1,1,0,0,1,1,0,0,0,0,0,0,1,1,0,1,
   1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,1,
   1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,1,
   1,1,1,1,0,0,0,0,1,1,0,0,1,1,0,1,
   1,1,0,0,0,0,0,0,1,1,0,0,1,1,0,1,
   1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,1,
   1,1,1,1,1,1,1,1,1,1,1,1,1,0,3,1
};

int map3[XSIZE][YSIZE] = {
   1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,
   1,1,1,1,1,1,1,1,1,1,0,1,1,0,0,1,
   1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
   1,0,0,0,0,0,1,1,0,0,0,0,0,0,0,1,
   1,0,0,0,1,1,1,1,1,1,0,0,1,1,0,1,
   1,0,0,1,1,1,1,1,1,1,5,1,1,1,0,1,
   1,0,1,1,1,1,1,1,1,1,1,1,1,1,7,1,
   1,0,0,1,1,1,1,1,1,1,6,0,0,0,0,1,
   1,1,0,1,1,1,1,1,0,0,0,1,1,0,0,1,
   1,1,0,0,0,1,1,1,1,0,1,1,1,1,7,1,
   1,0,0,0,0,0,1,1,0,0,0,0,1,0,0,1,
   1,0,0,0,0,1,1,4,0,0,0,1,0,0,1,1,
   1,0,0,0,0,1,1,1,1,0,0,1,1,0,1,1,
   1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,
   1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,1,
   1,1,1,1,1,1,1,1,1,1,1,1,0,0,3,1
};
int map3_[XSIZE][YSIZE] = {
   1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,
   1,1,1,1,1,1,1,1,1,1,0,1,1,0,0,1,
   1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
   1,0,0,0,0,0,1,1,0,0,0,0,0,0,0,1,
   1,0,0,0,1,1,1,1,1,1,0,0,1,1,0,1,
   1,0,0,1,1,1,1,1,1,1,5,1,1,1,0,1,
   1,0,1,1,1,1,1,1,1,1,1,1,1,1,7,1,
   1,0,0,1,1,1,1,1,1,1,6,0,0,0,0,1,
   1,1,0,1,1,1,1,1,0,0,0,1,1,0,0,1,
   1,1,0,0,0,1,1,1,1,0,1,1,1,1,7,1,
   1,0,0,0,0,0,1,1,0,0,0,0,1,0,0,1,
   1,0,0,0,0,1,1,4,0,0,0,1,0,0,1,1,
   1,0,0,0,0,1,1,1,1,0,0,1,1,0,1,1,
   1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,
   1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,1,
   1,1,1,1,1,1,1,1,1,1,1,1,0,0,3,1
};

int map4[XSIZE][YSIZE] = {
   1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,
   1,1,1,1,1,1,1,0,0,0,0,0,1,0,0,1,
   1,1,1,0,0,4,0,0,0,1,0,0,1,0,0,1,
   1,1,1,0,0,0,0,0,0,1,0,0,0,0,0,1,
   1,1,1,0,0,0,0,0,1,0,0,0,0,0,0,1,
   1,1,1,0,0,0,0,0,1,0,0,0,0,0,1,1,
   1,0,0,0,0,0,1,1,1,0,0,0,5,0,0,1,
   1,0,0,0,0,1,1,1,1,1,1,1,1,0,0,1,
   1,0,0,1,1,1,1,0,0,1,1,1,1,1,1,1,
   1,0,0,1,1,1,1,0,0,1,1,1,1,1,1,1,
   1,0,1,1,1,1,1,0,0,1,1,0,0,0,0,1,
   1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,1,
   1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,
   1,0,0,1,1,1,0,0,0,0,0,0,0,0,1,1,
   1,0,0,1,1,1,1,1,1,1,1,0,0,0,1,1,
   1,1,1,1,1,1,1,1,1,1,1,1,0,0,3,1
};
int map4_[XSIZE][YSIZE] = {
   1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,
   1,1,1,1,1,1,1,0,0,0,0,0,1,0,0,1,
   1,1,1,0,0,4,0,0,0,1,0,0,1,0,0,1,
   1,1,1,0,0,0,0,0,0,1,0,0,0,0,0,1,
   1,1,1,0,0,0,0,0,1,0,0,0,0,0,0,1,
   1,1,1,0,0,0,0,0,1,0,0,0,0,0,1,1,
   1,0,0,0,0,0,1,1,1,0,0,0,5,0,0,1,
   1,0,0,0,0,1,1,1,1,1,1,1,1,0,0,1,
   1,0,0,1,1,1,1,0,0,1,1,1,1,1,1,1,
   1,0,0,1,1,1,1,0,0,1,1,1,1,1,1,1,
   1,0,1,1,1,1,1,0,0,1,1,0,0,0,0,1,
   1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,1,
   1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,
   1,0,0,1,1,1,0,0,0,0,0,0,0,0,1,1,
   1,0,0,1,1,1,1,1,1,1,1,0,0,0,1,1,
   1,1,1,1,1,1,1,1,1,1,1,1,0,0,3,1
};

int map5[XSIZE][YSIZE] = {
   1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,
   1,0,0,0,0,1,1,0,0,0,0,0,1,0,0,1,
   1,0,0,0,0,1,1,0,1,1,1,0,1,0,0,1,
   1,0,0,0,0,0,1,0,1,0,1,0,1,0,0,1,
   1,1,0,0,0,0,0,0,1,0,1,0,1,0,0,1,
   1,1,0,0,0,0,0,0,1,0,1,0,0,0,1,1,
   1,1,0,0,1,1,0,0,1,0,1,1,0,0,1,1,
   1,1,0,0,1,1,5,0,0,0,1,1,0,0,1,1,
   1,0,0,0,1,1,1,1,1,1,1,1,0,0,0,1,
   1,0,0,0,1,1,1,1,1,1,1,1,1,0,0,1,
   1,1,4,0,0,0,1,1,1,1,0,0,0,1,1,1,
   1,1,0,0,0,0,1,1,1,1,0,1,0,1,1,1,
   1,1,0,0,0,0,0,0,1,1,0,1,0,1,1,1,
   1,1,1,1,0,0,0,0,0,0,0,1,0,0,1,1,
   1,1,1,1,0,0,1,1,1,1,1,0,1,0,0,1,
   1,1,1,1,1,1,1,1,1,1,1,1,0,0,3,1
};
int map5_[XSIZE][YSIZE] = {
   1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,
   1,0,0,0,0,1,1,0,0,0,0,0,1,0,0,1,
   1,0,0,0,0,1,1,0,1,1,1,0,1,0,0,1,
   1,0,0,0,0,0,1,0,1,0,1,0,1,0,0,1,
   1,1,0,0,0,0,0,0,1,0,1,0,1,0,0,1,
   1,1,0,0,0,0,0,0,1,0,1,0,0,0,1,1,
   1,1,0,0,1,1,0,0,1,0,1,1,0,0,1,1,
   1,1,0,0,1,1,5,0,0,0,1,1,0,0,1,1,
   1,0,0,0,1,1,1,1,1,1,1,1,0,0,0,1,
   1,0,0,0,1,1,1,1,1,1,1,1,1,0,0,1,
   1,1,4,0,0,0,1,1,1,1,0,0,0,1,1,1,
   1,1,0,0,0,0,1,1,1,1,0,1,0,1,1,1,
   1,1,0,0,0,0,0,0,1,1,0,1,0,1,1,1,
   1,1,1,1,0,0,0,0,0,0,0,1,0,0,1,1,
   1,1,1,1,0,0,1,1,1,1,1,0,1,0,0,1,
   1,1,1,1,1,1,1,1,1,1,1,1,0,0,3,1
};

int map6[XSIZE][YSIZE] = {
   1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
   1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,
   1,0,0,0,1,0,0,0,0,0,5,0,1,0,0,1,
   1,0,0,1,0,0,0,0,0,0,0,0,1,0,0,1,
   1,0,0,0,5,0,0,0,0,0,0,0,0,0,0,1,
   1,0,0,0,0,0,0,0,0,0,0,0,5,0,0,1,
   1,0,0,0,0,0,0,5,0,0,0,0,0,0,0,1,
   1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,
   1,0,0,0,0,1,0,0,0,0,0,5,0,0,0,1,
   1,0,0,5,0,1,1,1,0,0,0,0,0,0,0,1,
   1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
   1,1,1,0,0,0,0,0,0,0,1,1,0,5,0,1,
   1,0,1,1,0,0,0,0,0,1,1,0,0,0,0,1,
   1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,
   1,0,0,0,0,0,0,5,0,0,0,0,0,0,0,1,
   1,1,1,1,1,1,1,1,1,1,1,1,1,1,3,1
};
int map6_[XSIZE][YSIZE] = {
   1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
   1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,
   1,0,0,0,1,0,0,0,0,0,5,0,1,0,0,1,
   1,0,0,1,0,0,0,0,0,0,0,0,1,0,0,1,
   1,0,0,0,5,0,0,0,0,0,0,0,0,0,0,1,
   1,0,0,0,0,0,0,0,0,0,0,0,5,0,0,1,
   1,0,0,0,0,0,0,5,0,0,0,0,0,0,0,1,
   1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,
   1,0,0,0,0,1,0,0,0,0,0,5,0,0,0,1,
   1,0,0,5,0,1,1,1,0,0,0,0,0,0,0,1,
   1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
   1,1,1,0,0,0,0,0,0,0,1,1,0,5,0,1,
   1,0,1,1,0,0,0,0,0,1,1,0,0,0,0,1,
   1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,
   1,0,0,0,0,0,0,5,0,0,0,0,0,0,0,1,
   1,1,1,1,1,1,1,1,1,1,1,1,1,1,3,1
};

//커서지움
void removeCursor(void)
{
    CONSOLE_CURSOR_INFO curInfo;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
    curInfo.bVisible = 0;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
}

//커서위치 바꿈
void gotoxy(int x, int y)
{
    COORD pos; //Windows.h 에 정의
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos); //커버위치를 바꿔주는 것
}

//글자색
void textcolor(int fg_color, int bg_color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), fg_color | bg_color << 4);
}

//화면 지우고 원하는 배경색 설정
void cls(int bg_color, int text_color)
{
    char cmd[100];
    system("cls");
    sprintf(cmd, "COLOR %x%x", bg_color, text_color);
    system(cmd);
}

//초기화면
void initialScreen()
{
    textcolor(GREEN1, BLACK);
    printf("\n\n\n\n\n");
    printf("         ■     ■■■  ■        ■ ■■■■ ■      ■ ■■■■■ ■      ■ ■■■■  ■■■■\n");
    printf("       ■  ■   ■    ■ ■      ■  ■       ■■    ■     ■     ■      ■ ■     ■ ■      \n");
    printf("      ■    ■  ■     ■ ■    ■   ■■■■ ■  ■  ■     ■     ■      ■ ■■■■  ■■■■\n");
    printf("     ■■■■■ ■    ■   ■  ■    ■       ■    ■■     ■     ■■  ■■ ■    ■  ■      \n");
    printf("     ■      ■ ■■■       ■      ■■■■ ■      ■     ■       ■■■   ■     ■ ■■■■\n");
    textcolor(WHITE, BLACK);

    textcolor(YELLOW1, BLACK);
    gotoxy(29, 17);
    printf("★ ");
    textcolor(WHITE, BLACK);
    gotoxy(32, 17);
    printf("게임을 시작하려면 space를 누르세요");
    textcolor(YELLOW1, BLACK);
    gotoxy(66, 17);
    printf(" ★");
    textcolor(WHITE, BLACK);
    gotoxy(85, 23);
    printf("게임설명(U)");
    gotoxy(85, 25);
    printf("게임종료(ESC)");
}

void gameDescription() //게임설명
{
    int i;
    cls(BLACK, WHITE);
    gotoxy(40, 1); printf("<   게 임 설 명   >\n\n");
    for (i = 3; i <= 26; i++) {
        gotoxy(49, i); printf("│");
    }
    gotoxy(5, 5); printf(">> 이동\n"); //방향키
    gotoxy(5, 7);  printf("           △\n");
    gotoxy(5, 9); printf("1P :   ◁      ▷ \n");
    gotoxy(5, 11); printf("           ▽\n");
    gotoxy(28, 7);  printf("          W\n");
    gotoxy(28, 9); printf("2P :  A       D \n");
    gotoxy(28, 11); printf("          S\n");

    gotoxy(5, 16); printf(">> 주의");
    gotoxy(5, 18); printf("- 생명을 모두 잃으면 게임이 종료됩니다\n");
    gotoxy(5, 20); printf("- 보너스단계에서 20초의 시간제한이 있습니다\n");
    gotoxy(5, 22); printf("- 제한시간이 지나면 게임이 종료됩니다\n");

    gotoxy(56, 5); printf("출구 :");
    textcolor(GREEN2, BLACK);
    gotoxy(63, 5); printf("▲\n");
    textcolor(WHITE, BLACK);
    gotoxy(56, 7); printf("캐릭터 :");
    textcolor(YELLOW1, BLACK);
    gotoxy(63, 7); printf("★\n");
    textcolor(WHITE, BLACK);

    gotoxy(56, 10); printf(">> 생명 or 점수 감소\n");
    gotoxy(56, 12); printf("생명 :");
    textcolor(RED2, BLACK);
    gotoxy(63, 12); printf("※\n");
    textcolor(WHITE, BLACK);
    gotoxy(56, 14); printf("점수 :");
    textcolor(GREEN2, BLACK);
    gotoxy(63, 14); printf("♭\n");
    textcolor(WHITE, BLACK);

    gotoxy(56, 17); printf(">> 생명 or 점수 증가\n");
    gotoxy(56, 19); printf("생명 :");
    textcolor(BLUE2, BLACK);
    gotoxy(63, 19); printf("♥\n");
    textcolor(WHITE, BLACK);
    gotoxy(56, 21); printf("점수 :");
    textcolor(CYAN2, BLACK);
    gotoxy(63, 21); printf("◈\n");
    textcolor(WHITE, BLACK);

    gotoxy(85, 23);
    printf("게임시작(SPACE)");
    gotoxy(85, 25);
    printf("게임종료(ESC)");
}

void show_time(int remain_time) //보너스 스테이지에서 남은시간
{
    gotoxy(43, 25);
    textcolor(GREEN2, GRAY2);
    printf("남은 시간 : %02d", remain_time);
    textcolor(GRAY1, BLACK);
}

void show_score(int player) //점수판
{
    textcolor(GREEN2, GRAY2);
    switch (player) {
    case 0: // player 1
        gotoxy(14, 1);
        printf("점수 : %d", score[player]);
        break;
    case 1: // player 2
        gotoxy(64, 1);
        printf("점수 : %d", score[player]);
        break;
    }
    textcolor(WHITE, BLACK);
}

void finish_point() { //보너스 스테이지에서 제한시간이 다 되어 게임이 종료 되었을 때
    unsigned char ch;

    while (1) {
        int c1, c2;
        do {
            c1 = rand() % 16;
            c2 = rand() % 16;
        } while (c1 == c2);
        textcolor(c1, c2);

        Sleep(100);
        gotoxy(40, 12);

        if (score[0] > score[1])
            printf(" WINNER IS PLAYER1!! ");
        else if (score[0] < score[1])
            printf(" WINNER IS PLAYER2!! ");
        else
            printf("       DRAW!!        ");

        gotoxy(30, 14);
        textcolor(GREEN1, WHITE);
        printf(">> 게임을 종료하시려면 Esc를 누르세요 <<");
        textcolor(WHITE, BLACK);

        if (_kbhit() == 1) { //키보드가 눌려져 있으면
            ch = _getch(); //key값 읽음
            if (ch == ESC)
                exit(1);
        }
    }
}

void finish_life() { //생명이 0이 되어 게임이 종료되었을 때
    unsigned char ch;

    while (1) {
        int c1, c2;
        do {
            c1 = rand() % 16;
            c2 = rand() % 16;
        } while (c1 == c2);
        textcolor(c1, c2);

        Sleep(100);
        gotoxy(40, 12);
        if (life[0] > life[1])
            printf(" WINNER IS PLAYER1!! ");
        else if (life[0] < life[1])
            printf(" WINNER IS PLAYER2!! ");
        else
            printf("       DRAW!!        ");

        gotoxy(30, 14);
        textcolor(GREEN1, WHITE);
        printf(">> 게임을 종료하시려면 Esc를 누르세요 <<");
        textcolor(WHITE, BLACK);

        if (_kbhit() == 1) { //키보드가 눌려져 있으면
            ch = _getch(); //key값 읽음
            if (ch == ESC)
                exit(1);
        }
    }
}

void show_coin() //보너스 스테이지에서 움직일 때 코인 생성
{
    int x, y;
    x = rand() % XSIZE;
    y = rand() % YSIZE;

    if (map6[y][x] == 0) {
        map6[y][x] = 6;
    }
    if (map6_[y][x] == 0) {
        map6_[y][x] = 6;
    }
}

void show_flat() //보너스 스테이지에서 움직일 때 플랫 생성
{
    int x, y;
    x = rand() % XSIZE;
    y = rand() % YSIZE;

    if (map6[x][y] == 0) {
        map6[x][y] = 2;
    }
    if (map6_[y][x] == 0) {
        map6_[y][x] = 2;
    }
}

void show_life(int player) //생명 보여줌
{
    textcolor(GREEN2, GRAY2);
    switch (player) {
    case 0: // player 1
        gotoxy(27, 1);
        printf("생명 : %d", life[player]);
        break;
    case 1: // player 2
        gotoxy(77, 1);
        printf("생명 : %d", life[player]);
        break;
    }
    textcolor(WHITE, BLACK);

    if (life[player] == 0) {
        finish_life();
    }
}

void draw_hline(int y, int x1, int x2, char ch) //윗줄 -> 생명, 시간
{
    gotoxy(x1, y);
    for (; x1 <= x2; x1++)
        putchar(ch);
}

void draw_uline(int y, int x1, int x2, char ch) //아랫줄 -> 남은 시간(보너스 스테이지에서만 나타남)
{
    gotoxy(x1, y);
    for (; x1 <= x2; x1++)
        putchar(ch);
}

void move_monster() { //몬스터 이동함수
    //스테이지1
    if (stage == 1) {

        if (lr_1_1 == 1)
        {
            newx1 = x1 + 1;
            if ((map1[2][newx1] == 3)) {
                life[0]--;
                show_life(0);
                if (map1[2][x1] != 3)
                    map1[2][x1] = 0;

                if (newx1 == 11) //몬스터가 일정구간에 오면 방향 전환
                    lr_1_1 = 2;
                x1 = newx1;
            }
            else {

                if (map1[2][x1] != 3)
                    map1[2][x1] = 0;
                newx1 = x1 + 1;
                if (newx1 == 11) //몬스터가 일정구간에 오면 방향 전환
                    lr_1_1 = 2;
                map1[2][newx1] = 4;
                x1 = newx1;
            }
        }
        else if (lr_1_1 == 2)
        {
            newx1 = x1 - 1;
            if ((map1[2][newx1] == 3)) {
                //newx1 = x1;
                life[0]--;
                show_life(0);
                if (map1[2][x1] != 3)
                    map1[2][x1] = 0;

                if (newx1 == 5)
                    lr_1_1 = 1;

                x1 = newx1;
            }
            else {
                if (map1[2][x1] != 3)
                    map1[2][x1] = 0;
                newx1 = x1 - 1;
                if (newx1 == 5)
                    lr_1_1 = 1;
                map1[2][newx1] = 4;
                x1 = newx1;
            }
        }

        if (ud_1_1 == 2)
        {
            newy1 = y1 + 1;
            if ((map1[newy1][6] == 3)) {
                life[0]--;
                show_life(0);
                if (map1[y1][6] != 3)
                    map1[y1][6] = 0;

                if (newy1 == 14) //몬스터가 일정구간에 오면 방향 전환
                    ud_1_1 = 1;
                y1 = newy1;
            }
            else {
                if (map1[y1][6] != 3)
                    map1[y1][6] = 0;
                newy1 = y1 + 1;
                if (newy1 == 14) //몬스터가 일정구간에 오면 방향 전환
                    ud_1_1 = 1;
                map1[newy1][6] = 5;
                y1 = newy1;
            }
        }
        else if (ud_1_1 == 1)
        {
            newy1 = y1 - 1;
            if ((map1[newy1][6] == 3)) {
                life[0]--;
                show_life(0);
                if (map1[y1][6] != 3)
                    map1[y1][6] = 0;

                if (newy1 == 9)
                    ud_1_1 = 2;

                y1 = newy1;
            }
            else {
                if (map1[y1][6] != 3)
                    map1[y1][6] = 0;
                newy1 = y1 - 1;
                if (newy1 == 9)
                    ud_1_1 = 2;
                map1[newy1][6] = 5;
                y1 = newy1;
            }
        }

        //2player
        if (lr_2_1 == 1)
        {
            newx2 = x2 + 1;
            if ((map1_[2][newx2] == 3)) {
                life[1]--;
                show_life(1);
                if (map1_[2][x2] != 3)
                    map1_[2][x2] = 0;

                if (newx2 == 11) //몬스터가 일정구간에 오면 방향 전환
                    lr_2_1 = 2;
                x2 = newx2;
            }
            else {

                if (map1_[2][x2] != 3)
                    map1_[2][x2] = 0;
                newx2 = x2 + 1;
                if (newx2 == 11) //몬스터가 일정구간에 오면 방향 전환
                    lr_2_1 = 2;
                map1_[2][newx2] = 4;
                x2 = newx2;
            }
        }
        else if (lr_2_1 == 2)
        {
            newx2 = x2 - 1;
            if ((map1_[2][newx2] == 3)) {
                //newx1 = x1;
                life[1]--;
                show_life(1);
                if (map1_[2][x2] != 3)
                    map1_[2][x2] = 0;

                if (newx2 == 5)
                    lr_2_1 = 1;

                x2 = newx2;
            }
            else {
                if (map1_[2][x2] != 3)
                    map1_[2][x2] = 0;
                newx2 = x2 - 1;
                if (newx2 == 5)
                    lr_2_1 = 1;
                map1_[2][newx2] = 4;
                x2 = newx2;
            }
        }
        if (ud_2_1 == 2)
        {
            newy2 = y2 + 1;
            if ((map1_[newy2][6] == 3)) {
                life[1]--;
                show_life(1);
                if (map1_[y2][6] != 3)
                    map1_[y2][6] = 0;

                if (newy2 == 14) //몬스터가 일정구간에 오면 방향 전환
                    ud_2_1 = 1;
                y2 = newy2;
            }
            else {
                if (map1_[y2][6] != 3)
                    map1_[y2][6] = 0;
                newy2 = y2 + 1;
                if (newy2 == 14) //몬스터가 일정구간에 오면 방향 전환
                    ud_2_1 = 1;
                map1_[newy2][6] = 5;
                y2 = newy2;
            }
        }
        else if (ud_2_1 == 1)
        {
            newy2 = y2 - 1;
            if ((map1_[newy2][6] == 3)) {
                life[1]--;
                show_life(1);
                if (map1_[y2][6] != 3)
                    map1_[y2][6] = 0;

                if (newy2 == 9)
                    ud_2_1 = 2;

                y2 = newy2;
            }
            else {
                if (map1_[y2][6] != 3)
                    map1_[y2][6] = 0;
                newy2 = y2 - 1;
                if (newy2 == 9)
                    ud_2_1 = 2;
                map1_[newy2][6] = 5;
                y2 = newy2;
            }
        }

        int x, y;
        for (y = 0; y < 16; y++) { //움직일 때마다 몬스터를 그려줌
            for (x = 0; x < 16; x++) {
                gotoxy((x * 2) + 10, y + 5); //player1 stage1맵
                switch (map1[y][x]) {
                case 0:
                    printf("  "); //길
                    break;
                case 3:
                    textcolor(YELLOW1, BLACK);
                    printf("★"); //캐릭터
                    textcolor(WHITE, BLACK);
                    break;
                case 4:
                case 5:
                    textcolor(RED2, BLACK);
                    printf("※"); //몬스터
                    textcolor(WHITE, BLACK);
                    break;
                }

                gotoxy((x * 2) + 59, y + 5); //player2 stage1맵
                switch (map1_[y][x]) {
                case 0:
                    printf("  "); //길
                    break;
                    textcolor(YELLOW1, BLACK);
                    printf("★"); //캐릭터
                    textcolor(WHITE, BLACK);
                    break;
                case 4:
                case 5:
                    textcolor(RED2, BLACK);
                    printf("※"); //몬스터
                    textcolor(WHITE, BLACK);
                    break;
                }
            }
        }
    }

    //스테이지2
    if (stage == 2) {

        if (lr_1_2 == 1)
        {
            newx1_2 = x1_2 + 1;
            if ((map2[4][newx1_2] == 3)) {
                life[0]--;
                show_life(0);
                if (map2[4][x1_2] != 3)
                    map2[4][x1_2] = 0;

                if (newx1_2 == 6) //몬스터가 일정구간에 오면 방향 전환
                    lr_1_2 = 2;
                x1_2 = newx1_2;
            }
            else {

                if (map2[4][x1_2] != 3)
                    map2[4][x1_2] = 0;
                newx1_2 = x1_2 + 1;
                if (newx1_2 == 6) //몬스터가 일정구간에 오면 방향 전환
                    lr_1_2 = 2;
                map2[4][newx1_2] = 4;
                x1_2 = newx1_2;
            }
        }
        else if (lr_1_2 == 2)
        {
            newx1_2 = x1_2 - 1;
            if ((map2[4][newx1_2] == 3)) {
                //newx1 = x1;
                life[0]--;
                show_life(0);
                if (map2[4][x1_2] != 3)
                    map2[4][x1_2] = 0;

                if (newx1_2 == 4)
                    lr_1_2 = 1;

                x1_2 = newx1_2;
            }
            else {
                if (map2[4][x1_2] != 3)
                    map2[4][x1_2] = 0;
                newx1_2 = x1_2 - 1;
                if (newx1_2 == 4)
                    lr_1_2 = 1;
                map2[4][newx1_2] = 4;
                x1_2 = newx1_2;
            }
        }

        if (ud_1_2 == 2)
        {
            newy1_2 = y1_2 + 1;
            if ((map2[newy1_2][3] == 3)) {
                life[0]--;
                show_life(0);
                if (map2[y1_2][3] != 3)
                    map2[y1_2][3] = 0;

                if (newy1_2 == 6) //몬스터가 일정구간에 오면 방향 전환
                    ud_1_2 = 1;
                y1_2 = newy1_2;
            }
            else {
                if (map2[y1_2][3] != 3)
                    map2[y1_2][3] = 0;
                newy1_2 = y1_2 + 1;
                if (newy1_2 == 6) //몬스터가 일정구간에 오면 방향 전환
                    ud_1_2 = 1;
                map2[newy1_2][3] = 5;
                y1_2 = newy1_2;
            }
        }
        else if (ud_1_2 == 1)
        {
            newy1_2 = y1_2 - 1;
            if ((map2[newy1_2][3] == 3)) {
                life[0]--;
                show_life(0);
                if (map2[y1_2][3] != 3)
                    map2[y1_2][3] = 0;

                if (newy1_2 == 3)
                    ud_1_2 = 2;

                y1_2 = newy1_2;
            }
            else {
                if (map2[y1_2][3] != 3)
                    map2[y1_2][3] = 0;
                newy1_2 = y1_2 - 1;
                if (newy1_2 == 3)
                    ud_1_2 = 2;
                map2[newy1_2][3] = 5;
                y1_2 = newy1_2;
            }
        }

        //2player
        if (lr_2_2 == 1)
        {
            newx2_2 = x2_2 + 1;
            if ((map2_[4][newx2_2] == 3)) {
                life[1]--;
                show_life(1);
                if (map2_[4][x2_2] != 3)
                    map2_[4][x2_2] = 0;

                if (newx2_2 == 6) //몬스터가 일정구간에 오면 방향 전환
                    lr_2_2 = 2;
                x2_2 = newx2_2;
            }
            else {
                if (map2_[4][x2_2] != 3)
                    map2_[4][x2_2] = 0;
                newx2_2 = x2_2 + 1;
                if (newx2_2 == 6) //몬스터가 일정구간에 오면 방향 전환
                    lr_2_2 = 2;
                map2_[4][newx2_2] = 4;
                x2_2 = newx2_2;
            }
        }
        else if (lr_2_2 == 2)
        {
            newx2_2 = x2_2 - 1;
            if ((map2_[4][newx2_2] == 3)) {
                //newx1 = x1;
                life[1]--;
                show_life(1);
                if (map2_[4][x2_2] != 3)
                    map2_[4][x2_2] = 0;

                if (newx2_2 == 4)
                    lr_2_2 = 1;

                x2_2 = newx2_2;
            }
            else {
                if (map2_[4][x2_2] != 3)
                    map2_[4][x2_2] = 0;
                newx2_2 = x2_2 - 1;
                if (newx2_2 == 4)
                    lr_2_2 = 1;
                map2_[4][newx2_2] = 4;
                x2_2 = newx2_2;
            }
        }
        if (ud_2_2 == 2)
        {
            newy2_2 = y2_2 + 1;
            if ((map2_[newy2_2][3] == 3)) {
                life[1]--;
                show_life(1);
                if (map2_[y2_2][3] != 3)
                    map2_[y2_2][3] = 0;

                if (newy2_2 == 6) //몬스터가 일정구간에 오면 방향 전환
                    ud_2_2 = 1;
                y2_2 = newy2_2;
            }
            else {
                if (map2_[y2_2][3] != 3)
                    map2_[y2_2][3] = 0;
                newy2_2 = y2_2 + 1;
                if (newy2_2 == 6) //몬스터가 일정구간에 오면 방향 전환
                    ud_2_2 = 1;
                map2_[newy2_2][3] = 5;
                y2_2 = newy2_2;
            }
        }
        else if (ud_2_2 == 1)
        {
            newy2_2 = y2_2 - 1;
            if ((map2_[newy2_2][3] == 3)) {
                life[1]--;
                show_life(1);
                if (map2_[y2_2][3] != 3)
                    map2_[y2_2][3] = 0;

                if (newy2_2 == 3)
                    ud_2_2 = 2;

                y2_2 = newy2_2;
            }
            else {
                if (map2_[y2_2][3] != 3)
                    map2_[y2_2][3] = 0;
                newy2_2 = y2_2 - 1;
                if (newy2_2 == 3)
                    ud_2_2 = 2;
                map2_[newy2_2][3] = 5;
                y2_2 = newy2_2;
            }
        }

        int x, y;
        for (y = 0; y < 16; y++) { //움직일 때마다 몬스터를 그려줌
            for (x = 0; x < 16; x++) {
                gotoxy((x * 2) + 10, y + 5); //player1 stage1맵
                switch (map2[y][x]) {
                case 0:
                    printf("  "); //길
                    break;
                case 3:
                    textcolor(YELLOW1, BLACK);
                    printf("★"); //캐릭터
                    textcolor(WHITE, BLACK);
                    break;
                case 4:
                case 5:
                    textcolor(RED2, BLACK);
                    printf("※"); //몬스터
                    textcolor(WHITE, BLACK);
                    break;
                }

                gotoxy((x * 2) + 59, y + 5); //player2 stage1맵
                switch (map2_[y][x]) {
                case 0:
                    printf("  "); //길
                    break;
                    textcolor(YELLOW1, BLACK);
                    printf("★"); //캐릭터
                    textcolor(WHITE, BLACK);
                    break;
                case 4:
                case 5:
                    textcolor(RED2, BLACK);
                    printf("※"); //몬스터
                    textcolor(WHITE, BLACK);
                    break;
                }
            }
        }
    }

    //스테이지3
    if (stage == 3) {

        if (lr_1_3 == 1)
        {
            newx1_3 = x1_3 + 1;
            if ((map3[11][newx1_3] == 3)) {
                life[0]--;
                show_life(0);
                if (map3[11][x1_3] != 3)
                    map3[11][x1_3] = 0;

                if (newx1_3 == 10) //몬스터가 일정구간에 오면 방향 전환
                    lr_1_3 = 2;
                x1_3 = newx1_3;
            }
            else {

                if (map3[11][x1_3] != 3)
                    map3[11][x1_3] = 0;
                newx1_3 = x1_3 + 1;
                if (newx1_3 == 10) //몬스터가 일정구간에 오면 방향 전환
                    lr_1_3 = 2;
                map3[11][newx1_3] = 4;
                x1_3 = newx1_3;
            }
        }
        else if (lr_1_3 == 2)
        {
            newx1_3 = x1_3 - 1;
            if ((map3[11][newx1_3] == 3)) {
                //newx1 = x1;
                life[0]--;
                show_life(0);
                if (map3[11][x1_3] != 3)
                    map3[11][x1_3] = 0;

                if (newx1_3 == 7)
                    lr_1_3 = 1;

                x1_3 = newx1_3;
            }
            else {
                if (map3[11][x1_3] != 3)
                    map3[11][x1_3] = 0;
                newx1_3 = x1_3 - 1;
                if (newx1_3 == 7)
                    lr_1_3 = 1;
                map3[11][newx1_3] = 4;
                x1_3 = newx1_3;
            }
        }

        if (ud_1_3 == 2)
        {
            newy1_3 = y1_3 + 1;
            if ((map3[newy1_3][10] == 3)) {
                life[0]--;
                show_life(0);
                if (map3[y1_3][10] != 3)
                    map3[y1_3][10] = 0;

                if (newy1_3 == 5) //몬스터가 일정구간에 오면 방향 전환
                    ud_1_3 = 1;
                y1_3 = newy1_3;
            }
            else {
                if (map3[y1_3][10] != 3)
                    map3[y1_3][10] = 0;
                newy1_3 = y1_3 + 1;
                if (newy1_3 == 5) //몬스터가 일정구간에 오면 방향 전환
                    ud_1_3 = 1;
                map3[newy1_3][10] = 5;
                y1_3 = newy1_3;
            }
        }
        else if (ud_1_3 == 1)
        {
            newy1_3 = y1_3 - 1;
            if ((map3[newy1_3][10] == 3)) {
                life[0]--;
                show_life(0);
                if (map3[y1_3][10] != 3)
                    map3[y1_3][10] = 0;

                if (newy1_3 == 1)
                    ud_1_3 = 2;

                y1_3 = newy1_3;
            }
            else {
                if (map3[y1_3][10] != 3)
                    map3[y1_3][10] = 0;
                newy1_3 = y1_3 - 1;
                if (newy1_3 == 1)
                    ud_1_3 = 2;
                map3[newy1_3][10] = 5;
                y1_3 = newy1_3;
            }
        }

        //2player
        if (lr_2_3 == 1)
        {
            newx2_3 = x2_3 + 1;
            if ((map3_[11][newx2_3] == 3)) {
                life[1]--;
                show_life(1);
                if (map3_[11][x2_3] != 3)
                    map3_[11][x2_3] = 0;

                if (newx2_3 == 10) //몬스터가 일정구간에 오면 방향 전환
                    lr_2_3 = 2;
                x2_3 = newx2_3;
            }
            else {

                if (map3_[11][x2_3] != 3)
                    map3_[11][x2_3] = 0;
                newx2_3 = x2_3 + 1;
                if (newx2_3 == 10) //몬스터가 일정구간에 오면 방향 전환
                    lr_2_3 = 2;
                map3_[11][newx2_3] = 4;
                x2_3 = newx2_3;
            }
        }
        else if (lr_2_3 == 2)
        {
            newx2_3 = x2_3 - 1;
            if ((map3_[11][newx2_3] == 3)) {
                //newx1 = x1;
                life[1]--;
                show_life(1);
                if (map3_[11][x2_3] != 3)
                    map3_[11][x2_3] = 0;

                if (newx2_3 == 7)
                    lr_2_3 = 1;

                x2_3 = newx2_3;
            }
            else {
                if (map3_[11][x2_3] != 3)
                    map3_[11][x2_3] = 0;
                newx2_3 = x2_3 - 1;
                if (newx2_3 == 7)
                    lr_2_3 = 1;
                map3_[11][newx2_3] = 4;
                x2_3 = newx2_3;
            }
        }

        if (ud_2_3 == 2)
        {
            newy2_3 = y2_3 + 1;
            if ((map3_[newy2_3][10] == 3)) {
                life[1]--;
                show_life(1);
                if (map3_[y2_3][10] != 3)
                    map3_[y2_3][10] = 0;

                if (newy2_3 == 5) //몬스터가 일정구간에 오면 방향 전환
                    ud_2_3 = 1;
                y2_3 = newy2_3;
            }
            else {
                if (map3_[y2_3][10] != 3)
                    map3_[y2_3][10] = 0;
                newy2_3 = y2_3 + 1;
                if (newy2_3 == 5) //몬스터가 일정구간에 오면 방향 전환
                    ud_2_3 = 1;
                map3_[newy2_3][10] = 5;
                y2_3 = newy2_3;
            }
        }
        else if (ud_2_3 == 1)
        {
            newy2_3 = y2_3 - 1;
            if ((map3_[newy2_3][10] == 3)) {
                life[1]--;
                show_life(1);
                if (map3_[y2_3][10] != 3)
                    map3_[y2_3][10] = 0;

                if (newy2_3 == 1)
                    ud_2_3 = 2;

                y2_3 = newy2_3;
            }
            else {
                if (map3_[y2_3][10] != 3)
                    map3_[y2_3][10] = 0;
                newy2_3 = y2_3 - 1;
                if (newy2_3 == 1)
                    ud_2_3 = 2;
                map3_[newy2_3][10] = 5;
                y2_3 = newy2_3;
            }
        }

        int x, y;
        for (y = 0; y < 16; y++) { //움직일 때마다 몬스터를 그려줌
            for (x = 0; x < 16; x++) {
                gotoxy((x * 2) + 10, y + 5); //player1 stage1맵
                switch (map3[y][x]) {
                case 0:
                    printf("  "); //길
                    break;
                case 3:
                    textcolor(YELLOW1, BLACK);
                    printf("★"); //캐릭터
                    textcolor(WHITE, BLACK);
                    break;
                case 4:
                case 5:
                case 7:
                    textcolor(RED2, BLACK);
                    printf("※"); //몬스터
                    textcolor(WHITE, BLACK);
                    break;
                }

                gotoxy((x * 2) + 59, y + 5); //player2 stage1맵
                switch (map3_[y][x]) {
                case 0:
                    printf("  "); //길
                    break;
                    textcolor(YELLOW1, BLACK);
                    printf("★"); //캐릭터
                    textcolor(WHITE, BLACK);
                    break;
                case 4:
                case 5:
                case 7:
                    textcolor(RED2, BLACK);
                    printf("※"); //몬스터
                    textcolor(WHITE, BLACK);
                    break;
                }
            }
        }
    }

    //스테이지4
    if (stage == 4) {

        if (lr_1_4 == 1)
        {
            newx1_4 = x1_4 + 1;
            if ((map4[2][newx1_4] == 3)) {
                life[0]--;
                show_life(0);
                if (map4[2][x1_4] != 3)
                    map4[2][x1_4] = 0;

                if (newx1_4 == 8) //몬스터가 일정구간에 오면 방향 전환
                    lr_1_4 = 2;
                x1_4 = newx1_4;
            }
            else {

                if (map4[2][x1_4] != 3)
                    map4[2][x1_4] = 0;
                newx1_4 = x1_4 + 1;
                if (newx1_4 == 8) //몬스터가 일정구간에 오면 방향 전환
                    lr_1_4 = 2;
                map4[2][newx1_4] = 4;
                x1_4 = newx1_4;
            }
        }
        else if (lr_1_4 == 2)
        {
            newx1_4 = x1_4 - 1;
            if ((map4[2][newx1_4] == 3)) {
                //newx1 = x1;
                life[0]--;
                show_life(0);
                if (map4[2][x1_4] != 3)
                    map4[2][x1_4] = 0;

                if (newx1_4 == 6)
                    lr_1_4 = 1;

                x1_4 = newx1_4;
            }
            else {
                if (map4[2][x1_4] != 3)
                    map4[2][x1_4] = 0;
                newx1_4 = x1_4 - 1;
                if (newx1_4 == 6)
                    lr_1_4 = 1;
                map4[2][newx1_4] = 4;
                x1_4 = newx1_4;
            }
        }

        if (ud_1_4 == 2)
        {
            newy1_4 = y1_4 + 1;
            if ((map4[newy1_4][12] == 3)) {
                life[0]--;
                show_life(0);
                if (map4[y1_4][12] != 3)
                    map4[y1_4][12] = 0;

                if (newy1_4 == 6) //몬스터가 일정구간에 오면 방향 전환
                    ud_1_4 = 1;
                y1_4 = newy1_4;
            }
            else {
                if (map4[y1_4][12] != 3)
                    map4[y1_4][12] = 0;
                newy1_4 = y1_4 + 1;
                if (newy1_4 == 6) //몬스터가 일정구간에 오면 방향 전환
                    ud_1_4 = 1;
                map4[newy1_4][12] = 5;
                y1_4 = newy1_4;
            }
        }
        else if (ud_1_4 == 1)
        {
            newy1_4 = y1_4 - 1;
            if ((map4[newy1_4][12] == 3)) {
                life[0]--;
                show_life(0);
                if (map4[y1_4][12] != 3)
                    map4[y1_4][12] = 0;

                if (newy1_4 == 3)
                    ud_1_4 = 2;

                y1_4 = newy1_4;
            }
            else {
                if (map4[y1_4][12] != 3)
                    map4[y1_4][12] = 0;
                newy1_4 = y1_4 - 1;
                if (newy1_4 == 3)
                    ud_1_4 = 2;
                map4[newy1_4][12] = 5;
                y1_4 = newy1_4;
            }
        }

        //2player
        if (lr_2_4 == 1)
        {
            newx2_4 = x2_4 + 1;
            if ((map4_[2][newx2_4] == 3)) {
                life[1]--;
                show_life(1);
                if (map4_[2][x2_4] != 3)
                    map4_[2][x2_4] = 0;

                if (newx2_4 == 8) //몬스터가 일정구간에 오면 방향 전환
                    lr_2_4 = 2;
                x2_4 = newx2_4;
            }
            else {

                if (map4_[2][x2_4] != 3)
                    map4_[2][x2_4] = 0;
                newx2_4 = x2_4 + 1;
                if (newx2_4 == 8) //몬스터가 일정구간에 오면 방향 전환
                    lr_2_4 = 2;
                map4_[2][newx2_4] = 4;
                x2_4 = newx2_4;
            }
        }
        else if (lr_2_4 == 2)
        {
            newx2_4 = x2_4 - 1;
            if ((map4_[2][newx2_4] == 3)) {
                //newx1 = x1;
                life[1]--;
                show_life(1);
                if (map4_[2][x2_4] != 3)
                    map4_[2][x2_4] = 0;

                if (newx2_4 == 6)
                    lr_2_4 = 1;

                x2_4 = newx2_4;
            }
            else {
                if (map4_[2][x2_4] != 3)
                    map4_[2][x2_4] = 0;
                newx2_4 = x2_4 - 1;
                if (newx2_4 == 6)
                    lr_2_4 = 1;
                map4_[2][newx2_4] = 4;
                x2_4 = newx2_4;
            }
        }

        if (ud_2_4 == 2)
        {
            newy2_4 = y2_4 + 1;
            if ((map4_[newy2_4][12] == 3)) {
                life[1]--;
                show_life(1);
                if (map4_[y2_4][12] != 3)
                    map4_[y2_4][12] = 0;

                if (newy2_4 == 6) //몬스터가 일정구간에 오면 방향 전환
                    ud_2_4 = 1;
                y2_4 = newy2_4;
            }
            else {
                if (map4_[y2_4][12] != 3)
                    map4_[y2_4][12] = 0;
                newy2_4 = y2_4 + 1;
                if (newy2_4 == 6) //몬스터가 일정구간에 오면 방향 전환
                    ud_2_4 = 1;
                map4_[newy2_4][12] = 5;
                y2_4 = newy2_4;
            }
        }
        else if (ud_2_4 == 1)
        {
            newy2_4 = y2_4 - 1;
            if ((map4_[newy2_4][12] == 3)) {
                life[1]--;
                show_life(1);
                if (map4_[y2_4][12] != 3)
                    map4_[y2_4][12] = 0;

                if (newy2_4 == 3)
                    ud_2_4 = 2;

                y2_4 = newy2_4;
            }
            else {
                if (map4_[y2_4][12] != 3)
                    map4_[y2_4][12] = 0;
                newy2_4 = y2_4 - 1;
                if (newy2_4 == 3)
                    ud_2_4 = 2;
                map4_[newy2_4][12] = 5;
                y2_4 = newy2_4;
            }
        }

        int x, y;
        for (y = 0; y < 16; y++) { //움직일 때마다 몬스터를 그려줌
            for (x = 0; x < 16; x++) {
                gotoxy((x * 2) + 10, y + 5); //player1 stage1맵
                switch (map4[y][x]) {
                case 0:
                    printf("  "); //길
                    break;
                case 3:
                    textcolor(YELLOW1, BLACK);
                    printf("★"); //캐릭터
                    textcolor(WHITE, BLACK);
                    break;
                case 4:
                case 5:
                    textcolor(RED2, BLACK);
                    printf("※"); //몬스터
                    textcolor(WHITE, BLACK);
                    break;
                }

                gotoxy((x * 2) + 59, y + 5); //player2 stage1맵
                switch (map4_[y][x]) {
                case 0:
                    printf("  "); //길
                    break;
                    textcolor(YELLOW1, BLACK);
                    printf("★"); //캐릭터
                    textcolor(WHITE, BLACK);
                    break;
                case 4:
                case 5:
                    textcolor(RED2, BLACK);
                    printf("※"); //몬스터
                    textcolor(WHITE, BLACK);
                    break;
                }
            }
        }
    }

    //스테이지5
    if (stage == 5) {

        if (lr_1_5 == 1)
        {
            newx1_5 = x1_5 + 1;
            if ((map5[10][newx1_5] == 3)) {
                life[0]--;
                show_life(0);
                if (map5[10][x1_5] != 3)
                    map5[10][x1_5] = 0;

                if (newx1_5 == 5) //몬스터가 일정구간에 오면 방향 전환
                    lr_1_5 = 2;
                x1_5 = newx1_5;
            }
            else {

                if (map5[10][x1_5] != 3)
                    map5[10][x1_5] = 0;
                newx1_5 = x1_5 + 1;
                if (newx1_5 == 5) //몬스터가 일정구간에 오면 방향 전환
                    lr_1_5 = 2;
                map5[10][newx1_5] = 4;
                x1_5 = newx1_5;
            }
        }
        else if (lr_1_5 == 2)
        {
            newx1_5 = x1_5 - 1;
            if ((map5[10][newx1_5] == 3)) {
                //newx1 = x1;
                life[0]--;
                show_life(0);
                if (map5[10][x1_5] != 3)
                    map5[10][x1_5] = 0;

                if (newx1_5 == 2)
                    lr_1_5 = 1;

                x1_5 = newx1_5;
            }
            else {
                if (map5[10][x1_5] != 3)
                    map5[10][x1_5] = 0;
                newx1_5 = x1_5 - 1;
                if (newx1_5 == 2)
                    lr_1_5 = 1;
                map5[10][newx1_5] = 4;
                x1_5 = newx1_5;
            }
        }

        if (ud_1_5 == 2)
        {
            newy1_5 = y1_5 + 1;
            if ((map5[newy1_5][6] == 3)) {
                life[0]--;
                show_life(0);
                if (map5[y1_5][6] != 3)
                    map5[y1_5][6] = 0;

                if (newy1_5 == 6) //몬스터가 일정구간에 오면 방향 전환
                    ud_1_5 = 1;
                y1_5 = newy1_5;
            }
            else {
                if (map5[y1_5][6] != 3)
                    map5[y1_5][6] = 0;
                newy1_5 = y1_5 + 1;
                if (newy1_5 == 6) //몬스터가 일정구간에 오면 방향 전환
                    ud_1_5 = 1;
                map5[newy1_5][6] = 5;
                y1_5 = newy1_5;
            }
        }
        else if (ud_1_5 == 1)
        {
            newy1_5 = y1_5 - 1;
            if ((map5[newy1_5][6] == 3)) {
                life[0]--;
                show_life(0);
                if (map5[y1_5][6] != 3)
                    map5[y1_5][6] = 0;

                if (newy1_5 == 3)
                    ud_1_5 = 2;

                y1_5 = newy1_5;
            }
            else {
                if (map5[y1_5][6] != 3)
                    map5[y1_5][6] = 0;
                newy1_5 = y1_5 - 1;
                if (newy1_5 == 3)
                    ud_1_5 = 2;
                map5[newy1_5][6] = 5;
                y1_5 = newy1_5;
            }
        }

        //2player
        if (lr_2_5 == 1)
        {
            newx2_5 = x2_5 + 1;
            if ((map5_[10][newx2_5] == 3)) {
                life[1]--;
                show_life(1);
                if (map5_[10][x2_5] != 3)
                    map5_[10][x2_5] = 0;

                if (newx2_5 == 5) //몬스터가 일정구간에 오면 방향 전환
                    lr_2_5 = 2;
                x2_5 = newx2_5;
            }
            else {

                if (map5_[10][x2_5] != 3)
                    map5_[10][x2_5] = 0;
                newx2_5 = x2_5 + 1;
                if (newx2_5 == 5) //몬스터가 일정구간에 오면 방향 전환
                    lr_2_5 = 2;
                map5_[10][newx2_5] = 4;
                x2_5 = newx2_5;
            }
        }
        else if (lr_2_5 == 2)
        {
            newx2_5 = x2_5 - 1;
            if ((map5_[10][newx2_5] == 3)) {
                //newx1 = x1;
                life[1]--;
                show_life(1);
                if (map5_[10][x2_5] != 3)
                    map5_[10][x2_5] = 0;

                if (newx2_5 == 2)
                    lr_2_5 = 1;

                x2_5 = newx2_5;
            }
            else {
                if (map5_[10][x2_5] != 3)
                    map5_[10][x2_5] = 0;
                newx2_5 = x2_5 - 1;
                if (newx2_5 == 2)
                    lr_2_5 = 1;
                map5_[10][newx2_5] = 4;
                x2_5 = newx2_5;
            }
        }

        if (ud_2_5 == 2)
        {
            newy2_5 = y2_5 + 1;
            if ((map5_[newy2_5][6] == 3)) {
                life[1]--;
                show_life(1);
                if (map5_[y2_5][6] != 3)
                    map5_[y2_5][6] = 0;

                if (newy2_5 == 6) //몬스터가 일정구간에 오면 방향 전환
                    ud_2_5 = 1;
                y2_5 = newy2_5;
            }
            else {
                if (map5_[y2_5][6] != 3)
                    map5_[y2_5][6] = 0;
                newy2_5 = y2_5 + 1;
                if (newy2_5 == 6) //몬스터가 일정구간에 오면 방향 전환
                    ud_2_5 = 1;
                map5_[newy2_5][6] = 5;
                y2_5 = newy2_5;
            }
        }
        else if (ud_2_5 == 1)
        {
            newy2_5 = y2_5 - 1;
            if ((map5_[newy2_5][6] == 3)) {
                life[1]--;
                show_life(1);
                if (map5_[y2_5][6] != 3)
                    map5_[y2_5][6] = 0;

                if (newy2_5 == 3)
                    ud_2_5 = 2;

                y2_5 = newy2_5;
            }
            else {
                if (map5_[y2_5][6] != 3)
                    map5_[y2_5][6] = 0;
                newy2_5 = y2_5 - 1;
                if (newy2_5 == 3)
                    ud_2_5 = 2;
                map5_[newy2_5][6] = 5;
                y2_5 = newy2_5;
            }
        }

        int x, y;
        for (y = 0; y < 16; y++) { //움직일 때마다 몬스터를 그려줌
            for (x = 0; x < 16; x++) {
                gotoxy((x * 2) + 10, y + 5); //player1 stage1맵
                switch (map5[y][x]) {
                case 0:
                    printf("  "); //길
                    break;
                case 3:
                    textcolor(YELLOW1, BLACK);
                    printf("★"); //캐릭터
                    textcolor(WHITE, BLACK);
                    break;
                case 4:
                case 5:
                    textcolor(RED2, BLACK);
                    printf("※"); //몬스터
                    textcolor(WHITE, BLACK);
                    break;
                }

                gotoxy((x * 2) + 59, y + 5); //player2 stage1맵
                switch (map5_[y][x]) {
                case 0:
                    printf("  "); //길
                    break;
                    textcolor(YELLOW1, BLACK);
                    printf("★"); //캐릭터
                    textcolor(WHITE, BLACK);
                    break;
                case 4:
                case 5:
                    textcolor(RED2, BLACK);
                    printf("※"); //몬스터
                    textcolor(WHITE, BLACK);
                    break;
                }
            }
        }
    }

}


int player1(unsigned char ch, int stage) { //플레이어1 이동과 관련된 함수
    static int newx = 14, newy = 15, x = 14, y = 15;
    static int laststage = 0;

    if (laststage != stage) //현재 스테이지와 이전 스테이지가 다르면 다음 맵에서의 자리를 위해서 자리를 초기화해줌
    {
        newx = 14, newy = 15, x = 14, y = 15;
        laststage = stage;
    }

    switch (ch) { //방향키
    case UP:
        newy = y - 1;
        break;
    case DOWN:
        newy = y + 1;
        break;
    case LEFT:
        newx = x - 1;
        break;
    case RIGHT:
        newx = x + 1;
        break;
    }

    if (stage == 1) {
        map1[y][x] = 0;
        if (map1[newy][newx] == 2) { //출구에 도착하면 점수 50점 증가하고 자리 초기화
            score[0] += 50;
            show_score(0);
            newx = 14, newy = 15, x = 14, y = 15;
            return 1;
        }
        else if (map1[newy][newx] == 1) { //벽과 닿았을 경우
            newx = x;
            newy = y;
        }
        else if (map1[newy][newx] == 4 || map1[newy][newx] == 5) { //몬스터와 닿으면 생명 감소
            life[0]--;
            show_life(0);
        }
        else if (map1[newy][newx] == 6) { //하트 먹으면 생명 증가
            life[0]++;
            show_life(0);
        }
        map1[newy][newx] = 3; //캐릭터를 새로운 자리에 그려줌
        x = newx;
        y = newy;
    }

    if (stage == 2) {
        map2[y][x] = 0;
        if (map2[newy][newx] == 2) {
            score[0] += 50;
            show_score(0);
            newx = 14, newy = 15, x = 14, y = 15;
            return 2;
        }
        else if (map2[newy][newx] == 1) {
            newx = x;
            newy = y;
        }
        else if (map2[newy][newx] == 4 || map2[newy][newx] == 5) {
            life[0]--;
            show_life(0);
        }
        else if (map2[newy][newx] == 6) {
            life[0]++;
            show_life(0);
        }
        map2[newy][newx] = 3;
        x = newx;
        y = newy;
    }

    if (stage == 3) {
        map3[y][x] = 0;
        if (map3[newy][newx] == 2) {
            score[0] += 50;
            show_score(0);
            newx = 14, newy = 15, x = 14, y = 15;
            return 3;
        }
        else if (map3[newy][newx] == 1) {
            newx = x;
            newy = y;
        }
        else if (map3[newy][newx] == 4 || map3[newy][newx] == 5) {
            life[0]--;
            show_life(0);
        }
        else if (map3[newy][newx] == 6) {
            life[0]++;
            show_life(0);
        }
        else if (map3[newx][newy] == 7) {
            life[0]--;
            show_life(0);
            newx = x;
            newy = y;
        }
        map3[newy][newx] = 3;
        x = newx;
        y = newy;
    }

    if (stage == 4) {
        map4[y][x] = 0;
        if (map4[newy][newx] == 2) {
            score[0] += 50;
            show_score(0);
            newx = 14, newy = 15, x = 14, y = 15;
            return 4;
        }
        else if (map4[newy][newx] == 1) {
            newx = x;
            newy = y;
        }
        else if (map4[newy][newx] == 4 || map4[newy][newx] == 5) {
            life[0]--;
            show_life(0);
        }
        else if (map4[newy][newx] == 6) {
            life[0]++;
            show_life(0);
        }
        map4[newy][newx] = 3;
        x = newx;
        y = newy;
    }

    if (stage == 5) {
        map5[y][x] = 0;
        if (map5[newy][newx] == 2) {
            score[0] += 50;
            show_score(0);
            newx = 14, newy = 15, x = 14, y = 15;
            return 5;
        }
        else if (map5[newy][newx] == 1) {
            newx = x;
            newy = y;
        }
        else if (map5[newy][newx] == 4 || map5[newy][newx] == 5) {
            life[0]--;
            show_life(0);
        }
        else if (map5[newy][newx] == 6) {
            life[0]++;
            show_life(0);
        }
        map5[newy][newx] = 3;
        x = newx;
        y = newy;
    }

    if (stage == 6) {
        show_coin();
        show_flat();
        map6[y][x] = 0;
        if (map6[15][14] == 0) {
            map6[15][14] = 1;
        }
        if (map6[newy][newx] == 2) {
            if (score[0] <= 0)
                score[0] = 0;
            else
                score[0] -= 10;
            show_score(0);
        }
        else if (map6[newy][newx] == 1) {
            newx = x;
            newy = y;
        }
        else if (map6[newy][newx] == 4 || map6[newy][newx] == 5) {
            life[0]--;
            show_life(0);
            newx = x;
            newy = y;
        }
        else if (map6[newy][newx] == 6) {
            score[0] += 10;
            show_score(0);
        }
        map6[newy][newx] = 3;
        x = newx;
        y = newy;
    }

    return 0;
}

int player2(unsigned char ch, int stage) {
    static int newx = 14, newy = 15, x = 14, y = 15;
    static int laststage = 0;

    if (laststage != stage)
    {
        newx = 14, newy = 15, x = 14, y = 15;
        laststage = stage;
    }

    switch (ch) {
    case UP2:
        newy = y - 1;
        break;
    case DOWN2:
        newy = y + 1;
        break;
    case LEFT2:
        newx = x - 1;
        break;
    case RIGHT2:
        newx = x + 1;
        break;
    }

    if (stage == 1) {
        map1_[y][x] = 0;
        if (map1_[newy][newx] == 2) {
            score[1] += 50;
            show_score(1);
            newx = 14, newy = 15, x = 14, y = 15;
            return 1;
        }
        else if (map1_[newy][newx] == 1) {
            newx = x;
            newy = y;
        }
        else if (map1_[newy][newx] == 4 || map1_[newy][newx] == 5) {
            life[1]--;
            show_life(1);
            //newx = x;
             //newy = y;
        }
        else if (map1_[newy][newx] == 6) {
            life[1]++;
            show_life(1);
        }
        map1_[newy][newx] = 3;
        x = newx;
        y = newy;
    }

    if (stage == 2) {
        map2_[y][x] = 0;
        if (map2_[newy][newx] == 2) {
            score[1] += 50;
            show_score(1);
            newx = 14, newy = 15, x = 14, y = 15;
            return 2;
        }
        else if (map2_[newy][newx] == 1) {
            newx = x;
            newy = y;
        }
        else if (map2_[newy][newx] == 4 || map2_[newy][newx] == 5) {
            life[1]--;
            show_life(1);
        }
        else if (map2_[newy][newx] == 6) {
            life[1]++;
            show_life(1);
        }
        map2_[newy][newx] = 3;
        x = newx;
        y = newy;
    }

    if (stage == 3) {
        map3_[y][x] = 0;
        if (map3_[newy][newx] == 2) {
            score[1] += 50;
            show_score(1);
            newx = 14, newy = 15, x = 14, y = 15;
            return 3;
        }
        else if (map3_[newy][newx] == 1) {
            newx = x;
            newy = y;
        }
        else if (map3_[newy][newx] == 4 || map3_[newy][newx] == 5) {
            life[1]--;
            show_life(1);
        }
        else if (map3_[newy][newx] == 6) {
            life[1]++;
            show_life(1);
        }
        else if (map3[newx][newy] == 7) {
            life[0]--;
            show_life(0);
            newx = x;
            newy = y;
        }
        map3_[newy][newx] = 3;
        x = newx;
        y = newy;
    }

    if (stage == 4) {
        map4_[y][x] = 0;
        if (map4_[newy][newx] == 2) {
            score[1] += 50;
            show_score(1);
            newx = 14, newy = 15, x = 14, y = 15;
            return 4;
        }
        else if (map4_[newy][newx] == 1) {
            newx = x;
            newy = y;
        }
        else if (map4_[newy][newx] == 4 || map4_[newy][newx] == 5) {
            life[1]--;
            show_life(1);
        }
        else if (map4_[newy][newx] == 6) {
            life[1]++;
            show_life(1);
        }
        map4_[newy][newx] = 3;
        x = newx;
        y = newy;
    }

    if (stage == 5) {
        map5_[y][x] = 0;
        if (map5_[newy][newx] == 2) {
            score[1] += 50;
            show_score(1);
            newx = 14, newy = 15, x = 14, y = 15;
            return 5;
        }
        else if (map5_[newy][newx] == 1) {
            newx = x;
            newy = y;
        }
        else if (map5_[newy][newx] == 4 || map5_[newy][newx] == 5) {
            life[1]--;
            show_life(1);
        }
        else if (map5_[newy][newx] == 6) {
            life[1]++;
            show_life(1);
        }
        map5_[newy][newx] = 3;
        x = newx;
        y = newy;
    }

    if (stage == 6) {
        show_coin();
        show_flat();
        map6_[y][x] = 0;
        if (map6_[15][14] == 0) {
            map6_[15][14] = 1;
        }
        if (map6_[newy][newx] == 2) {
            if (score[1] <= 0)
                score[1] = 0;
            else
                score[1] -= 10;
            show_score(1);
        }
        else if (map6_[newy][newx] == 1) {
            newx = x;
            newy = y;
        }
        else if (map6_[newy][newx] == 4 || map6_[newy][newx] == 5) {
            life[1]--;
            show_life(1);
            newx = x;
            newy = y;
        }
        else if (map6_[newy][newx] == 6) {
            score[1] += 10;
            show_score(1);
        }
        map6_[newy][newx] = 3;
        x = newx;
        y = newy;
    }

    return 0;
}

void stage6() //스테이지6
{
    int i, x, y;
    unsigned char ch;
    static int newx = 14, newy = 15;

    cls(BLACK, WHITE);
    for (y = 0; y < 16; y++) {
        for (x = 0; x < 16; x++) {
            gotoxy((x * 2) + 10, y + 5); //player1 stage5맵
            switch (map6[y][x]) {
            case 0:
                printf("  "); //길
                break;
            case 1:
                textcolor(GRAY1, BLACK);
                printf("■"); //벽
                textcolor(WHITE, BLACK);
                break;
            case 2:
                textcolor(GREEN2, BLACK);
                printf("♭"); //다음단계
                textcolor(WHITE, BLACK);
                break;
            case 3:
                textcolor(YELLOW1, BLACK);
                printf("★"); //캐릭터
                textcolor(WHITE, BLACK);
                break;
            case 4:
            case 5:
                textcolor(RED2, BLACK);
                printf("※"); //몬스터
                textcolor(WHITE, BLACK);
                break;
            case 6:
                textcolor(CYAN2, BLACK);
                printf("◈");
                textcolor(WHITE, BLACK);
                break;
            }

            gotoxy((x * 2) + 59, y + 5); //player2 stage5맵
            switch (map6_[y][x]) {
            case 0:
                printf("  "); //길
                break;
            case 1:
                textcolor(GRAY1, BLACK);
                printf("■"); //벽
                textcolor(WHITE, BLACK);
                break;
            case 2:
                textcolor(GREEN2, BLACK);
                printf("♭"); //다음단계
                textcolor(WHITE, BLACK);
                break;
            case 3:
                textcolor(YELLOW1, BLACK);
                printf("★"); //캐릭터
                textcolor(WHITE, BLACK);
                break;
            case 4:
            case 5:
                textcolor(RED2, BLACK);
                printf("※"); //몬스터
                textcolor(WHITE, BLACK);
                break;
            case 6:
                textcolor(CYAN2, BLACK);
                printf("◈");
                textcolor(WHITE, BLACK);
                break;
            }
        }
    }

    int run_time, start_time, remain_time, last_remain_time;

    textcolor(GREEN2, GRAY2);
    draw_hline(1, 0, 101, ' ');
    textcolor(WHITE, BLACK);
    show_score(0); show_score(1);
    show_life(0); show_life(1);

    for (i = 3; i <= 23; i++) {
        gotoxy(49, i); printf("│");
    }//구분선

    start_time = (time(NULL));
    last_remain_time = remain_time = time_out;
    textcolor(GREEN2, GRAY2);
    draw_uline(25, 0, 101, ' ');
    textcolor(WHITE, BLACK);
    show_time(remain_time);

    while (1) {
        int a;

        run_time = time(NULL) - start_time;
        remain_time = time_out - run_time;
        if (remain_time < last_remain_time) {
            show_time(remain_time);
            last_remain_time = remain_time;
        }
        if (remain_time == 0) {
            break;
        }

        if (_kbhit() == 1) {  // 키보드가 눌려져 있으면
            ch = _getch(); // key 값을 읽는다
            if (ch == SPECIAL1 || ch == SPECIAL2) { // 만약 특수키
                // 예를 들어 UP key의 경우 0xe0 0x48 두개의 문자가 들어온다.
                ch = _getch();
                // Player1은 방향키로 움직인다.
                switch (ch) {
                case UP:
                case DOWN:
                case LEFT:
                case RIGHT:
                    a = player1(ch, stage);//player1만 방향 전환
                    player2(0, stage);
                    break;
                default: // 방향 전환이 아니면
                    player1(0, stage);
                    player2(0, stage);
                }
            }
            else {
                // Player2은 AWSD 로 움직인다.
                switch (ch) {
                case UP2:
                case DOWN2:
                case LEFT2:
                case RIGHT2://player2만 방향 전환
                    a = player2(ch, stage);
                    player1(0, stage);
                    break;
                default:// 방향 전환이 아니면
                    player1(0, stage);
                    player2(0, stage);
                }
            }
            if (a == 6)
                break;
            for (y = 0; y < 16; y++) {
                for (x = 0; x < 16; x++) {
                    gotoxy((x * 2) + 10, y + 5); //player1 stage1맵
                    switch (map6[y][x]) {
                    case 0:
                        printf("  "); //길
                        break;
                    case 1:
                        textcolor(GRAY1, BLACK);
                        printf("■"); //벽
                        textcolor(WHITE, BLACK);
                        break;
                    case 2:
                        textcolor(GREEN2, BLACK);
                        printf("♭"); //다음단계
                        textcolor(WHITE, BLACK);
                        break;
                    case 3:
                        textcolor(YELLOW1, BLACK);
                        printf("★"); //캐릭터
                        textcolor(WHITE, BLACK);
                        break;
                    case 4:
                    case 5:
                        textcolor(RED2, BLACK);
                        printf("※"); //몬스터
                        textcolor(WHITE, BLACK);
                        break;
                    case 6:
                        textcolor(CYAN2, BLACK);
                        printf("◈");
                        textcolor(WHITE, BLACK);
                        break;
                    }

                    gotoxy((x * 2) + 59, y + 5); //player2 stage1맵
                    switch (map6_[y][x]) {
                    case 0:
                        printf("  "); //길
                        break;
                    case 1:
                        textcolor(GRAY1, BLACK);
                        printf("■"); //벽
                        textcolor(WHITE, BLACK);
                        break;
                    case 2:
                        textcolor(GREEN2, BLACK);
                        printf("♭"); //다음단계
                        textcolor(WHITE, BLACK);
                        break;
                    case 3:
                        textcolor(YELLOW1, BLACK);
                        printf("★"); //캐릭터
                        textcolor(WHITE, BLACK);
                        break;
                    case 4:
                    case 5:
                        textcolor(RED2, BLACK);
                        printf("※"); //몬스터
                        textcolor(WHITE, BLACK);
                        break;
                    case 6:
                        textcolor(CYAN2, BLACK);
                        printf("◈");
                        textcolor(WHITE, BLACK);
                        break;
                    }
                }
            }
        }
        Sleep(100);
    }
    finish_point();
}

void stage5() //스테이지5
{
    int i, x, y;
    unsigned char ch;
    static int newx = 14, newy = 15;

    cls(BLACK, WHITE);
    newx1_5 = x1_5 = 2; newx2_5 = x2_5 = 2;
    newy1_5 = y1_5 = 7; newy2_5 = y2_5 = 7;

    for (y = 0; y < 16; y++) {
        for (x = 0; x < 16; x++) {
            gotoxy((x * 2) + 10, y + 5); //player1 stage5맵
            switch (map5[y][x]) {
            case 0:
                printf("  "); //길
                break;
            case 1:
                textcolor(GRAY1, BLACK);
                printf("■"); //벽
                textcolor(WHITE, BLACK);
                break;
            case 2:
                textcolor(GREEN2, BLACK);
                printf("▲"); //다음단계
                textcolor(WHITE, BLACK);
                break;
            case 3:
                textcolor(YELLOW1, BLACK);
                printf("★"); //캐릭터
                textcolor(WHITE, BLACK);
                break;
            case 4:
            case 5:
                textcolor(RED2, BLACK);
                printf("※"); //몬스터
                textcolor(WHITE, BLACK);
                break;
            case 6:
                textcolor(BLUE2, BLACK);
                printf("♥");
                textcolor(WHITE, BLACK);
                break;
            }

            gotoxy((x * 2) + 59, y + 5); //player2 stage5맵
            switch (map5_[y][x]) {
            case 0:
                printf("  "); //길
                break;
            case 1:
                textcolor(GRAY1, BLACK);
                printf("■"); //벽
                textcolor(WHITE, BLACK);
                break;
            case 2:
                textcolor(GREEN2, BLACK);
                printf("▲"); //다음단계
                textcolor(WHITE, BLACK);
                break;
            case 3:
                textcolor(YELLOW1, BLACK);
                printf("★"); //캐릭터
                textcolor(WHITE, BLACK);
                break;
            case 4:
            case 5:
                textcolor(RED2, BLACK);
                printf("※"); //몬스터
                textcolor(WHITE, BLACK);
                break;
            case 6:
                textcolor(BLUE2, BLACK);
                printf("♥");
                textcolor(WHITE, BLACK);
                break;
            }
        }
    }

    textcolor(GREEN2, GRAY2);
    draw_hline(1, 0, 101, ' ');
    textcolor(WHITE, BLACK);
    show_score(0); show_score(1);
    show_life(0); show_life(1);

    for (i = 3; i <= 26; i++) {
        gotoxy(49, i); printf("│");
    }//구분선

    while (1) {
        int a;
        move_monster();

        if (_kbhit() == 1) {  // 키보드가 눌려져 있으면
            ch = _getch(); // key 값을 읽는다
            if (ch == SPECIAL1 || ch == SPECIAL2) { // 만약 특수키
                // 예를 들어 UP key의 경우 0xe0 0x48 두개의 문자가 들어온다.
                ch = _getch();
                // Player1은 방향키로 움직인다.
                switch (ch) {
                case UP:
                case DOWN:
                case LEFT:
                case RIGHT:
                    a = player1(ch, stage);//while문에서 탈출하기 위해 stage 값을 a에 넣어줌
                    player2(0, stage);
                    break;
                default: // 방향 전환이 아니면
                    player1(0, stage);
                    player2(0, stage);
                }
            }
            else {
                // Player2은 AWSD 로 움직인다.
                switch (ch) {
                case UP2:
                case DOWN2:
                case LEFT2:
                case RIGHT2://player2만 방향 전환
                    a = player2(ch, stage);
                    player1(0, stage);
                    break;
                default:// 방향 전환이 아니면
                    player1(0, stage);
                    player2(0, stage);
                }
            }
            if (a == 5) //a가 5면 whie문에서 탈출
                break;
            for (y = 0; y < 16; y++) {
                for (x = 0; x < 16; x++) {
                    gotoxy((x * 2) + 10, y + 5); //player1 stage1맵
                    switch (map5[y][x]) {
                    case 0:
                        printf("  "); //길
                        break;
                    case 1:
                        textcolor(GRAY1, BLACK);
                        printf("■"); //벽
                        textcolor(WHITE, BLACK);
                        break;
                    case 2:
                        textcolor(GREEN2, BLACK);
                        printf("▲"); //다음단계
                        textcolor(WHITE, BLACK);
                        break;
                    case 3:
                        textcolor(YELLOW1, BLACK);
                        printf("★"); //캐릭터
                        textcolor(WHITE, BLACK);
                        break;
                    case 4:
                    case 5:
                        textcolor(RED2, BLACK);
                        printf("※"); //몬스터
                        textcolor(WHITE, BLACK);
                        break;
                    case 6:
                        textcolor(BLUE2, BLACK);
                        printf("♥");
                        textcolor(WHITE, BLACK);
                        break;
                    }

                    gotoxy((x * 2) + 59, y + 5); //player2 stage1맵
                    switch (map5_[y][x]) {
                    case 0:
                        printf("  "); //길
                        break;
                    case 1:
                        textcolor(GRAY1, BLACK);
                        printf("■"); //벽
                        textcolor(WHITE, BLACK);
                        break;
                    case 2:
                        textcolor(GREEN2, BLACK);
                        printf("▲"); //다음단계
                        textcolor(WHITE, BLACK);
                        break;
                    case 3:
                        textcolor(YELLOW1, BLACK);
                        printf("★"); //캐릭터
                        textcolor(WHITE, BLACK);
                        break;
                    case 4:
                    case 5:
                        textcolor(RED2, BLACK);
                        printf("※"); //몬스터
                        textcolor(WHITE, BLACK);
                        break;
                    case 6:
                        textcolor(BLUE2, BLACK);
                        printf("♥");
                        textcolor(WHITE, BLACK);
                        break;
                    }
                }
            }
        }
        Sleep(100);
    }
    stage++;
    stage6(); //보너스 스테이지
}

void stage4() //스테이지4
{
    int i, x, y;
    unsigned char ch;
    static int newx = 14, newy = 15;

    cls(BLACK, WHITE);
    newx1_4 = x1_4 = 5; newx2_4 = x2_4 = 5;
    newy1_4 = y1_4 = 6; newy2_4 = y2_4 = 6;
    for (y = 0; y < 16; y++) {
        for (x = 0; x < 16; x++) {
            gotoxy((x * 2) + 10, y + 5); //player1 stage2맵
            switch (map4[y][x]) {
            case 0:
                printf("  "); //길
                break;
            case 1:
                textcolor(GRAY1, BLACK);
                printf("■"); //벽
                textcolor(WHITE, BLACK);
                break;
            case 2:
                textcolor(GREEN2, BLACK);
                printf("▲"); //다음단계
                textcolor(WHITE, BLACK);
                break;
            case 3:
                textcolor(YELLOW1, BLACK);
                printf("★"); //캐릭터
                textcolor(WHITE, BLACK);
                break;
            case 4:
            case 5:
                textcolor(RED2, BLACK);
                printf("※"); //몬스터
                textcolor(WHITE, BLACK);
                break;
            case 6:
                textcolor(BLUE2, BLACK);
                printf("♥");
                textcolor(WHITE, BLACK);
                break;
            }

            gotoxy((x * 2) + 59, y + 5); //player2 stage1맵
            switch (map4_[y][x]) {
            case 0:
                printf("  "); //길
                break;
            case 1:
                textcolor(GRAY1, BLACK);
                printf("■"); //벽
                textcolor(WHITE, BLACK);
                break;
            case 2:
                textcolor(GREEN2, BLACK);
                printf("▲"); //다음단계
                textcolor(WHITE, BLACK);
                break;
            case 3:
                textcolor(YELLOW1, BLACK);
                printf("★"); //캐릭터
                textcolor(WHITE, BLACK);
                break;
            case 4:
            case 5:
                textcolor(RED2, BLACK);
                printf("※"); //몬스터
                textcolor(WHITE, BLACK);
                break;
            case 6:
                textcolor(BLUE2, BLACK);
                printf("♥");
                textcolor(WHITE, BLACK);
                break;
            }
        }
    }

    textcolor(GREEN2, GRAY2);
    draw_hline(1, 0, 101, ' ');
    textcolor(WHITE, BLACK);
    show_score(0); show_score(1);
    show_life(0); show_life(1);

    for (i = 3; i <= 26; i++) {
        gotoxy(49, i); printf("│");
    }//구분선

    while (1) {
        int a;
        move_monster();

        if (_kbhit() == 1) {  // 키보드가 눌려져 있으면
            ch = _getch(); // key 값을 읽는다
            if (ch == SPECIAL1 || ch == SPECIAL2) { // 만약 특수키
                // 예를 들어 UP key의 경우 0xe0 0x48 두개의 문자가 들어온다.
                ch = _getch();
                // Player1은 방향키로 움직인다.
                switch (ch) {
                case UP:
                case DOWN:
                case LEFT:
                case RIGHT:
                    a = player1(ch, stage);//player1만 방향 전환
                    player2(0, stage);
                    break;
                default: // 방향 전환이 아니면
                    player1(0, stage);
                    player2(0, stage);
                }
            }
            else {
                // Player2은 AWSD 로 움직인다.
                switch (ch) {
                case UP2:
                case DOWN2:
                case LEFT2:
                case RIGHT2://player2만 방향 전환
                    a = player2(ch, stage);
                    player1(0, stage);
                    break;
                default:// 방향 전환이 아니면
                    player1(0, stage);
                    player2(0, stage);
                }
            }
            if (a == 4)
                break;
            for (y = 0; y < 16; y++) {
                for (x = 0; x < 16; x++) {
                    gotoxy((x * 2) + 10, y + 5); //player1 stage1맵
                    switch (map4[y][x]) {
                    case 0:
                        printf("  "); //길
                        break;
                    case 1:
                        textcolor(GRAY1, BLACK);
                        printf("■"); //벽
                        textcolor(WHITE, BLACK);
                        break;
                    case 2:
                        textcolor(GREEN2, BLACK);
                        printf("▲"); //다음단계
                        textcolor(WHITE, BLACK);
                        break;
                    case 3:
                        textcolor(YELLOW1, BLACK);
                        printf("★"); //캐릭터
                        textcolor(WHITE, BLACK);
                        break;
                    case 4:
                    case 5:
                        textcolor(RED2, BLACK);
                        printf("※"); //몬스터
                        textcolor(WHITE, BLACK);
                        break;
                    case 6:
                        textcolor(BLUE2, BLACK);
                        printf("♥");
                        textcolor(WHITE, BLACK);
                        break;
                    }

                    gotoxy((x * 2) + 59, y + 5); //player2 stage1맵
                    switch (map4_[y][x]) {
                    case 0:
                        printf("  "); //길
                        break;
                    case 1:
                        textcolor(GRAY1, BLACK);
                        printf("■"); //벽
                        textcolor(WHITE, BLACK);
                        break;
                    case 2:
                        textcolor(GREEN2, BLACK);
                        printf("▲"); //다음단계
                        textcolor(WHITE, BLACK);
                        break;
                    case 3:
                        textcolor(YELLOW1, BLACK);
                        printf("★"); //캐릭터
                        textcolor(WHITE, BLACK);
                        break;
                    case 4:
                    case 5:
                        textcolor(RED2, BLACK);
                        printf("※"); //몬스터
                        textcolor(WHITE, BLACK);
                        break;
                    case 6:
                        textcolor(BLUE2, BLACK);
                        printf("♥");
                        textcolor(WHITE, BLACK);
                        break;
                    }
                }
            }
        }
        Sleep(100);
    }
    stage++;
    stage5();
}

void stage3() //스테이지3
{
    int i, x, y;
    unsigned char ch;
    static int newx = 14, newy = 15;

    cls(BLACK, WHITE);
    newx1_3 = x1_3 = 7; newx2_3 = x2_3 = 7;
    newy1_3 = y1_3 = 5; newy2_3 = y2_3 = 5;
    for (y = 0; y < 16; y++) {
        for (x = 0; x < 16; x++) {
            gotoxy((x * 2) + 10, y + 5); //player1 stage2맵
            switch (map3[y][x]) {
            case 0:
                printf("  "); //길
                break;
            case 1:
                textcolor(GRAY1, BLACK);
                printf("■"); //벽
                textcolor(WHITE, BLACK);
                break;
            case 2:
                textcolor(GREEN2, BLACK);
                printf("▲"); //다음단계
                textcolor(WHITE, BLACK);
                break;
            case 3:
                textcolor(YELLOW1, BLACK);
                printf("★"); //캐릭터
                textcolor(WHITE, BLACK);
                break;
            case 4:
            case 5:
            case 7:
                textcolor(RED2, BLACK);
                printf("※"); //몬스터
                textcolor(WHITE, BLACK);
                break;
            case 6:
                textcolor(BLUE2, BLACK);
                printf("♥");
                textcolor(WHITE, BLACK);
                break;
            }

            gotoxy((x * 2) + 59, y + 5); //player2 stage1맵
            switch (map3_[y][x]) {
            case 0:
                printf("  "); //길
                break;
            case 1:
                textcolor(GRAY1, BLACK);
                printf("■"); //벽
                textcolor(WHITE, BLACK);
                break;
            case 2:
                textcolor(GREEN2, BLACK);
                printf("▲"); //다음단계
                textcolor(WHITE, BLACK);
                break;
            case 3:
                textcolor(YELLOW1, BLACK);
                printf("★"); //캐릭터
                textcolor(WHITE, BLACK);
                break;
            case 4:
            case 5:
            case 7:
                textcolor(RED2, BLACK);
                printf("※"); //몬스터
                textcolor(WHITE, BLACK);
                break;
            case 6:
                textcolor(BLUE2, BLACK);
                printf("♥");
                textcolor(WHITE, BLACK);
                break;
            }
        }
    }

    textcolor(GREEN2, GRAY2);
    draw_hline(1, 0, 101, ' ');
    textcolor(WHITE, BLACK);
    show_score(0); show_score(1);
    show_life(0); show_life(1);

    for (i = 3; i <= 26; i++) {
        gotoxy(49, i); printf("│");
    }//구분선

    while (1) {
        int a;
        move_monster();

        if (_kbhit() == 1) {  // 키보드가 눌려져 있으면
            ch = _getch(); // key 값을 읽는다
            if (ch == SPECIAL1 || ch == SPECIAL2) { // 만약 특수키
                // 예를 들어 UP key의 경우 0xe0 0x48 두개의 문자가 들어온다.
                ch = _getch();
                // Player1은 방향키로 움직인다.
                switch (ch) {
                case UP:
                case DOWN:
                case LEFT:
                case RIGHT:
                    a = player1(ch, stage);//player1만 방향 전환
                    player2(0, stage);
                    break;
                default: // 방향 전환이 아니면
                    player1(0, stage);
                    player2(0, stage);
                }
            }
            else {
                // Player2은 AWSD 로 움직인다.
                switch (ch) {
                case UP2:
                case DOWN2:
                case LEFT2:
                case RIGHT2://player2만 방향 전환
                    a = player2(ch, stage);
                    player1(0, stage);
                    break;
                default:// 방향 전환이 아니면
                    player1(0, stage);
                    player2(0, stage);
                }
            }
            if (a == 3)
                break;
            for (y = 0; y < 16; y++) {
                for (x = 0; x < 16; x++) {
                    gotoxy((x * 2) + 10, y + 5); //player1 stage1맵
                    switch (map3[y][x]) {
                    case 0:
                        printf("  "); //길
                        break;
                    case 1:
                        textcolor(GRAY1, BLACK);
                        printf("■"); //벽
                        textcolor(WHITE, BLACK);
                        break;
                    case 2:
                        textcolor(GREEN2, BLACK);
                        printf("▲"); //다음단계
                        textcolor(WHITE, BLACK);
                        break;
                    case 3:
                        textcolor(YELLOW1, BLACK);
                        printf("★"); //캐릭터
                        textcolor(WHITE, BLACK);
                        break;
                    case 4:
                    case 5:
                    case 7:
                        textcolor(RED2, BLACK);
                        printf("※"); //몬스터
                        textcolor(WHITE, BLACK);
                        break;
                    case 6:
                        textcolor(BLUE2, BLACK);
                        printf("♥");
                        textcolor(WHITE, BLACK);
                        break;
                    }

                    gotoxy((x * 2) + 59, y + 5); //player2 stage1맵
                    switch (map3_[y][x]) {
                    case 0:
                        printf("  "); //길
                        break;
                    case 1:
                        textcolor(GRAY1, BLACK);
                        printf("■"); //벽
                        textcolor(WHITE, BLACK);
                        break;
                    case 2:
                        textcolor(GREEN2, BLACK);
                        printf("▲"); //다음단계
                        textcolor(WHITE, BLACK);
                        break;
                    case 3:
                        textcolor(YELLOW1, BLACK);
                        printf("★"); //캐릭터
                        textcolor(WHITE, BLACK);
                        break;
                    case 4:
                    case 5:
                    case 7:
                        textcolor(RED2, BLACK);
                        printf("※"); //몬스터
                        textcolor(WHITE, BLACK);
                        break;
                    case 6:
                        textcolor(BLUE2, BLACK);
                        printf("♥");
                        textcolor(WHITE, BLACK);
                        break;
                    }
                }
            }
        }
        Sleep(100);
    }
    stage++;
    stage4();
}

void stage2() //스테이지2
{
    int i, x, y;
    unsigned char ch;
    static int newx = 14, newy = 15;

    cls(BLACK, WHITE);
    newx1_2 = x1_2 = 4; newx2_2 = x2_2 = 4;
    newy1_2 = y1_2 = 6; newy2_2 = y2_2 = 6;

    for (y = 0; y < 16; y++) {
        for (x = 0; x < 16; x++) {
            gotoxy((x * 2) + 10, y + 5); //player1 stage2맵
            switch (map2[y][x]) {
            case 0:
                printf("  "); //길
                break;
            case 1:
                textcolor(GRAY1, BLACK);
                printf("■"); //벽
                textcolor(WHITE, BLACK);
                break;
            case 2:
                textcolor(GREEN2, BLACK);
                printf("▲"); //다음단계
                textcolor(WHITE, BLACK);
                break;
            case 3:
                textcolor(YELLOW1, BLACK);
                printf("★"); //캐릭터
                textcolor(WHITE, BLACK);
                break;
            case 4:
            case 5:
                textcolor(RED2, BLACK);
                printf("※"); //몬스터
                textcolor(WHITE, BLACK);
                break;
            case 6:
                textcolor(BLUE2, BLACK);
                printf("♥");
                textcolor(WHITE, BLACK);
                break;
            }

            gotoxy((x * 2) + 59, y + 5); //player2 stage1맵
            switch (map2_[y][x]) {
            case 0:
                printf("  "); //길
                break;
            case 1:
                textcolor(GRAY1, BLACK);
                printf("■"); //벽
                textcolor(WHITE, BLACK);
                break;
            case 2:
                textcolor(GREEN2, BLACK);
                printf("▲"); //다음단계
                textcolor(WHITE, BLACK);
                break;
            case 3:
                textcolor(YELLOW1, BLACK);
                printf("★"); //캐릭터
                textcolor(WHITE, BLACK);
                break;
            case 4:
            case 5:
                textcolor(RED2, BLACK);
                printf("※"); //몬스터
                textcolor(WHITE, BLACK);
                break;
            case 6:
                textcolor(BLUE2, BLACK);
                printf("♥");
                textcolor(WHITE, BLACK);
                break;
            }
        }
    }

    textcolor(GREEN2, GRAY2);
    draw_hline(1, 0, 101, ' ');
    textcolor(WHITE, BLACK);
    show_score(0); show_score(1);
    show_life(0); show_life(1);

    for (i = 3; i <= 26; i++) {
        gotoxy(49, i); printf("│");
    }//구분선

    while (1) {
        int a;
        move_monster();

        if (_kbhit() == 1) {  // 키보드가 눌려져 있으면
            ch = _getch(); // key 값을 읽는다
            if (ch == SPECIAL1 || ch == SPECIAL2) { // 만약 특수키
                // 예를 들어 UP key의 경우 0xe0 0x48 두개의 문자가 들어온다.
                ch = _getch();
                // Player1은 방향키로 움직인다.
                switch (ch) {
                case UP:
                case DOWN:
                case LEFT:
                case RIGHT:
                    a = player1(ch, stage);//player1만 방향 전환
                    player2(0, stage);
                    break;
                default: // 방향 전환이 아니면
                    player1(0, stage);
                    player2(0, stage);
                }
            }
            else {
                // Player2은 AWSD 로 움직인다.
                switch (ch) {
                case UP2:
                case DOWN2:
                case LEFT2:
                case RIGHT2://player2만 방향 전환
                    a = player2(ch, stage);
                    player1(0, stage);
                    break;
                default:// 방향 전환이 아니면
                    player1(0, stage);
                    player2(0, stage);
                }
            }
            if (a == 2)
                break;
            for (y = 0; y < 16; y++) {
                for (x = 0; x < 16; x++) {
                    gotoxy((x * 2) + 10, y + 5); //player1 stage1맵
                    switch (map2[y][x]) {
                    case 0:
                        printf("  "); //길
                        break;
                    case 1:
                        textcolor(GRAY1, BLACK);
                        printf("■"); //벽
                        textcolor(WHITE, BLACK);
                        break;
                    case 2:
                        textcolor(GREEN2, BLACK);
                        printf("▲"); //다음단계
                        textcolor(WHITE, BLACK);
                        break;
                    case 3:
                        textcolor(YELLOW1, BLACK);
                        printf("★"); //캐릭터
                        textcolor(WHITE, BLACK);
                        break;
                    case 4:
                    case 5:
                        textcolor(RED2, BLACK);
                        printf("※"); //몬스터
                        textcolor(WHITE, BLACK);
                        break;
                    case 6:
                        textcolor(BLUE2, BLACK);
                        printf("♥");
                        textcolor(WHITE, BLACK);
                        break;
                    }

                    gotoxy((x * 2) + 59, y + 5); //player2 stage1맵
                    switch (map2_[y][x]) {
                    case 0:
                        printf("  "); //길
                        break;
                    case 1:
                        textcolor(GRAY1, BLACK);
                        printf("■"); //벽
                        textcolor(WHITE, BLACK);
                        break;
                    case 2:
                        textcolor(GREEN2, BLACK);
                        printf("▲"); //다음단계
                        textcolor(WHITE, BLACK);
                        break;
                    case 3:
                        textcolor(YELLOW1, BLACK);
                        printf("★"); //캐릭터
                        textcolor(WHITE, BLACK);
                        break;
                    case 4:
                    case 5:
                        textcolor(RED2, BLACK);
                        printf("※"); //몬스터
                        textcolor(WHITE, BLACK);
                        break;
                    case 6:
                        textcolor(BLUE2, BLACK);
                        printf("♥");
                        textcolor(WHITE, BLACK);
                        break;
                    }
                }
            }
        };
        Sleep(100);
    }
    stage++;
    stage3();
}

void stage1() //게임시작. 스테이지1
{
    int i, x, y;
    unsigned char ch;
    static int newx = 14, newy = 15;

    cls(BLACK, WHITE);
    newx1 = x1 = 5; newx2 = x2 = 5;
    newy1 = y1 = 14; newy2 = y2 = 14;

    for (y = 0; y < 16; y++) {
        for (x = 0; x < 16; x++) {
            gotoxy((x * 2) + 10, y + 5); //player1 stage1맵
            switch (map1[y][x]) {
            case 0:
                printf("  "); //길
                break;
            case 1:
                textcolor(GRAY1, BLACK);
                printf("■"); //벽
                textcolor(WHITE, BLACK);
                break;
            case 2:
                textcolor(GREEN2, BLACK);
                printf("▲"); //다음단계
                textcolor(WHITE, BLACK);
                break;
            case 3:
                textcolor(YELLOW1, BLACK);
                printf("★"); //캐릭터
                textcolor(WHITE, BLACK);
                break;
            case 4:
            case 5:
                textcolor(RED2, BLACK);
                printf("※"); //몬스터
                textcolor(WHITE, BLACK);
                break;
            case 6:
                textcolor(BLUE2, BLACK);
                printf("♥");
                textcolor(WHITE, BLACK);
                break;
            }

            gotoxy((x * 2) + 59, y + 5); //player2 stage1맵
            switch (map1_[y][x]) {
            case 0:
                printf("  "); //길
                break;
            case 1:
                textcolor(GRAY1, BLACK);
                printf("■"); //벽
                textcolor(WHITE, BLACK);
                break;
            case 2:
                textcolor(GREEN2, BLACK);
                printf("▲"); //다음단계
                textcolor(WHITE, BLACK);
                break;
            case 3:
                textcolor(YELLOW1, BLACK);
                printf("★"); //캐릭터
                textcolor(WHITE, BLACK);
                break;
            case 4:
            case 5:
                textcolor(RED2, BLACK);
                printf("※"); //몬스터
                textcolor(WHITE, BLACK);
                break;
            case 6:
                textcolor(BLUE2, BLACK);
                printf("♥");
                textcolor(WHITE, BLACK);
                break;
            }
        }
    }

    textcolor(GREEN2, GRAY2);
    draw_hline(1, 0, 101, ' ');
    textcolor(WHITE, BLACK);
    show_score(0); show_score(1);
    show_life(0); show_life(1);

    for (i = 3; i <= 26; i++) {
        gotoxy(49, i); printf("│");
    }//구분선

    while (1) {
        int a;
        move_monster();

        if (_kbhit() == 1) {  // 키보드가 눌려져 있으면
            ch = _getch(); // key 값을 읽는다
            if (ch == SPECIAL1 || ch == SPECIAL2) { // 만약 특수키
                // 예를 들어 UP key의 경우 0xe0 0x48 두개의 문자가 들어온다.
                ch = _getch();
                // Player1은 방향키로 움직인다.
                switch (ch) {
                case UP:
                case DOWN:
                case LEFT:
                case RIGHT:
                    a = player1(ch, stage); //player1만 방향 전환
                    player2(0, stage);
                    break;
                default: // 방향 전환이 아니면
                    player1(0, stage);
                    player2(0, stage);
                }
            }
            else {
                // Player2은 AWSD 로 움직인다.
                switch (ch) {
                case UP2:
                case DOWN2:
                case LEFT2:
                case RIGHT2://player2만 방향 전환
                    a = player2(ch, stage);
                    player1(0, stage);
                    break;
                default:// 방향 전환이 아니면
                    player1(0, stage);
                    player2(0, stage);
                }
            }
            if (a == 1)
                break;
            for (y = 0; y < 16; y++) {
                for (x = 0; x < 16; x++) {
                    gotoxy((x * 2) + 10, y + 5); //player1 stage1맵
                    switch (map1[y][x]) {
                    case 0:
                        printf("  "); //길
                        break;
                    case 1:
                        textcolor(GRAY1, BLACK);
                        printf("■"); //벽
                        textcolor(WHITE, BLACK);
                        break;
                    case 2:
                        textcolor(GREEN2, BLACK);
                        printf("▲"); //다음단계
                        textcolor(WHITE, BLACK);
                        break;
                    case 3:
                        textcolor(YELLOW1, BLACK);
                        printf("★"); //캐릭터
                        textcolor(WHITE, BLACK);
                        break;
                    case 4:
                    case 5:
                        textcolor(RED2, BLACK);
                        printf("※"); //몬스터
                        textcolor(WHITE, BLACK);
                        break;
                    case 6:
                        textcolor(BLUE2, BLACK);
                        printf("♥");
                        textcolor(WHITE, BLACK);
                        break;
                    }

                    gotoxy((x * 2) + 59, y + 5); //player2 stage1맵
                    switch (map1_[y][x]) {
                    case 0:
                        printf("  "); //길
                        break;
                    case 1:
                        textcolor(GRAY1, BLACK);
                        printf("■"); //벽
                        textcolor(WHITE, BLACK);
                        break;
                    case 2:
                        textcolor(GREEN2, BLACK);
                        printf("▲"); //다음단계
                        textcolor(WHITE, BLACK);
                        break;
                    case 3:
                        textcolor(YELLOW1, BLACK);
                        printf("★"); //캐릭터
                        textcolor(WHITE, BLACK);
                        break;
                    case 4:
                    case 5:
                        textcolor(RED2, BLACK);
                        printf("※"); //몬스터
                        textcolor(WHITE, BLACK);
                        break;
                    case 6:
                        textcolor(BLUE2, BLACK);
                        printf("♥");
                        textcolor(WHITE, BLACK);
                        break;
                    }
                }
            }
        }
        Sleep(100);
    }
    stage++;
    stage2();
}

int main()
{
    unsigned char ch;

    removeCursor();
    cls(BLACK, WHITE);
    initialScreen(); //초기화면

    while (1) {

        if (_kbhit() == 1) { //키보드가 눌려져 있으면
            ch = _getch(); //key값 읽음
            if (ch == SPACE) //게임 시작
                break;
            if (ch == U)
                gameDescription(); //게임설명
            if (ch == ESC)
                exit(1); //게임종료
        }
    }

    stage++;
    stage1(); //게임시작. 스테이지1 
}