#include <iostream>
#include <iomanip>
using namespace std;

#define N 9  // size of the Sudoku grid

// Function to print the Sudoku grid with enhanced formatting
void printGrid(int grid[N][N]) {
    cout << "\n╔═══════╦═══════╦═══════╗\n";
    for (int row = 0; row < N; row++) {
        if (row == 3 || row == 6) {
            cout << "╠═══════╬═══════╬═══════╣\n";
        }
        cout << "║ ";
        for (int col = 0; col < N; col++) {
            if (grid[row][col] == 0) {
                cout << ". ";
            } else {
                cout << grid[row][col] << " ";
            }
            if ((col + 1) % 3 == 0) {
                cout << "║ ";
            }
        }
        cout << "\n";
    }
    cout << "╚═══════╩═══════╩═══════╝\n";
}

// Check if placing num at grid[row][col] is valid
bool isSafe(int grid[N][N], int row, int col, int num) {
    // Row check
    for (int x = 0; x < N; x++) {
        if (grid[row][x] == num) return false;
    }
    
    // Column check
    for (int x = 0; x < N; x++) {
        if (grid[x][col] == num) return false;
    }
    
    // 3x3 subgrid check
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (grid[i + startRow][j + startCol] == num) return false;
        }
    }
    
    return true;
}

// Solve Sudoku using backtracking
bool solveSudoku(int grid[N][N]) {
    int row = -1, col = -1;
    bool empty = false;
    
    // Find an empty cell
    for (int i = 0; i < N && !empty; i++) {
        for (int j = 0; j < N && !empty; j++) {
            if (grid[i][j] == 0) {
                row = i;
                col = j;
                empty = true;
            }
        }
    }
    
    // If no empty cell left, puzzle is solved
    if (!empty) return true;
    
    // Try placing digits 1 to 9
    for (int num = 1; num <= 9; num++) {
        if (isSafe(grid, row, col, num)) {
            grid[row][col] = num;  // place number
            
            if (solveSudoku(grid)) return true;  // recursive call
            
            grid[row][col] = 0;  // backtrack
        }
    }
    
    return false;  // trigger backtracking
}

// Function to input Sudoku grid from user
void inputGrid(int grid[N][N]) {
    cout << "\n📝 Enter the Sudoku puzzle (use 0 for empty cells)\n";
    cout << "Enter 9 numbers per row, separated by spaces:\n\n";
    
    for (int i = 0; i < N; i++) {
        bool validRow = false;
        while (!validRow) {
            cout << "Row " << (i + 1) << ": ";
            validRow = true;
            
            for (int j = 0; j < N; j++) {
                if (!(cin >> grid[i][j])) {
                    cout << "❌ Invalid input! Please enter numbers only.\n";
                    cin.clear();
                    cin.ignore(10000, '\n');
                    validRow = false;
                    break;
                }
                
                if (grid[i][j] < 0 || grid[i][j] > 9) {
                    cout << "❌ Invalid input! Please enter numbers between 0 and 9.\n";
                    validRow = false;
                    break;
                }
            }
            
            if (!validRow) {
                cin.clear();
                cin.ignore(10000, '\n');
            }
        }
    }
}

// Validate if the initial Sudoku grid is valid
bool isValidGrid(int grid[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (grid[i][j] != 0) {
                int temp = grid[i][j];
                grid[i][j] = 0;  // Temporarily remove the number
                
                if (!isSafe(grid, i, j, temp)) {
                    grid[i][j] = temp;  // Restore the number
                    cout << "❌ Conflict found at Row " << (i+1) << ", Col " << (j+1) 
                         << " with value " << temp << "\n";
                    return false;
                }
                
                grid[i][j] = temp;  // Restore the number
            }
        }
    }
    return true;
}

// Count empty cells in the puzzle
int countEmptyCells(int grid[N][N]) {
    int count = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (grid[i][j] == 0) count++;
        }
    }
    return count;
}

