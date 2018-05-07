#include "maze.hpp"
#include <iostream>
#include <fstream>

using namespace std;

void Maze::loadFile(string filename)
{

    // Load the file
    ifstream inFile;
    inFile.open(filename);

    // Get the height and width of the maze
    inFile >> height;
    inFile >> width;

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
}