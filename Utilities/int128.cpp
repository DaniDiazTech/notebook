typedef __int128 ll;
// typedef __uint128 ll;

ostream &operator<<(ostream &os, const ll &p) {
    vector<int> v;
    ll x = p;
    if (x == 0) v.push_back(0);
    while(x){
      v.push_back(x % 10);
      x /= 10;
    }
    reverse(v.begin(), v.end());
    for(int i : v){
        os << i;
    }
    return os;
}
istream &operator>>(istream &is, ll &p) {
    string s;
    is >> s;
    p = 0;
    for(char i : s){
      p = p * 10 + (i - '0');
    }
    return is;
}