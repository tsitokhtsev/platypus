/* Platypus class definition */

#pragma once
#include <string>

using namespace std;

class Platypus
{
    /* Fields */
    float weight; // kilograms
    short age;    // months
    char name;    // initial
    char gender;  // male or female
    bool alive;   // alive or dead
    bool mutant;  // mutant or not

public:
    /* Constructors */
    Platypus();
    Platypus(float, short, char, char);

    /* Methods */
    void print() const;
    void age_me();
    void fight(Platypus &);
    void eat();
    Platypus hatch();

    /* Getters */
    float get_weight() const;
    short get_age() const;
    char get_name() const;
    char get_gender() const;
    bool get_alive() const;
    bool get_mutant() const;

    /* Setters */
    void set_weight(float);
    void set_age(short);
    void set_name(char);
    void set_gender(char);
    void set_alive(bool);
    void set_mutant(bool);
};

/* Global functions */
int rand_num(const int, const int);
void is_dead(const char, const string);