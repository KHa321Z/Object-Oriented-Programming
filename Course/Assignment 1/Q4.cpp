#include <iostream>

using namespace std;

class Stack {

    private:
        int top;
        int length;
        int* stack;

    public:
        Stack() : length(10), top(-1) {

            this->stack = new int [this->length];

        };

        Stack(int len) : length(len), top(-1) {

            this->stack = new int [this->length];

        };

        ~Stack() {

            delete[] this->stack;

        };

        void push(int data) {

            if (this->top == this->length - 1)
                cout << "Stack Overflow" << endl;
            
            else
                *(this->stack + ++this->top) = data;

        };

        void pop() {

            if (this->top == -1)
                cout << "Stack Underflow" << endl;
            
            else
                this->top--;

        };

        int getTop() {

            if (this->top == -1)
                cout << "Stack is Empty" << endl;
            
            else
                return *(this->stack + this->top);

        };

        bool isEmpty() {

            return this->top == -1;

        };

        int size() {

            return this->top + 1;

        };

        void display() {

            for (int i = 0; i < this->top + 1; i++)
                cout << "The value is: " << *(this->stack + i) << endl;

        };

};

class Queue {

    private:
        int front;
        int rear;
        int length;
        int* queue;

    public:
        Queue() : length(10), front(-1), rear(-1) {

            this->queue = new int [this->length];

        };

        Queue(int len) : length(len), front(-1), rear(-1) {

            this->queue = new int [this->length];

        };

        ~Queue() {

            delete[] this->queue;

        };

        void enqueue(int data) {

            if (!this->isFull()) {

                this->rear = (this->rear + 1) % this->length;
                *(this->queue + this->rear) = data;

            } else
                cout << "Stack Overflow" << endl;

        };
        
        int dequeue() {

            if (!this->isEmpty())
                return *(this->queue + (this->front = (this->front + 1) % this->length));

            cout << "Stack Underflow" << endl;
            return INT_MIN;

        };

        int getFront() {

            return *(this->queue + this->front);

        };

        int getRear() {

            return *(this->queue + this->rear);

        };

        bool isEmpty() {

            return (this->rear == this->front);

        };

        bool isFull() {

            return (this->front == (this->rear + 1) % this->length);

        };

        int size() {

            return this->length;

        };

        void display() {

            if (!isEmpty()) {

                int currentIndex = this->front;

                while (currentIndex != this->rear) {
                    currentIndex = (currentIndex + 1) % this->length;
                    cout << "The value is: " << *(this->queue + currentIndex) << endl;
                }

            } else
                cout << "Queue is empty" << endl;

        };

};

int main() {
    
    Queue myq;
    Stack mystack;
    int data;

    for (int i = 0; i < 10; i++) {

        cout << "Enter Value: ";
        cin >> data;

        mystack.push(data);
        
        if (i % 3 == 0) {
        	cout << "popped" << endl;
        	mystack.pop();
        }

    }

    mystack.display();
    
	for (int i = 0; i < 10; i++) {

        cout << "Enter Value: ";
        cin >> data;

        myq.enqueue(data);
        
        if (i % 3 == 0) {
        	cout << "Dequeued" << endl;
        	cout << myq.dequeue() << endl;
        }
        
    }

    myq.display();

    return 0;

}