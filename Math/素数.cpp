//素数相关算法
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e5+10;
int prime[maxn];
bool is_prime[maxn];//->0
int prime_cnt = 0;

//埃式筛
void A_prime(int n)
{
    for(int i=1;i<=n;i++)is_prime[i] = 1;
    is_prime[0] = is_prime[1] = 0;
    for(int i=2;i<=n;i++){
        if(is_prime[i]){
            prime[++prime_cnt] = i;
            for(int j=2*i;j<=n;j+=i)
            {
                is_prime[j] = 0;
            }
        }
    }

}

//Pollard Rho 算法
ll gcd(ll a,ll b)
{
    return (b == 0?a:gcd(b,a%b));
}
ll f(ll x,ll c,ll n)
{
    return (x*x+c)%n;
}
ll Pollard_Rho(ll N) {
  ll c = rand() % (N - 1) + 1;
  ll t = f(0, c, N);
  ll r = f(f(0, c, N), c, N);
  while (t != r) {
    ll d = gcd(abs(t - r), N);
    if (d > 1) return d;
    t = f(t, c, N);
    r = f(f(r, c, N), c, N);
  }
  return N;
}
//因子求法，快速求解1到n区间中每个数的所有因子
vector<int>factor[maxn];
void find_factor(int n)
{
    for(int i=1;i<=n;i++)
        for(int j=i;j<=n;j+=i)
            factor[j].push_back(i);
}
vector<pair<int,int>>ans;

 //整数分解，将任意一个整数n分解为p1^l1*p2^l2*.....pk^lk,其中p1到pk为素数
void divide(int n)
{
    for(int i=2;i<=n/i;i++){
        int cnt=0;
        while(n%i==0){
            n/=i;
            cnt++;
        }
        if(i!=0)ans.push_back(make_pair(i,cnt));
    }
    if(n!=1)ans.push_back(make_pair(n,1));
}

int main()
{
    return 0;
}