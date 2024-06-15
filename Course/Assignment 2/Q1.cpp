#include <iostream>

using namespace std;

class Stack {

    private:

        int top;
        int size;
        int* stack;

    public:

        Stack(int s = 10) : top(-1), size(s), stack(new int [size]) {}

        ~Stack() { delete[] this->stack; }

        void push(int value) {

            if (++this->top == this->size) {

                int* tempStack = new int [++this->size];

                for (int i = 0; i < this->size - 1; i++)
                    tempStack[i] = this->stack[i];

                delete[] this->stack;

                this->stack = tempStack;

            }

            this->stack[this->top] = value;

        }

        int pop() {
            return this->stack[this->top--];
        }

};

int main() {

    int n;
    int box;
    int chocos = 0;

    cout << "Enter the number of minutes: ";
    cin >> n;

    Stack C(n);

    cout << "Enter the number of chocolates in each box:" << endl;

    for (int i = 0; i < n; i++) {

        cout << "Box " << (i + 1) << " : "; 
        cin >> box;

        if (box)
            C.push(box);
        else
            chocos += C.pop();

    }

    cout << "Total sold: " << chocos << endl;

    return 0;

}