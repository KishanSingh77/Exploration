#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

struct Point {
    int row;
    int col;
    Point() : row(0), col(0) {};
    Point(int x, int y) : row(x), col(y) {}
    bool operator<(const Point& other) const {
        return row < other.row ||
              (row == other.row && col < other.col);
    }
};

bool isValid(const Point &pos) {
    return 0 <= pos.row && pos.row < 8 && 0 <= pos.col && pos.col < 8;
}

// Input: a row, col position on an 8x8 chessboard of a knight
// Output: a vector of row, col positions that the knight could move to
// on a chessboard.
std::vector<Point> getKnightMoves(const Point& pos) {
    // TODO: implement
    int dr[8] = {-2, -2, -1, -1, 1, 1, 2, 2};
    int dc[8] = {1, -1, 2, -2, 2, -2, 1, -1};
    std::vector<Point> newKnightMoves = std::vector<Point>();
    for (int i = 0; i < 8; i++) {
        Point newPosition = Point(pos.row + dr[i], pos.col + dc[i]);
        if (isValid(newPosition)) {
            newKnightMoves.push_back(newPosition);
        }
    }
    return newKnightMoves;
}

// Main function for parsing input and displaying output
// You should not have to change this in your final solution
int main(int argc, char** argv) {
    if (argc < 3) {
        std::cout << "usage: " << argv[0] << " row col\n";
        return 1;
    }
    const int row = std::stoi(argv[1]);
    const int col = std::stoi(argv[2]);
    std::vector<Point> result = getKnightMoves(Point(row, col));
    std::sort(result.begin(), result.end());
    for (size_t i = 0; i < result.size(); ++i) {
        const Point& elem = result[i];
        std::cout << elem.row << ", " << elem.col << '\n';
    }
    return 0;
}
