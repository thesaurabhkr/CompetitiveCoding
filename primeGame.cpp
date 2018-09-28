//Hourstorm #3 
//(Problem B) Prime Game 

#include<bits/stdc++.h>
using namespace std;

long long int mulmod(long long int a, long long int b, long long int mod)
{
    long long int x = 0,y = a % mod;
    while (b > 0)
    {
        if (b % 2 == 1)
        {    
            x = (x + y) % mod;
        }
        y = (y * 2) % mod;
        b /= 2;
    }
    return x % mod;
}

long long int power(long long int base, long long int exponent, long long int mod)
{
    long long int x = 1;
    long long int y = base;
    while (exponent > 0)
    {
        if (exponent % 2 == 1)
            x = mulmod(x, y, mod); 
        y = mulmod(y, y, mod);
        exponent = exponent / 2;
    }
    return x % mod;
}

bool MillerRabin(long long int p,int iteration)
{
    if (p < 2)
    {
        return false;
    }
    if (p != 2 && p % 2==0)
    {
        return false;
    }
    long long int s = p - 1;
    while (s % 2 == 0)
    {
        s /= 2;
    }
    for (int i = 0; i < iteration; i++)
    {
        long long int a = rand() % (p - 1) + 1, temp = s;
        long long int mod = power(a, temp, p);
        if(mod==1 || mod == p-1)
            continue;
        while (temp != p - 1 && mod != 1 && mod != p - 1)
        {
            mod = mulmod(mod, mod, p);
            temp *= 2;
        }
        if (mod != p - 1)return false;  
     }
  
     return true;
}

long long int removeFirstDigit(long long int cur)
{
    long long int mul = 1;
    long long int res = 0;
    long long int tmp = 0;
    while(cur > 0)
    {
        tmp = cur % 10;
        cur = cur /10;
        if(cur > 0)
        {
            res = tmp * mul + res;
            mul = mul*10;
        }
    }
    return res;
}   

int solve(long long int num, int turn)
{
    if(turn == 1)                   //Current move of Alice
    {
        int ans1, ans2;
        long long int res = removeFirstDigit(num);
        int flag = 0;
        if(!MillerRabin(res, 5))
        {
            ans1 = solve(res, 1-turn);
        }
        else
        {
            ans1 = 1-turn;
        }
        if(!MillerRabin(num/10, 5))
        {
            ans2 = solve(num/10, 1-turn);
        }
        else
        {
            ans2 = 1 - turn;
        }
        return ans1|ans2;
    }
    else                            //Current move of Bob
    {
        int ans1, ans2;
        long long int res = removeFirstDigit(num);
        int flag = 0;
        if(!MillerRabin(res, 5))
        {
            ans1 = solve(res, 1-turn);
        }
        else
        {
            ans1 = 1 - turn;
        }
        if(!MillerRabin(num/10, 5))
        {
            ans2 = solve(num/10, 1-turn);
        }
        else
        {
            ans2 = 1 - turn;
        }
        return ans1&ans2;
    }
}

int main()
{
    long long int n, tc;
    cin >> tc;
    while(tc--)
    {
        cin >> n;
        if(solve(n, 1))
        {
            cout << "Alice" << endl;
        }
        else
        {
            cout << "Bob" << endl;
        }
    }
    return 0;
}