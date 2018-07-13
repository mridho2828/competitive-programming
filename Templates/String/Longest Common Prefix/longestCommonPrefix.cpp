int Phi[N], LCP[N], PLCP[N];

void computeLCP() {
	int L = 0;
	Phi[SA[0]] = -1;
	for (int i = 1; i < n; ++i) Phi[SA[i]] = SA[i-1];
	for (int i = 0; i < n; ++i) {
		if (Phi[i] == -1) {
			PLCP[i] = 0;
			continue;
		}
		while (T[i + L] == T[Phi[i] + L]) ++L;
		PLCP[i] = L;
		L = max(L-1, 0);
	}

	for (int i = 0; i < n; ++i) {
		LCP[i] = PLCP[SA[i]];
	}
}