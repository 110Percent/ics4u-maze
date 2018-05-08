#include "maze.hpp"
#include <iostream>
#include <fstream>

using namespace std;

bool Maze::loadFile(string filename)
{

    // Load the file
    ifstream inFile;
    inFile.open(filename);
    if (inFile.fail()){
        cout << "Error: Maze file either could not be opened or does not exist." << endl;
        return false;
    }

    // Set the filename property of the maze (to display)
    file = filename;

    // Get the height and width of the maze
    inFile >> height;
    inFile >> width;

    if (height > 20 || width > 20) {
        cout << "Error: Maze dimensions exceed maximum size." << endl;
        return false;
    }

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {

            // Record the character at the given position
            inFile >> tiles[i][j].data;

            // S marks the starting point, so save it if it's found
            if (tiles[i][j].data == 'S') {
                startX = j;
                startY = i;
            } 

        }
    }

    return true;
}