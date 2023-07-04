#pragma once
#include <string>

class Terrain
{
protected:
    bool passable;
    int mvtCost;
    std::string color;
    int x;
    int y;
public:
    Terrain();
    ~Terrain();

    void displayTerrain();

    void displayCoordinates();

    void changeColor(std::string couleur);

    void modifyCoordinates(int coorX, int coorY);

    bool isPassable();

    int getMvtCost();
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
