#include <iostream>

using namespace std;

enum direction {
    NONE = 0, 
    DOWN = 1,
    UP = -1, 
    RIGHT = 2,
    LEFT = -2
};

struct position {
    int x;
    int y;
    direction move = NONE;
};

void expand(position* &oneDarray, const int &size) {

    position* temp = new position [size + 1] {};

    for (int i = 0; i < size; i++)
        *(temp + i) = *(oneDarray + i);

    if (oneDarray)
        delete[] oneDarray;

    oneDarray = temp;

}

void copyAndExpand(position** &twoDarray, int &size, const int &addRow) {

    position** temp = new position* [++size] {};

    for (int i = 0; i < size; i++)
        if (i < addRow)
            *(temp + i) = *(twoDarray + i);

        else if (i > addRow)
            *(temp + i) = *(twoDarray + i - 1);

    if (twoDarray)
        delete[] twoDarray;

    twoDarray = temp;

}

void shrink(position** &twoDarray, int &size, position* &ignoringPointer) {        

    position** temp = new position* [--size] {};

    for (int i = 0; i < size + 1; i++)
        if (*(twoDarray + i) < ignoringPointer)
            *(temp + i) = *(twoDarray + i);

        else if (*(twoDarray + i) > ignoringPointer)
            *(temp + i - 1) = *(twoDarray + i);

    delete[] twoDarray;
    delete[] ignoringPointer;

    if (size)
        twoDarray = temp;
    
    else 
        twoDarray = nullptr;

}

bool** mazeGenerator(const int n) {

    bool **maze = new bool* [n];

    for (int i = 0; i < n; i++) {
        
        *(maze + i) = new bool [n];

        for (int j = 0; j < n; j++)
            *(*(maze + i) + j) = rand() % 2;

    }

    maze[0][0] = maze[n - 1][n - 1] = 1;

    return maze;

}

position* moveGenerator(const int n, bool** map, const position &lastPosition) {

    int index = 0;
    position* moves = new position [4] {};

    if ((lastPosition.move != UP) && (lastPosition.x + 1 < n) && map[lastPosition.x + 1][lastPosition.y])
        moves[index++] = { 
            lastPosition.x + 1, 
            lastPosition.y, 
            DOWN 
        };

    if ((lastPosition.move != DOWN) && (lastPosition.x - 1 >= 0) && map[lastPosition.x - 1][lastPosition.y])
        moves[index++] = {
            lastPosition.x - 1, 
            lastPosition.y, 
            UP
        };
    
    if ((lastPosition.move != LEFT) && (lastPosition.y + 1 < n) && map[lastPosition.x][lastPosition.y + 1])
        moves[index++] = {
            lastPosition.x, 
            lastPosition.y + 1, 
            RIGHT
        };

    if ((lastPosition.move != RIGHT) && (lastPosition.y - 1 >= 0) && map[lastPosition.x][lastPosition.y - 1])
        moves[index++] = {
            lastPosition.x, 
            lastPosition.y - 1, 
            LEFT
        };

    return moves;

}

position* pathFind(const int n, bool** map) {

    int depthLevel = 1;
    int pathCounter = 1;
    position* currentPath = nullptr;
    position** allPossiblePaths = new position* [pathCounter] { 
        new position [depthLevel] { 0, 0, NONE }
    };

    while (pathCounter) {

        for (int i = 0; i < pathCounter; i++) {

            currentPath = *(allPossiblePaths + i);

            position* moves = moveGenerator(n, map, *(currentPath + depthLevel - 1));
        
            // if no moves available then path is dead end
            // remove path and reduce pathCounter as well as current index
            if (!(*moves).move) {

                delete[] moves;

                shrink(allPossiblePaths, pathCounter, currentPath);
                i--;

                continue;

            // only one possible move
            } else if (!(*(moves + 1)).move) {

                expand(currentPath, depthLevel);

                *(allPossiblePaths + i) = currentPath;
                *(currentPath + depthLevel) = *moves;

            // branching
            } else {

                expand(currentPath, depthLevel);

                *(allPossiblePaths + i) = currentPath;
                *(currentPath + depthLevel) = *moves;

                for (position* currentMove = moves + 1; (*currentMove).move; currentMove++) {

                    copyAndExpand(allPossiblePaths, pathCounter, ++i);
                    //expand(*(allPossiblePaths + pathCounter - 1), depthLevel);

                    *(allPossiblePaths + i) = new position [depthLevel + 1];

                    for (int k = 0; k < depthLevel; k++)
                        *(*(allPossiblePaths + i) + k) = *(currentPath + k);

                    *(*(allPossiblePaths + i) + depthLevel) = *currentMove;

                }

            }

            delete[] moves;

            // breaking condition end reached
            if (((*(currentPath + depthLevel)).x == n - 1) && ((*(currentPath + depthLevel)).y == n - 1)) {

                for (int k = 0; k < pathCounter; k++)
                    if (*(allPossiblePaths + k) != currentPath)
                        delete[] *(allPossiblePaths + k);

                delete[] allPossiblePaths;

                expand(currentPath, depthLevel + 1);

                return currentPath;

            // path reached start somehow so discard it
            } else if (((*(currentPath + depthLevel)).x == 0) && ((*(currentPath + depthLevel)).y == 0)) {

                shrink(allPossiblePaths, pathCounter, currentPath);
                currentPath--;

                continue;

            }

        }

        depthLevel++;

    }

    return nullptr;

}


int main() {

    srand(time(0));

    int n = 7;
    position* path;
    bool** maze; 

    // maze = new bool* [7] {
    //     new bool [7] {1, 0, 1, 1, 1, 1, 0},
    //     new bool [7] {1, 0, 1, 0, 0, 1, 1},
    //     new bool [7] {1, 0, 1, 1, 1, 0, 1},
    //     new bool [7] {1, 0, 1, 0, 1, 0, 1},
    //     new bool [7] {1, 0, 1, 1, 1, 0, 1},
    //     new bool [7] {1, 0, 1, 0, 0, 1, 1},
	//     new bool [7] {1, 1, 1, 0, 0, 1, 1}
    // };

//     1 0 0 0 0 1
// 1 0 0 1 1 0
// 1 0 1 1 0 0
// 1 1 1 1 1 1
// 0 1 0 1 1 0
// 1 0 1 0 1 1

    cout << "Enter Size of Maze: ";
    cin >> n;
    cout << endl;

    maze = mazeGenerator(n);

    for (int i = 0; i < n; i++, cout << endl)
        for (int j = 0; j < n; j++)
            cout << *(*(maze + i) + j) << " ";

    cout << endl;
    cout << "Path:" << endl;

    path = pathFind(n, maze);
    
    if (!path)
        cout << "No Path Exists!" << endl;

    else 
        for (int i = 1; (*(path + i)).move; i++)
            if ((*(path + i)).move == DOWN)
                cout << "down ";
            else if ((*(path + i)).move == UP)
                cout << "up ";
            else if ((*(path + i)).move == RIGHT)
                cout << "right ";
            else
                cout << "left ";

    return 0;

}