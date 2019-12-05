#include <bits/stdc++.h>
using namespace std;

int factor(int n){

  int ans = -1;
  int c = 0;

  for(int i=2;i<=sqrt(n);i++){

    bool ok = false;

    while(n%i==0){
      ok = true;
      n/=i;
    }

    if(ok){
      c++;
      ans = i;
    }

  }

  if(c==0) return n;//se for primo
  if(c>1) return -1;//se tem varios fatores diferentes

  return ans;//se tem apenas um fator

}

int main(){

  int n;

  cin >> n;

  int ans = factor(n);

  if(ans==-1){
    cout << 1 << endl;
  }else{
    cout << ans << endl;
  }

  return 0;
}
