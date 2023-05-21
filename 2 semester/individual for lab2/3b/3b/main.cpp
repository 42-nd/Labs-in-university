#include <iostream>
#include <fstream>
#include <queue>
#include <string>
using namespace std;

int main() {
	ifstream fin("test.txt");
	ofstream fout;

	queue <int> digits;
	string s;
	while (getline(fin,s,'\n')) {
		for (int i = 0; s[i] != '\0'; i++) {
			if (((int)s[i] >= 48) && ((int)s[i] <= 57)) {
				digits.push(s[i]-48);
			}
			else {
				cout << s[i];
			}
			
		}
		while (!digits.empty()){
			cout << digits.front();
			digits.pop();
		}
		cout << endl;
	}

	return 0;
}