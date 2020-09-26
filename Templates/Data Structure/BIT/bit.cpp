#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N = 100005;

int tc;
int n, q;
ll BIT[N][2];
 
void update(int k, ll val, int idx) {
	for (; k <= n; k += k & -k) BIT[k][id] += val;
}
 
ll query(int k) {
	ll m = 0, c = 0;
	for (int i = k; i > 0; i -= i & -i) {
		m += BIT[0][i];
		c += BIT[1][i];
	}
	return m * k - c;
}
 
int main() {
	scanf("%d", &tc);
	while (tc--) {
		scanf("%d %d", &n, &q);
		memset(BIT, 0, sizeof BIT);
		while (q--) {
			int op; scanf("%d", &op);
			if (op == 0) {
				int a, b;
				ll v;
				scanf("%d %d %lld", &a, &b, &v);
				update(0, a, v);
				update(0, b+1, -v);
 
				update(1, a, v * (a - 1));
				update(1, b+1, -v * b);
			}
			else {
				int a, b; scanf("%d %d", &a, &b);
				ll res = query(b) - query(a-1);
				printf("%lld\n", res);
			}
		}
	}
	return 0;
} 