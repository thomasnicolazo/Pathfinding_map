#include <iostream>
#include <ctime>
#include "Map.hpp"
#include "Terrain.hpp"

Map::Map(int height, int width,int mapCharacteristic){
    heightMapSize = height;
    widthMapSize = width;

    initMap(mapCharacteristic);

}

Map::~Map(){}
/*
Map coordinates
    ----> y (width)
    |
    |
 x  v
 (height)


*/

void Map::initMap(int mapCharacteristic){
    /* mapCharacteristique  0: just plains (Base terrain, 1: plains with mountains

    */
    if (mapCharacteristic == 0){ //plains
        BaseTerrain land;
        std::deque<Terrain> line;
        for(int j=0; j<widthMapSize; j++){ // create line object
            line.push_back(land);
        }
        for(int i=0; i< heightMapSize;i++){
            mapGrid.push_back(line); // add line to each element of the first deque

        }
    /*
    for(int i=0; i< heightMapSize;i++){ // dirty change
        for(int j=0; j<widthMapSize;j++){
            mapGrid[i][j].modifyCoordinates(i,j);
        }
    }
    */
    }
    else if(mapCharacteristic ==1){ //  plains with mountains
        std::srand(std::time(nullptr)); // use current time as seed for random generator
        int random_variable;

        BaseTerrain landB;
        MountainsTerrain landM;
        std::deque<Terrain> line;
        for(int i=0;i<heightMapSize;i++){
            for(int j=0; j<widthMapSize; j++){ // create line object
                random_variable = std::rand() % 100;
                if (random_variable < 10){
                    line.push_back(landM);
                }
                else{
                    line.push_back(landB);
                }
            }
            mapGrid.push_back(line); // add line to each element of the first deque
            line.clear();
        }


    }
}

int Map::getMapWidth(){
    return widthMapSize;
}

int Map::getMapHeight(){
    return heightMapSize;
}

void Map::changeColor(int x, int y,std::string couleur){ // change color of a specific element of map
    mapGrid[x][y].changeColor(couleur);
}

void Map::resetColor(std::string couleur){ // change color to all elements in map
    for(int i=0;i<heightMapSize;i++){
        for(int j=0;j<widthMapSize;j++){
            mapGrid[i][j].changeColor(couleur);
        }
    }
}

void Map::displayMap(){ // show map
    std::cout << heightMapSize << widthMapSize << std::endl;
    for(int i = 0; i<heightMapSize; i++){
        for(int j=0; j<widthMapSize;j++){
            mapGrid[i][j].displayTerrain();
        }
        printf("\n");
    }
}

Terrain Map::getElementAt(int x, int y){
    return mapGrid[x][y];
}

void Map::setElement(int x, int y , Terrain value){ // change terrain in map at coordinates
    mapGrid[x][y] = value;
}

void Map::addTop(int x,int y,Terrain value){ // add line on the top of the map
    int nbLineToAdd = -x;;
    std::deque<Terrain> line;
    for(int j=0; j<widthMapSize; j++){
        line.push_back(value);
    }
    for(int i=0; i< nbLineToAdd;i++){
        mapGrid.push_front(line); // add line to each element of the first deque
    }
    heightMapSize += nbLineToAdd; // increase heigth map with the number of lines added on the top
}

void Map::addRight(int x, int y, Terrain value){  // add line on the right of the map
    int nbElementToAddPerLine = (y-widthMapSize);
    for(int i =0; i<heightMapSize;i++){
        for(int j =0;j< (y-widthMapSize); j++){
            mapGrid[i].push_back(value);
        }
    }
    widthMapSize += nbElementToAddPerLine; //increase width map with the number of elements added on one line

}

void Map::addBottom(int x, int y ,Terrain value){  // add line on the bottom of the map
    // int for now
    int nbLineToAdd = x-heightMapSize;
    std::deque<Terrain> line; // int for now
    for(int j=0; j<widthMapSize; j++){
        line.push_back(value);  // int for now
    }
    for(int i=0; i< nbLineToAdd;i++){
        mapGrid.push_back(line); // add line to each element of the first deque
    }
    heightMapSize += nbLineToAdd; // increase heigth map with the number of lines added on the bottom
}

void Map::addLeft(int x, int y,Terrain value){  // add line on the left of the map
    for(int i =0; i<heightMapSize;i++){
        for(int j =0;j< -y; j++){
            mapGrid[i].push_front(value);
        }
    }
    widthMapSize -= y; //increase width map with the number of elements added on one line
}

void Map::addElement(int x, int y, Terrain value){ //value is int for now    , // add point to the right/left or top/bottom
    //  x >heightMapSize xor y > widthMapSize  ->  bool xorRes = ((!(x >heightMapSize && y > widthMapSize)) && (x >heightMapSize || y > widthMapSize));

    if (x<0 && ((y>0 && y<widthMapSize))){ //top
        addTop(x,y,value);
    }
    else if(x<0 && (y>widthMapSize)){ // top right
        int copy_x = x;
        int copy_y = y;
        addTop(copy_x,0, value);
        addRight(0,copy_y,value);

    }
    else if((x > 0 && x < heightMapSize) && (y > widthMapSize)){ // right
        addRight(x,y,value);
    }
    else if(x>heightMapSize && y>widthMapSize){ // bottom right
        int copy_x = x;
        int copy_y = y;
        addBottom(copy_x,0,value);
        addRight(0,copy_y,value);
    }
    else if(x > heightMapSize && ((y>0 && y<widthMapSize))){ // bottom
        addBottom(x,y,value);
    }
    else if(x>heightMapSize && y<0){ // bottom left
        int copy_x = x;
        int copy_y = y;
        addBottom(copy_x,0,value);
        addLeft(0,copy_y,value);
    }
    else if(y<0 && ((x>0 && x<heightMapSize))){ // left
        addLeft(x,y,value);

    }
    else if(x<0 && y<0){ // left top
        int copy_x = x;
        int copy_y = y;
        addTop(copy_x,0,value);
        addLeft(0,copy_y,value);
    }
    else{
        std::cerr << "can only add points which are not already on the map" << std::endl;
        exit(2);
    }
    /*
    for(int i=0; i< heightMapSize;i++){ // dirty change
        for(int j=0; j<widthMapSize;j++){
            mapGrid[i][j].modifyCoordinates(i,j);
        }
    }
    */
}

