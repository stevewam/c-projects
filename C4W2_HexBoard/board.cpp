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
#include <numeric>
using namespace std;

typedef vector<vector<int>> matrix;
typedef pair<int, int> piece;
enum class player: short{X=1, O}; // X -> Horizontal, O -> Vertical

class HexBoard {
public:
    HexBoard(): size(11), hexagons(init_hexagons()), board(init_board()){}
    HexBoard(int n);
    bool move(player p, int i, int j);
    bool end();
    void print();
    void print_matrix();
private:
    int size;
    matrix init_board();
    matrix init_hexagons();
    bool reach(player p, piece p1);
    matrix hexagons;
    matrix board;
    
};

HexBoard::HexBoard(int n){
    size = n;
    board = init_board();
    hexagons = init_hexagons();
}

matrix HexBoard::init_hexagons(){
    int nodes = size*size;
    matrix hex_slots(nodes, vector<int>(nodes, 0));
    for(int i = 0; i < nodes; ++i){
        if (i-size >= 0) hex_slots[i][i-size] = 1;
        if (i-size+1 >= 0 && (i-size+1)%size != 0) hex_slots[i][i-size+1] = 1;
        if ((i-1)%size != 2 && i-1 >= 0) hex_slots[i][i-1] = 1;
        if ((i+1)%size != 0 && i+1 < nodes) hex_slots[i][i+1] = 1;
        if ((i+size-1)%size != 2 && i+size-1 < nodes) hex_slots[i][i+size-1] = 1;
        if (i+size < nodes && i+size < nodes) hex_slots[i][i+size] = 1;
    }
    return hex_slots;
}

matrix HexBoard::init_board(){
    matrix new_board(size, vector<int>(size, 0));
    return new_board;
}

void HexBoard::print_matrix(){
    int nodes = size*size;
    string top, bottom, spacing, board_display;

    for (int i = 0; i < nodes; ++i){
        top.clear(), bottom.clear();
        for (int j = 0; j < nodes; ++j){
            top += (to_string(hexagons[i][j]) + " ");
        }
        board_display += (top + "\n");
    } 
    cout << board_display;
}


void HexBoard::print(){
    int node = 0;
    string top, bottom, stone, spacing, board_display;

    for (int i = 0; i < size; ++i){
        top.clear(), bottom.clear();
        top += spacing, bottom += spacing;
        for (int j = 0; j < size; ++j){
            if (board[i][j] == 0) stone = ".";
            else if (board[i][j] == 1) stone = "x";
            else stone = "o";
            (j != size-1) ? (top += stone + " — ") : (top += stone);
            (i != size-1) ? ((j != size-1) ? (bottom += " \\ /") 
                : (bottom += " \\   ")) : (bottom);
            node++;
        }
        board_display += (top + "\n");
        board_display += (bottom + "\n");
        spacing += "  ";
    } 
    cout << board_display;
}

bool HexBoard::move(player p, int i, int j){
    if (i > size-1 || j > size-1 || i < 0 || j < 0) {
        cout << "Position is outside the bound of the hex board." << endl;
        return false;
    }
    else if (board[i][j] == 0) {
        board[i][j] = static_cast<int>(p);
        // cout << "Player " << static_cast<int>(p) << " places a stone in " 
        //     << "(" << i << ", " << j << ")" << endl;
        return true;
    }
    else {
        cout << "Position is already filled." << endl;
        return false;
    }
}

