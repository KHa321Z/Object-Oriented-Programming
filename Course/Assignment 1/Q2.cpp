#include <iostream>
#include <ctime>
#include <random>

using namespace std;

enum direction {
    NONE, UP, RIGHT, LEFT, DOWN
};

struct Node {

    int position[2] = {0, 0};
    direction move = NONE;

    int depth = 0;
    Node* parent = nullptr;

};

class Queue {

    private:
        int front;
        int rear;
        int length;
        Node** queue;

    public:
        Queue() : length(10), front(-1), rear(-1) {

            this->queue = new Node* [this->length];
        };

        Queue(int len) : length(len), front(-1), rear(-1) {

            this->queue = new Node* [this->length];

        };

        ~Queue() {

            while (!this->isEmpty()) {
                Node* delNode = this->dequeue();

                if (delNode)
                    delete delNode;
            }

            delete[] this->queue;

        };

        void expand() {

            Node** tempQueue = new Node* [this->length + 1];

            for (int i = 0; i < this->length; i++)
                tempQueue[i] = this->dequeue();

            delete[] this->queue;
            
            this->front = 0;
            this->rear = this->length - 1;
            this->length++;
            this->queue = tempQueue;

        }

        void enqueue(Node* data) {

            if (this->isFull())
                this->expand();

            this->rear = (this->rear + 1) % this->length;
            this->queue[this->rear] = data;

        };
        
        Node* dequeue() {

            if (!this->isEmpty())
                return this->queue[this->front = (this->front + 1) % this->length];

            return nullptr;

        };

        Node* getFront() {

            return this->queue[this->front];

        };

        Node* getRear() {

            return this->queue[this->rear];

        };

        bool isEmpty() {

            return this->rear == this->front;

        };

        bool isFull() {

            return this->front == (this->rear + 1) % this->length;

        };

        int size() {

            return this->length;

        };

};

bool** mazeGenerator(int n) {

    bool **maze = new bool* [n];

    for (int i = 0; i < n; i++) {
        
        *(maze + i) = new bool [n];

        for (int j = 0; j < n; j++)
            *(*(maze + i) + j) = rand() % 2;

    }

    maze[0][0] = maze[n - 1][n - 1] = 1;

    return maze;

}

Node** movesGenerator(int n, bool** map, Node* currentNode) {

    int index = 0;
    Node** possibleMoves = new Node* [3] {};

    if (currentNode->move != DOWN && (currentNode->position[0] - 1 >= 0) && map[currentNode->position[0] - 1][currentNode->position[1]])
        map[currentNode->position[0] - 1][currentNode->position[1]] = 0, 
        possibleMoves[index++] = new Node {
            {
                currentNode->position[0] - 1, 
                currentNode->position[1]
            }, 
            UP,
            currentNode->depth + 1,
            currentNode
        };

    if (currentNode->move != UP && (currentNode->position[0] + 1 < n) && map[currentNode->position[0] + 1][currentNode->position[1]])
        map[currentNode->position[0] + 1][currentNode->position[1]] = 0,
        possibleMoves[index++] = new Node {
            {
                currentNode->position[0] + 1, 
                currentNode->position[1]
            }, 
            DOWN,
            currentNode->depth + 1,
            currentNode
        };

    if (currentNode->move != RIGHT && (currentNode->position[1] - 1 >= 0) && map[currentNode->position[0]][currentNode->position[1] - 1])
        map[currentNode->position[0]][currentNode->position[1] - 1] = 0,
        possibleMoves[index++] = new Node {
            {
                currentNode->position[0], 
                currentNode->position[1] - 1
            }, 
            LEFT,
            currentNode->depth + 1,
            currentNode
        };

    if (currentNode->move != LEFT && (currentNode->position[1] + 1 < n) && map[currentNode->position[0]][currentNode->position[1] + 1])
        map[currentNode->position[0]][currentNode->position[1] + 1] = 0,
        possibleMoves[index++] = new Node {
            {
                currentNode->position[0], 
                currentNode->position[1] + 1
            }, 
            RIGHT,
            currentNode->depth + 1,
            currentNode
        };

    return possibleMoves;

}

char** pathFinder(int n, bool** map) {

    char** path;
    bool pathFound = false;
    Node* tempNode = new Node;

    Queue nodes(n * 2);
    nodes.enqueue(tempNode);

    while (!nodes.isEmpty() && !pathFound) {

        do {
            tempNode = nodes.dequeue();
        } while (!tempNode && !nodes.isEmpty());

        if (!tempNode && nodes.isEmpty())
            break;

        Node** moves = movesGenerator(n, map, tempNode);

        for (int i = 0; i < 3 && moves[i]; i++)
            if (moves[i]->position[0] == n - 1 && moves[i]->position[1] == n - 1)
                pathFound = true, tempNode = moves[i];
            else
                nodes.enqueue(moves[i]);

        delete[] moves;

    }

    if (pathFound) {

        int counter = tempNode->depth - 1;
        Node* parent = tempNode->parent;
        path = new char* [tempNode->depth + 1] {};
        
        for (; tempNode->parent; tempNode = parent) {
        
            if (tempNode->move == UP)
                path[counter--] = new char [6] {"up"};

            else if (tempNode->move == DOWN)
                path[counter--] = new char [6] {"down"};

            else if (tempNode->move == RIGHT)
                path[counter--] = new char [6] {"right"};

            else if (tempNode->move == LEFT)
                path[counter--] = new char [6] {"left"};

            parent = tempNode->parent;
            delete tempNode;

        }

    } else {

        for (Node* parent = tempNode->parent; tempNode; tempNode = parent) {
            parent = tempNode->parent;
            delete tempNode;
        }

        path = new char* [4] {};

        path[0] = new char [6] {"path"};
        path[1] = new char [6] {"not"};
        path[2] = new char [6] {"found"};

    }

    return path;

}

int main() {

    srand(time(0));

    int n = 5;
    char** path;
    bool** maze; 
    
    // maze = new bool* [5] {
    //     new bool [5] {1, 1, 1, 0, 0},
    //     new bool [5] {1, 0, 1, 1, 1},
    //     new bool [5] {1, 0, 1, 0, 1},
    //     new bool [5] {1, 0, 1, 0, 1},
    //     new bool [5] {1, 1, 1, 0, 1}
    // };

    cout << "Enter Size of Maze: ";
    cin >> n;
    cout << endl;

    maze = mazeGenerator(n);

    for (int i = 0; i < n; i++, cout << endl)
        for (int j = 0; j < n; j++)
            cout << *(*(maze + i) + j) << " ";

    cout << endl;
    cout << "Path:" << endl;

    path = pathFinder(n, maze);

    for (int i = 0; path[i]; i++) {
        cout << path[i] << " ";
        delete[] path[i];
    }

    for (int i = 0; i < n; i++)
        delete[] maze[i];

    delete[] maze;
    delete[] path;

    return 0;

}