#include <time.h>
#include <iostream>

void printBoard(int board[9][9]){
    for(int i = 0; i < 9; i++){
        if((i)%3 == 0 && i != 0){
            std::cout<<"---------------"<<std::endl;
        }
        std::cout<<std::endl;
        for(int j = 0; j < 9; j++){
            if(j%3 == 0 && j != 0){
                std::cout<<" | ";
            }
            std::cout<<board[i][j];
        }
    }
    std::cout<<std::endl;
    std::cout<<std::endl;
}

struct coord{
    int x;
    int y;
};

coord findEmpty(int board[9][9]){
    coord out = {-1, -1};
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            if(board[i][j] == 0){
                out.x = i;
                out.y = j;
                return out;
            }
        }
    }
    return out;
}

bool valid(int board[9][9], coord curr, int num){
    //Check row
    for(int i = 0; i < 9; i++){
        if(board[i][curr.y] == num){
            return false;
        }
    }
    //Check column
    for(int i = 0; i < 9; i++){
        if(board[curr.x][i] == num){
            return false;
        }
    }

    int boxX = curr.x/3;
    int boxY = curr.y/3;

    for(int i = boxX*3; i < (boxX*3)+3; i++){
        for(int j = boxY*3; j < (boxY*3)+3; j++){
            if(board[i][j] == num){
                return false;
            }
        }
    }

    return true;
}

bool solve(int board[9][9]){
    coord curr = findEmpty(board);
    if(curr.x == -1){
        return true;
    }else{
        for(int i = 1; i < 10; i++){
            if(valid(board, curr, i)){
                board[curr.x][curr.y] = i;

                if(solve(board)){
                    return true;
                }

                board[curr.x][curr.y] = 0;
            }
        }
    }
    return false;
}

int main(){
    clock_t start, end;
    double cpu_time_used;

    int counter = 0;

    start = clock();
    while(cpu_time_used < 5){
        int board[9][9] = {
                            {0,9,0,0,8,6,0,0,0},
                            {3,0,0,0,0,0,0,0,7},
                            {5,6,0,0,2,0,0,0,3},
                            {0,0,0,0,3,0,0,0,0},
                            {0,1,0,4,0,7,0,0,0},
                            {7,0,4,0,0,0,0,0,2},
                            {0,0,0,1,0,0,0,4,0},
                            {0,0,0,0,0,0,8,9,0},
                            {8,0,0,0,0,0,0,2,0}
                        };

        solve(board);
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        counter++;
    }
    std::cout<<cpu_time_used<<" s"<<std::endl;
    std::cout<<"This ran: "<<counter<<" times"<<std::endl;
    return 0;
}