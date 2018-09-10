/*
    use 2-sat algorithm, if i-th character is vowel then node 2*i is true and node 2*i+1 is false and vice versa, 
    since there are 400 nodes , we can use floyd to find for each pair if there is a path connecting them
    if there is a cycle between node 2*i and 2*i+1 then there is no valid solution
    if there is a path from 2*i to 2*i+1 then i-th character must be a consonant and vice versa
    so for some characters we know before hand whether they are vowels or consonants
    then we iterate index by index and try to put the smallest possible character that doesnt violate any rules 
    putting a character means assigning value to a node in the graph, if this node already contains the opposite value
    then we can't put this character, else we can and if this value is 1, then we also mark all unmarked nodes that are reachable
    from current node by 1, and if this value is 0 then we need to mark all nodes that reach this node by 0 aswell
    which can be done with a simple loop.
    
    we dont need to try all characters, it only matter 2 things , is it vowel or not and is it less than character in current index or not
    then we are basically iterating length of the common prefix and checking validity using 2sat, so overall complexity is O(n*m)
*/

#include<bits/stdc++.h>
using namespace std;

#define scl(x) scanf("%lld",&x)
#define sc(x)  scanf("%d",&x)
#define ll long long
#define lop(i,n) for(int i=0;i<n;++i)
typedef pair<int, int> ii;
typedef pair<ll, ll> pll;

const int N=405;
bool mat[N][N];
int n,m,l;
char x[N];
char type[30];
char nxto[128];
char nxtz[128];

bool get(char c){
	return (type[c-'a']=='C');
}
int getId(int idx,char c){
	return 2*idx+(c=='C');
}
int state[N];
vector<int> vec;
bool dfs(int cur,int p){
	if(state[cur]!=-1)return (state[cur]==p);
	vec.push_back(cur);
	state[cur]=p;
	if(p==1){
		lop(i,2*n)if(mat[cur][i]&&state[i]==-1)state[i]=p,vec.push_back(i);
	}
	else {
		lop(i,2*n)if(mat[i][cur]&&state[i]==-1)state[i]=p,vec.push_back(i);
	}
	dfs(cur^1,p^1);
	return 1;
}
char result[N];
bool solve(int idx,bool isg);
bool check(int idx,char c,int isg){
	if(c==-1)return 0;
	vector<int> v;
	bool res=dfs(2*idx,!get(c));
	v=vec;
	vec.clear();
	if(!res)return 0;
	if(solve(idx+1,isg||c>x[idx]))
		return result[idx]=c,1;
	lop(i,v.size())state[v[i]]=-1;
	return 0;
}
bool solve(int idx,bool isg){
	if(idx==n)return 1;
	char a,b;
	if(isg){
		a=nxtz['a'];
		b=nxto['a'];
	}
	else{
		if(check(idx,x[idx],isg))return 1;
		a=nxtz[x[idx]+1];
		b=nxto[x[idx]+1];
	}
	if(a>b)swap(a,b);
	if(check(idx,a,isg))return 1;
	if(check(idx,b,isg))return 1;
	return 0;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("i.txt","r",stdin);
#endif
	scanf(" %s",type);
	l=strlen(type);
	nxto['a'+l]=nxtz['a'+l]=-1;
	for(char c='a'+l-1;c>='a';c--){
		nxto[c]=nxto[c+1];
		nxtz[c]=nxtz[c+1];
		if(get(c))nxto[c]=c;
		else nxtz[c]=c;
	}
	sc(n),sc(m);
	lop(i,m){
		int p1,p2;
		char t1,t2;
		scanf("%d %c %d %c",&p1,&t1,&p2,&t2);
		p1--,p2--;
		mat[getId(p1,t1)][getId(p2,t2)]=1;
		mat[getId(p2,t2)^1][getId(p1,t1)^1]=1;
	}
	scanf(" %s",x);
	lop(i,2*n)lop(j,2*n)lop(k,2*n)
			mat[j][k]|=(mat[j][i]&&mat[i][k]);
	lop(i,n)if(mat[2*i][2*i+1]&&mat[2*i+1][2*i])return puts("-1");
	memset(state,-1,sizeof state);
	lop(i,n){
		if(mat[2*i][2*i+1])dfs(2*i,0);
		if(mat[2*i+1][2*i])dfs(2*i+1,0);
	}
	vec.clear();
	if(!solve(0,0))return puts("-1");
	printf("%s\n",result);



}
