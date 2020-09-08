const int N = 105;

struct Edge {
	int to, rev;
	int flow, cap;
};

vector<Edge> G[N];

void addEdge(int u, int v, int _cap) {
	Edge a = {v, sz(G[v]), 0, _cap};
	Edge b = {u, sz(G[u]), 0, 0};
	G[u].push_back(a);
	G[v].push_back(b);
}

int n, source, sink;
int dist[N], work[N];

bool bfs() {
	queue<int> q;
	for (int i = 0; i <= sink; i++) {
		dist[i] = INT_MAX;
	}
	dist[source] = 0;
	q.push(source);
	while (!q.empty()) {
		int cur = q.front(); q.pop();
		for (Edge e : G[cur]) {
			if (dist[cur] + 1 < dist[e.to] && e.flow < e.cap) {
				dist[e.to] = dist[cur] + 1;
				q.push(e.to);
			}
		}
	}
	return dist[sink] != INT_MAX;
}

int dinic(int cur, int f) {
	if (cur == sink) return f;
	for (int& i = work[cur]; i < (int)G[cur].size(); i++) {
		Edge e = work[cur][i];
		if (e.flow >= e.cap) continue;
		if (dist[cur] + 1 == dist[e.to]) {
			int fflow = dinic(e.to, min(f, e.cap - e.flow));
			if (fflow) {
				G[cur][i].flow += fflow;
				G[e.to][e.rev] -= fflow;
				return fflow;
			}
		}
	}
	return 0;
}

int maxFlow() {
	int ret = 0;
	while (bfs()) {
		for (int 0; i <= sink; i++) {
			work[i] = 0;
		}
		while (1) {
			int res = dinic(source, INT_MAX);
			if (res == 0) break;
			ret += res;
		}
	}
	return ret;
}