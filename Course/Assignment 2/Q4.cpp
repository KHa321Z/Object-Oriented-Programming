#include <iostream>

using namespace std;

class Polynomial {

    private:

        int totalTerms; // Total terms in a Polynomial
        int *coeff;     // to save array of coefficients
        int *exp;       // to save array of exponents

    public:

        Polynomial(int terms = 0, int* coefficients = nullptr, int* exponents = nullptr) : totalTerms(terms) {

            for (int i = 0; i < terms; i++)
                if ((*(exponents + i) != 0) && (*(coefficients + i) == 0))
                    totalTerms--;

            coeff = new int [totalTerms];
            exp = new int [totalTerms];

            for (int i = 0; i < terms; i++)
                if (*(coefficients + i) || (!*(coefficients + i) && !*(exponents + i)))
                    *(coeff + i) = *(coefficients + i), 
                    *(exp + i) = *(exponents + i);

        }

        Polynomial(const Polynomial &otherExpression) {

            totalTerms = otherExpression.totalTerms;
            coeff = new int [totalTerms];
            exp = new int [totalTerms];

            for (int i = 0; i < totalTerms; i++)
                *(coeff + i) = *(otherExpression.coeff + i), 
                *(exp + i) = *(otherExpression.exp + i);

        }

        ~Polynomial() {

            delete[] coeff;
            delete[] exp;

        }

        bool operator! () {

            if ((totalTerms == 1) && (*coeff == 0) && (*exp == 0))
                return true;

            return false;

        }

        bool operator!= (const Polynomial &otherPolynomial) const {

            if (totalTerms != otherPolynomial.totalTerms)
                return true;

            for (int i = 0; i < totalTerms; i++)
                if ((*(coeff + i) != *(otherPolynomial.coeff + i)) && (*(exp + i) != *(otherPolynomial.exp + i)))
                    return true;

            return false;

        }

        Polynomial operator+ (const Polynomial &otherPolynomial) const {

            int terms = otherPolynomial.totalTerms;
            int* coefficients = new int [terms + totalTerms] {};
            int* exponents = new int [terms + totalTerms] {};

            for (int i = 0; i < terms; i++)
                *(coefficients + i) = *(otherPolynomial.coeff + i), 
                *(exponents + i) = *(otherPolynomial.exp + i);

            for (int i = 0; i < totalTerms; i++) {

                int j = 0;

                for (; j < otherPolynomial.totalTerms; j++)
                    if (*(exp + i) == *(otherPolynomial.exp + j)) {
                        *(coefficients + j) = *(coeff + i);
                        break;
                    }

                if (j == otherPolynomial.totalTerms)
                    *(coefficients + terms) = *(coeff + i), 
                    *(exponents + terms++) = *(exp + i);

            }

            int* tempCoefficients = new int [terms];
            int* tempExponents = new int [terms];

            for (int i = 0; i < terms; i++)
                *(tempCoefficients + i) = *(coefficients + i), 
                *(tempExponents + i) = *(exponents + i);

            delete[] coefficients;
            delete[] exponents; 

            for (int i = 0; i < terms; i++)
                for (int j = i; j < terms - 1; j++)
                    if (*(tempExponents + j) < *(tempExponents + j + 1))
                        swap(*(tempExponents + j), *(tempExponents + j + 1)), 
                        swap(*(tempCoefficients + j), *(tempCoefficients + j + 1));

            return Polynomial (terms, tempCoefficients, tempExponents);

        }

        Polynomial& operator++ () {

            for (int i = 0; i < totalTerms; i++)
                (*(coeff + i))++;

            return *this;            

        }

        Polynomial operator++ (int) {

            Polynomial temp(*this);

            for (int i = 0; i < totalTerms; i++)
                (*(coeff + i))++;

            return temp;

        }

        void operator= (const Polynomial &otherExpression) {

            delete[] coeff;
            delete[] exp;

            totalTerms = otherExpression.totalTerms;
            coeff = new int [totalTerms];
            exp = new int [totalTerms];

            for (int i = 0; i < totalTerms; i++)
                *(coeff + i) = *(otherExpression.coeff + i), 
                *(exp + i) = *(otherExpression.exp + i);

        }

        int getTotalTerms() const {
            return totalTerms;
        }

        int getCoefficient(int index) const {
            return *(coeff + index);
        }

        int getExponent(int index) const {
            return *(exp + index);
        }

};

ostream& operator<< (ostream &cout, const Polynomial &expression) {

    for (int i = 0; i < expression.getTotalTerms(); i++)
        cout << expression.getCoefficient(i) << (expression.getExponent(i) ? "x^" : "") << char((expression.getExponent(i)) ? expression.getExponent(i) + '0' : 0) << ((i != expression.getTotalTerms() - 1) ? " + " : "");

    return cout;

}

Polynomial operator+ (int constant, const Polynomial &expression) {

    int terms = expression.getTotalTerms();
    int* coefficients = new int [terms];
    int* exponents = new int [terms];

    for (int i = 0; i < terms; i++)
        *(coefficients + i) = expression.getCoefficient(i), 
        *(exponents + i) = expression.getExponent(i);

    *(coefficients + terms - 1) += 2;

    Polynomial sum(terms, coefficients, exponents);

    delete[] coefficients;
    delete[] exponents;

    return sum;

}

main() {

    int coeff_P1[] = {1, 2, 5};             // Coefficients for Polynomial P1
    int exp_P1[] = {4, 2, 0};               // Exponents for Polynomial P1

    int coeff_P2[] = {4, 3};                // Coefficients for Polynomial P2
    int exp_P2[] = {6, 2};                  // Exponents for Polynomial P2

    Polynomial P1(3, coeff_P1, exp_P1);     // Creates P1 with 3 terms (P1 = 1x^4 + 2x^2 + 5x^0 )
    Polynomial P2(2, coeff_P2, exp_P2);     // Creates P2 with 2 terms (P2 = 4x^6 + 3x^2)

    cout << "P1 = " << P1 << endl;          // Prints P1 = x^4+2x^2+5
    cout << "P2 = " << P2 << endl;          // Prints P2 = 4x^6+3x^2

    if (!P1)
        cout << "P1 is zero" << endl;       /*if polynomial has only 1 term and its coeff and exp are zero. i.e. if p1 = 0.*/

    if (P1 != P2)
        cout << "P1 is Not Equal to P2" << endl;
    
    Polynomial P3 = P1 + P2;                // Adds P1 and P2 and saves result in P3.You may consume extra space for resultant Polynomial in Add function
    
    cout << "P3 = " << P3 << endl;          // Prints P3 = 4x^6+x^4+5x^2+5
    
    cout << ++P1 << endl; // adds 1 in all the coefficient.
    cout << P1 << endl;
    cout << P1++ << endl; // adds 1 in all the coefficient.
    cout << P1 << endl;

    P3 = 2 + P1;                            // Assume P1 already has a constant term, add 2 in it.
    
    cout << "P3 = " << P3 << endl;

    return 0;

}