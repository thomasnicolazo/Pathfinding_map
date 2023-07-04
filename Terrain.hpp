#pragma once
#include <string>

class Terrain
{
protected:
    bool passable;
    int mvtCost;
    std::string color;
    //not used
    int x;
    int y;
public:
    Terrain();
    ~Terrain();

    void displayTerrain();

    void displayCoordinates();

    void changeColor(std::string couleur); // change color of the terrain

    void modifyCoordinates(int coorX, int coorY); // not used

    bool isPassable(); // check if we can go through the terrain

    int getMvtCost(); // get mouvement cost of the terrain
};


class BaseTerrain : public Terrain
{
public:
    BaseTerrain();
    ~BaseTerrain();

    void displayTerrain();
};

class MountainsTerrain : public Terrain
{
public:
    MountainsTerrain();

    ~MountainsTerrain();

    void displayTerrain();
};
