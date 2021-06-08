#include <iostream>
#include <vector>
#include <stdlib.h>
using namespace std;

class Move{
public:
    int x;
    int y;
    int count;
    Move()
    {   
        x = 0;
        y = 0;
        count = 0;
    }
    Move(int a, int b, int c){
        x = a;
        y = b; 
        count = c;
    }
};

class Othello{
private:
    vector<vector<int> > gameboard;
    int playerTurn; // player turns
    int whiteScore;
    int blackScore;
    int size;
public:
    Othello(){
        size = 8;
        //vector<vector<int> > gameboard(8, vector<int> (8, 0)); // 2d board
        for(int i = 0; i < size; i++){
            vector<int> temp;
            for(int j = 0; j < size; j++){
                temp.push_back(0);
            }
            gameboard.push_back(temp);
        }
        whiteScore = 0;
        blackScore = 0;
        playerTurn = 1;   // black player always starts first (BLACK: 1 WHITE: 2)
        gameboard[3][4] = 2;
        gameboard[4][3] = 2;
        gameboard[3][3] = 1;
        gameboard[4][4] = 1;
    }
    
    bool checkBounds(int i){
        if(i >= 0 && i < 8){
            return true;
        } return false;
    }
    
    void printBoard(){
        cout << "Board:\n   ";
        for(int i = 0; i < size; i++){
            cout << i << " ";
        }
        cout << endl;
        for(int i = 0; i < size; i++){
            cout << i << "  ";
            for(int j = 0; j < size; j++){
                if(gameboard[i][j] == 1){
                    cout << "P ";
                } else if (gameboard[i][j] == 2){
                    cout << "C ";
                } else{
                    cout << "  ";
                }
            }
            cout << endl;
        }
        cout << endl;
    }
    
