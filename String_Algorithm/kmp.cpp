#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e6+10;
char t[maxn];//模式串
char s[maxn];//主串
int nxt[maxn];
int cnt[maxn];
ll sum[maxn];

void kmp(int len)
{
    nxt[1] = 0;//只有一个字符组成的字符串自然border最大长度为0（border即满足字符串真前缀与真后缀相等的前缀组成的字符串）
    //接下来的循环中，i代表实时更新nxt数组的位置，j代表前缀的长度，也即是j+1代表后缀后一位的位置
    for(int i=2,j=0;i<=len;i++){
        while(j&&t[i]!=t[j+1]){
            //如果j还不为零，且s[i]!=s[j+1]，这时候我们就要继续寻找1...j的真前缀与i-j+1...i的真后缀相等的最大长度
            //又因为实际上1...j == i-j+1....i,所以我们只需要寻找1..j自己的最大border长度即可，也即是之前已经求过的nxt[j]
            j = nxt[j];
        }
        if(t[i] == t[j+1])j++;//如果后一位一致，j后移一位
        nxt[i] = j;
    }
}
vector<int>cmp(int s_len,int t_len)
{
    vector<int>res;
    int s_pos = 1;
    int t_pos = 1;
    while(s_pos<=s_len){
        if(s[s_pos] == t[t_pos]){
            s_pos++;
            t_pos++;
        }
        else if(t_pos!=1){
            t_pos = nxt[t_pos-1] + 1;
        }
        else s_pos++;
        if(t_pos == t_len+1){
            res.push_back(s_pos - t_pos+1);
            t_pos = nxt[t_pos-1] + 1;
        }
    }
    return res;
}
void solve()
{
    cin>>(s+1)>>(t+1);
    int s_len = strlen(s+1);
    int t_len = strlen(t+1);
    kmp(t_len);//对模式串t做kmp求得nxt数组
    vector<int>ans = cmp(s_len,t_len);//比较两字符串并按先后顺序返回匹配一致的位置
    for(int i = 0;i<ans.size();i++)cout<<ans[i]<<"\n";
    for(int i = 1;i<=t_len;i++)cout<<nxt[i]<<" ";
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int t =1;
    while(t--){
        solve();
    }
    return 0;
}