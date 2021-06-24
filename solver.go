package main

import (
	"fmt"
	"time"
)

func printBoard(board [9][9]int){
	var i, j int;
    for i = 0; i < 9; i++{
        if((i)%3 == 0 && i != 0){
            fmt.Println();
            fmt.Println("---------------");
        }else{
            fmt.Println();
        }
        for j = 0; j < 9; j++{
            if(j%3 == 0 && j != 0){
                fmt.Print(" | ");
            }
            fmt.Print(board[i][j]);
        }
    }
	fmt.Println();
	fmt.Println();
}

type coord struct{
    x int;
    y int;
};

func findEmpty(board [9][9]int) (out coord){
    out = coord{-1, -1};
	var i, j int;
    for i = 0; i < 9; i++{
        for j = 0; j < 9; j++{
            if(board[i][j] == 0){
                out.x = i;
                out.y = j;
                return;
            }
        }
    }
    return;
}

func valid(board [9][9]int, curr coord, num int) (bool){
	var i, j int;
    //Check row
    for i = 0; i < 9; i++{
        if(board[i][curr.y] == num){
            return false;
        }
    }
    //Check column
    for i = 0; i < 9; i++{
        if(board[curr.x][i] == num){
            return false;
        }
    }

    var boxX = curr.x/3;
    var boxY = curr.y/3;

    for i = boxX*3; i < (boxX*3)+3; i++{
        for j = boxY*3; j < (boxY*3)+3; j++{
            if(board[i][j] == num){
                return false;
            }
        }
    }

    return true;
}

func solve(board *[9][9]int) (bool){
	var i int;
    var curr = findEmpty(*board);
    if(curr.x == -1){
        return true;
    }else{
        for i = 1; i < 10; i++{
            if(valid(*board, curr, i)){
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

func main(){

	start := time.Now();
	t := time.Now();
	counter := 0;

	for(t.Sub(start) < 5*time.Second){
		board := [9][9]int{
						{0,9,0,0,8,6,0,0,0},
						{3,0,0,0,0,0,0,0,7},
						{5,6,0,0,2,0,0,0,3},
						{0,0,0,0,3,0,0,0,0},
						{0,1,0,4,0,7,0,0,0},
						{7,0,4,0,0,0,0,0,2},
						{0,0,0,1,0,0,0,4,0},
						{0,0,0,0,0,0,8,9,0},
						{8,0,0,0,0,0,0,2,0},
					};
	
		solve(&board);
		t = time.Now()
		counter++;
	}
	elapsed := t.Sub(start)

	fmt.Println(elapsed);
	fmt.Println("This ran: ", counter, " times");
}