typedef vector<int> vi;

vi adj[N];
int deleted[N], subsize[N];

void process(int center) {
	// do something useful here
}

void dfs(int cur, int prev) {
	subsize[cur] = 1;
	for (int nxt : adj[cur]) {
		if (nxt == prev || deleted[nxt]) continue;
		dfs(nxt, cur);
		subsize[cur] += subsize[nxt];
	}
}

int findcenter(int cur, int prev, int tot) {
	for (int nxt : adj[cur]) {
		if (nxt == prev || deleted[nxt]) continue;
		if ((tot >> 1) < subsize[nxt]) return findcenter (nxt, cur, tot);
	}
	return cur;
}

void decompose(int cur, int tot) {
	if (tot == 1) return;
	dfs(cur, -1);
	int center = findcenter(cur, -1, tot);
	process(center);
	deleted[center] = true;
	int sum = 0, other = -1;
	for (int nxt : adj[center]) {
		if (deleted[nxt]) continue;
		if (subsize[nxt] < subsize[center]) {
			sum += subsize[nxt];
			decompose(nxt, subsize[nxt]);
		}
		else {
			other = nxt;
		}
	}
	
	if (other != -1) decompose(other, tot - sum - 1);
}