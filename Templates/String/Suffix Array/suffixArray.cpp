int RA[N], tmpRA[N];
int SA[N], tmpSA[N];
int c[N];

inline void countingSort(int k) {
	int sum = 0;
	int maxi = max(300, n);
	reset(c, 0);
	for (int i = 0; i < n; ++i) ++c[i + k < n ? RA[i+k] : 0];
	
	for (int i = 0; i < maxi; ++i) {
		int t = c[i];
		c[i] = sum;
		sum += t;
	}

	for (int i = 0; i < n; ++i) {
		tmpSA[c[SA[i] + k < n ? RA[SA[i] + k] : 0]++] = SA[i];
	}

	for (int i = 0; i < n; ++i) {
		SA[i] = tmpSA[i];
	}
}

inline void constructSA() {
	for (int i = 0; i < n; ++i) RA[i] = T[i] - '.';
	for (int i = 0; i < n; ++i) SA[i] = i;
	for (int k = 1; k < n; k <<= 1) {
		countingSort(k);
		countingSort(0);	
		int r = 0;
		tmpRA[SA[0]] = r;
		for (int i = 1; i < n; ++i) {
			tmpRA[SA[i]] = (RA[SA[i]] == RA[SA[i-1]] && RA[SA[i]+k] == RA[SA[i-1]+k]) ? r : ++r;
		}
		for (int i = 0; i < n; ++i) {
			RA[i] = tmpRA[i];
		}
	}
}