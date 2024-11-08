// This structure solves problems related to boolean satisfiability
// when the formula is in Conjunctive Normal Form using clauses with 2 variables each
// Example: (a OR b) AND (c XOR a) AND (b == a) AND (c AND b) ...
// This can determine if the formula is satisfiable or not, and gives a solution

// Time complexity: O(V + C)
// Space complexity: O(V + C)
// V = Number of variables, C = Number of clauses

// Tested: https://codeforces.com/contest/228/submission/290603765

// Requires: find_SCC
class Two_sat {
  private:
    vector<vector<int>> graph;
    vector<int> who_scc;
    vector<bool> value;
    bool know_solvable = false;
    bool know_solution = false;
    bool can_solve = false;
    int varn, cnt_scc;

  public:
    Two_sat(int number_of_variables) {
      varn = number_of_variables;
      graph.clear(); graph.resize(2 * varn + 1);
      value.clear(); value.resize(2 * varn + 1);
    }
    int get_node(int var) {
      assert(var != 0 && -varn <= var && var <= varn);
      if (0 < var) return var;
      return varn - var;
    }
    void add_implication(int var_from, int var_to) {
      int from = get_node(var_from), to = get_node(var_to);
      graph[from].push_back(to);
      know_solvable = false;
      know_solution = false;
    }

    // Boolean Operators ↓
    void make_true(int a) { add_implication(-a, a); }
    void make_false(int a) { add_implication(a, -a); }
    void add_or(int a, int b) {
      add_implication(-a, b);
      add_implication(-b, a);
    }
    void add_and(int a, int b) { make_true(a), make_true(b); }
    void add_xor(int a, int b) { add_or(a, b); add_or(-a, -b); }
    void add_equal(int a, int b) { add_or(-a, b); add_or(a, -b); }
    void at_most_one(int a, int b) { add_or(-a, -b); }
    // Boolean operators ↑

    bool solvable() {
      if (know_solvable) return can_solve;
      who_scc = find_SCC(graph, cnt_scc);
      can_solve = true;
      for (int var = 1; var <= varn; ++var) {
        int neg = get_node(-var);
        if (who_scc[var] == who_scc[neg]) can_solve = false;
        if (!can_solve) break;
      }
      know_solvable = true;
      return can_solve;
    }

    bool calc_solution() {
      if (know_solution) return true;
      if (!solvable()) return false;

      vector<int> indeg(cnt_scc + 1, 0);
      vector<int> order(cnt_scc + 1, -1);
      vector<vector<int>> condensation(cnt_scc + 1);
      for (int node = 1; node <= 2 * varn; ++node) {
        for (int adj: graph[node]) {
          if (who_scc[node] != who_scc[adj]) {
            condensation[who_scc[node]].push_back(who_scc[adj]);
            ++indeg[who_scc[adj]];
          }
        }
      }
      queue<int> que;
      for (int node = 1; node <= cnt_scc; ++node) {
        if (indeg[node] == 0) que.push(node);
      }
      int timer = 0;
      while (!que.empty()) {
        int node = que.front();
        que.pop();
        order[node] = ++timer;
        for (int adj: condensation[node]) {
          if (--indeg[adj] == 0) que.push(adj);
        }
      }
      for (int var = 1; var <= varn; ++var) {
        int neg = get_node(-var);
        value[var] = order[who_scc[neg]] < order[who_scc[var]];
        value[neg] = !value[var];
      }
      know_solution = true;
      return true;
    }

    // The expression must be satisfiable to execute get_value()
    bool get_value(int var) { // Value of a variable in the formula solution
      assert(calc_solution());
      int node = get_node(var);
      return value[node];
    }
};
