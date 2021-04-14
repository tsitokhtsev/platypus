#include "platypus.h"
#include <iostream>

using namespace std;

int main()
{
    Platypus p1; // creating obj with default constructor
    p1.age_me(); // won't work, because p1 is not initialized

    /* p1 initialization using setters */
    p1.set_name('G');
    p1.set_weight(2.3);
    p1.set_age(5);
    p1.set_gender('m');
    p1.set_alive(true);
    p1.print();

    short p1_age = p1.get_age();        // getting info from p1
    Platypus p2(4.6, p1_age, 'C', 'f'); // creating obj with parameterized constructor
    p2.print();
    p2.eat();

    Platypus p4 = p1.hatch(); // won't work, because p1 is a male platypus, creates obj with default constructor
    p2.set_mutant(true);
    Platypus p3 = p2.hatch(); // won't work, because p2 is a mutant, creates obj with default constructor

    p1.set_gender('f');
    Platypus p5 = p1.hatch(); // creates obj with parameterized constructor
    p5.print();

    p2.fight(p1);
    p2.print();

    p2.set_alive(false);
}