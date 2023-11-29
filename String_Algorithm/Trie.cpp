#include<bits/stdc++.h>
using namespace std;

const int maxn = 1e6+10;
int cnt = 0;
struct NODE{
    int child[30];
    //这里仅仅定义了子节点，可以根据题目的要求选择增加定义字典树节点的变量类型
    int num;//这里的变量是根据题意而改变的字典树节点上的值
}trie[maxn];
void insert(string s,int val)
{
    int rt = 0;
    int len = s.length();
    int tmp_val = 0;
    for(int i=0;i<len;i++){
        if(i>=val)tmp_val = 1;
        else tmp_val = 0;
        int x = s[i] - 'a' + 1;
        if(trie[rt].child[x] == 0){
            int new_id = ++cnt;
            trie[rt].child[x] = new_id;
            trie[new_id].num = tmp_val;
        }
        else{
            int new_id = trie[rt].child[x];
            trie[new_id].num+=tmp_val;
        }
        //这里也可以根据具体题目需求来添加相应的语句。
        rt = trie[rt].child[x];
    }
}
//这里的find函数返回0代表没找到，其余返回值以具体题意为准
int find(string s)
{
    int rt = 0;
    int len = s.length();
    for(int i=0;i<len;i++){
        int x = s[i] - 'a' + 1;
        if(trie[rt].child[x] == 0)return 0;
        else{
            rt = trie[rt].child[x];
        }
    }
    return trie[rt].num;
}