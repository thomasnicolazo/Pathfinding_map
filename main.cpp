#include <iostream>
#include <deque>
#include <utility>
#include <vector>
#include <float.h>
#include <cmath>
#include "Terrain.hpp"
#include "Map.hpp"




// A structure to hold the necessary parameters
struct Node {
    // Row and Column index of its parent
    // Note that 0 <= i <= ROW-1 & 0 <= j <= COL-1
    int parent_i, parent_j;
    // f = g + h
    double f, g, h;
    int x,y;
};

// A Utility Function to check whether given cell (row, col)
// is a valid cell or not.
bool isInMap(Map* mapGrid, int row, int col) // check if successor points are in map
{
    // Returns true if row number and column number
    // is in range
    const int height = mapGrid->getMapHeight();
    const int width = mapGrid->getMapWidth();
    return (row >= 0) && (row < height) && (col >= 0) && (col < width);
}

// A Utility Function to check whether the given cell is
// blocked or not
bool isUnBlocked(Map* mapGrid, int x, int y) // check if terrain is passable
{
    // Returns true if the cell is not blocked else false
    if ((mapGrid->getElementAt(x,y)).isPassable() == true)
        return (true);
    else
        return (false);
}

void initStartNode(std::vector<Node>* openList,int start_x,int start_y){ // init first node, it corresponds to the starting point
    Node startNode;
    startNode.x = start_x;
    startNode.y = start_y;
    startNode.f, startNode.g, startNode.h =0;
    openList->push_back(startNode);
}

int getMinFInList(std::vector<Node>* openList){ // return position in list of the node with the smallest F value
    double f = FLT_MAX;
    int posNodeWithSmallestF = NULL;
    for(int i=0; i<openList->size();i++){
        if(openList->at(i).f < f){
            f = openList->at(i).f;
            posNodeWithSmallestF = i;
        }

    }
    return posNodeWithSmallestF;
}

std::vector<Node> getSuccessors(Map* mapGrid, Node q){ // return the 8 nearest nodes of the node q
    Node successor;
    std::vector<Node> successorList;
    for(int i=-1;i<=1;i++){
        for(int j =-1;j<=1;j++){
            if( i!=0 || j!=0){
                successor.parent_i = q.x;
                successor.parent_j =q.y;
                successor.x = q.x + i; // add successor coordinates
                successor.y = q.y + j;
                successor.f ,successor.g,successor.h = FLT_MAX;
                successorList.push_back(successor);
                //std::cout << i <<" "<<j <<std::endl;
            }
        }
    }
    //std::cout << successorList.size() <<std::endl;
    return successorList;
}

void computeDistances(Map* mapGrid,Node* successor, Node* q, int dest_x, int dest_y){
    double diffx = std::abs(q->x - successor->x);
    double diffy = std::abs(q->y - successor->y);
    double mvtCost = mapGrid->getElementAt(successor->x,successor->y).getMvtCost();
    if( diffx ==1 && diffy ==1){
        successor->g = q->g + (double)std::sqrt(2)* mvtCost;
    }
    else{
        successor->g = q->g + (double)1 * mvtCost;
    }
        successor->h = std::abs(dest_x - successor->x) + std::abs(dest_y - successor->y); // Manhattan
        successor->f = successor->g + successor->h;
}

bool isInList(std::vector<Node> liste,Node successor){ // if a node with the same position as successor is in the list which has a lower f than successor return true
    for(int i= 0; i< liste.size();i++){
        int posx = successor.x;
        int posy = successor.y;
        int posInListx = liste[i].x;
        int posInListy = liste[i].y;
        double f = successor.f;
        double fInList = liste[i].f;
        if (posx == posInListx && posy==posInListy && fInList<f){
            return true;
        }
    }
    return false;
}


