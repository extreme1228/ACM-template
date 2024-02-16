## gcd
```cpp
//求a和b的最大公约数
ll gcd(ll a,ll b)
{
    return (b == 0?a:gcd(b,a%b));
}
//a和b的最小公倍数
ll lcm(ll a,ll b)
{
    return a*b/gcd(a,b);
}
```
## exgcd
```cpp
//扩展欧几里得定理，可以求出ax+by = gcd(a,b)的具体的x与y的解x0,y0,
//通解,x = x0 + b/gcd(a,b)*k,y = y0 - a/gcd(a,b)*k
//也可以求a在模b意义下的逆元(当且仅当gcd(a,b) == 1时逆元存在)
void exgcd(ll a,ll b,ll&d,ll& x,ll& y)
{
    if(b == 0){
        d = a;
        x = 1;
        y = 0;
        return;
    }
    exgcd(b,a%b,d,x,y);
    ll tmp = x;
    x = y;
    y = tmp - a/b*y;
    return;
}
```
## CRT
```cpp
/*
求解 
x = a1(mod n1)
x = a2(mod n2)
......
x = ak(mod nk)
的解的问题，如果n1,n2...,nk两两互素，则可以直接求出x在模n意义下的唯一解
n = n1*n2*...*nk
x = /sum_{i:1->k}(a[i]*(n/ni)*inv(n/ni,ni))
如果ni不满足两两互素，那么我们需要通过扩展欧几里得定理来求解
*/
//第一种各个n互素的情况
ll quick_power(ll a,ll k,ll mod)
{
    ll res = 1;
    while(k){
        if(k&1)res = (res*a)%mod;
        a = (a*a)%mod;
        k>>=1;
    }
    return res;
}
ll inv(ll a,ll b)
{
    return quick_power(a,b-2,b);
}
ll CRT(vector<ll>a,vector<ll>n,ll mul,ll k)
{
    ll ans = 0;
    for(int i=1;i<=k;i++){
        ans = (ans + a[i]*(mul/n[i])%mul*inv(mul/n[i],n[i]))%mul;
    }
    return ans;
}
```