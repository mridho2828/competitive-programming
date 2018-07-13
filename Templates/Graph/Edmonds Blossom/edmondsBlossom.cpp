int n, m;
vi adj[N];
int match[N];

int lca(vi& base, vi& p, int a, int b) {
	vector<bool> used(N);
	while (1) {
		a = base[a];
		used[a] = 1;
		if (match[a] == -1) break;
		a = p[match[a]];
	}
	while (1) {
		b = base[b];
		if (used[b]) return b;
		b = p[match[b]];
	}
	return -1;
}

void markPath(vi& base, vector<bool>& blossom, vi& p, int v, int b, int children) {
	for (; base[v] != b; v = p[match[v]]) {
		blossom[base[v]] = blossom[base[match[v]]] = true;
		p[v] = children;
		children = match[v];
	}
}

int findPath(vi& p, int root) {
	vector<bool> used(N);
	for (int i = 0; i < sz(p); ++i) p[i] = -1;
	vi base(N);
	for (int i = 0; i < n; ++i) base[i] = i;
	used[root] = true;
	int qh = 0;
	int qt = 0;
	vector<int> q(N);
	q[qt++] = root;
	while (qh < qt) {
		int v = q[qh++];
		for (int to : adj[v]) {
			if (base[v] == base[to] || match[v] == to) continue;
			if (to == root || match[to] != -1 && p[match[to]] != -1) {
				int curbase = lca(base, p, v, to);
				vector<bool> blossom(N);
				markPath(base, blossom, p, v, curbase, to);
				markPath(base, blossom, p, to, curbase, v);
				for (int i = 0; i < n; ++i) {
					if (blossom[base[i]]) {
						base[i] = curbase;
						if (!used[i]) {
							used[i] = true;
							q[qt++] = i;
						}
					}
				}
			}
			else if (p[to] == -1) {
				p[to] = v;
				if (match[to] == -1) return to;
				to = match[to];
				used[to] = true;
				q[qt++] = to;
			}
		}
	}
	return -1;
}

int maxMatching() {
	memset(match, -1, sizeof(match));
	vi p(N);
	for (int i = 0; i < n; ++i) {
		if (match[i] == -1) {
			int v = findPath(p, i);
			while (v != -1) {
				int pv = p[v];
				int ppv = match[pv];
				match[v] = pv;
				match[pv] = v;
				v = ppv;
			}
		}
	}
	int matches = 0;
	for (int i = 0; i < n; ++i) {
		if (match[i] != -1) {
			++matches;
		}
	}
	return matches / 2;
}