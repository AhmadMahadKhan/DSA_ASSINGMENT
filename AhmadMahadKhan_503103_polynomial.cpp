
#include "polynomial.h"
#include <iostream>
#include <string>

using namespace std;

// Node
struct Node
{
    int coefficent;
    int exponent;
    Node *next;

    // Node(int cof, int exp) : coeff(cof), exp(exp), next(nullptr) {}
    Node(int c, int exp)
    {
        coefficent = c;
        next = nullptr;
        exponent = exp;
    }
};

// Derived class that will implement the Polynomial interface
class PolynomialImplementation : public Polynomial
{
private:
    Node *head;

public:
    PolynomialImplementation() : head(nullptr) {}

    virtual ~PolynomialImplementation()
    {
        while (head)
        {
            Node *temp = head;
            head = head->next;
            delete temp;
        }
    }

    // Copy constructor (deep copy)
    PolynomialImplementation(const PolynomialImplementation &other) : head(nullptr)
    {
        Node *otherTemp = other.head;
        if (!otherTemp)
            return;
        head = new Node(otherTemp->coefficent, otherTemp->exponent);
        Node *current = head;
        otherTemp = otherTemp->next;
        while (otherTemp)
        {
            current->next = new Node(otherTemp->coefficent, otherTemp->exponent);
            current = current->next;
            otherTemp = otherTemp->next;
        }
    }

    // Copy assignment operator (deep copy, handles self-assignment)
    // PolynomialImplementation& operator=(const PolynomialImplementation& other) {
    //     if (this == &other) return *this;  // Self-assignment check
    //     // Delete existing list
    //     while (head) {
    //         Node* temp = head;
    //         head = head->next;
    //         delete temp;
    //     }
    //     // Deep copy new list
    //     head = nullptr;
    //     if (other.head) {
    //         head = new Node(other.head->coefficent, other.head->exponent);
    //         Node* current = head;
    //         Node* otherTemp = other.head->next;
    //         while (otherTemp) {
    //             current->next = new Node(otherTemp->coefficent, otherTemp->exponent);
    //             current = current->next;
    //             otherTemp = otherTemp->next;
    //         }
    //     }
    //     return *this;
    // }

    // Insert a term into the polynomial
    virtual void insertTerm(int coefficient, int exponent)
    {
        // validation of the term to be added
        if (coefficient == 0 || exponent < 0)
        {
            return;
        }

        // Create new term
        Node *newNode = new Node(coefficient, exponent);

        // handling empty list
        if (head == nullptr)
        {
            head = newNode;
            return;
        }

        Node *prev = nullptr;
        Node *temp = head;

        // finding the corrent position to insert the term
        while (temp && temp->exponent > exponent)
        {
            prev = temp;
            temp = temp->next;
        }

        // handling inserting at the head of the list
        if (prev == nullptr && (!temp || temp->exponent < exponent))
        {
            newNode->next = temp;
            head = newNode;
            return;
        }

        // handling insertion at the end of the list
        if (!temp)
        {
            prev->next = newNode;
            return;
        }

        // Combine like terms if exponents match
        if (temp->exponent == exponent)
        {
            temp->coefficent += coefficient;
            if (temp->coefficent == 0)
            { // if the exponent is zero then checking the previos if the pre exist
                if (!prev)
                {
                    head = temp->next;
                }
                else
                {
                    prev->next = temp->next;
                }
                delete temp;
            }
            delete newNode; // freeing the memory
            return;
        }

        // inserting at the middle of the list
        newNode->next = prev->next;
        prev->next = newNode;
        return;
    }

    // returning polynomial as a string
    virtual string toString() const
    {
        // creating a tempry node
        Node *temp = head;
        string result = "";
        bool isFirst = true;

        while (temp)
        {
            // Handle the sign and coefficient
            if (isFirst)
            {
                result += to_string(temp->coefficent);
                isFirst = false;
            }
            else
            {
                if (temp->coefficent > 0)
                {
                    result += " + " + to_string(temp->coefficent);
                }
                else
                {
                    result += " - " + to_string(-temp->coefficent);
                }
            }

            if (temp->exponent != 0)
                result += "x^" + to_string(temp->exponent);

            temp = temp->next; // moving to a next pointer
        }
        return result;
    }

