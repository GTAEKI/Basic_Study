#include <iostream>
#include <stack>
#include "Stack_t.h"

namespace samples
{
    void StartStack()
    {
        std::stack<std::string> studentNameStack;
        studentNameStack.push("Coco");
        studentNameStack.push("Mocha");
        
        while(!studentNameStack.empty())
        {
            std::cout << studentNameStack.top() << std::endl;
            studentNameStack.pop();
        }
    }
}