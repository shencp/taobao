#include <iostream>
#include <cmath>
#include <string>

using namespace std;

string decimalToBinString(int a, int bits)
{
    string s;
    for (int i = bits - 1; i >= 0; i--)
    {
        if (a & (1 << i))
        {
            s += "1";
        }
        else
        {
            s += "0";
        }
    }

    return s;
}

string positiveDecimalToTwo(int a)
{
    string str;
    for (int i = a; i > 0;)
    {
        if (i % 2)
        {
            str = str + '1';
        }
        else
        {
            str = str + '0';
        }
        i /= 2;
    }

    return str;
}

string decimalToTwosComplementString(int a, int L)
{
    string strComplement = positiveDecimalToTwo(abs(a));
    string strNegativeComplement="";
    int change_flag = 0;
    int change_start_index;
    if (a < 0)
    {
        for (int i = 0; i < strComplement.length(); i++)
        {

            if (strComplement[i] == '1'&& change_flag==0)
            {
                change_start_index = i;
                change_flag = 1;
            }
            
            if(change_flag)
            {
                if (change_start_index==i)
                {
                    strNegativeComplement += strComplement[i];
                }
                else
                {
                    strNegativeComplement += strComplement[i] == '1' ? '0' : '1';
                }
                
            }
            else
            {
                strNegativeComplement += strComplement[i];
            }
        }

        strComplement = strNegativeComplement;
    }


    int pre_len = strComplement.length();

    if (L > pre_len)
    {
        for (int i = 0; i < (L - pre_len); i++)
        {
            strComplement += '0';
        }
    }

    string strReversal = "";
    for (int i = L-1; i >=0; i--)
    {
        strReversal += strComplement[i];
    }

    if (a < 0&& L > pre_len)
    {
        strReversal[0] = '1';
    }
    
    return strReversal;
}

string twosComplementStringsAddition(string A, string B)
{
    int a = stoi(A, 0, 2);
    int b = stoi(B, 0, 2);
    int c = a + b;

    return decimalToBinString(c, A.length());
}

int twosComplementStringToDecimal(string C)
{
    if (C[0] == '0')
    {
        return stoi(C, 0, 2);
    }
    if (C.length() == 1)
    {
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
    } while (L <= 0);

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