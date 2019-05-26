#include <iostream>
#include <unistd.h>
#include <conio.h>
#include <thread>
#include <cstdlib>

using namespace std;

const int rowScreen = 20;
const int colScreen = 30;

//const int rowSnake = rowScreen;
//const int colSnake = colScreen;

const int rowSnake = (rowScreen-2)*(colScreen-2);
const int colSnake = 2;
int keyPress, keyPressHist;
bool gameOver = false;
int lengthSnake = 3;
unsigned int microseconds = 60000;
bool noFood = true;

bool printSnake(int i, int j, int** snake){
    for (int k = 0; k < rowSnake; k++) {
        if((i == snake[k][0]) && (j == snake[k][1])){
            return true;
        }
    }
    return false;
}

// method 2
void printScreen(char** screen, int** snake, int** food){


    for(int i = 0; i < rowScreen; i++){
        for(int j = 0; j < colScreen; j++){
            if(screen[i][j] == '*'){
                cout << screen[i][j];
            } else if(printSnake(i, j, snake)) {
                cout << '*';
            } else if((food[0][0]==i)&&(food[0][1]==j)) {
                cout << '*';
            } else {
                cout << ' ';
            }
        }
        cout << endl;
    }
}

// Ekranı ve sınırları olustur
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



// Yılan olustur
int** getSnake(int lengthSnake){

    int** snake = new int*[rowSnake];
    for (int i = 0; i < rowSnake; i++) {
        snake[i] = new int[colSnake];
    }

    int tmpX = 10;
    int tmpY = 15;
    for(int i = 0; i < lengthSnake; i++){
        snake[i][0] = tmpX;
        snake[i][1] = tmpY;
        tmpY = tmpY - 1;
    }

    return snake;
}


void updateSnake(int** snake, char direction, int** food){
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
    //return snake;
}


int** getFood(){
    int** food = new int*[1];
    food[0] = new int[2];
    return food;
}

void updateFood(int** snake, int** food){
    int foodLocationXTmp = food[0][0];
    int foodLocationYTmp = food[0][1];

    while(noFood){
        foodLocationXTmp = rand() % (rowScreen-2);
        foodLocationYTmp = rand() % (colScreen-2);
        noFood = false;

        for(int i = 0; i < rowSnake; i++){
            if((foodLocationXTmp == snake[i][0])&&(foodLocationYTmp == snake[i][1])){
                noFood = true;
            }
        }
    }
    food[0][0] = foodLocationXTmp;
    food[0][1] = foodLocationYTmp;
   }


bool isGameOver(char** screen, int** snake){
    // Duvara Carpma Durumu
    if(screen[snake[0][0]][snake[0][1]] == '*'){
        gameOver = true;
    }
    // Kuyruguna Carpma Durumu
    for(int i = 1; i < rowSnake; i++){
        if((snake[0][0] == snake[i][0]) && (snake[0][1] == snake[i][1])){
            gameOver = true;
        }
    }
    return gameOver;
}

void growSnake(int** snake, int** food){
    if((snake[0][0]==food[0][0])&&(snake[0][1]==food[0][1])){
        snake[lengthSnake][0] = food[0][0];
        snake[lengthSnake][1] = food[0][1];
        lengthSnake = lengthSnake + 1;
        noFood = true;
    }
}

int moveSnake(char** screen, int** snake, int** food) {

    while(true)
    {
        if((keyPress == 72) && (keyPressHist != 80)){
            updateSnake(snake,'u',food);
            keyPressHist = keyPress;
        } else if((keyPress == 80) && (keyPressHist == 72)){
            updateSnake(snake,'u',food);
        } else if((keyPress == 72) && (keyPressHist == 80)){
            updateSnake(snake,'d',food);
        } else if((keyPress == 80) && (keyPressHist != 72)){
            updateSnake(snake,'d',food);
            keyPressHist = keyPress;
        } else if((keyPress == 77) && (keyPressHist != 75)){
            updateSnake(snake,'r',food);
            keyPressHist = keyPress;
        } else if((keyPress == 77) && (keyPressHist == 75)){
            updateSnake(snake,'l',food);
        } else if((keyPress == 75) && (keyPressHist == 77)){
            updateSnake(snake,'r',food);
        } else if((keyPress == 75) && (keyPressHist != 77)){
            updateSnake(snake,'l',food);
            keyPressHist = keyPress;

        }
        system("CLS");
        if(isGameOver(screen, snake)){
            break;
        }
        growSnake(snake, food);
        updateFood(snake, food);
        printScreen(screen, snake, food);
        usleep(microseconds);
        }
    cout << "Game Over" << endl;
    return 1;
}

[[noreturn]] void thread_handler() {
    while(true)
    {
        if(gameOver){
            break;
        }
        keyPress = getch();
    }
}

int main() {
    char **screen;
    int **snake;
    int **food;
    screen = getScreen();
    snake = getSnake(lengthSnake);
    food = getFood();
    //thread t(thread_handler, screen, snake);
    thread t(thread_handler);
    moveSnake(screen, snake, food);
    t.join();
}

