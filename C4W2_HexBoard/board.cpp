#include <iostream>
#include <cstdlib>
#include <cfloat>
#include <ctime>
#include <vector>
#include <iomanip>
#include <exception>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <string>
using namespace std;

typedef vector<vector<int>> matrix;

class HexBoard {
public:
    HexBoard(): size(11), board(init_board()), pieces(init_pieces()){}
    HexBoard(int n);
    void move(int player, int i, int j);
    void evaluate();
    void print();
    void print_matrix();
private:
    int size;
    matrix init_board();
    matrix init_pieces();
    matrix board;
    matrix pieces;
    
};

HexBoard::HexBoard(int n){
    size = n;
    board = init_board();
    pieces = init_pieces();
}

matrix HexBoard::init_board(){
    int nodes = size*size;
    matrix new_board(nodes, vector<int>(nodes, 0));
    for(int i = 0; i < nodes; ++i){
        if (i-size >= 0) new_board[i][i-size] = 1;
        if (i-size+1 >= 0 && (i-size+1)%size != 0) new_board[i][i-size+1] = 1;
        if ((i-1)%size != 2 && i-1 >= 0) new_board[i][i-1] = 1;
        if ((i+1)%size != 0 && i+1 < nodes) new_board[i][i+1] = 1;
        if ((i+size-1)%size != 2 && i+size-1 < nodes) new_board[i][i+size-1] = 1;
        if (i+size < nodes && i+size < nodes) new_board[i][i+size] = 1;
    }
    return new_board;
}

matrix HexBoard::init_pieces(){
    matrix new_pieces(size, vector<int>(size, 0));
    return new_pieces;
}

void HexBoard::print_matrix(){
    int nodes = size*size;
    string top, bottom, spacing, board_display;

    for (int i = 0; i < nodes; ++i){
        top.clear(), bottom.clear();
        // top += spacing, bottom += spacing;
        for (int j = 0; j < nodes; ++j){
            top += (to_string(board[i][j]) + " ");
            // bottom += (to_string(board[i][j]) + " ");
        }
        board_display += (top + "\n");
        // board_display += (bottom + "\n");
        // spacing += "  ";
    } 
    cout << board_display;
}


void HexBoard::print(){
    int node = 0;
    string top, bottom, spacing, board_display;

    for (int i = 0; i < size; ++i){
        top.clear(), bottom.clear();
        top += spacing, bottom += spacing;
        for (int j = 0; j < size; ++j){
            // top += (to_string(board[i][j]) + " ");
            // bottom += (to_string(board[i][j]) + " ");
            (j != size-1) ? (top += ". — ") : (top += ".");
            (i != size-1) ? ((j != size-1) ? (bottom += " \\ /") : (bottom += " \\   ")) : (bottom);
            node++;
        }
        board_display += (top + "\n");
        board_display += (bottom + "\n");
        spacing += "  ";
    } 
    cout << board_display;
}

int main(){
    HexBoard test_board(5);
    test_board.print();
    test_board.print_matrix();
    return 0;
}
