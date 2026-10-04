//游戏终止函数
#include"game.h"
void checkwin(Game* g)//判定游戏输赢函数
{
    int i,j;
    for(i=0;i<BOARD_SIZE;i++)
    {
        for(j=0;j<BOARD_SIZE;j++)
        {
           char player=g->cells[i][j];
            if(player==EMPTY_CELL)
            {
                continue;
            }
            if(j+4<BOARD_SIZE&&player==g->cells[i][j+1]&&player==g->cells[i][j+2]&&player==g->cells[i][j+3]&&player==g->cells[i][j+4])
            {
                if(player=='X')
                {
                g->status= GAME_X_WINS;
                }
                else
                {
                g->status= GAME_O_WINS;
                }
           }
           if(i+4<BOARD_SIZE&&player==g->cells[i+1][j]&&player==g->cells[i+2][j]&&player==g->cells[i+3][j]&&player==g->cells[i+4][j])
           {
                if(player=='X')
                {
                g->status= GAME_X_WINS;
                }
                else
                {
                g->status= GAME_O_WINS;
                }
           }
           if(i+4<BOARD_SIZE&&j+4<BOARD_SIZE&&player==g->cells[i+1][j+1]&&player==g->cells[i+2][j+2]&&player==g->cells[i+3][j+3]&&player==g->cells[i+4][j+4])
           {
                if(player=='X')
                {
                g->status= GAME_X_WINS;
                }
                else{
                g->status= GAME_O_WINS;
                }
           }
           if(i-4>=0&&j+4<BOARD_SIZE&&player==g->cells[i-1][j+1]&&player==g->cells[i-2][j+2]&&player==g->cells[i-3][j+3]&&player==g->cells[i-4][j+4])
           {
            if(player=='X')
                {
                g->status= GAME_X_WINS;
                }
                else
                {
                g->status= GAME_O_WINS;
                }
           }
        }
        if(g->move_count==BOARD_SIZE*BOARD_SIZE)
        {
            g->status=GAME_DRAW;
        }
       
    }   
      
}
