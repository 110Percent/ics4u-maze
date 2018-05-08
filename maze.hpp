#include <iostream>

struct tile
{
    char data;
    int dirs[4] = {0, 0, 0, 0};
    bool onPath = false;
    int pathDir;
};

class Maze
{
  public:
    tile tiles[48][48];
    int height, width, startX, startY;
    bool loadFile(std::string);
};