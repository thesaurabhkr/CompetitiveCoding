//Miller Rabbin 
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

int main()
{  
    int tc;
    scanf("%d", &tc);
    while(tc--)
    {
        int tests = 10;
        long long int num;
        scanf("%lld", &num); 
        if (MillerRabin(num, tests))
            printf("YES\n");
        else printf("NO\n");
    }
    
}

