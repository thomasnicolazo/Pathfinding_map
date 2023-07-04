#include <iostream>
#include "Terrain.hpp"

/*class Terrain
    class Terrain is a template to construct specific terrain
*/
Terrain::Terrain(){
    passable = true;
    mvtCost =1;
    color = "\033[1;42mo\033[0m";
}

Terrain::~Terrain(){}

void Terrain::displayTerrain(){
    std::cout << color;
}

void Terrain::displayCoordinates(){
    std::cout << color << "x: "<< x << " y: "<<y <<std::endl;;
}

void Terrain::changeColor(std::string couleur){
    color =  couleur;
}

// not used
void Terrain::modifyCoordinates(int coorX, int coorY){
    x = coorX;
    y = coorY;
}
bool Terrain::isPassable(){ // can we cross the terrain
    return passable;
}

int Terrain::getMvtCost(){ //mouvement cost of the terrain
    return mvtCost;
}

// class BaseTerrain
/*
Base terrain (green by default ), mouvement cost to go through it is 1,
*/

BaseTerrain::BaseTerrain(){
    passable = true;
    mvtCost = 1;
    color = "\033[1;42mo\033[0m";
    int x = 0;
    int y = 0;
}

BaseTerrain::~BaseTerrain(){}

void BaseTerrain::displayTerrain(){
    std::cout << color;
}

// class Mountain Terrain
/*
Mountain terrain (green by default ) , can't go through it
*/

MountainsTerrain::MountainsTerrain(){
    passable = false;
    mvtCost = 100;
    color = "\033[1;107mX\033[0m";
    int x = 0;
    int y = 0;
}

MountainsTerrain::~MountainsTerrain(){}


void MountainsTerrain::displayTerrain(){
    std::cout << color;
}
