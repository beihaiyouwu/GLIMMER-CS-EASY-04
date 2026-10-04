
#include<stdio.h>
#include"game.h"
#include"console.h"
int main(void)
{  
    do{
    Console con;//结构体变量
    Game game;
    initGame(&game);//初始化棋盘
    initconsole(&con);//初始化控制台结构体
    while(game.status== GAME_RUNNING)
    {
      drawBoard(&game);//绘制棋盘
      readmouse(&game);//设置鼠标模式
      game_place(&game);//读取坐标并转换，绘制新棋盘
    }
    }while( wait());//询问用户是否再来
    restoreConsole();//恢复控制台状态
    return 0;

}
