#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct node {
	ll val, lazy;
};
 
const int N = 100005;

int tc;
int n, q;
node segtree[N*4];
 
void propagate(int id, int L, int R) {
	int mid = (L + R) >> 1;
	segtree[id * 2].val += (mid - L + 1) * segtree[id].lazy;
	segtree[id * 2 + 1].val += (R - mid) * segtree[id].lazy;
	segtree[id * 2].lazy += segtree[id].lazy;
	segtree[id * 2 + 1].lazy += segtree[id].lazy;
	segtree[id].lazy = 0;
}
 
void update(int id, int L, int R, int x, int y, ll added_val) {
	if (x <= L && R <= y) {
		segtree[id].val += (R - L + 1) * added_val;
		segtree[id].lazy += added_val;
		return;
	}
	propagate(id, L, R);
	int mid = (L + R) >> 1;
	if (x <= mid) update(id * 2, L, mid, x, y, added_val);
	if (y > mid) update(id * 2 + 1, mid + 1, R, x, y, added_val);
	segtree[id].val = segtree[id * 2].val + segtree[id * 2 + 1].val;
}
 
ll query(int id, int L, int R, int x, int y) {
	if (x <= L && R <= y) {
		return segtree[id].val;
	}
	propagate(id, L, R);
	int mid = (L + R) >> 1;
	if (y <= mid) return query(id * 2, L, mid, x, y);
	if (x > mid) return query(id * 2 + 1, mid + 1, R, x, y);
	ll tmp1 = query(id * 2, L, mid, x, y);
	ll tmp2 = query(id * 2 + 1, mid + 1, R, x, y);
	return tmp1 + tmp2;
}
 
int main () {
	scanf("%d", &tc);
	while (tc--) {
		scanf("%d %d", &n, &q);
		for (int i = 1; i <= 4*n; i++) {
			segtree[i].val = segtree[i].lazy = 0;
		}
		int op, p, q;
		ll v;
		while (q--) {
			scanf("%d %d %d", &op, &p, &q);
			if (op == 0) {
				scanf("%lld", &v);
				update(1, 0, N - 1, --p, --q, v);
			}
			else {
				ll res = query(1, 0, N - 1, --p, --q);
				printf("%lld\n", res);
			}
		}
	}
	return 0;
} 