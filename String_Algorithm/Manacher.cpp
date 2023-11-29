/*
Manacher算法适用于O(n)复杂度内解决字符串的回文串的求解问题
*/
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e6+10;//字符串长度
int d[maxn];

void Manacher(string tmp)
{
    //首先对字符串s做一些处理使之变为奇数串
    int len = tmp.length();
    tmp = ' '+tmp;
    string s = string(2*len+10,'#');
    for(int i=1;i<=len;i++){
        s[2*i] = tmp[i];
    }
    int l = 0, r = 0;
    for(int i=1;i<=len;i++){
        int j = l+(r-i);
        if(i<r)d[i] = min(d[j],r-i+1);
        while(i-d[i]>=1&&i+d[i]<=len&&s[i-d[i]] == s[i+d[i]])d[i]++;
        if(i + d[i] - 1>r){
            r = i + d[i] - 1;
            l = i - d[i] + 1;
        }
    }
    return;
}
int main()
{
    string s;
    Manacher(s);
    return 0;
}