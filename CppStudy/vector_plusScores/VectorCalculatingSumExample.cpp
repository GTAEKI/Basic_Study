#include<iostream>
#include<vector>
#include "VectorCalculatingSumExample.h"

using namespace std;

namespace samples
{
    int CalculateSum(const vector<int>& scores)
    {
        int sum = 0;
        for(size_t i = 0; i < scores.size(); i++)
        {
            sum += scores[i];
        }
        return sum;
    }

    void VectorCalculatingSumExample()
    {
        vector<int> myScores;
        myScores.reserve(3);

        vector<int> yourScores;
        yourScores.reserve(3);

        myScores.push_back(1);
        myScores.push_back(3);
        myScores.push_back(5);

        yourScores.push_back(2);
        yourScores.push_back(4);
        yourScores.push_back(6);

        yourScores.clear();

        cout << "myScores" << endl;
        cout << "Sum : " << CalculateSum(myScores) << endl << endl;
        
        cout << "yourScores" << endl;
        cout << "Sum : " << CalculateSum(yourScores) << endl << endl;

    }
}