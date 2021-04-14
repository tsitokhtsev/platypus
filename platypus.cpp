/* Platypus class implementation */

#include "platypus.h"
#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

/*
 rand_num()
    Generates random integer between 0 and 100 by default.
    Range can be changed by passing max and min values to function.
*/
int rand_num(const int max = 100, const int min = 0)
{
    srand(time(NULL));
    return min + (rand() % (max - min + 1));
}

/*
 is_dead()
    Prints out that platypus is dead.
    Can notify user about action which didn't happen by passing it to function.
*/
void is_dead(const char name, const string action = "")
{
    name == '-' ? printf("Platypus is dead...") : printf("%c is dead...", name);
    action == "" ? printf("\n\n") : printf(" Can't %s.\n\n", action.c_str());
}

/*
 is_initialized()
    Tells if platypus is initialized or not.
*/
bool is_initialized(const float weight, const char name, const char gender)
{
    return (weight != 0.0 && name != '-' && gender != '-');
}

/* 
 Default constructor
    Creates dead platypus.
*/
Platypus::Platypus()
    : weight{0.0}, age{0}, name{'-'}, gender{'-'}, alive{false}, mutant{false} {}

/*
 Parameterized constructor
    Creates alive platypus which isn't mutated.
    Platypus' gender, weight, age and name must be passed to constuctor.
*/
Platypus::Platypus(float w, short a, char n, char g)
    : weight{w}, age{a}, name{n}, gender{g}, alive{true}, mutant{false} {}

/*
 print()
    Prints out info about platypus if it's alive.
*/
void Platypus::print() const
{
    if (!alive)
    {
        is_dead(name);
        return;
    }

    printf("Platypus %c\n", name);
    cout << setw(20) << setfill('-') << "-" << setfill(' ') << endl;
    printf("Weight:\t%g kg\n", weight);
    printf("Age:\t%d month old\n", age);
    gender == 'm' ? printf("Gender:\tMale\n") : printf("Gender:\tFemale\n");
    mutant ? printf("Mutant:\tYes\n\n") : printf("Mutant:\tNo\n\n");
}

/*
 age_me()
    Ages platypus for one month.
    There's a 2% chance that platypus can become a mutant
    and a chance to die which is equal to platypus' weight multiplied by 10.
*/
void Platypus::age_me()
{
    if (!alive)
    {
        is_dead(name, "age");
        return;
    }

    if (rand_num() <= weight * 10.0)
    {
        alive = false;
        printf("%c was obese and died...\n\n", name);
        return;
    }
    
    if (rand_num() < 2)
    {
        mutant = true;
        printf("%c mutated. We all change as we grow up...\n", name);
    }

    age++;
    printf("Now %c is %d month(s) old.\n\n", name, age);
}

/*
 fight()
    By passing other platypus to this function they can fight.
    Defeated platypus dies. Winner loses 10% of its weight.
*/
void Platypus::fight(Platypus &enemy)
{
    if (!this->alive)
    {
        is_dead(this->name, "fight");
        return;
    }
    else if (!enemy.alive)
    {
        is_dead(enemy.name, "fight");
        return;
    }

    const float fight_ratio = this->weight / enemy.weight * 50.0;
    Platypus *winner, *loser;

    if (fight_ratio > rand_num())
    {
        winner = this;
        loser = &enemy;
    }
    else
    {
        winner = &enemy;
        loser = this;
    }

    winner->weight -= round(winner->weight * 0.1 * 1000) / 1000;
    loser->alive = false;

    printf("Platypus %c VS Platypus %c\n", this->name, enemy.name);
    printf("%c has won! %c is dead!\n\n", winner->name, loser->name);
}

/*
 eat()
    Increases platypus' weight by 0.1-5% of its weight randomly.
*/
void Platypus::eat()
{
    if (!alive)
    {
        is_dead(name, "eat");
        return;
    }

    weight = round(weight * (1 + rand_num(50, 1) / 1000.) * 1000) / 1000;
    printf("%c ate some food.\n", name);
    printf("Now %c is %g kg.\n\n", name, weight);
}

