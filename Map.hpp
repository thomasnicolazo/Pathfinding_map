#include <deque>
#include "Terrain.hpp"
#include "string"

class Map
{
// indices of map begin at 0,0
private:
    std::deque<std::deque<Terrain>> mapGrid; // int for now
    int heightMapSize; // height of the map
    int widthMapSize;   // width of the map

public:
    Map(int height, int width,int mapCharacteristic);

    ~Map();

    void initMap(int mapCharacteristic);

    int getMapWidth();

    int getMapHeight();

    void changeColor(int x, int y,std::string couleur); // change element color in map

    void resetColor(std::string couleur);

    void displayMap();

    Terrain getElementAt(int x, int y); // get element terrain at  specific coordinates

    void setElement(int x, int y , Terrain value); // set element terrain at specific coordinates

    void addTop(int x,int y,Terrain value); // add lines on the top of the map with terrain

    void addRight(int x, int y, Terrain value); // add columns on the right of the map with terrain

    void addBottom(int x, int y ,Terrain value); // add lines on the bottom of the map with terrain 

    void addLeft(int x, int y,Terrain value); // add columns on the left of the map with terrain

    void addElement(int x, int y, Terrain value); // fill the difference between the point(with coordinates x,y) and the map with terrain
};

