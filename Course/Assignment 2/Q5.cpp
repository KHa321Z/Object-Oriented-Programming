#include <iostream>

using namespace std;

class Customer {

    private:

        int id;
        string name;
        int discount;

    public:

        Customer(int ID, string naam, int disc) : id(ID), name(naam), discount(disc) {}

        int getID() {
            return this->id;
        }

        string getName() {
            return this->name;
        }

        int getDiscount() {
            return this->discount;
        }

        void setDiscount(int disc) {
            this->discount = disc;
        }

        string toString() {
            return (this->name + "(" + to_string(this->id) + ")(" + to_string(this->discount) + "%)");
        }

};

class Invoice {

    private:

        int id;
        Customer customer;
        double amount;

    public:

        Invoice(int ID, Customer custom, double am) : id(ID), customer(custom), amount(am) {}

        int getID() {
            return this->id;
        }

        Customer getCustomer() {
            return this->customer;
        }

        void setCustomer(Customer custom) {
            this->customer = custom;
        }

        double getAmount() {
            return this->amount;
        }

        void setAmount(double am) {
            this->amount = am;
        }

        int getCustomerID() {
            return this->customer.getID();
        }

        string getCustomerName() {
            return this->customer.getName();
        }

        int getCustomerDiscount() {
            return this->customer.getDiscount();
        }

        double getAmountAfterDiscount() {
            return (this->amount - (this->amount * this->customer.getDiscount() / 100));
        }

        string toString() {
            return ("Invoice[id=" + to_string(this->id) + ", customer=" + this->customer.toString() + ", amount=" + to_string(this->amount) + "]");
        }

};

int main () {

    Customer c1(1, "Ali", 10);
    Customer c2(2, "Ahmed", 20);
    Customer c3(3, "Asad", 30);

    Invoice i1(1, c1, 1000);
    Invoice i2(2, c2, 2000);
    Invoice i3(3, c3, 3000);

    cout << i1.toString() << endl;
    cout << i2.toString() << endl;
    cout << i3.toString() << endl;

    return 0;

}