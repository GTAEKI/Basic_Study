#pragma once

#include<string>
#include"Animal.h" // 상속받기 위해서 컴파일러가 Animal이 뭔지 알고 있어야 함

namespace samples
{
    class Dog : public Animal
    {
        public:
        Dog(int age);
        std::string Bark() const;
    };
}