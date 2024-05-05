#include <bits/stdc++.h>
using namespace std;

#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp> // Including tree_order_statistics_node_update
using namespace __gnu_pbds;

/*
Set with search by order of the comparator function.

O(log n) operations:
 - find(key)
 - erase(*pointer to element)
 - find_by_order(k) -> Find kth element ordered by comp function
 - order_of_key(key) -> Gets the position in which the key element would be in the set if inserted
*/
typedef tree<
int,
null_type,
less<int>,
rb_tree_tag,
tree_order_statistics_node_update>
ordered_set;

/*
Custom comparator, and other types.

Multiset could be implemented with pairs
*/

struct comp{

  bool operator() (const pair<long long, string> &p1, const pair<long long, string> &p2) {
    if (p1.first != p2.first) return p1.first > p2.first;
    return p1.second < p2.second;
  }

};

typedef tree<
pair<long long, string>,
null_type,
comp,
rb_tree_tag,
tree_order_statistics_node_update>
custom_ordered_set;

/*
Examples
*/

int main(){
  ordered_set X;
  X.insert(1);
  X.insert(2);
  X.insert(4);
  X.insert(8);
  X.insert(16);

  cout<<*X.find_by_order(1)<<endl; // 2
  cout<<*X.find_by_order(2)<<endl; // 4
  cout<<*X.find_by_order(4)<<endl; // 16
  cout<<(end(X)==X.find_by_order(6))<<endl; // true

  cout<<X.order_of_key(-5)<<endl;  // 0
  cout<<X.order_of_key(1)<<endl;   // 0
  cout<<X.order_of_key(3)<<endl;   // 2
  cout<<X.order_of_key(4)<<endl;   // 2
  cout<<X.order_of_key(400)<<endl; // 5


  custom_ordered_set t;
  t.insert({1, "ab"});

  auto p = *t.find({1, "ab"});
  cout << p.first << " " << p.second << endl; // 1 ab

  t.erase({1, "ab"});  

  p = *t.find({1, "ab"}); // 0
  cout << p.first << " " << p.second << endl;
}