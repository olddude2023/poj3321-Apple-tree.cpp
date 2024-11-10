#include<cstdio>
using namespace std;
const int maxn=100005;

struct node{
    int v,next;
}edge[maxn<<1];

int head[maxn],tr[maxn],s[maxn],e[maxn];
bool vis[maxn],a[maxn];
int n,m,cnt,tim;

void add(int u,int v){
    edge[cnt].v=v;
    edge[cnt].next=head[u];
    head[u]=cnt++;
}

void dfs(int p){
    s[p]=++tim;
    vis[p]=1;
    for(int i=head[p];i!=-1;i=edge[i].next){
        if(vis[edge[i].v]) continue;
        dfs(edge[i].v);
    }
    e[p]=tim;
}

int lowbit(int x){
    return x&(-x);
}

void update(int x,int num){
    while(x<=n){
        tr[x]+=num;
        x+=lowbit(x);
    }    
}

int query(int x){
    int ans=0;
    while(x>0){
        ans+=tr[x];
        x-=lowbit(x);
    }
    return ans;
}

int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;++i){
        head[i]=-1;
        a[i]=1;
        update(i,1);
    }
    for(int i=1;i<n;++i){
        int u,v;
        scanf("%d%d",&u,&v);
        add(u,v);
        add(v,u);
    }
    dfs(1);
    scanf("%d",&m);
    char c;
    int t; 
    while(m--){
        scanf(" %c%d",&c,&t);
        if(c=='C'){
            if(a[t]){
                a[t]=0;
                update(s[t],-1);
            }
            else{
                a[t]=1;
                update(s[t],1);
            }
        }
        else{
            printf("%d\n",query(e[t])-query(s[t]-1));
        }
    }
    return 0;
}
