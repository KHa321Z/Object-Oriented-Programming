#include <iostream>

using namespace std;

class Account {

	private:

		int number;
		float balance;

	public:

		Account() : number(0), balance(0) {};

		virtual ~Account() { cout << "~Account Destroyed." << endl; }

		void setNumber(int no) {
			this->number = no;
		}

		int getNumber() {
			return this->number;
		}

		void setBalance(float bal) {
			this->balance = bal;
		}

		float getBalance() {
			return this->balance;
		}

		virtual void print() {
			
			cout << "Account Details:" << endl;
			cout << "Account Number: " << this->number << endl;
			cout << "Account Balance: " << this->balance << endl;

		}

		virtual void debit(float amount) {
		
			this->setBalance(this->getBalance() - amount);

		};

		virtual void credit(float amount) {

			this->setBalance(this->getBalance() + amount);

		}

};

class CurrentAccount : public Account {

	private:

		float serviceCharges;
		float minBalance;

	public:

		CurrentAccount() : Account(), serviceCharges(0), minBalance(0) {}

		~CurrentAccount() { cout << "~CurrentAccount Destroyed." << endl; }

		void print() override {

			this->Account::print();
			cout << "Minimum Balance: " << this->minBalance << endl;
			cout << "Service Charges: " << this->serviceCharges << endl;

		}

		void debit(float amount) override {
		
			if (this->getBalance() < amount) {

				cout << "Error in Transaction!" << endl;
				cout << "Insufficient Balance! Transaction Terminated!" << endl;

			} else {

				this->Account::debit(amount);

				if (this->getBalance() < this->minBalance)
					this->setBalance(this->getBalance() - this->serviceCharges);

			}
		
		}

};

class SavingAccount : public Account {

	private:

		int interestRate;

	public:

		SavingAccount() : Account(), interestRate(0) {}

		~SavingAccount() { cout << "~SavingAccount Destroyed." << endl; }

		void print() override {

			this->Account::print();
			cout << "Interest Rate: " << this->interestRate << endl;

		}

		void debit(float amount) override {

			if (this->getBalance() < amount) {

				cout << "Error in Transaction!" << endl;
				cout << "Insufficient Balance! Transaction Terminated!" << endl;

			} else
				this->Account::debit(amount);

		}

};

int main() {

	//Array of base pointers
	Account** alist = new Account* [5];
	alist[0] = new SavingAccount;
	alist[1] = new CurrentAccount;
	alist[2] = new Account;
	alist[3] = new CurrentAccount;
	alist[4] = new SavingAccount;
	
	//Print data of all accounts polymorphic behavior
	for (int i = 0; i < 5; i++)
		alist[i]->print(), cout << endl;

	//credit and debit polymorphic behavior
	alist[0]->credit(50);
	alist[2]->debit(333);

	for (int i = 0; i < 5; i++)
		delete alist[i];

	delete[] alist;

	return 0;

}