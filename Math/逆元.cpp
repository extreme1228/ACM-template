//列举求逆元的几种方法
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod = 1e9+7;

//a^k的快速幂
ll quick_power(ll a,ll k)
{
    ll res = 1;
    while(k){
        if(k&1)res = (res*a)%mod;
        a = (a%mod*a)%mod;
        k>>=1;
    }
    return res;
}
//a在模mod下的逆元,利用费马小定理求解，要求mod为素数
ll _inv(ll a)
{
    return quick_power(a,mod - 2);
}
//exgcd求逆元,调用方法：exgcd(a,mod,d,inv_a,tmp);条件gcd(a,mod) = 1
void exgcd(ll a,ll b,ll&d,ll& x,ll& y)
{
    if(b == 0){
        d = 0;
        x = 1;
        y = 0;
    }
    exgcd(b,a%b,d,x,y);
    ll tmp = x;
    x = y;
    y = tmp - a/b*y;
    return;
}

//线性求逆元
const int maxn = 1e6+10;
ll inv[maxn];
void get_inv(int n)
{
    for (int i = 2; i <= n; ++i) {
        inv[i] = (long long)(mod - mod / i) * inv[mod % i] % mod;
    }
}

int main()
{
    return 0;
}