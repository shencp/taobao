#include <iostream>
#include <cmath>
#include <string>

using namespace std;

string decimalToBinString(int a, int bits) {
	string s;
    for (int i = bits - 1; i >= 0; i--) {
    	if (a & (1 << i)) {
    		s += "1";
    	} else {
    		s += "0";
    	}
    }

	return s;
}

string decimalToTwosComplementString(int a, int L) {
	int mask = pow(2, (L - 1));
    int c = -(a & mask) + (a & ~mask);

    return decimalToBinString(c, L);
}

string twosComplementStringsAddition(string A, string B) {
	int a = stoi(A, 0, 2);
	int b = stoi(B, 0, 2);
	int c = a + b;

	return decimalToBinString(c, A.length());
}

int twosComplementStringToDecimal(string C) {
	if (C[0] == '0') {
		return stoi(C, 0, 2);
	}
	if (C.length() == 1) {
		return -1;
	}

	string D = C.substr(1, C.length() - 1);
	int d = stoi(D, 0, 2);
	int c = -1 * pow(2, C.length() - 1) + d;

	return c;
}

int main()
{
	//Read in the bit pattern size
	int L;
	do
	{
		cout << "Enter positive integer for the bit pattern size ";
		cin >> L;
	}while (L <= 0);

	//Read in two integers a and b 
	int a, b;
	cout << "Enter an integer a ";
	cin >> a;
	cout << "Enter an integer b ";
	cin >> b;

	//Calculate the decimal arithmetic sum of a and b and print the result
	int c1 = a + b;
	cout << "In decimal " << a << " + " << b << " is " << c1 << endl;

	//Compute the two's complement representations of a and b
	//Each integer must be represented in L-bits pattern
	//Also these two's complement representations must be returned as string data types
	string A = decimalToTwosComplementString(a, L);
	string B = decimalToTwosComplementString(b, L);

	//Print the two's complement representations of a and b
	cout << "The two's complement of " << a << " is\t " << A << endl;
	cout << "The two's complement of " << b << " is\t " << B << endl;

	//Compute the binary sum of the two's complement representations of a and b
	//The result must be returned as L-bit pattern string data type
	string C = twosComplementStringsAddition(A, B);

	//Print the two's complement representation binary sum
	cout << "The binary sum of " << A << " and " << B << " is " << C << endl;

	//Convert the two's complement representation binary sum to decimal and print
	int c2 = twosComplementStringToDecimal(C);
	cout << "In two's complement arithmetic, " << a << " + " << b << " is " << c2 << endl;

	//Print some concluding results
	if (c1 == c2)
		cout << c1 << " is equal to " << c2 << ". Good Job!" << endl;
	else
	{
		cout << c1 << " is not equal to " << c2 << endl;
		cout << "Either " << c1 << " cannot be represented by the given bit pattern OR we have made a mistake!" << endl;
	}
	system("Pause");
	return 0;
}