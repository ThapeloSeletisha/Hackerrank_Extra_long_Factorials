#include <bits/stdc++.h>
#include <string>
#include <vector> 
using namespace std;

string ltrim(const string &);
string rtrim(const string &);

/*
 * Complete the 'extraLongFactorials' function below.
 *
 * The function accepts INTEGER n as parameter.
 */

class BigInt
{
private:
    string mNumber;

public:
    BigInt();
    BigInt(string number);
    BigInt(int number);

    operator std::string() const;

    BigInt operator+(BigInt const &that);
    BigInt operator+(int const &that);

};

BigInt::BigInt()
{
    mNumber = "0";
}

BigInt::BigInt(string number)
{
    reverse(number.begin(), number.end());
    mNumber = number;
}

BigInt::BigInt(int number)
{
    string number_string = to_string(number);
    reverse(number_string.begin(), number_string.end());
    mNumber = number_string;
}

BigInt::operator std::string() const
{
    string number = mNumber;
    reverse(number.begin(), number.end());
    return number;
}

BigInt BigInt::operator+(BigInt const &that)
{
    string num1, num2, remainder = "", final = "";
    num1 = mNumber;
    num2 = string(that);
    reverse(num2.begin(), num2.end());

    int length_1, length_2, next;
    length_1 = num1.size();
    length_2 = num2.size();

    for(int i = 0; i < max(length_1, length_2); i++)
    {
        // remainder, num1 and num2 still have digits
        if (i < min(length_1, length_2) && remainder != "")
        {
            next = num1[i] + num2[i] + remainder[0] - (3 * '0');
        }
        // num1 and num2 still have digits
        else if (i < min(length_1, length_2) && remainder == "")
        {
            next = num1[i] + num2[i] - (2 * '0');
        }
        // remainder and num1 still has digits
        else if (i < length_1 && remainder != "")
        {
            next = num1[i] + remainder[0] - (2 * '0');
        }
        // num1 still has digits
        else if (i < length_1 && remainder == "")
        {
            next = num1[i] - '0';
        }
        // remainder and num2 still has digits
        else if (i < length_2 && remainder != "")
        {
            next = num2[i] + remainder[0] - (2 * '0');
            
        }
        // num2 still has digits
        else if (i < length_2 && remainder == "")
        {
            next = num2[i] - '0';
        }
        final.append(to_string(next%10));
        if (next >= 10)
        {
            remainder = to_string((next - (next%10)) / 10);
        }
        else 
        {
            remainder = "";
        }

    }
    if (remainder != "")
    {
        final.append(remainder);
    }
    reverse(final.begin(), final.end());
    return BigInt(final);
    
}

BigInt BigInt::operator+(int const &that)
{
    return *this + BigInt(that);
}

void extraLongFactorials(int n) {
   
}

int main()
{
    BigInt a, b;
    a = BigInt("548034803948039803");
    b = BigInt("999");

    cout << string(a) << endl;
    cout << string(b) << endl;
    cout << string(a+b) << endl;
    cout << string(a + 999) << endl;
    cout << string(b + 1) << endl;
    return 0;
}

// int main()
// {
//     string n_temp;
//     getline(cin, n_temp);

//     int n = stoi(ltrim(rtrim(n_temp)));

//     extraLongFactorials(n);

//     return 0;
// }

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}
