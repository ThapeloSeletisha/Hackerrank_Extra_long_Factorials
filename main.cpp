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

class ComparisonException : public exception
{
private:
    string mMessage;

public:
    explicit ComparisonException(const std::string& message)
        : mMessage(message){}
    const char* what() const noexcept override {
        return mMessage.c_str();
    }
};

class BigInt
{
private:
    string mNumber;

public:
    BigInt();
    BigInt(string number);
    BigInt(int number);

    operator std::string() const;

    bool operator<(BigInt const &that);
    bool operator<(int const &that);

    bool operator>(BigInt const &that);
    bool operator>(int const &that);

    bool operator==(BigInt const &that);
    bool operator==(int const &that);

    bool operator!=(BigInt const &that);
    bool operator!=(int const &that);

    bool operator<=(BigInt const &that);
    bool operator<=(int const &that);

    bool operator>=(BigInt const &that);
    bool operator>=(int const &that);

    BigInt operator+(BigInt const &that);
    BigInt operator+(int const &that);

    BigInt operator-(BigInt const &that);
    BigInt operator-(int const &that);

    BigInt operator*(BigInt const &that);
    BigInt operator*(int const &that);

    static BigInt factorial(BigInt &n);

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

bool BigInt::operator<(BigInt const &that)
{
    string num1, num2;
    num1 = mNumber;
    num2 = string(that);
    reverse(num2.begin(), num2.end());

    int length_1, length_2, next;
    length_1 = num1.size();
    length_2 = num2.size();

    if (num1[length_1 - 1] != '-' && num2[length_2 - 1] != '-')
    {
        if (length_1 < length_2)
        {
            return true;
        }
        else if (length_1 == length_2)
        {
            int last_digit_1 = num1[0];
            int last_digit_2 = num2[0];
            return last_digit_1 < last_digit_2;
        }
        else 
        {
            return false;
        }
    }
    else if (num1[length_1 - 1] == '-' && num2[length_2 - 1] != '-')
    {
        return true;
    }
    else if (num1[length_1 - 1] != '-' && num2[length_2 - 1] == '-')
    {
        return false;
    }
    else if (num1[length_1 - 1] == '-' && num2[length_2 - 1] == '-')  
    {
        if (length_1 < length_2)
        {
            return false;
        }
        else if (length_1 == length_2)
        {
            int last_digit_1 = num1[0];
            int last_digit_2 = num2[0];
            return last_digit_1 > last_digit_2;
        }
        else 
        {
            return true;
        }
    }  
    throw ComparisonException("Reached end of comparison function");
    return false;
}

bool BigInt::operator<(int const &that)
{
    return *this < BigInt(that);
}

bool BigInt::operator>(BigInt const &that)
{
    BigInt negativeThis, negativeThat;
    if (string(*this)[0] != '-' && string(that)[0] != '-')
    {
        negativeThis = BigInt("-" + string(*this));
        negativeThat = BigInt("-" + string(that));
    }
    else if (string(*this)[0] == '-' && string(that)[0] != '-')
    {
        negativeThis = BigInt(string(*this).substr(1));
        negativeThat = BigInt("-" + string(that));
    }
    else if (string(*this)[0] != '-' && string(that)[0] == '-')
    {
        negativeThis = BigInt("-" + string(*this));
        negativeThat = BigInt(string(that).substr(1));
    }
    else if (string(*this)[0] == '-' && string(that)[0] == '-')
    {
        negativeThis = BigInt(string(*this).substr(1));
        negativeThat = BigInt(string(that).substr(1));
    }

    return negativeThis < negativeThat;
    
}

bool BigInt::operator>(int const &that)
{
    return *this > BigInt(that);
}

bool BigInt::operator==(BigInt const &that)
{
    string thisString = string(*this);
    string thatString = string(that);
    return thisString == thatString;
}

bool BigInt::operator==(int const &that)
{
    return *this == BigInt(that);
}

bool BigInt::operator!=(BigInt const &that)
{
    return !((*this) == that);
}

bool BigInt::operator!=(int const &that)
{
    return (*this) != BigInt(that);
}

bool BigInt::operator<=(BigInt const &that)
{
    return ((*this) == that) ||
        ((*this) < that);
}

bool BigInt::operator<=(int const &that)
{
    return (*this) <= BigInt(that);
}

bool BigInt::operator>=(BigInt const &that)
{
    return ((*this) > that) ||
        ((*this) == that);
}

bool BigInt::operator>=(int const &that)
{
    return (*this) <= BigInt(that);
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

BigInt BigInt::operator-(BigInt const &that)
{
    string num1, num2, remainder = "0", final = "";
    num1 = mNumber;
    num2 = string(that);
    reverse(num2.begin(), num2.end());

    int length_1, length_2, next;
    length_1 = num1.size();
    length_2 = num2.size();

    if (num1 == num2)
    {
        return BigInt(0);
    }
    if (num1[length_1 - 1] != '-' && num2[length_2 -1] != '-')
    {
        string sign = "";
        if (*this < that)
        {
            sign = "-";
            string tmpString = num1;
            int tmpInt = length_1;
            num1 = num2;
            length_1 = length_2;
            num2 = tmpString;
            length_2 = tmpInt;
        }
        for (int i = 0; i < length_1; i++)
        {
            if (i < length_2)
            {
                next = num1[i] - remainder[0] - num2[i] + '0';
            }
            else 
            {
                next = num1[i] - remainder[0];
            }
            
            if (next < -10)
            {
                remainder = "2";
                next += 20;
            }
            else if (next < 0)
            {
                remainder = "1";
                next += 10;
            }
            else 
            {
                remainder = "0";
            }
            final.append(to_string(next));
        }
        final.append(sign);
    }
    else if (num1[length_1 - 1] == '-' && num2[length_2 -1] != '-')
    {
        reverse(num1.begin(), num1.end());
        reverse(num2.begin(), num2.end());
        BigInt positiveFinal = BigInt(num1.substr(1)) + BigInt(num2);
        reverse(num1.begin(), num1.end());
        reverse(num2.begin(), num2.end());

        final = "-" + string(positiveFinal);

        reverse(final.begin(), final.end());


    }
    else if (num1[length_1 - 1] != '-' && num2[length_2 -1] == '-')
    {
        reverse(num1.begin(), num1.end());
        reverse(num2.begin(), num2.end());
        BigInt positiveFinal = BigInt(num1) + BigInt(num2.substr(1));
        reverse(num1.begin(), num1.end());
        reverse(num2.begin(), num2.end());

        final = string(positiveFinal);

        reverse(final.begin(), final.end());
    }
    else 
    {
        reverse(num1.begin(), num1.end());
        reverse(num2.begin(), num2.end());

        return BigInt(num2.substr(1)) - BigInt(num1.substr(1));
    }

    reverse(final.begin(), final.end());
    if (final.size() >= 2)
    {
        if (final[0] == '0')
        {
            final = final.substr(1);
        }
        else if (final.size() >= 3)
        {
            if (final.substr(0, 2) == "-0")
            {
                final = "-" + final.substr(2);
            }
        }
    }
    return BigInt(final);
}

BigInt BigInt::operator-(int const &that)
{
    return (*this) - BigInt(that);
}

BigInt BigInt::operator*(BigInt const &that)
{
    string num1, num2, sign, prod;
    BigInt final = BigInt(0);
    num1 = mNumber;
    num2 = string(that);
    reverse(num2.begin(), num2.end());

    int length_1, length_2, next;
    length_1 = num1.size();
    length_2 = num2.size();

    if (num1[length_1 - 1] == '-' && num2[length_2 - 1] == '-')
    {
        sign = "";
        num1 = num1.substr(0, length_1 - 1);
        num2 = num2.substr(0, length_2 - 1);
        length_1--;
        length_2--;
    }
    else if (num1[length_1 - 1] == '-' && num2[length_2 - 1] != '-')
    {
        sign = "-";
        num1 = num1.substr(0, length_1 - 1);
        length_1--;
    }
    else if (num1[length_1 - 1] != '-' && num2[length_2 - 1] == '-')
    {
        sign = "-";
        num2 = num2.substr(0, length_2 - 1);
        length_2--;
    }
    else
    {
        sign = "";
    }

    for (int i = 0; i < length_1; i++)
    {
        for (int j = 0; j < length_2; j++)
        {
            next = (num1[i] - '0') * 
                (num2[j] - '0');
            prod = to_string(next);
            for (int k = 0; k < i + j; k++)
            {
                prod += "0";
            }
            final = final + BigInt(prod);
        }
    }

    if (sign == "-")
    {
        final = final - final - final;
    }
    return final;
    
}

BigInt BigInt::operator*(int const &that)
{
    return (*this) * BigInt(that);
}

BigInt BigInt::factorial(BigInt &n)
{
    if (n == BigInt(1) || n == BigInt(0))
    {
        return BigInt(1);
    }
    BigInt nMinus1 = n - BigInt(1);
    return n * BigInt::factorial(nMinus1);
}

void extraLongFactorials(int n) {
   BigInt N = BigInt(n);
   BigInt fact = BigInt::factorial(N);

   cout << string(fact) << endl;
}

int main()
{
    string n_temp;
    getline(cin, n_temp);

    int n = stoi(ltrim(rtrim(n_temp)));

    extraLongFactorials(n);

    return 0;
}

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
