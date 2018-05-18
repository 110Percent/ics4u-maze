
// Preprocessor stuff
#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>
#include "maze.hpp"

using namespace std;

// Prototype functions
bool searchMaze(Maze, int, int, int);
void display(Maze, int, int, int);

// Declare variables
string printDirs[4] = {"up", "right", "down", "left"};
int sleepTime = 50;

// Create new Maze
Maze topMaze;

int main() {

    string fileName;
    cout << "Enter map filename (located in maps directory, eg. 'maze1.dat'): ";
    cin >> fileName;

    // Load maze file (TODO: Allow user to enter filename)
    if (!topMaze.loadFile("mazes/" + fileName))
        return 1;   

    // Start solving maze recursively
    bool found = searchMaze(topMaze, topMaze.startX, topMaze.startY, 4);
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
    int dirs[7] = {0, 1, 2, 3, 0, 1, -1};
    bool goodPath = false;

    // Mark this tile as "on the path"
    maze.tiles[y][x].onPath = true;

    // Mark this tile as 'having been touched before
    topMaze.tiles[y][x].tapped = true;


    // Repeat for all directions (iterates if dead end found)
    for (int i = 0; i < 4; i++) {

        this_thread::sleep_for(chrono::milliseconds(sleepTime / 2));

        // Print the map
        display(maze, x, y, pastDir);
        

        //cout << maze.tiles[y][x].dirs[0] << ' ' << maze.tiles[y][x].dirs[1] << ' ' << maze.tiles[y][x].dirs[2] << ' ' << maze.tiles[y][x].dirs[3] << endl;
         cout << endl << "Cursor position: (" << x << ", " << y << "), " << ((pastDir > -1) ? "pointing " + printDirs[pastDir] : "standing still") << endl;

         // Don't go back and forth across the same two tiles
         if (i == dirs[pastDir + 2])
             continue;

         switch (i)
         {
         // Go up
         case 0:
             if (y != 0 && maze.tiles[y - 1][x].data != '#' && !topMaze.tiles[y - 1][x].tapped)
                 goodPath = searchMaze(maze, x, y - 1, 0);
             break;
         // Right
         case 1:
             if (x + 1 != maze.width && maze.tiles[y][x + 1].data != '#' && !topMaze.tiles[y][x + 1].tapped)
                 goodPath = searchMaze(maze, x + 1, y, 1);
             break;
         // Down
         case 2:
             if (y + 1 != maze.height && maze.tiles[y + 1][x].data != '#' && !topMaze.tiles[y + 1][x].tapped)
                 goodPath = searchMaze(maze, x, y + 1, 2);
             break;
         // Left
         case 3:
             if (x != 0 && maze.tiles[y][x - 1].data != '#' && !topMaze.tiles[y][x - 1].tapped)
                 goodPath = searchMaze(maze, x - 1, y, 3);
             break;
        }
        // Don't continue the loop if the goal is found
        if (goodPath) break;
    }

    this_thread::sleep_for(chrono::milliseconds(sleepTime / 2));

    // Returns true if on the path to the goal, false if on a bad path
    return goodPath;

}

// Print the map to the screen, with a pointer indicating the position and direction of the navigator
void display(Maze maze, int x, int y, int dir) {

    // I found a lot of screen tearing when printing characters to the screen individually, so I used a buffer instead
    string outBuffer = "";

    // Clear the screen lmao
    outBuffer += string(50, '\n');
    outBuffer += "MAZE NAVIGATOR\n\nFile: " + maze.file + "\n\n";

    // Print the map, with the appropriate pointer inside
    for (int i = 0; i < maze.height; i++) {
        for (int j = 0; j < maze.width; j++) {

            // Print start/goal
            if (maze.tiles[i][j].data == 'S' || maze.tiles[i][j].data == 'G')
                outBuffer += "\033[39m" + string(1,maze.tiles[i][j].data) + " ";

            // Print pointer
            else if (i == y && j == x)
                outBuffer += "\033[37;1m● ";

            // Print non-wall
            else if (maze.tiles[i][j].data == '.') {

                // If the space is on the path, print a big circle
                if (maze.tiles[i][j].onPath)
                    outBuffer += "\033[32m⬤ ";

                // If the tile is not on the path, yet has been passed over, it is on a "bad" path, and is marked with an x
                else if (topMaze.tiles[i][j].tapped)
                    outBuffer += "\033[91mx ";

                // Empty space that has not been touched before, print a .
                else
                    outBuffer += "\033[39m. ";
            }

            // Print wall
            else if (maze.tiles[i][j].data == '#')
                outBuffer += "\033[34;1m# ";
            
            // I dunno what else it's gonna be, but just print it anyways
            else outBuffer += maze.tiles[i][j].data + " ";
        }
        
        // Newline
        outBuffer += "\033[39m\n";
    }

    // Print buffer to the screen
    cout << outBuffer;
}   