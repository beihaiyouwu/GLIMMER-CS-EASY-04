#include<windows.h>
typedef struct {
    HANDLE hIn;
    HANDLE hout;
    DWORD  inputMode;
    DWORD  outputMode;
    int    width;
    int    height;
} Console;
void initconsole(Console*m);