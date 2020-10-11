#include "Pathfinder.h"

using namespace std;

Pathfinder::Pathfinder(){}
Pathfinder::~Pathfinder(){}

string Pathfinder::toString() const{
    string sarray;
    stringstream ss;
    int i, j, k;
    for (i = 0; i<5; ++i){
        for (j = 0; j<5; ++j){
            for (k = 0; k<5; ++k){
                if (k < 4){
                    ss << mazeArray[k][j][i] << " ";
                }
                else{
                     ss << mazeArray[k][j][i];
                }
            }
            ss << endl;
        }
        if (i<4){
            ss << endl;
        }
    }
    sarray = ss.str();
    return sarray;
}
void Pathfinder::createRandomMaze(){
    int i, j, k;
    for (i = 0; i<5; ++i){
        for (j = 0; j<5; ++j){
            for (k = 0; k<5; ++k){
                mazeArray[i][j][k] = rand()%2;
            }
        }
    }
    mazeArray[0][0][0] = 1;
    mazeArray[4][4][4] = 1;
}
bool Pathfinder::importMaze(string file_name){
    ifstream import(file_name);
    int i, j, k;
    int value = 0;
    if(import){
        for (i = 0; i<5; ++i){
            for (j = 0; j<5; ++j){
                for (k = 0; k<5; ++k){
                    if (!import.eof()){
                        import >> value;
                        if (value == 1 || value == 0){
                            newMaze[k][j][i] = value;
                        }
                        else{
                            return false;
                        }
                    }
                    else{
                        return false;
                    }
                }
            }
        }
        if(newMaze[0][0][0] == 1 && newMaze[4][4][4] == 1){
            if (import.eof()){
                for (i = 0; i<5; ++i){
                    for (j = 0; j<5; ++j){
                        for (k = 0; k<5; ++k){
                            mazeArray[i][j][k] = newMaze[i][j][k];
                        }
                    }
                }
                return true;
            }
            else{
                return false;
            }
        }
        else{
            return false;
        }
    }
    else{
        return false;
    }
}
bool Pathfinder::findPath(int x, int y, int z){
    string coordinates;
    stringstream ss;
    ss << "(" << x << ", " << y << ", " << z << ")";
    coordinates = ss.str();
    path.push_back(coordinates);
    if(x < 0 || x > 4 || y < 0 || y > 4 || z < 0 || z > 4){
        path.pop_back();
        return false;
    }
    if(newMaze[x][y][z] != 1){
        path.pop_back();
        return false;
    }
    if (x == 4 && y == 4 && z == 4 && newMaze[x][y][z] == 1){
        return true;
    }
    newMaze[x][y][z] = 2;
    if (findPath(x+1, y, z)){
        return true;
    }
    else if(findPath(x-1, y, z)){
        return true;
    }
    else if(findPath(x, y+1, z)){
        return true;
    }
    else if(findPath(x, y-1, z)){
        return true;
    }
    else if(findPath(x, y, z+1)){
        return true;
    }
    else if(findPath(x, y, z-1)){
        return true;
    }
    else{
        path.pop_back();
        return false;
    }
}
vector<string> Pathfinder::solveMaze(){
    int a= 0;
    int b = 0;
    int c = 0;
    path.clear();
    int i, j, k;
    for (i = 0; i<5; ++i){
        for (j = 0; j<5; ++j){
            for (k = 0; k<5; ++k){
                newMaze[i][j][k] = mazeArray[i][j][k];
            }
        }
    }    
    findPath(a, b, c);
    return path;
}