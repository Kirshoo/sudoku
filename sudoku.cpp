#include "sudoku.h"
#include <iostream>
#include <vector>

bool Sudoku::isInBounds(int row, int col) const {
  return row >= 0 && row < SIZE && col >= 0 && col < SIZE; 
}

// Constructor
Sudoku::Sudoku(int values[SIZE][SIZE]) {
  initial.reserve(SIZE);
  for (int i {0}; i < SIZE; ++i) {
    std::vector<int> row;
    row.reserve(9);

    for (int j {0}; j < SIZE; ++j) {
      row.emplace_back(values[i][j]);
    }

    initial.emplace_back(row);
  }

  field = initial;
}

// Prints out the board
void Sudoku::print(std::ostream& o) const {
  o << std::endl;
  for (int row {0}; row < SIZE; ++row) {
    for (int col {0}; col < SIZE; ++col) {
      o << (col % SQUARE_SIZE == 0 ? " " : "") << field[row][col] << " ";
    }

    o << (row % SQUARE_SIZE == SQUARE_SIZE - 1 ? "\n\n" : "\n");
  }

  return;
}

// Checks if the digit is valid
bool Sudoku::checkDigitInField(int digit, int row, int col) {
  if (!isInBounds(row, col)) return false;

  // Check row and column for duplicates
  for (int i {0}; i < SIZE; ++i) {
    // Check for column
    if (field[i][col] == digit) return false;

    // Check for row
    if (field[row][i] == digit) return false;
  }

  // Check in a square
  int square_row = row / SQUARE_SIZE;
  int square_col = col / SQUARE_SIZE;
  for (int i {square_row * 3}; i < square_row * 3 + 3; ++i) {
    for (int j {square_col * 3}; j < square_col * 3 + 3; ++j) {
      if (field[i][j] == digit) return false;
    }
  }

  return true;
}

/*
 * Sets digit on a specified location */
bool Sudoku::setDigitInField(int digit, int row, int col) {
  if (!initial[row][col]) { // Only set 0 or null digits from initial
    field[row][col] = digit;
    return true;
  }

  return false;
}

/*
 * Removes a digits from a specified location */
bool Sudoku::removeDigitInField(int row, int col) {
  if (initial[row][col]) {
    return false;
  }

  field[row][col] = 0;
  return true;
}

/* 
 * Solves sudoku with a backtracking algorithm */
bool Sudoku::solve(int row, int col) {
  // Base case
  if (col == SIZE) { // Reached the end of the column
    col = 0;
    row += 1; // Move to the next row
    if (row == SIZE) // Reached the last row, puzzle is solved
      return true;
  }

  // If the digits is already there, skip it
  if (initial[row][col] != 0) {
    return solve(row, col + 1);
  } 
  
  for (int i {1}; i <= 9; ++i) {
    // For each digit from 1 to 9
    if (checkDigitInField(i, row, col)) { // Check if its valid
      setDigitInField(i, row, col); // If so, set it to the field

      // If it ends up solving the puzzle with the digit, return
      if (solve(row, col + 1)) {
        return true;
      }
      
      // Else remove digit
      removeDigitInField(row, col);
    }
    
    // Non valid digits are skipped
  }

  return false; // Puzzle is unsolvable
}