std::vector<Node> aStar(Map* mapGrid,int start_x,int start_y,int dest_x,int dest_y){
    std::vector<Node> openList; //list of possible positions to go to point A to point B
    std::vector<Node> closedList; // list of positions to go to point A to point B
    initStartNode(&openList,start_x,start_y);
    //std::cout << openList.size();
    while(!openList.empty()){
        int posNodeWithSmallestF = getMinFInList(&openList);
        //std::cout << posNodeWithSmallestF;
        Node q = openList[posNodeWithSmallestF];
        openList.erase(openList.begin() + posNodeWithSmallestF);
        //std::cout << openList.size();
        std::vector<Node> successorList = getSuccessors(mapGrid,q);
        //std::cout << successorList.size() <<std::endl;
        for(int i =0; i<successorList.size();i++){
            int posSuccessor_x = successorList[i].x;
             int posSuccessor_y = successorList[i].y;
            if(posSuccessor_x == dest_x && posSuccessor_y == dest_y){
                closedList.push_back(q);
                closedList.push_back(successorList[i]);
                return closedList;
            }else if(!isInMap(mapGrid,posSuccessor_x,posSuccessor_y)){
                //std::cout << "bonjour";
                continue;
            }
            else if(isUnBlocked(mapGrid,posSuccessor_x,posSuccessor_y)==false){
                continue;
            }
            computeDistances(mapGrid,&successorList[i],&q,dest_x,dest_y);
            if(isInList(openList,successorList[i])){
                continue;
            }
            if(isInList(closedList,successorList[i])){
                continue;
            }
            else{
                openList.push_back(successorList[i]);
                //std::cout << successorList.size() <<std::endl;
            }
        }
        closedList.push_back(q); // list of positions to go to point A to point B

    }
    return closedList;
}

int main()
{

    //init map and terrain object
    Map mapGrid(10,10,0);
    BaseTerrain land;
    land.changeColor("\033[1;44mo\033[0m");
    mapGrid.displayMap();
    // dissplay element at coordinates
    mapGrid.getElementAt(2,4).displayCoordinates();
    // set element land at coordinates in blue
    mapGrid.setElement(2,4,land);
    mapGrid.displayMap();
    //add Elements in blue
    mapGrid.addElement(12,1,land); // bottom
    mapGrid.displayMap();
    mapGrid.addElement(-2,1,land); // top
    mapGrid.displayMap();
    mapGrid.addElement(1,-2,land); // left
    mapGrid.displayMap();
    mapGrid.addElement(1,14,land); // right
    mapGrid.displayMap();
    // set one terrain in cyan at coordinates
    land.changeColor("\033[1;46mo\033[0m");
    mapGrid.setElement(13,13,land);
    mapGrid.getElementAt(13,13).displayCoordinates();

    // add points on diagonale
    land.changeColor("\033[1;45mo\033[0m");
    mapGrid.addElement(16,17,land); // bottom right in magenta
    mapGrid.displayMap();

    land.changeColor("\033[1;41mo\033[0m");
    mapGrid.addElement(17,-2,land); // bottom Left in red
    mapGrid.displayMap();

    land.changeColor("\033[1;47mo\033[0m");
    mapGrid.addElement(-2,-3,land); // Top Left in white
    mapGrid.displayMap();

    land.changeColor("\033[1;40mo\033[0m");
    mapGrid.addElement(-6,25,land); // Top right in black
    mapGrid.displayMap();


    //reset map to green
    mapGrid.resetColor("\033[1;42mo\033[0m");
    mapGrid.displayMap();
    printf("\n");

    std::vector<Node> path = aStar(&mapGrid,1,3,10,10);
    for(int i =0; i<path.size();i++){
        mapGrid.changeColor(path[i].x,path[i].y,"\033[1;41mo\033[0m");
        std::cout << "x: " << path[i].x << " y : " << path[i].y << std::endl;
    }
    mapGrid.displayMap();


   // Map with montains

    Map mapGridWithMountainss(50,50,1);
    mapGridWithMountainss.displayMap();
    std::vector<Node> pathM = aStar(&mapGrid,1,3,16,26);
    for(int i =0; i<pathM.size();i++){
        mapGridWithMountainss.changeColor(path[i].x,path[i].y,"\033[1;41mo\033[0m");
        std::cout << "x: " << path[i].x << " y : " << path[i].y << std::endl;
    }
    mapGridWithMountainss.displayMap();


    return 0;
}