/*
 hatch()
    Female platypus can give birth to new one if she is not a mutant.
    New platypus will have no mutations, its weight can be between 0.1-1 kilograms,
    age will be 0 month and gender can be male or female with equal probability.
    User can change new platypus' initial (name) or computer will choose it randomly.
    If parent doesn't match requirements, function will return default constructor.
*/
Platypus Platypus::hatch()
{
    if (!alive)
    {
        is_dead(name, "hatch");
        return Platypus();
    }
    else if (gender == 'm')
    {
        printf("%c is a male platypus. Can't hatch.\n\n", name);
        return Platypus();
    }
    else if (mutant)
    {
        printf("%c is a mutant. Can't hatch.\n\n", name);
        return Platypus();
    }

    float new_weight = rand_num(10, 1) / 10.0;
    short new_age = 0;
    char new_name;
    char new_gender = rand_num() < 50 ? 'm' : 'f';

    while (true)
    {
        printf("Enter your platypus' initial using capital letter\n");
        printf("or type '.' to let computer choose it: ");
        cin >> new_name;
        cin.clear();                                         // clears input
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ignores the rest of characters

        if (new_name == '.')
        {
            srand(time(NULL));
            new_name = 'A' + rand_num(25);
        }

        if (new_name < 'A' && new_name > 'Z')
        {
            printf("\nInput doesn't match requirements. Try again.\n\n");
            continue;
        }

        printf("\n");
        break;
    }

    return Platypus(new_weight, new_age, new_name, new_gender);
}

/* Getters */
float Platypus::get_weight() const { return weight; }
short Platypus::get_age() const { return age; }
char Platypus::get_name() const { return name; }
char Platypus::get_gender() const { return gender; }
bool Platypus::get_alive() const { return alive; }
bool Platypus::get_mutant() const { return mutant; }

/* Setters */
void Platypus::set_weight(float new_weight)
{
    if (!alive && is_initialized(weight, name, gender))
    {
        is_dead(name, "set new weight");
        return;
    }

    if (new_weight > 0)
    {
        printf("You've set %c's weight to %g.\n\n", name, new_weight);
        weight = new_weight;
    }
    else
        printf("Can't set new weight. Weight must be positive.\n\n");
}

void Platypus::set_age(short new_age)
{
    if (!alive && is_initialized(weight, name, gender))
    {
        is_dead(name, "set new age");
        return;
    }

    if (new_age >= 0)
    {
        printf("You've set %c's age to %d.\n\n", name, new_age);
        age = new_age;
    }
    else
        printf("Can't set new age. Age can't be negative.\n\n");
}

void Platypus::set_name(char new_name)
{
    if (!alive && is_initialized(weight, name, gender))
    {
        is_dead(name, "set new name");
        return;
    }

    if (new_name >= 'A' && new_name <= 'Z')
    {
        printf("You've set %c's name to %c.\n\n", name, new_name);
        name = new_name;
    }
    else
        printf("Can't set new name. Name must be a capital letter.\n\n");
}

void Platypus::set_gender(char new_gender)
{
    if (!alive && is_initialized(weight, name, gender))
    {
        is_dead(name, "set new gender");
        return;
    }

    if (new_gender == 'm' || new_gender == 'f')
    {
        new_gender == 'm' ? printf("You've set %c's gender to male.\n\n", name) : printf("You've set %c's gender to female.\n\n", name);
        gender = new_gender;
    }
    else
        printf("Can't set new gender. It must be 'm' or 'f'.\n\n");
}

void Platypus::set_alive(bool new_alive)
{
    if (!alive && new_alive)
    {
        alive = new_alive;
        printf("Yay! You've brought %c to life.\n\n", name);
    }
    else if (alive && !new_alive)
    {
        alive = new_alive;
        printf("You've killed %c...\n\n", name);
    }
}

void Platypus::set_mutant(bool new_mutant)
{
    if (!alive && is_initialized(weight, name, gender))
    {
        is_dead(name, "make mutant");
        return;
    }

    if (!mutant && new_mutant)
    {
        mutant = new_mutant;
        printf("You've made %c mutant.\n\n", name);
    }
    else if (mutant && !new_mutant)
    {
        mutant = new_mutant;
        printf("You've cured %c's mutation.\n\n", name);
    }
}