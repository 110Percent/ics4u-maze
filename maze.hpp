#include <iostream>

struct tile
{
    char data;
    bool dirs[4] = {true, true, true, true};
};

class Maze
{
  public:
    tile tiles[128][128];
    int height, width, startX, startY;
    void loadFile(std::string);
};