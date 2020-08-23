#include <iostream>
#include <stdlib.h>
#include <ctime>


int main() {
    srand(time(0));
    const int width = 25;
    const int height = 12;

    int userX = rand()%width+1;
    int userY = rand()%height+1;

    int traps[3][2] = { { 4, 6}, 
                        {10, 3}, 
                        {20, 9}};
                        
    int treasure[2] = {23, 10};


    while (true) {
        int user[2] = {rand()%width+1, rand()%height+1};
        bool diff = false;

        if (user[0] != treasure[0] && user[1] != treasure[1])
            diff = true;
        for(int i = 0; i < sizeof(traps)/sizeof(traps[0]); i++) {
            if (user[0] != traps[i][0] && user[1] != traps[i][1])
                diff = true;
        }
        if (diff)
            break;
    }

    char input = ' ';
    while (true) {
        // Display board
        system("cls");
        for (int y = height; y > 0; y--) {
            for (int x = 0; x < width; x++) {
                bool empty = true;

                // Plot User
                if (x == userX && y == userY) {
                    empty = false;
                    std::cout << "@";
                }

                // Plot Traps    
                for (int i = 0; i < 3; i++) {
                    if (x == traps[i][0] && y == traps[i][1]) {
                        empty = false;
                        std::cout << "T";
                        break;
                    } 
                }

                // Plot Treasure
                if (x == treasure[0] && y == treasure[1]) {
                    empty = false;
                    std::cout << "X";
                }

                // Plot Empty Space
                if (empty)
                    std::cout << ".";
            }
            std::cout << std::endl;
        } // end Display

        // Move Character
        bool invalid = true;
        while (invalid) {
            std::cin >> input;
            invalid = false;
            switch (input) {
                case 'w':
                    userY++;
                    break;
                case 'a':
                    userX--;
                    break;
                case 's':
                    userY--;
                    break;
                case 'd':
                    userX++;
                    break;
                case 'q':
                    return(0);
                default:
                    invalid = true;
                    std::cout << "Invalid" << std::endl;
            }

            
            if (userX > width-1)
                userX = width-1;
            if (userX < 0)
                userX = 0;
            if (userY > height)
                userY = height;
            if (userY < 1) 
                userY = 1;
        
        } // end Move Character
        
        // Move Traps
        for (int i = 0; i < sizeof(traps)/sizeof(traps[0]); i++) {
            int movement = rand()%4;
            if (movement == 0 && traps[i][0] < width-1 && !(treasure[0]-traps[i][0] == 1 && treasure[1] == traps[i][1]))
                traps[i][0]++;
            else if (movement == 1 && traps[i][1] < height && !(treasure[1]-traps[i][1] == 1 && treasure[0] == traps[i][0]))
                traps[i][1]++;
            else if (movement == 2 && traps[i][0] > 0 && !(treasure[0]-traps[i][0] == -1 && treasure[1] == traps[i][1]))
                traps[i][0]--;
            else if (movement == 3 && traps[i][1] > 1 && !(treasure[1]-traps[i][1] == -1 && treasure[0] == traps[i][0]))
                traps[i][1]--;            
        }


        
        // Check Lose
        bool gameOver = false;
        for (int i = 0; i < sizeof(traps)/sizeof(traps[0]); i++) {
            if (userX == traps[i][0] && userY == traps[i][1]) {
                gameOver = true;
            }
        }
        
        if (gameOver) {
            std::cout << "You fell in a trap" << std::endl;
            std::cout << "Game Over" << std::endl;
            return(0);
        }
        
        // Check Win
        if (userX == treasure[0] && userY == treasure[1]) {
            std::cout << "You found the treasure!" << std::endl;
            std::cout << "You Win!" << std::endl;
            return(0);
        }
        

    } // end while    
} // end main