int main() {
    int grid[N][N];
    int choice;
    
    cout << "╔═══════════════════════════════════╗\n";
    cout << "║   SUDOKU SOLVER (Backtracking)   ║\n";
    cout << "╚═══════════════════════════════════╝\n\n";
    
    cout << "Choose input method:\n";
    cout << "1️⃣  Use predefined puzzle (Easy)\n";
    cout << "2️⃣  Use predefined puzzle (Hard)\n";
    cout << "3️⃣  Enter custom puzzle\n";
    cout << "\nEnter choice (1, 2, or 3): ";
    cin >> choice;
    
    if (choice == 1) {
        // Predefined easy puzzle
        int predefined[N][N] = {
            {5,3,0, 0,7,0, 0,0,0},
            {6,0,0, 1,9,5, 0,0,0},
            {0,9,8, 0,0,0, 0,6,0},
            
            {8,0,0, 0,6,0, 0,0,3},
            {4,0,0, 8,0,3, 0,0,1},
            {7,0,0, 0,2,0, 0,0,6},
            
            {0,6,0, 0,0,0, 2,8,0},
            {0,0,0, 4,1,9, 0,0,5},
            {0,0,0, 0,8,0, 0,7,9}
        };
        
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                grid[i][j] = predefined[i][j];
            }
        }
        
        cout << "\n✅ Using predefined EASY puzzle\n";
    } 
    else if (choice == 2) {
        // Predefined hard puzzle
        int predefined[N][N] = {
            {0,0,0, 0,0,0, 0,0,0},
            {0,0,0, 0,0,3, 0,8,5},
            {0,0,1, 0,2,0, 0,0,0},
            
            {0,0,0, 5,0,7, 0,0,0},
            {0,0,4, 0,0,0, 1,0,0},
            {0,9,0, 0,0,0, 0,0,0},
            
            {5,0,0, 0,0,0, 0,7,3},
            {0,0,2, 0,1,0, 0,0,0},
            {0,0,0, 0,4,0, 0,0,9}
        };
        
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                grid[i][j] = predefined[i][j];
            }
        }
        
        cout << "\n✅ Using predefined HARD puzzle\n";
    }
    else if (choice == 3) {
        inputGrid(grid);
    } 
    else {
        cout << "❌ Invalid choice! Using predefined easy puzzle.\n";
        
        int predefined[N][N] = {
            {5,3,0, 0,7,0, 0,0,0},
            {6,0,0, 1,9,5, 0,0,0},
            {0,9,8, 0,0,0, 0,6,0},
            
            {8,0,0, 0,6,0, 0,0,3},
            {4,0,0, 8,0,3, 0,0,1},
            {7,0,0, 0,2,0, 0,0,6},
            
            {0,6,0, 0,0,0, 2,8,0},
            {0,0,0, 4,1,9, 0,0,5},
            {0,0,0, 0,8,0, 0,7,9}
        };
        
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                grid[i][j] = predefined[i][j];
            }
        }
    }
    
    // Display initial grid
    cout << "\n📋 Initial Sudoku Puzzle:";
    printGrid(grid);
    
    int emptyCells = countEmptyCells(grid);
    cout << "\n📊 Empty cells: " << emptyCells << " / 81\n";
    
    // Validate the initial grid
    if (!isValidGrid(grid)) {
        cout << "\n❌ Error: The initial Sudoku grid is invalid!\n";
        cout << "There are conflicting numbers in rows, columns, or subgrids.\n";
        return 1;
    }
    
    cout << "\n⏳ Solving...\n";
    
    // Solve the Sudoku
    if (solveSudoku(grid)) {
        cout << "\n✅ Solution found!\n";
        printGrid(grid);
        cout << "\n🎉 Puzzle solved successfully!\n";
    } else {
        cout << "\n❌ No solution exists for this Sudoku puzzle!\n";
    }
    
    return 0;
}