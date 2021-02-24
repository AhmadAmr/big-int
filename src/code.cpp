#include<iostream>
#include<algorithm>
using namespace std;

class BigInt
{

private:
    string s;
    bool sign = false;

    string Bigsum(string str1, string str2)
    {
        if (str1.size() > str2.size()) swap(str1, str2);

        int carry = 0;
        int n1 = str1.size();
        int n2 = str2.size();
        int diff = n2 - n1;
        string result = "";
        for (int i = n1 - 1;i >= 0;i--)
        {
            int sum = str1[i] - '0' + str2[i + diff] - '0' + carry;
            result.push_back(sum % 10 + '0');
            carry = sum / 10;
        }
        for (int i = diff - 1;i >= 0;i--)
        {
            int sum = str2[i] - '0' + carry;
            result.push_back(sum % 10 + '0');
            carry = sum / 10;
        }
        if (carry) result.push_back(carry + '0');
        reverse(result.begin(), result.end());
        s = result;
        return s;
    }
    bool isSmaller(string str1, string str2)
    {
        // Calculate lengths of both string
        int n1 = str1.length(), n2 = str2.length();

        if (n1 < n2)
            return true;
        if (n2 < n1)
            return false;

        for (int i = 0; i < n1; i++)
            if (str1[i] < str2[i])
                return true;
            else if (str1[i] > str2[i])
                return false;

        return false;
    }
    string Bigsub( string str1,  string str2)
    {
        bool neg = 0;
        if (isSmaller(str2, str1)) swap(str1, str2), neg = 1;

        int carry = 0;
        int n1 = str1.size();
        int n2 = str2.size();
        int diff = n2 - n1;
        string result = "";
        for (int i = n1 - 1;i >= 0;i--)
        {
            int sub = (str2[i + diff] - '0') - (str1[i] - '0') - carry;

            if (sub < 0) sub += 10, carry = 1;

            else
                carry = 0;

            result.push_back(sub + '0');
        }
        for (int i = diff - 1;i >= 0;i--)
        {
            if (str2[i] == '0' && carry) {
                result.push_back('9');
                continue;
            }
            int sub = (str2[i] - '0') - carry;
            if (i > 0 || sub > 0)
                result.push_back(sub + '0');
            carry = 0;
        }

        reverse(result.begin(), result.end());
        s = result;
        return s;
    }
    string multiply(string str1, string str2) {
        if (str2.size() == 1 && str2[0] == '0') return "0";
        if (str1.size() == 1 && str1[0] == '0') return "0";

        // let num1 be the longer one
        if (str1.size() < str2.size()) {
            swap(str1, str2);
        }
        string result = "";

        int N(str1.size()), n(str2.size());
        int carry(0), sum(0);
        int jMax(0), jMin(0);

        for (int i = 0; i < N + n - 1; ++i) {
            sum = carry % 10;
            carry /= 10;
            jMax = min(i, n - 1);
            jMin = max(0, i + 1 - N);
            for (int j = jMin; j <= jMax; ++j) {
                int l = str1[N - 1 - (i - j)] - '0';
                int r = str2[n - 1 - j] - '0';
                sum += (l * r);
            }
            carry += (sum / 10);
            result.push_back((sum % 10) + '0');
        }
        while (carry != 0) {
            result.push_back((carry % 10) + '0');
            carry /= 10;
        }
        reverse(result.begin(), result.end());
        s = result;
        return s;
    }

public:


    void Reverse()
    {

        std::reverse(s.begin(), s.end());
        s.erase(0, s.find_first_not_of('0'));

    }
    void Sort()
    {
        sort(s.begin(), s.end());
    }

    BigInt  operator + (const BigInt& obj)
    {
        BigInt temp;
        if (obj.sign == false && this->sign)
        {
            if (isSmaller(obj.s, s)) temp.sign = true;
            temp.s = Bigsub(s, obj.s); // -(a) + b = b-a  , a +(-b) = a-b

        }
        else if (obj.sign && this->sign == false)
        {
            if (isSmaller(s, obj.s)) temp.sign = true;
            temp.s = Bigsub(s, obj.s); // -(a) + b = b-a  , a +(-b) = a-b
        }
        else if (obj.sign && this->sign)
        {
            temp.sign = true;
            temp.s = Bigsum(s, obj.s);
        }
        else temp.s = Bigsum(s, obj.s);
        return temp;

    }
    BigInt operator - (const BigInt& obj)
    {
        BigInt temp;

        if (obj.sign && this->sign == false) {
            temp.s = Bigsum(s, obj.s); // (a) - (-b) = (a + b)
            //if (isSmaller(obj.s, s)) temp.sign = true;
        }
        else if (this->sign && obj.sign == false)
        {
            temp.s = Bigsum(s, obj.s); // -(a) - b = -(a + b)
            temp.sign = true;
        }
        else if (this->sign && obj.sign) {  // (-a)-(-b) =b-a
            if (isSmaller(obj.s, s))temp.sign = true;
            temp.s = Bigsub(s, obj.s);
        }
        else {
            if (isSmaller(s, obj.s)) temp.sign = true;
            temp.s = Bigsub(s, obj.s);
        }
        return temp;
    }
    BigInt operator * (const BigInt& obj)
    {
        BigInt temp;
        if ((sign || obj.sign) && (!sign || !obj.sign))temp.sign = true;
        temp.s = multiply(s, obj.s);
        return temp;
    }
    // print class  object using cout
    friend ostream& operator << (  ostream& Str,  const BigInt& v)
    {
        if (v.s == "") return Str<< 0;
        if (v.sign) cout << "-";
        return  Str << v.s;

    }
    // cin class object
    friend istream& operator >> (istream& in, BigInt& t)
    {

        in >> t.s;
       // check if string is negative
        if (t.s[0] == '-') {
            t.sign = true;
            t.s.erase(0, 1);       // remove the negative sign
        }
        t.s.erase(0, t.s.find_first_not_of('0')); // Handel leading zeros
        return in;
    }
};
