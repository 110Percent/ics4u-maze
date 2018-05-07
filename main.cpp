
// Preprocessor stuff
#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>
#include "maze.hpp"

// We have to do this in CompSci don't hate me
using namespace std;

// Prototype functions
bool searchMaze(Maze, int, int, int);
void display(Maze, int, int, int);
string printDirs[4] = {"up", "right", "down", "left"};

int main() {

    // Create new Maze
    Maze maze;

    // Load maze file (TODO: Allow user to enter filename)
    maze.loadFile("mazes/maze2.dat");

    // Start solving maze recursively
    searchMaze(maze, maze.startX, maze.startY, -1);

    return 0;

}

// Recursive maze-solving function
bool searchMaze(Maze maze, int x, int y, int pastDir) {



    // If on the goal, print the coordinates and finish the search
    if (maze.tiles[y][x].data == 'G') {
        display(maze, x, y, pastDir);
        cout << "Goal located at coordinates " << x + 1 << ", " << y + 1 << endl;
        return true;
    }

    // Declare variables
    int dirs[6] = {0, 1, 2, 3, 0, 1};
    bool goodPath = false;

    // Repeat for all directions (iterates if dead end found)
    for (int i = 0; i < 4; i++) {

        // Print the map
        display(maze, x, y, pastDir);

        cout << endl << "Cursor position: (" << x << ", " << y << "), " << ((pastDir > -1) ? "pointing " + printDirs[pastDir] : "standing still") << endl;

        // Make the maze navigation actually visible
        this_thread::sleep_for(chrono::milliseconds(75));


        // Don't go back and forth across the same two tiles
        if (i == dirs[pastDir + 2])
            continue;
        

        switch (i) {
            // Go up
            case 0:
                if (y != 0 && maze.tiles[y - 1][x].data != '#' && maze.tiles[y][x].dirs[0])
                {
                    goodPath = searchMaze(maze, x, y - 1, 0);
                    // If all upward paths are dead ends, do not go up again
                    if (!goodPath)
                        maze.tiles[y][x].dirs[0] = false;
                }
                break;
            // Right
            case 1:
                if (x + 1 != maze.width && maze.tiles[y][x + 1].data != '#' && maze.tiles[y][x].dirs[1])
                {
                    goodPath = searchMaze(maze, x + 1, y, 1);
                    if (!goodPath)
                        maze.tiles[y][x].dirs[1] = false;
                }
                break;
            // Down
            case 2:
                if (y + 1 != maze.height && maze.tiles[y + 1][x].data != '#' && maze.tiles[y][x].dirs[2])
                {
                    goodPath = searchMaze(maze, x, y + 1, 2);
                    if (!goodPath)
                        maze.tiles[y][x].dirs[2] = false;
                }
                break;
            // Left
            case 3:
                if (x != 0 && maze.tiles[y][x - 1].data != '#' && maze.tiles[y][x].dirs[3])
                {
                    goodPath = searchMaze(maze, x - 1, y, 3);
                    if (!goodPath)
                        maze.tiles[y][x].dirs[3] = false;
                }
                break;
        }
        // Don't continue the loop if the goal is found
        if (goodPath) break;
    }

    return goodPath;

}

// Print the map to the screen, with a pointer indicating the position and direction of the navigator
void display(Maze maze, int x, int y, int dir) {

    // Clear the screen lmao
    cout << string(50, '\n') << endl;
    cout << "MAZE NAVIGATOR" << endl << endl;

    // Pointerbois
    char dirs[4] = {'^', '>', 'v', '<'};

    // Print the map, with the appropriate pointer inside
    for (int i = 0; i < maze.height; i++) {
        for (int j = 0; j < maze.width; j++) {
            if (i == y && j == x)
                cout << dirs[dir] << ' ';
            else
                cout << maze.tiles[i][j].data << ' ';
        }
        cout << endl;
    }
}