bool HexBoard::reach(player p, piece p1){
    int node1 = p1.first * size + p1.second;
    int origin, position;
    int reference = static_cast<int>(p);
    vector<int> tree, queue;
    piece loc;
    queue.push_back(node1);
    tree.push_back(node1);

    
    while (!queue.empty()){
        origin = queue[queue.size()-1];
        // cout << "Popped from queue " << origin << endl;
        queue.pop_back();
        auto it = find(hexagons[origin].begin(), hexagons[origin].end(), 1);
        while (it != hexagons[origin].end()) {
            position = it - hexagons[origin].begin();
            // cout << "Neighbor " << position << endl;
            loc = make_pair(position/size, position%size);
            // cout << loc.first << ", " << loc.second;
            // if (reference == 1 && position%size == size-1) return 1;
            // else if (reference == 2 && position/size == size-1) return 1;
            // cout << "   " << board[loc.first][loc.second] << endl;
            if (board[loc.first][loc.second] == reference) {
                if (reference == 1 && position%size == size-1) return 1;
                else if (reference == 2 && position/size == size-1) return 1;
                if (find(tree.begin(), tree.end(), position) == tree.end()){
                    // cout << "Added to tree " << position << endl;
                    tree.push_back(position);
                    queue.push_back(position);
                }
            }
            it = find(++it, hexagons[origin].end(), 1);
            // break;
        }
        // break;
    }
    return 0;   
}

bool HexBoard::end(){
    int sum;
    vector<piece> v_start, v_end, h_start, h_end;

    for (int i = 0, j = 0; i < size; ++i){
        if (board[i][j] == 1) 
            h_start.push_back(make_pair(i, j)); 
    }
    
    if (h_start.size() > 0){
        for (int i = 0, j = size-1; i < size; ++i){
            if (board[i][j] == 1) 
                h_end.push_back(make_pair(i, j)); 
        }
        if (h_end.size() == 0) h_start.clear();
    }

    for (int i = 0, j = 0; j < size; ++j){
        if (board[i][j] == 2) 
            v_start.push_back(make_pair(i, j)); 
    }
    
    if (v_start.size() > 0){
        for (int i = size-1, j = 0; j < size; ++j){
            if (board[i][j] == 2) 
                v_end.push_back(make_pair(i, j)); 
        }
        if (v_end.size() == 0) v_start.clear();
    }

    if (v_start.size() < 1 && h_start.size() < 1)
        return false;
    
    for (auto slot: h_start){
        // cout << "(" << slot.first << ", " << slot.second << ") ";
        if (reach(player::X, slot)) {
            cout << "The game has ended. Player 1 has won. Congratulations!";
            return true;
        }
    }
    // cout << endl;
    for (auto slot: v_start){
        // cout << "(" << slot.first << ", " << slot.second << ") ";
        if (reach(player::O, slot)) {
            cout << "The game has ended. Player 2 has won. Congratulations!";
            return true;
        }
    }
    // cout << endl;
    for (auto row: board)
        sum += accumulate(row.begin(), row.end(), 0);
    
    if (sum == size*size) {
        cout << "No moves left. It is a draw.";
        return true;
    }
    return false;
}

int main(){
    int size, i, j;
    int end = 0;
    int legal = 0;
    cout << endl << "HEX" << endl << endl;
    cout << "Choose your board size: ";
    cin >> size;
    cout << endl;
    // cout << size << endl << endl;

    HexBoard board(size);

    cout << "Board" << endl << endl;
    board.print();

    cout << "Instruction: " << endl;
    cout << "Player 1, your token is X. To win, you must connect the two vertical sides of the board." << endl;
    cout << "Player 2, your token is O. To win, you must connect the two horizontal sides of the board." << endl;
    cout << "To place a token, enter the desired coordinate x y." << endl << endl;

    while (!end) {
        while (!legal) {
            cout << "Player 1's Move [row column]: ";
            cin >> i >> j;
            legal = board.move(player::X, i-1, j-1);
        }
        legal = 0;
        cout << endl;
        board.print();
        end = board.end();
        // cout << end;
        if (end) break;

        while (!legal) {
            cout << "Player 2's Move [row column]: ";
            cin >> i >> j;
            legal = board.move(player::O, i-1, j-1);
        }
        legal = 0;
        cout << endl;
        board.print();
        end = board.end();
    }
    cout << endl << endl;

    return 0;
}