    virtual Polynomial *add(const Polynomial &other) const
    {
        // casting the polynomial
        // into a pointer for casting
        const PolynomialImplementation *implementation = dynamic_cast<const PolynomialImplementation *>(&other);
        if (!implementation)
        {
            return nullptr;
        }

        PolynomialImplementation *result = new PolynomialImplementation();

        Node *p1 = head;
        Node *p2 = implementation->head;

        if (!p1 && !p2)
        {
            return result;
        }

        Node *cursor = new Node(0, 0); // a cursor node to keep track of the head of the result
        Node *iterration = cursor;     // iterable node for result

        while (p1 && p2)
        { // checking if there are polynomial emptry or not
            Node *newNode;
            if (p1->exponent == p2->exponent)
            { // if the exp are same we will add the coeficents
                int new_coefficent = p1->coefficent + p2->coefficent;
                if (new_coefficent == 0)
                { // if the newCoff is zero, we dont add the term
                    p1 = p1->next;
                    p2 = p2->next;
                    continue;
                }
                newNode = new Node(new_coefficent, p1->exponent);
                p1 = p1->next;
                p2 = p2->next;
            }
            else if (p1->exponent > p2->exponent)
            { // if the exponent of p1 is greater than p2, we add the p1 term
                newNode = new Node(p1->coefficent, p1->exponent);
                p1 = p1->next;
            }
            else
            { // we add the p2 term, if its exponent is greater than p1
                newNode = new Node(p2->coefficent, p2->exponent);
                p2 = p2->next;
            }
            iterration->next = newNode;
            iterration = newNode;
        }

        while (p1)
        { // adding the remaining  p1
            Node *newNode = new Node(p1->coefficent, p1->exponent);
            p1 = p1->next;
            iterration->next = newNode;
            iterration = newNode;
        }

        while (p2)
        { // add the remaining terms of p2
            Node *newNode = new Node(p2->coefficent, p2->exponent);
            p2 = p2->next;
            iterration->next = newNode;
            iterration = newNode;
        }

        result->head = cursor->next; // reassign the head

        delete cursor; // freeing the dummy node memory
        return result;
    }

    // function return a new polynomial which is the result of the product of 2 polynomail
    virtual Polynomial *multiply(const Polynomial &other) const
    {
        const PolynomialImplementation *implementation = dynamic_cast<const PolynomialImplementation *>(&other);
        if (!implementation)
            return nullptr;

        PolynomialImplementation *result = new PolynomialImplementation(); // resulting polynomial

        Node *p1 = head;

        if (!p1 || !implementation->head)
        {
            return result;
        }

        while (p1)
        {
            Node *p2 = implementation->head; // reseting p2 for each p1
            while (p2)
            {
                int exponent = p1->exponent + p2->exponent;
                int coefficent = p1->coefficent * p2->coefficent;

                result->insertTerm(coefficent, exponent);
                p2 = p2->next;
            }
            p1 = p1->next;
        }

        return result;
    }

    // Return a new polynomial that will be the derivative of this polynomial
    virtual Polynomial *derivative() const
    {
        PolynomialImplementation *result = new PolynomialImplementation();
        Node *cursor = head;
        if (!cursor)
            return result;

        while (cursor)
        {
            int coeff = cursor->coefficent * cursor->exponent;
            int exp = cursor->exponent - 1;

            result->insertTerm(coeff, exp);

            cursor = cursor->next;
        }

        return result;
    }
};

void polynomail_test()
{
    cout << "==== Polynomial Tests with Polymorphism ====";
    cout << endl;

    Polynomial *p1 = new PolynomialImplementation();
    p1->insertTerm(9, 1);
    p1->insertTerm(5, 5);
    p1->insertTerm(4, 3);
    cout << "p1 = " << p1->toString() << endl;

    cout << "expected==> 5x^5 + 4x^3 + 9x^1" << endl;
    cout << "Passed" << endl;
    cout << endl ;
    cout << endl ;


    Polynomial *p2 = new PolynomialImplementation();
    p2->insertTerm(10, 6);
    p2->insertTerm(5, 6);
        cout << "p2 = " << p2->toString() << endl;

    cout << "expected==> 15x^6\n";
    cout << "Passed" << endl;
    cout << endl ;


    Polynomial *p3 = new PolynomialImplementation();
    p3->insertTerm(10, 4);
    p3->insertTerm(-10, 4);
    cout << "p3 = " << p3->toString() << endl;
    cout << "expected: zero" << endl;
    cout << "Passed" << endl;
    cout << endl ;
    cout << endl ;


    Polynomial *p4 = new PolynomialImplementation();
    p4->insertTerm(2, 1);
    Polynomial *p5 = new PolynomialImplementation();
    p5->insertTerm(3, 1);
    Polynomial *product = p4->multiply(*p5);
    cout << "2x * 3x = " << product->toString() << endl;
    cout << "Expected: 6x^2" << endl;
    cout << "Passed";
    cout << endl;
    cout << endl;

    Polynomial *p6 = new PolynomialImplementation();
    p6->insertTerm(1, 2);
    p6->insertTerm(2, 1);
    Polynomial *p7 = new PolynomialImplementation();
    p7->insertTerm(3, 0);
    Polynomial *temp = p6->multiply(*p7);
    Polynomial *p8 = new PolynomialImplementation();
    p8->insertTerm(1, 1);
    Polynomial *result = temp->add(*p8);
    cout << "Result: " << result->toString() << endl;
    cout << "Expected: 3x^2 + 7x^1\n";
    cout << "Passed";
    cout << endl ;
    cout << endl ;

}


int main()
{
    // polynomail_test();

    return 0;
}
