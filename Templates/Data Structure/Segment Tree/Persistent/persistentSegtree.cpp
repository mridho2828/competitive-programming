#include<bits/stdc++.h>

#define sz(a) (int)(a).size()
#define all(a) (a).begin(), (a).end()

using namespace std;

typedef vector<int> vi;
 
const int N = 100005;
 
struct Node {
	int val;
	int lft, rght;
};
 
int n, m;
int ar[N];
 
struct PersistentSegmentTree {
	int pnode = 1, proot;
	int root[N];
	Node node[2000005]; // approx N*LOGN nodes
	
	void update(int id, int L, int R, int old, int pos) {
		if (L == R) {
			node[id].val = node[old].val + 1;
			return;
		}
		int mid = (L + R) >> 1;
		if (pos <= mid) {
			node[id].lft = pnode++;
			node[id].rght = node[old].rght;
			update(node[id].lft, L, mid, node[old].lft, pos);
		}
		else {
			node[id].lft = node[old].lft;
			node[id].rght = pnode++;
			update(node[id].rght, mid + 1, R, node[old].rght, pos);
		}
		node[id].val = node[node[id].lft].val + node[node[id].rght].val;
	}
	
	void _update(int pos) {
		root[++proot] = pnode++;
		update(root[proot], 0, n-1, root[proot - 1], pos);
	}
	
	int query(int u, int v, int L, int R, int k) {
		if (L == R) return L;
		int mid = (L + R) >> 1;
		int val_lft = node[node[v].lft].val - node[node[u].lft].val;
		if (val_lft >= k) return query(node[u].lft, node[v].lft, L, mid, k);
		return query(node[u].rght, node[v].rght, mid + 1, R, k - val_lft);
	}
	
	int _query (int l, int r, int k) {
		return query(root[l - 1], root[r], 0, n-1, k);
	}
};

PersistentSegmentTree segtree;
 
int main() {
	scanf("%d %d", &n, &m);
	vi uniq;
	for (int i = 0; i < n; i++) {
		scanf("%d", &ar[i]);
		uniq.push_back(ar[i]);
	}
	
	sort(all(uniq));
	
	for (int i = 0; i < n; i++) {
		int id = lower_bound(all(uniq), ar[i]) - uniq.begin();
		segtree._update(id);
	}
	
	while (m--) {
		int l, r, k;
		scanf("%d %d %d", &l, &r, &k);
		int ans = segtree._query(l, r, k);
		printf("%d\n", uniq[ans]);
	}
	return 0;
} 
