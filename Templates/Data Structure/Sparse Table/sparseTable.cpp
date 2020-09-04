int dat[N];
int lg2[N];
int spTable[N][LOGN];

void fillTable() {
	for (int i = 2; i <= n; i++) {
		lg2[i] = lg2[i>>1] + 1;
	}
	for (int i = 0; i < n; i++) {
		spTable[i][0] = dat[i];
	}

	for (int j = 1; j < LOGN; j++) {
		for (int i = 0; i + (1<<j) - 1 < n; i++) {
			spTable[i][j] = max(spTable[i][j-1], spTable[i + (1<<(j-1))][j-1]);
		}
	}
}

int query(int l, int r) {
	int lg = lg2[r-l+1];
	return max(spTable[l][lg], spTable[r - (1<<lg) + 1][lg]);
}