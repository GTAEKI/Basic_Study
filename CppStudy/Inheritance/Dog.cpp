#include<iostream>
#include"Dog.h"

using namespace std;

namespace samples
{
    Dog::Dog(int age)
        : Animal(age)
    {
    }

    void Dog::Move() const
    {
        std::cout << "A dog is moving"<< std::endl;
    }

    void Dog::Speak() const
    {
        std::cout << "Woof " << std::endl;
    }

    string Dog::Bark() const
    {
        return string("BowWow");
    }

}