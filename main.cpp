
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
int sleepTime = 20  ;

int main() {

    // Create new Maze
    Maze maze;

    string fileName;

    cout << "Enter map filename (located in maps directory, eg. 'maze1.dat'): ";
    cin >> fileName;

    // Load maze file (TODO: Allow user to enter filename)
    if (!maze.loadFile("mazes/" + fileName))
        return 1;   

    // Start solving maze recursively
    bool found = searchMaze(maze, maze.startX, maze.startY, -1);
    if (!found)
        cout << endl << "Maze is unsolvable!" << endl;

    return 0;

}

// Recursive maze-solving function
bool searchMaze(Maze maze, int x, int y, int pastDir) {



    // If on the goal, print the coordinates and finish the search
    if (maze.tiles[y][x].data == 'G') {
        display(maze, x, y, pastDir);
        cout << endl << "Goal located at coordinates " << x + 1 << ", " << y + 1 << endl;
        return true;
    }

    // Declare variables
    int dirs[6] = {0, 1, 2, 3, 0, 1};
    bool goodPath = false;


    // Repeat for all directions (iterates if dead end found)
    for (int i = 0; i < 4; i++) {

        // Print the map
        display(maze, x, y, pastDir);
        

        //cout << maze.tiles[y][x].dirs[0] << ' ' << maze.tiles[y][x].dirs[1] << ' ' << maze.tiles[y][x].dirs[2] << ' ' << maze.tiles[y][x].dirs[3] << endl;
         cout << endl << "Cursor position: (" << x << ", " << y << "), " << ((pastDir > -1) ? "pointing " + printDirs[pastDir] : "standing still") << endl;

         maze.tiles[y][x].onPath = true;
         // Don't go back and forth across the same two tiles
         if (i == dirs[pastDir + 2])
             continue;

         switch (i)
         {
         // Go up
         case 0:
             if (y != 0 && maze.tiles[y - 1][x].data != '#' && maze.tiles[y][x].dirs[0] < 1)
             {
                 this_thread::sleep_for(chrono::milliseconds(sleepTime));
                 maze.tiles[y][x].dirs[0] = 1;

                 // Find if the space is part of a path to the goal
                 goodPath = searchMaze(maze, x, y - 1, 0);
                 
                 // If all upward paths are dead ends, do not go up again
                 if (!goodPath)
                     maze.tiles[y][x].dirs[0] = 2;
             }
             break;
         // Right
         case 1:
             if (x + 1 != maze.width && maze.tiles[y][x + 1].data != '#' && maze.tiles[y][x].dirs[1] < 1)
             {
                 this_thread::sleep_for(chrono::milliseconds(sleepTime));
                 maze.tiles[y][x].dirs[1] = 1;
                 goodPath = searchMaze(maze, x + 1, y, 1);
                 if (!goodPath)
                     maze.tiles[y][x].dirs[1] = 2;
             }
             break;
         // Down
         case 2:
             if (y + 1 != maze.height && maze.tiles[y + 1][x].data != '#' && maze.tiles[y][x].dirs[2] < 1)
             {
                 this_thread::sleep_for(chrono::milliseconds(sleepTime));
                 maze.tiles[y][x].dirs[2] = 1;
                 goodPath = searchMaze(maze, x, y + 1, 2);
                 if (!goodPath)
                     maze.tiles[y][x].dirs[2] = 2;
             }
             break;
         // Left
         case 3:
             if (x != 0 && maze.tiles[y][x - 1].data != '#' && maze.tiles[y][x].dirs[3] < 1)
             {
                 this_thread::sleep_for(chrono::milliseconds(sleepTime));
                 maze.tiles[y][x].dirs[3] = 1;
                 goodPath = searchMaze(maze, x - 1, y, 3);
                 if (!goodPath)
                     maze.tiles[y][x].dirs[3] = 2;
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

    // I found a lot of screen tearing when printing characters to the screen individually, so I used a buffer instead
    string outBuffer = "";

    // Clear the screen lmao
    outBuffer += string(50, '\n');
    outBuffer += "MAZE NAVIGATOR\n\n";

    // Print the map, with the appropriate pointer inside
    for (int i = 0; i < maze.height; i++) {
        for (int j = 0; j < maze.width; j++) {

            // Print start/goal
            if (maze.tiles[i][j].data == 'S' || maze.tiles[i][j].data == 'G')
                outBuffer += "\033[39m" + string(1,maze.tiles[i][j].data) + " ";

            // Print pointer
            else if (i == y && j == x)
                outBuffer += "\033[37;1m● ";

            // Print space (big circle if the space is in the path to the goal)
            else if (maze.tiles[i][j].data == '.') {
                if (maze.tiles[i][j].onPath)
                    outBuffer += "\033[32m⬤ ";
                else
                    outBuffer += "\033[39m. ";
            }

            // Print wall
            else if (maze.tiles[i][j].data == '#')
                outBuffer += "\033[34;1m# ";
            
            // Whatever this is, print it
            else outBuffer += maze.tiles[i][j].data + " ";
        }
        outBuffer += "\033[39m\n";
    }
    cout << outBuffer;
}