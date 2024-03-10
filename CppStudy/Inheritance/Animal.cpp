#include "Animal.h"

namespace samples
{
    Animal::Animal()
    {

    }

    Animal::Animal(int age)
        : mAge(age);
    {

    }

    int Animal::GetAge() const
    {
        return mAge;
    }
}