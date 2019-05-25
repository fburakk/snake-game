#include <iostream>
#include <unistd.h>
#include <conio.h>
#include <thread>

using namespace std;

const int rowScreen = 20;
const int colScreen = 30;

//const int rowSnake = rowScreen;
//const int colSnake = colScreen;

const int rowSnake = (rowScreen-2)*(colScreen-2);
const int colSnake = 2;
//const int lengthSnake = 2;
int keyPress;
bool gameOver = false;


/*
// method1
void printScreen(char** screen, char** snake){
    //int rows =  sizeof myword / sizeof myword[0]; // 2 rows
    //int cols = sizeof myword[0] / sizeof(int); // 5 cols

    for(int i = 0; i < rowScreen; i++){
        for(int j = 0 ; j < colScreen; j++){
            if(screen[i][j] == '*'){
                cout << screen[i][j];
            } else if(snake[i][j] == '?' ){
                cout << snake[i][j];
            } else {
                cout << ' ';
            }
        }
        cout << endl;
    }

    //system ("CLS");
    //cout << flush;
}*/

bool printSnake(int i, int j, int** snake){
    for (int k = 0; k < rowSnake; k++) {
        if((i == snake[k][0]) && (j == snake[k][1])){
            return true;
        }
    }
    return false;
}

// method 2
void printScreen(char** screen, int** snake){
    //int rows =  sizeof myword / sizeof myword[0]; // 2 rows
    //int cols = sizeof myword[0] / sizeof(int); // 5 cols

    for(int i = 0; i < rowScreen; i++){
        for(int j = 0 ; j < colScreen; j++){
            if(screen[i][j] == '*'){
                cout << screen[i][j];
            } else if(printSnake(i, j, snake)) {
                cout << '*';
            } else {
                cout << ' ';
            }
        }
        cout << endl;
    }
}





char** getScreen(){
    char** screen = new char*[rowScreen];
    for (int i = 0; i < rowScreen; i++) {
        screen[i] = new char[colScreen];
        for (int j = 0; j < colScreen; j++) {
            if((i==0)||(j==0)||(i==rowScreen-1)||(j=colScreen-1)){
                screen[i][j] = '*';
            }
        }
    }
    return screen;
}

/*
char** getSnake(){
    char** snake = new char*[rowSnake];
    for (int i = 0; i < rowSnake; i++) {
        snake[i] = new char[colSnake];
        for (int j = 0; j < colSnake; j++) {
            if(((i==10)&&(j==15))||((i==10)&&(j==16))||((i==10)&&(j==17))){
                snake[i][j] = '?';
            }
        }
    }
    return snake;
}
*/


int** getSnake(){
    int** snake = new int*[rowSnake];
    for (int i = 0; i < rowSnake; i++) {
        snake[i] = new int[colSnake];
    }
    snake[0][0] = 10;
    snake[0][1] = 15;

    snake[1][0] = 10;
    snake[1][1] = 14;

    snake[2][0] = 10;
    snake[2][1] = 13;

    return snake;
}


int** updateSnake(int** snake, char direction){
    int tmpX1 = 0, tmpY1 = 0, tmpX2 = 0, tmpY2 = 0;
    for (int i = 0; i < rowSnake; i++) {
            if(i == 0){
                tmpX1 = snake[i][0];
                tmpY1 = snake[i][1];
                tmpX2 = tmpX1;
                tmpY2 = tmpY1;
                if (direction == 'l') {
                    snake[i][1] = snake[i][1] - 1;
                } else if (direction == 'r') {
                    snake[i][1] = snake[i][1] + 1;
                } else if (direction == 'u') {
                    snake[i][0] = snake[i][0] - 1;
                } else if (direction == 'd') {
                    snake[i][0] = snake[i][0] + 1;
                }

            } else if ((snake[i][0]>0)&&(snake[i][1]>0)) {
                tmpX1 = snake[i][0];
                tmpY1 = snake[i][1];
                snake[i][0] = tmpX2;
                snake[i][1] = tmpY2;
                tmpX2 = tmpX1;
                tmpY2 = tmpY1;
            }
    }
    return snake;
}

/*
void updateScreen(char** screen, int** snake){
    while (true) {
        system("CLS");
        printScreen(screen, snake);
    }
}
*/


void moveSnake(char** screen, int** snake) {

    while(true)
    {

    switch(keyPress)
        {
        case 72:
        {
            //UP
            updateSnake(snake,'u');
            //printScreen(screen, snake);
            break;
        }
        case 80:
        {
            // DOWN
            updateSnake(snake,'d');
            //printScreen(screen, snake);
            break;
        }
        case 77:
        {
            // RIGHT
            updateSnake(snake,'r');
            //printScreen(screen, snake);
            break;
        }
        case 75:
        {
            // LEFT
            updateSnake(snake,'l');
            //printScreen(screen, snake);
            break;
        }
    }
    printScreen(screen, snake);
    sleep(1);
    system("CLS");
    }
}

void thread_handler() {
    while(true)
    {
        keyPress = getch();
    }
}

int main() {
    char **screen;
    int **snake;
    screen = getScreen();
    snake = getSnake();
    //thread t(thread_handler, screen, snake);
    thread t(thread_handler);
    moveSnake(screen, snake);
    t.join();
}

