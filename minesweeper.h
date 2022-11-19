void gameMenu();
void selectDifficulty();
void printBoard();
void initBoard();
void unveilEmpty(int y, int x);
void unveilSpace(int x, int y);
void selectXY();
void play();
void goodbye();

#define MINESWEEPER_HEADER_IN_USE true
#define BOARD_SIZE 	10
#define FLOWER 		9
#define BOMB 		254

int difficulty = 3;
int nBombs;
char realBoard[BOARD_SIZE][BOARD_SIZE];
int valueBoard[BOARD_SIZE][BOARD_SIZE];
bool alive = true;

void unveilEmpty(int x, int y){
    realBoard[y][x] = ' ';


    if((y!=0) && (realBoard[y-1][x]=='#')){
        if(valueBoard[y-1][x]==0){ unveilEmpty(x, y-1); }
        else if(valueBoard[y-1][x]!=FLOWER){ realBoard[y-1][x] = valueBoard[y-1][x]+48; }
    }

    if((x!=0) && (realBoard[y][x-1]=='#')){
        if(valueBoard[y][x-1] == 0){ unveilEmpty(x-1, y); }
        else if(valueBoard[y][x-1]!=FLOWER){ realBoard[y][x-1] = valueBoard[y][x-1]+48; }
    }

    if((x!=(BOARD_SIZE-1)) && (realBoard[y][x+1]=='#')){
        if(valueBoard[y][x+1]==0){ unveilEmpty(x+1, y); }
        else if(valueBoard[y][x+1]!=FLOWER){ realBoard[y][x+1] = valueBoard[y][x+1]+48; }
    }

    if((y!=(BOARD_SIZE-1)) && (realBoard[y+1][x]=='#')){
        if(valueBoard[y+1][x]==0){ unveilEmpty(x, y+1); }
        else if(valueBoard[y+1][x]!=FLOWER){ realBoard[y+1][x] = valueBoard[y+1][x]+48; }
    }

    return;
}

void unveilSpace(int x, int y){
    switch(valueBoard[y][x]){
        case 0:
            unveilEmpty(x, y);
            break;
        case FLOWER:
            realBoard[y][x] = BOMB;
            printBoard();
            printf("\tYou choose a Bomb! You lose!");
            alive = false;
            break;
        default:
            realBoard[y][x] = valueBoard[y][x]+48;
            break;
    }

    return;
}

void gameMenu(){
    int selection = 0;

    do{
        system("cls");
        printf("\tWelcome to...\n\n");

        printf("\t __  __   _                     _____                                                \n");
        printf("\t|  \\/  | (_)                   / ____|                                               \n");
        printf("\t| \\  / |  _   _ __     ___    | (___   __      __   ___    ___   _ __     ___   _ __ \n");
        printf("\t| |\\/| | | | | '_ \\   / _ \\    \\___ \\  \\ \\ /\\ / /  / _ \\  / _ \\ | '_ \\   / _ \\ | '__|\n");
        printf("\t| |  | | | | | | | | |  __/    ____) |  \\ V  V /  |  __/ |  __/ | |_) | |  __/ | |   \n");
        printf("\t|_|  |_| |_| |_| |_|  \\___|   |_____/    \\_/\\_/    \\___|  \\___| | .__/   \\___| |_|   \n");
        printf("\t                                                                | |                  \n");
        printf("\t                                                                |_|                  \n\n");

        printf("\tSelect an Option: \n");
        printf("\t   1. Play\n");                                           //ASCII: 49
        printf("\t   2. Select Difficulty (Current: %d)\n", difficulty);    //ASCII: 50
        printf("\t   3. Exit\n");                                           //ASCII: 51
        selection = getch();
    }while(selection < 49 || selection > 51);

    switch(selection){
        case 49:
            play();
            break;
        case 50:
            selectDifficulty();
            break;
        case 51:
            goodbye();
        default:
            gameMenu();
            break;
    }

    return;
}

void selectDifficulty(){
    do{
        system("cls");
        printf("\n\tSelect a Difficulty (between 1 to 5): ");
        scanf("%d", &difficulty);
    }while(difficulty<1 || difficulty>5);

    printf("\n\t\t1     2     3     4     5\n\t\t");
    for(int i=1; i<difficulty; i++){ printf("      "); }
    printf("^");

    Sleep(1500);
    gameMenu();

    return;
}

void printBoard(){
    system("cls");

    printf("\t");

    for(int i=0; i<BOARD_SIZE; i++){ printf("  %d  ", i); }

    for(int y=0; y<BOARD_SIZE; y++){
        printf("\n\n    %d   ", y);
        for(int x=0; x<BOARD_SIZE; x++){
            printf("[ %c ]", realBoard[y][x]);
        }
    }

    printf("\n\n");

    return;
}

