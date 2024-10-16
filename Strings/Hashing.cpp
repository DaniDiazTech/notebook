/*
Classic hash
Another values = 1000234987, 1000567991, 1000111979, 1000777117
Complexity: O(n)
Tested: https://codeforces.com/contest/1968/submission/285218366
*/

const unsigned long long  MOD[2] = { 1001864327, 1001265673};//primes
struct hashing {
    vector<ll>values[2] ;
    vector<ll> pot[2];
    ll base=29; //prime
    //creates two hashes in vector 'values' over string s
    hashing (string s){
        int n=s.size();
        values[ 0 ].assign( n , 0 );
        values[ 1 ].assign( n , 0 );
        for( int j = 0; j <=1; ++j){
            for( int i = 0; i < n; ++i){
                if(i == 0) values[j][i] = 1 + s[i] - 'a';
                else{
                    values[ j ][ i ]=( ( ( values[j][ i - 1 ] * base ) ) + ( 1 + s[i] - 'a') ) % MOD[j];
                }
            }
        }

        int p0 = 1, p1 = 1;
        for(int i = 0; i < n; ++i){
            pot[ 0 ].push_back( p0 );
            pot[ 1 ].push_back( p1 );
            p0=(p0 * base)%MOD[0];
            p1=(p1 * base)%MOD[1];
        }
    }

    //query type [ l , r ]
    pair<ll,ll> query(int l, int r){
        if( l == 0 )return {values[ 0 ][ r ], values[ 1 ][ r ]};
        else{
            ll x = ((( values[ 0 ][ r ])-(( values[ 0 ][ l - 1 ] * pot[ 0 ][ r - l + 1] )% MOD[ 0 ])) + MOD[ 0 ])% MOD[ 0 ];
            ll y = ((( values[ 1 ][ r ])-(( values[ 1 ][ l - 1 ] * pot[ 1 ][ r - l + 1] )% MOD[ 1 ])) + MOD[ 1 ])% MOD[ 1 ];
            return { x , y };
        }
    }
};
