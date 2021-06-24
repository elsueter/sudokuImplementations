//#define CROW_ENABLE_SSL
#define CROW_MAIN

#include <crow.h>
#include <iostream>
#include <string>

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

std::string stringify(int board[9][9]){
    std::string out = "[";
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            out += std::to_string(board[i][j]);
            out+=",";
        }
    }
    out = out.substr(0, out.length()-1);
    out += "]";
    return out;
}

int main(){

    //Crow app and routing lambda functions (Web Server)
    crow::SimpleApp app;
    
    //Base request and main page fetch
    crow::mustache::set_base(".");
    CROW_ROUTE(app,"/")
    ([]{
        crow::mustache::context ctx;
        auto page = crow::mustache::load("index.html");
        
        return page.render();
    });

    CROW_ROUTE(app, "/fetch")
    .methods("POST"_method)
    ([](const crow::request& req){
        auto x = crow::json::load(req.body);
        if (!x)
            return crow::response(400);
        int board[9][9];
        for(int i = 0; i < 9; i++){
            for(int j = 0; j < 9; j++){
                board[i][j] = x[(i*9)+(j%9)].i();
            }
        }
        solve(board);
        crow::json::wvalue y;
        y["solved"] = stringify(board);
        return crow::response(y);
    });

    app.port(18082).multithreaded().run();

    return 0;
}
