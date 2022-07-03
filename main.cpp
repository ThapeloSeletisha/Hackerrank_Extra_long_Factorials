#include <bits/stdc++.h>
#include <string>
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
    BigInt operator*(BigInt const &that);
    static BigInt factorial(BigInt n);
    operator std::string () const;

};

BigInt::BigInt()
{
    mNumber = "0";
}

BigInt::BigInt(std::string number)
{
    mNumber = number;
}

void extraLongFactorials(int n) {
    BigInt N = BigInt(to_string(n));
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
