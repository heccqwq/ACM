struct Ufs{
    int fa[N],siz[N],cnt;
    int st[N],tp;
    int Find(int x){
        if(x==fa[x]){
            return fa[x];
        }
		return Find(fa[x]);
    }
    void Merge(int x,int y){
        int fx=Find(x);
        int fy=Find(y);
        if(fx==fy){
            return;
        }
        if(siz[fx]<siz[fy]){
            swap(fx,fy);
        }
        s[fy]=fx;
        siz[fx]+=siz[fy];
        st[++tp]=fy;
    }
    void Delete(int x){//撤销到第x次操作 
        while(tp>x){
            int k=st[tp];
            siz[fa[k]]-=siz[k];
            fa[k]=k;
            tp--;
        }
    }
};
