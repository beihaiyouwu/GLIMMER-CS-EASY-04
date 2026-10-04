#include<windows.h>
#include<stdio.h>
#include<stdlib.h>
#include"game.h"
#include"console.h"

void initGame(Game *g)//初始棋盘
{
    for(int i=0;i<BOARD_SIZE;i++)
    {
        for(int j=0;j<BOARD_SIZE;j++)
        {
            g->cells[i][j]=EMPTY_CELL;
        }
    }
    g->current_player='X';
    g->move_count=0;
    g->status=GAME_RUNNING;
}
void initconsole(Console*m)
{
    m->hIn=GetStdHandle(STD_INPUT_HANDLE);
    SetConsoleTitleA("wuziqigame\n");
    DWORD inMode;
    GetConsoleMode(m->hIn,&inMode);
}
void readmouse(Game*game)//设置鼠标初始化
{
    HANDLE hIn=GetStdHandle/*获取控制台输入手柄*/(STD_INPUT_HANDLE/*控制台输入设备*/);
    SetConsoleMode/*修改控制台输入模式*/(hIn,ENABLE_MOUSE_INPUT/*开启控制台鼠标*/ | ENABLE_EXTENDED_FLAGS);
}
void drawBoard(Game*g)//绘制棋盘
{
    //拿到新棋盘覆盖原先棋盘
    HANDLE hout=GetStdHandle(STD_OUTPUT_HANDLE);//拿到标准输出控制台的句柄
    COORD topLeft={0,0};//保存控制台坐标设为0，0
    DWORD written;
    CONSOLE_SCREEN_BUFFER_INFO csbi;//存放控制台缓冲区信息
    GetConsoleScreenBufferInfo(hout,&csbi);//读取缓存区信息
    DWORD totalChar=csbi.dwSize.X*csbi.dwSize.Y;//整个控制台缓冲区全部字符总数
    FillConsoleOutputCharacter(hout,' ',totalChar,topLeft,&written);//批量填充空格实现清屏
    SetConsoleCursorPosition(hout,topLeft);
        int row,col;
        for(col=0;col<BOARD_SIZE;col++) 
        {
            printf("+---");
        }
        printf("+\n");
        for(row=0;row<BOARD_SIZE;row++)
        {
        for(col=0;col<BOARD_SIZE;col++)
        {
            printf("| %c ",g->cells[row][col]);
        }
        printf("|\n");
      for(col=0;col<BOARD_SIZE;col++)
        {
            printf("+---");
        }
        printf("+\n");
    }
     if(g->status==GAME_RUNNING)
     {
    printf("currentplayer:%c\t",g->current_player);
    printf("game status:game running\n");
     }
    
}
void game_place(Game*game)
{               
                HANDLE hIn=GetStdHandle/*获取控制台输入手柄*/(STD_INPUT_HANDLE/*控制台输入设备*/);
                SetConsoleMode/*修改控制台输入模式*/(hIn,ENABLE_MOUSE_INPUT/*开启控制台鼠标*/ | ENABLE_EXTENDED_FLAGS);
                INPUT_RECORD ir;//存放控制台里所有输入事件
                DWORD nRead;//记录成功读取多少条输入事件
                MoveResult move;
            while(game->status==GAME_RUNNING)
            {
                int mouseX,mouseY,bx,by;//鼠标在控制台原始坐标和棋盘数组下标
                ReadConsoleInput(hIn,&ir,1,&nRead);//读取控制台输入事件，1次只读一次事件
                if(ir.EventType==MOUSE_EVENT)
                {
                if(ir.Event.MouseEvent.dwButtonState/*记录鼠标状态*/==FROM_LEFT_1ST_BUTTON_PRESSED)//只有左键按下才执行
            {
                COORD mousePos=ir.Event.MouseEvent.dwMousePosition;//从鼠标事件结构体里面取出鼠标点击屏幕的坐标，保存到mousepos
                int mouseX=mousePos.X;//取出横向坐标
                int mouseY=mousePos.Y;//取出纵向坐标
                int bx=(mouseX-1)/4;//棋盘坐标换算
                int by=(mouseY-1)/2;
                if(bx>9||by>9||bx<0||by<0)//超出棋盘范围
                {
                    printf("moveout,printf a to continue\n");
                    getchar();
                    move= MOVE_OUT_OF_BOUNDS;
                    drawBoard(game);
                }
                else
                   {
                if(game->cells[by][bx]==EMPTY_CELL)
                {
                    move=MOVE_ACCEPTED;
                    game->cells[by][bx]=game->current_player;
                    game->move_count=game->move_count+1;
                    if(game->current_player=='X')
                    {
                        game->current_player='O';
                    }
                    else
                    {
                            game->current_player='X';
                    }
                    drawBoard(game);  
                }
                else//重复落子
                {
                    move=MOVE_OCCUPIED;
                    drawBoard(game);   
                }
                  }
                        
            checkwin(game);
            drawBoard(game);
            printf("\ntotal step:%d\n",game->move_count);
            if(game->status==GAME_X_WINS)
            {
                printf("X win");
            }
            if(game->status==GAME_O_WINS)
            {
                printf("O win");
            }
            if(game->status==GAME_DRAW)
            {
                printf("game draw");
            }
            }
        }
} 
}
void restoreConsole(void) 
{
    HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
    // 写回原模式
}
int wait(void)
{
    char answer;
    printf("\ntry again?answer Y/N\n");
    scanf("%c",&answer);
    if(answer=='Y')
    {
      return 1;
    }
    else
    {
        return 0;
    }
}