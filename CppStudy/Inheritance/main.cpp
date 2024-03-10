#include <iostream>
#include "Cat.h"
#include "Dog.h"

int main() 
{    
    samples::Cat cat(5);
    std::cout << "Cat Age: " << cat.GetAge() << std::endl;
    std::cout << "Cat Purring: " << cat.Purr() << std::endl;
    
    samples::Dog dog(3);
    std::cout << "Dog Age: " << dog.GetAge() << std::endl;
    std::cout << "Dog Barking: " << dog.Bark() << std::endl;

    return 0;
}
