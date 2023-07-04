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

    void changeColor(int x, int y,std::string couleur);

    void resetColor(std::string couleur);

    void displayMap();

    Terrain getElementAt(int x, int y);

    void setElement(int x, int y , Terrain value);

    void addTop(int x,int y,Terrain value);

    void addRight(int x, int y, Terrain value);

    void addBottom(int x, int y ,Terrain value);

    void addLeft(int x, int y,Terrain value);

    void addElement(int x, int y, Terrain value);
};

