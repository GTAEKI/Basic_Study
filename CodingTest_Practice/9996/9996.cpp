#include <iostream>
#include <string>
using namespace std;
int main() {
	int n; 
    string s; 
    
    cin >> n;
    cin >> s;
	int index = s.find('*');
	string part1 = s.substr(0, index);
	string part2 = s.substr(index + 1);
    
	while (n--) {
		string cmp = "";
		cin >> cmp;
		if (part1.size() + part2.size() > cmp.size())cout << "NE\n";
		else if (cmp.find(part1) == 0) { 
			string ex = cmp.substr(cmp.size() - (part2.size()));
			if (ex == part2)cout << "DA\n";
			else cout << "NE\n";
		}
		else cout << "NE\n";
	}
}