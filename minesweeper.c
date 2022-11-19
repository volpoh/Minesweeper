#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>
#include "minesweeper.h"

#ifndef MINESWEEPER_HEADER_IN_USE
    #include "minesweeper.h"
#endif

#if BOARD_SIZE < 5
#undef BOARD_SIZE
    #define BOARD_SIZE 5
#endif

#if BOARD_SIZE > 15
#undef BOARD_SIZE
    #define BOARD_SIZE 15
#endif


int main(void){
	gameMenu();
	
    return 0;
}
