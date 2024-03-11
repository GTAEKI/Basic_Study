#include <iostream>
#include <queue>
#include "Queue_t.h"

namespace samples
{
    void StartQueue()
    {
        std::queue<std::string> studentNameQueue;
    	studentNameQueue.push("Coco");
    	studentNameQueue.push("Mocha");

        std::string change = studentNameQueue.front();
        change = "Momo";
        studentNameQueue.front() = "Momo";
    
    	while(!studentNameQueue.empty())
    	{
    		std::cout << "Waiting student: " << studentNameQueue.front() << std::endl;
            //std::cout << change << std::endl;
    		studentNameQueue.pop();
    	}
    }
}