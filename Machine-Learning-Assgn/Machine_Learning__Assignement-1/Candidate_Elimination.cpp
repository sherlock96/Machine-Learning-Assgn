#include<bits/stdc++.h>
using namespace std;
#define ll long long int
#define fi first
#define se second
#define mp make_pair
#define in insert
#define pb push_back

int arr[1000][17],l;
FILE *fp1;



typedef struct hypo{
    ll h[16];
}hp;



void read(){
    FILE *fp,*fp1;
    char  inp[10000];
    fp=fopen("zoo.data","r+");
    l=0;
    //cout<<"1";
    while(1){
        fgets(inp,10000,fp);
        //puts(inp);
        if(feof(fp)){
            return ;
        }
        ll x=0;
        while(inp[x]!=','){
            x++;
        }
        x++;
        for(ll y=0;y<17;y++){
            arr[l][y]=inp[x+2*y]-'0';
        }
        l++;
    }
}

int getans(hp a,ll b){
    for(ll x=0;x<16;x++){
        if(a.h[x]==-1){
            return 0;
        }
        if(a.h[x]==10){
            continue;
        }
        if(a.h[x]!=arr[b][x]){
            return 0;
        }
    }
    return 1;
}

int isgen(hp a,hp b){
    for(ll x=0;x<16;x++){
        if(!(a.h[x]==10||a.h[x]==b.h[x])&&b.h[x]!=-1){
            return 0;
        }
    }
    return 1;
}

void pr(hp a,ll b){
    for(ll x=0;x<16;x++){
        if(a.h[x]==10){
            if(b==0){
                fprintf(fp1,"? ");
            }else{
                cout<<"? ";
            }
        }else{
            if(b==0){
                fprintf(fp1,"%lld ",a.h[x]);
            }else{
                cout<<a.h[x]<<" ";
            }
        }
    }
    if(b==0){
        fprintf(fp1,"\n");
    }else{
        cout<<endl;
    }
}
void pr(list<hp>a,ll b){
    for(auto t=a.begin();t!=a.end();t++){
        pr(*t,b);
    }
}


ll fun(ll a){
    hp spec;
    list<hp>gen;
    gen.clear();
    hp temp1;
    for(ll x=0;x<16;x++){
        spec.h[x]=-1;
    }
    for(ll x=0;x<16;x++){
        temp1.h[x]=10;
    }
    gen.pb(temp1);
    for(ll x=0;x<l;x++){
        if(arr[x][16]==a){
            for(auto y=gen.begin();y!=gen.end();){
                if(getans(*y,x)==0){
                    auto tr=y;
                    y++;
                    gen.erase(tr);
                }else{
                    y++;
                }
            }
            if(getans(spec,x)==0){
                for(ll z=0;z<16;z++){
                    if((spec).h[z]==-1){
                        (spec).h[z]=arr[x][z];
                    }else if((spec).h[z]!=arr[x][z]){
                        (spec).h[z]=10;
                    }
                }
            }
            auto y=gen.begin();
            for(;y!=gen.end();y++){
                if(isgen(*y,spec)==1){
                    break;
                }
            }
            fprintf(fp1,"%lld\n",x);
            pr(spec,0);
            pr(gen,0);
            if(y==gen.end()){
                cout<<"cannot make spec or gen boundary"<<endl;
                return 0;
            }

        }else{
            if(getans(spec,x)==1){
                cout<<"cannot make spec or gen boundary"<<endl;
                return 0;
            }
            for(auto y=gen.begin();y!=gen.end();){
                if(getans((*y),x)==1){
                    list<hp>temp;
                    temp.clear();
                    hp z;
                    z=*y;
                    for(ll k=0;k<16;k++){
                        if(z.h[k]==10){
                            if(k==12){
                                for(ll j=0;j<10;j=j+2){
                                    z.h[k]=j;
                                    if(j!=arr[x][k]&&isgen(z,spec)){
                                        temp.pb(z);
                                    }
                                }
                                z.h[k]=(*y).h[k];
                            }else{
                                for(ll j=0;j<2;j++){
                                    z.h[k]=j;
                                    if(j!=arr[x][k]&&isgen(z,spec)){
                                        temp.pb(z);
                                    }
                                }
                                z.h[k]=(*y).h[k];
                            }
                        }
                    }
                    auto tr=y;
                    y++;
                    gen.erase(tr);
                    for(auto i=temp.begin();i!=temp.end();i++){
                        gen.pb(*i);
                    }
                }else{
                    y++;
                }
            }
            for(auto i=gen.begin();i!=gen.end();i++){
                for(auto q=gen.begin();q!=gen.end();q++){
                    if(isgen(*i,*q)==1&&i!=q){
                        auto tr=q;
                        i++;
                        gen.erase(tr);
                        if(gen.size()!=0){
                           i--;
                        }
                        break;
                    }
                }
            }

            fprintf(fp1,"%lld\n",x);
            pr(spec,0);
            pr(gen,0);
            if(gen.size()==0){
                cout<<"cannot make spec or gen boundary"<<endl;
                return 0;
            }

        }
    }
    cout<<"specific boundary"<<endl;
    pr(spec,1);
    cout<<"general boundary"<<endl;
    pr(gen,1);
    return 1;
}





int main(){
    fp1=fopen("temp.a","w+");
    read();
    for(ll x=1;x<=7;x++){
        cout<<"result for "<<x<<endl;
        fun(x);
        cout<<endl;
    }
}
