#ifndef SUDOKU_H
#define SUDOKU_H

#define SIZE 9
#define SQUARE_SIZE 3

#include <vector>
#include <iostream>

class Sudoku {
  std::vector<std::vector<int>> initial;
  std::vector<std::vector<int>> field;

  bool isInBounds(int row, int col) const;
public:
  // Constructor
  Sudoku(int values[SIZE][SIZE]);

  // Prints out the board
  void print(std::ostream& = std::cout) const;

  // Checks if the digit is valid
  bool checkDigitInField(int digit, int row, int col);

  // Sets digit on board[row][col]
  bool setDigitInField(int digit, int row, int col);

  bool removeDigitInField(int row, int col);

  bool solve(int row, int col);
};

#endif