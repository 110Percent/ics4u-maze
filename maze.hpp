#include <iostream>

struct tile
{
    char data;
    bool tapped = false;
    bool onPath = false;
    int pathDir;
};

class Maze
{
  public:
    std::string file;
    tile tiles[48][48];
    int height, width, startX, startY;
    bool loadFile(std::string);
};