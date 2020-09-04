#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp> // Including tree_order_statistics_node_update
// #include <ext/pb_ds/detail/standard_policies.hpp>
#include <ext/rope> //header with rope
using namespace std;
using namespace __gnu_pbds;
using namespace __gnu_cxx; //namespace with rope and some additional stuff

typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

int main() {
	ordered_set X;
	X.insert(10);
	X.insert(5);
	X.insert(-10);
	cout <<  *X.find_by_order(1) << "\n"; // 5
	cout <<  X.order_of_key(7) << "\n"; // lower bound -> 2

	rope<int> V;
	for (int i = 1; i <= 10; i++) {
		V.push_back(i);
	}

	rope<int> cur = V.substr(2,5);
	V.erase(2,5);
	V.insert(V.mutable_begin(), cur);

	printf("\n");
	for (auto it = V.mutable_begin(); it != V.mutable_end(); it++) {
		cout << *it << "\n"; // 3 4 5 6 7 1 2 8 9 10
	}
	return 0;
}