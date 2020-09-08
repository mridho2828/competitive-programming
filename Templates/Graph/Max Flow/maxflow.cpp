const int N = 105;

struct Edge {
	int to, rev;
	int cap;
};

vector<Edge> G[N];

void addEdge(int u, int v, int _cap) {
	Edge a = {v, sz(G[v]), _cap};
	Edge b = {u, sz(G[u]), 0};
	G[u].push_back(a);
	G[v].push_back(b);
}

int n, source, sink;
int dist[N];
ii par[N];

bool bfs() {
	queue<int> q;
	for (int i = 0; i <= sink; i++) {
		dist[i] = INT_MAX;
		par[i] = {-1, -1};
	}
	dist[source] = 0;
	q.push(source);
	while (!q.empty()) {
		int cur = q.front(); q.pop();
		for (Edge e : G[cur]) {
			if (dist[cur] + 1 < dist[e.to] && e.cap > 0) {
				dist[e.to] = dist[cur] + 1;
				q.push(e.to);
			}
		}
	}
	return dist[sink] != INT_MAX;
}

int maxFlow() {
	int ret = 0;
	while (bfs()) {
		int mins = INT_MAX;
		int cur = sink;
		while (cur != source) {
			ii prev = par[cur];
			mins = min(mins, G[prev.fi][prev.se].cap);
			cur = prev.fi;
		}
		ret += mins;
		cur = sink;
		while (cur != source) {
			ii prev = par[cur];
			G[prev.fi][prev.se].cap -= mins;
			G[cur][G[prev.fi][prev.se].rev] += mins;
			cur = prev.fi;
		}
	}
	return ret;
}