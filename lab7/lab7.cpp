#include <iostream>
#include <vector>
#include <string>

const char PLAYER_X = 'X';
const char PLAYER_O = 'O';
const char EMPTY = '.';

class TicTacToe {
public:
    TicTacToe(int size = 3) : size(size), board(size, std::vector<char>(size, EMPTY)) {}

    void playGame() {
        char currentPlayer = PLAYER_X;

        while (true) {
            printBoard();
            std::cout << "Ход игрока " << currentPlayer << ": ";
            int row, col;
            std::cin >> row >> col;

            if (!isValidMove(row, col)) {
                std::cout << "Неверный ход, попробуйте снова." << std::endl;
                continue;
            }

            board[row][col] = currentPlayer;

            if (isWinner(row, col)) {
                printBoard();
                std::cout << "Игрок " << currentPlayer << " выиграл!" << std::endl;
                break;
            }

            if (isBoardFull()) {
                printBoard();
                std::cout << "Ничья!" << std::endl;
                break;
            }

            currentPlayer = (currentPlayer == PLAYER_X) ? PLAYER_O : PLAYER_X;
        }
    }

private:
    int size;
    std::vector<std::vector<char>> board;

    void printBoard() const {
        for (const auto& row : board) {
            for (char cell : row) {
                std::cout << cell << " ";
            }
            std::cout << std::endl;
        }
    }

    bool isValidMove(int row, int col) const {
        return row >= 0 && row < size&& col >= 0 && col < size&& board[row][col] == EMPTY;
    }

    bool isWinner(int lastRow, int lastCol) const {
        char player = board[lastRow][lastCol];
        bool rowWin = true, colWin = true, diagWin1 = true, diagWin2 = true;

        for (int i = 0; i < size; ++i) {
            if (board[lastRow][i] != player) rowWin = false;
            if (board[i][lastCol] != player) colWin = false;
            if (board[i][i] != player) diagWin1 = false;
            if (board[i][size - i - 1] != player) diagWin2 = false;
        }

        return rowWin || colWin || (lastRow == lastCol && diagWin1) || (lastRow == size - lastCol - 1 && diagWin2);
    }

    bool isBoardFull() const {
        for (const auto& row : board) {
            for (char cell : row) {
                if (cell == EMPTY) return false;
            }
        }
        return true;
    }
};

int main() {
    setlocale(LC_ALL, "Russian");
    TicTacToe game;
    game.playGame();
    return 0;
}