void initBoard(){
    srand(time(NULL));

    system("cls");

    alive = true;

    for(int y=0; y<BOARD_SIZE; y++){
        for(int x=0; x<BOARD_SIZE; x++){
            realBoard[y][x] = '#';
            valueBoard[y][x] = 0;
        }
    }

    switch(difficulty){
        case 1:
            nBombs = (int) ceil((float) ((BOARD_SIZE*BOARD_SIZE*7)/100));
            break;
        case 2:
            nBombs = (int) ceil((float) ((BOARD_SIZE*BOARD_SIZE*10)/100));
            break;
        case 3:
            nBombs = (int) ceil((float) ((BOARD_SIZE*BOARD_SIZE*12)/100));
            break;
        case 4:
            nBombs = (int) ceil((float) ((BOARD_SIZE*BOARD_SIZE*15)/100));
            break;
        case 5:
            nBombs = (int) ceil((float) ((BOARD_SIZE*BOARD_SIZE*20)/100));
            break;
    }

    int check = 0;

    while(check < nBombs){
        int rx = rand() % BOARD_SIZE;
        int ry = rand() % BOARD_SIZE;

        if(valueBoard[ry][rx] != FLOWER){
            valueBoard[ry][rx] = FLOWER;
            check++;

            if(ry!=0){
                if((rx!=0) && (valueBoard[ry-1][rx-1] != FLOWER)){ valueBoard[ry-1][rx-1]++; }
                if(valueBoard[ry-1][rx] != FLOWER){ valueBoard[ry-1][rx]++; }
                if((rx!=(BOARD_SIZE-1)) && (valueBoard[ry-1][rx+1] != FLOWER)){ valueBoard[ry-1][rx+1]++; }
            }

            if((rx!=0) && (valueBoard[ry][rx-1] != FLOWER)){ valueBoard[ry][rx-1]++; }

            if((rx!=(BOARD_SIZE - 1)) && (valueBoard[ry][rx+1] != FLOWER)){ valueBoard[ry][rx+1]++; }

            if(ry!=(BOARD_SIZE - 1)){
                if((rx!=0) && (valueBoard[ry+1][rx-1] != FLOWER)){ valueBoard[ry+1][rx-1]++; }
                if(valueBoard[ry+1][rx] != FLOWER){ valueBoard[ry+1][rx]++; }
                if((rx!=(BOARD_SIZE-1)) && (valueBoard[ry+1][rx+1] != FLOWER)){ valueBoard[ry+1][rx+1]++; }
            }
        }
    }

    return;
}

void selectXY(){
    int x = 0, y = 0;

    do{
        system("cls");
        printBoard();
        printf("\tSelect X: ");
        fflush(stdin);
        scanf("%d", &x);
    }while(x<0 || x>=BOARD_SIZE);

    do{
        system("cls");
        printBoard();
        printf("\tSelect X: %d\n", x);
        printf("\tSelect Y: ");
        fflush(stdin);
        scanf("%d", &y);
    }while(y<0 || y>=BOARD_SIZE);

    unveilSpace(x, y);

    return;
}

void play(){
    initBoard();

    while(alive){
        printBoard();
        selectXY();
        Sleep(100);
    }

    getch();
    gameMenu();

    return;
}

void goodbye(){
    system("cls");

    printf("\t _______   _                       _               __                    _____    _                   _                   _ \n");
    printf("\t|__   __| | |                     | |             / _|                  |  __ \\  | |                 (_)                 | |\n");
    printf("\t   | |    | |__     __ _   _ __   | | __  ___    | |_    ___    _ __    | |__) | | |   __ _   _   _   _   _ __     __ _  | |\n");
    printf("\t   | |    | '_ \\   / _` | | '_ \\  | |/ / / __|   |  _|  / _ \\  | '__|   |  ___/  | |  / _` | | | | | | | | '_ \\   / _` | | |\n");
    printf("\t   | |    | | | | | (_| | | | | | |   <  \\__ \\   | |   | (_) | | |      | |      | | | (_| | | |_| | | | | | | | | (_| | |_|\n");
    printf("\t   |_|    |_| |_|  \\__,_| |_| |_| |_|\\_\\ |___/   |_|    \\___/  |_|      |_|      |_|  \\__,_|  \\__, | |_| |_| |_|  \\__, | (_)\n");
    printf("\t                                                                                               __/ |               __/ |    \n");
    printf("\t                                                                                              |___/               |___/     \n");

    exit(0);
}
