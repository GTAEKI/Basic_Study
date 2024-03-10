#include<iostream>
#include"Cat.h"

using namespace std;

namespace samples
{
    Cat::Cat(int age)
        : Animal(age)
    {

    }

    void Cat::Move() const{
        std::cout << "A cat is moving" << std::endl;
    }

    void Cat::Speak() const
    {
        std::cout << "Meow " << std::endl;
    }

    string Cat::Purr() const
    {
        return string("Purr");
    }
}