// This algorithms receives a list of integers and returns a bitset
// where if X is a possible subset sum, bitset[X] = 1 and
// bitset[X] = 0 otherwise

// Let S be the sum of the list
// Let N be the size of the list

// I'm not 100% sure about these complexities but you can use them as a reference
// Time complexity: O(√S * S / 32);
// Space complexity: O(√S + S)

// Tested: https://codeforces.com/contest/1856/submission/286483210

template<int BITSET_LEN>
bitset<BITSET_LEN> all_possible_subset_sums(vector<int> &arr) {
  bitset<BITSET_LEN> mask(1);

  map<int, int> frq;
  for (int e: arr) ++frq[e];

  for (auto [e, f]: frq) {
    for (int shift = 1; shift <= f; shift <<= 1) {
      mask |= (mask << (shift * e));
      f -= shift;
    }
    mask |= (mask << (f * e));
  }
  return mask;
}