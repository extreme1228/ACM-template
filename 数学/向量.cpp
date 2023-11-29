#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Vector{
    ll x,y,z;
    bool two_dimension;
    bool three_dimension;
    Vector(){
        x = y = z = 0;
        two_dimension = false;
        three_dimension = false;
    }
    Vector(ll rhs_x,ll rhs_y)
    {
        two_dimension = true;
        three_dimension = false;
        x = rhs_x;
        y = rhs_y;
    }
    Vector(ll rhs_x,ll rhs_y,ll rhs_z)
    {
        three_dimension = true;
        two_dimension = false;
        x = rhs_x;
        y = rhs_y;
        z = rhs_z;
    }
    ll dot_product(const Vector&rhs)
    {
        //this 点乘 rhs
        ll ans  = -1;
        if(two_dimension){
            ans = x*rhs.x + y*rhs.y;
        }
        if(three_dimension){
            ans = x*rhs.x + y*rhs.y + z*rhs.z;
        }
        return ans;
    }
    ll cross_product(const Vector&rhs)
    {
        //this 叉乘 rhs
        ll ans = -1;
        if(two_dimension){
            ans = x*rhs.y - rhs.x*y;
        }
        if(three_dimension){
            ans = (y*rhs.z - z*rhs.y) - (x*rhs.z - z*rhs.x) + (x*rhs.y - y*rhs.x);
        }
        return ans;
    }
};