    void printBoard(vector<vector<int>> &b){
        cout << "Backup:\n   ";
        for(int i = 0; i < size; i++){
            cout << i << " ";
        }
        cout << endl;
        for(int i = 0; i < size; i++){
            cout << i << "  ";
            for(int j = 0; j < size; j++){
                cout << b[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
    
    void EndGame(){
        blackScore = 0;
        whiteScore = 0;
        for(int i = 0; i < size; i++){
            for(int j = 0; j < size; j++){
                if(gameboard[i][j] == 1){
                    blackScore++;
                } else if (gameboard[i][j] == 2){
                    whiteScore++;
                }
            }
        }
        cout << "GAME OVER! \nScores:\n";
        cout << "White Scored: " << whiteScore << endl;
        cout << "Black Scored: " << blackScore << endl;
        if(whiteScore < blackScore){
            cout << "You're the G.O.A.T\n";
        } else if (whiteScore > blackScore) {
            cout << "Get Destroyed by a BOT\n";
        } else{
            cout << "GGs\n";
        }
    }
    int score(vector<vector<int>> &board){
        blackScore = 0;
        whiteScore = 0;
        for(int i = 0; i < size; i++){
            for(int j = 0; j < size; j++){
                if(board[i][j] == 1){
                    blackScore++;
                } else if (board[i][j] == 2){
                    whiteScore++;
                }
            }
        }
        return whiteScore - blackScore;
    }
    
    int elem(int i, int j, vector<vector<int>> &board){ // returns element of board if within bounds
        if(checkBounds(i) && checkBounds(j)){
            return board[i][j];
        }
        return -1;
    }
    
    void convertUpRight(int i, int j, int count, vector<vector<int>> &board, int turn){
        i--; j++;
        while(checkBounds(i) && checkBounds(j) && count > 0){
            board[i--][j++] = turn;
            count--;
        }
    }
    
    int countUpRight(int i, int j, vector<vector<int>> &board, int turn){
        int not_turn = (turn % 2) + 1;
        int count = 0;
        int newi = i - 1, newj = j + 1;
        while(newi > 0 && newj < (size - 1) && elem(newi,newj,board) == not_turn){
            newi--; newj++;
            count++;
        }
        if(elem(newi,newj,board) == turn && count > 0){
            return count;
        } else{
            return 0;
        }
    }
    
    void convertUpLeft(int i, int j, int count, vector<vector<int>> &board, int turn){
        i--; j--;
        while(checkBounds(i) && checkBounds(j) && count > 0){
            board[i--][j--] = turn;
            count--;
        }
    }
    
    int countUpLeft(int i, int j, vector<vector<int>> &board, int turn){
        int not_turn = (turn % 2) + 1;
        int count = 0;
        int newi = i - 1, newj = j - 1;
        while(newi > 0 && newj > 0 && elem(newi,newj,board) == not_turn){
            newi--; newj--;
            count++;
        }
        if(elem(newi,newj,board) == turn && count > 0){
            return count;
        } else{
            return 0;
        }
    }
    
    void convertDownRight(int i, int j, int count, vector<vector<int>> &board, int turn){
        i++; j++;
        while(checkBounds(i) && checkBounds(j) && count > 0){
            board[i++][j++] = turn;
            count--;
        }
    }
    
    int countDownRight(int i, int j, vector<vector<int>> &board, int turn){
        int not_turn = (turn % 2) + 1;
        int count = 0;
        int newi = i + 1, newj = j + 1;
        while(newi < (size - 1) && newj < (size - 1) && elem(newi,newj,board) == not_turn){
            newi++; newj++;
            count++;
        }
        if(elem(newi,newj,board) == turn && count > 0){
            return count;
        } else{
            return 0;
        }
    }
    
    void convertDownLeft(int i, int j, int count, vector<vector<int>> &board, int turn){
        i++; j--;
        while(checkBounds(i) && checkBounds(j) && count > 0){
            board[i++][j--] = turn;
            count--;
        }
    }
    
    int countDownLeft(int i, int j, vector<vector<int>> &board, int turn){
        int not_turn = (turn % 2) + 1;
        int count = 0;
        int newi = i + 1, newj = j - 1;
        while(newi < (size - 1) && newj > 0 && elem(newi,newj,board) == not_turn){
            newi++; newj--;
            count++;
        }
        if(elem(newi,newj,board) == turn && count > 0){
            return count;
        } else{
            return 0;
        }
    }
    
    void convertUp(int i, int j, int count, vector<vector<int>> &board, int turn){
        i--;
        while(checkBounds(i) && checkBounds(j) && count > 0){
            board[i--][j] = turn;
            count--;
        }
    }
    
    int countUp(int i, int j, vector<vector<int>> &board, int turn){ 
        int not_turn = (turn % 2) + 1;
        int count = 0;
        if(i - 1 > 0 && elem(i - 1, j, board) == not_turn){
            int newi = i - 1;
            while(newi > 0 && elem(newi, j, board) == not_turn){
                newi--;
                count++;
            }
            if(board[newi][j] == turn){
                return count;
            }
        }
        return 0;
    }
    
    void convertDown(int i, int j, int count, vector<vector<int>> &board, int turn){
        i++;
        while(checkBounds(i) && checkBounds(j) && count > 0){
            board[i++][j] = turn;
            count--;
        }
    }
    
    int countDown(int i, int j, vector<vector<int>> &board, int turn){
        int not_turn = (turn % 2) + 1;
        int count = 0;
        if(i + 1 < (size - 1) && elem(i + 1, j, board) == not_turn){
            int newi = i + 1;
            while(newi < (size - 1) && elem(newi, j, board) == not_turn){
                newi++;
                count++;
            }
            if(board[newi][j] == turn){
                return count;
            }
        }
        return 0;
    }
    
    void convertLeft(int i, int j, int count, vector<vector<int>> &board, int turn){
        j--;
        while(checkBounds(i) && checkBounds(j) && count > 0){
            board[i][j--] = turn;
            count--;
        }
    }
    
    int countLeft(int i, int j, vector<vector<int>> &board, int turn){
        int not_turn = (turn % 2) + 1;
        int count = 0;
        if(j - 1 > 0 && elem(i, j - 1, board) == not_turn){
            int newj = j - 1;
            while(newj > 0 && elem(i, newj, board) == not_turn){
                newj--;
                count++;
            }
            if(board[i][newj] == turn){
                return count;
            }
        }
        return 0;
    }
    
    void convertRight(int i, int j, int count, vector<vector<int>> &board, int turn){
        j++;
        while(checkBounds(i) && checkBounds(j) && count > 0){
            board[i][j++] = turn;
            count--;
        }
    }
    
    int countRight(int i, int j, vector<vector<int>> &board, int turn){
        int not_turn = (turn % 2) + 1;
        int count = 0;
        if(j + 1 < (size - 1) && elem(i, j + 1, board) == not_turn){
            int newj = j + 1;
            while(newj < (size - 1) && elem(i, newj, board) == not_turn){
                newj++;
                count++;
            }
            if(board[i][newj] == turn){
                return count;
            }
        }
        return 0;
    }
    
    int checkMove(int i, int j, vector<vector<int>> &board, int turn){
        if(checkBounds(i) && checkBounds(j) && board[i][j] == 0){
            board[i][j] = turn;
            int count = 0;
            count += countUp(i, j, board, turn);
            count += countDown(i, j, board, turn);
            count += countLeft(i, j, board, turn);
            count += countRight(i, j, board, turn);
            count += countUpRight(i, j, board, turn);
            count += countUpLeft(i, j, board, turn);
            count += countDownRight(i, j, board, turn);
            count += countDownLeft(i, j, board, turn);
            board[i][j] = 0;
            if(count > 0){
                return count;
            } 
        }
        return 0;
    }
    
    void printAllPossibleMoves(vector<Move> &moves){
        cout << "All Possible Moves\n";
        for(int i = 0; i < moves.size(); i++){
            cout << "i: " << moves[i].x << "\tj: " << moves[i].y << "\tPossible Converts " << moves[i].count << endl;
        }
        cout << endl;
    }
    
    vector<Move> allPossibleMoves(vector<vector<int>> &board, int turn){
        vector<Move> moves;
        int ret = 0;
        for(int i = 0; i < 8; i++){
            for(int j = 0; j < 8; j++){
                if(board[i][j] == 0){
                    ret = checkMove(i,j, board, turn);
                    if(ret > 0){
                        Move m = Move(i, j, ret);
                        moves.push_back(m);
                    }
                }
            }
        }
        return moves;
    }
    
    int playMove(int i, int j, vector<vector<int>> &board, int turn){
        if(checkBounds(i) && checkBounds(j) && board[i][j] == 0){
            board[i][j] = turn;
            int count = 0;
            int ret = 0;
            ret = countUp(i, j, board, turn);        
            convertUp(i, j, ret, board, turn);
            count += ret;
            ret = countDown(i, j, board, turn);      
            convertDown(i, j, ret, board, turn);
            count += ret;
            ret = countLeft(i, j, board, turn);      
            convertLeft(i, j, ret, board, turn);
            count += ret;
            ret = countRight(i, j, board, turn);      
            convertRight(i, j, ret, board, turn);
            count += ret;
            ret = countUpRight(i, j, board, turn);   
            convertUpRight(i, j, ret, board, turn);
            count += ret;
            ret = countUpLeft(i, j, board, turn);    
            convertUpLeft(i, j, ret, board, turn);
            count += ret;
            ret = countDownRight(i, j, board, turn); 
            convertDownRight(i, j, ret, board, turn);
            count += ret;
            ret = countDownLeft(i, j, board, turn);  
            convertDownLeft(i, j, ret, board, turn);
            count += ret;
            if(count > 0){
                return count;
            } else {
                board[i][j] = 0;
            }
        }
        return 0;
    }
    
    vector<vector<vector<int> > > allBoards(vector<Move> &moves, vector<vector<int>> &board, int turn){
        vector<vector<vector<int> > > boards;
        for(int i = 0; i < moves.size(); i++){
            vector<vector<int>> b (board);
            playMove(moves[i].x, moves[i].y, b, turn);
            boards.push_back(b);
        }
        return boards;
    }
    
    int AlphaBeta(int depth, bool maxPlayer, vector<vector<int>> &board, int alpha, int beta){
        if(depth == 2){
            return score(board);
        }
        int ret = -1;
        if(maxPlayer){
            int best = -100;
            vector<Move> moves = allPossibleMoves(board, 2); // check all the moves for the computer
            if(moves.size() == 0){
                return score(board);
            }
            vector<vector<vector<int>>> boards = allBoards(moves, board, 2);
            for(int i = 0; i < moves.size(); i++){
                ret = AlphaBeta(depth + 1, true, boards[i], alpha, beta);
                cout << "Ret : " << ret << endl;
                if(ret > best){
                    best = ret;
                }
                if(best > alpha){
                    alpha = best;
                }
                if(beta <= alpha){
                    break;
                }
            }
            return best;
        } else{
            int best = 100;
            vector<Move> moves = allPossibleMoves(board, 2);
            if(moves.size() == 0){
                return score(board);
            }
            vector<vector<vector<int>>> boards = allBoards(moves, board, 1);
            for(int i = 0; i < moves.size(); i++){
                ret = AlphaBeta(depth + 1, false, boards[i], alpha, beta);
                cout << "Ret : " << ret << endl;
                if(ret < best){
                    best = ret;
                }
                if(ret < best){
                    best = ret;
                }
                if(best < beta){
                    beta = best;
                }
                if(beta <= alpha){
                    break;
                }
            }
            return best;
        }
    }
    
    int computerMove(vector<vector<int> > &board, int turn){
        vector<Move> moves = allPossibleMoves(board, turn);
        if(moves.size() == 0){
            EndGame();
            exit(0);
        }
        printAllPossibleMoves(moves);
        vector<vector<vector<int> > > boards = allBoards(moves, board, turn);
        int best = -100;
        int bestIndex = -1;
        int ret = 0;
        int depth = 1;
        int alpha = -100;
        int beta = 100;
        vector<vector<int>> bestBoard;
        for(int i = 0; i < moves.size(); i++){
            ret = AlphaBeta(depth, false, boards[i], alpha, beta);
            if(ret > best){
                bestIndex = i;
                best = ret;
                bestBoard = boards[i];
            }
        }
        for(int i = 0; i < size; i++){
            for(int j = 0; j < size; j++){
                gameboard[i][j] = bestBoard[i][j];
            }
        }
        return 1;
    }
    
    void playGame(){
        int moves = 60;
        printBoard();
        while(moves > 0){    // while Move possible for the current turn
            // Make Move
            bool made = false;
            int count;
            vector<Move> possibleMoves = allPossibleMoves(gameboard,playerTurn);
            if(possibleMoves.size() == 0){
                EndGame();
                exit(0);
            }
            while(playerTurn == 1 && !made){
                cout << "Player Going\n";
                int r,c;
                cout << "Enter Row\n";
                cin >> r;
                cout << "Enter Col\n";
                cin >> c;
                count = playMove(r, c, gameboard, playerTurn);
                printBoard();
                if(count > 0){
                    made = true;
                    cout << "Player Score: " << count << " Disks\n";
                } else{
                    cout << "Invalid Move.... Go Again\n";
                }
            }
            while(playerTurn == 2 && !made){
                cout << "Computer Going\n";
                count = computerMove(gameboard, playerTurn);
                printBoard();
                made = true;
                cout << "Computer Played\n";
            }
            
            moves--;
            // Switch Turns
            playerTurn = (playerTurn % 2) + 1;
        }
        EndGame();  // If move not possible, declare a winner
    }
};

int main()
{
    Othello o = Othello();
    o.playGame();
}