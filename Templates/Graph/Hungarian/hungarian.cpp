int W[505][505], N; //MAXCOSTHUNGARIAN
int mx[505], my[505]; // match arr
int lx[505], ly[505]; // label arr
int x[505], y[505]; // used arr

int hungary(int nd) {
	x[nd] = 1;
	for(int i = 1; i <= N; ++i) {
		if(y[i] == 0 && W[nd][i] == lx[nd]+ly[i]) {
			y[i] = 1;
			if(my[i] == 0 || hungary(my[i])) {
				my[i] = nd;
				return 1;
			}
		}
	}
	return 0;
}

int KM() {
	int k, d;
	memset(mx, 0, sizeof(mx));
	memset(my, 0, sizeof(my));
	memset(lx, 0, sizeof(lx));
	memset(ly, 0, sizeof(ly));
	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= N; ++j) {
			lx[i] = max(lx[i], W[i][j]);
		}
	}

	for (int i = 1; i <= N; ++i) {
		while (1) {
			memset(x, 0, sizeof(x));
			memset(y, 0, sizeof(y));
			if (hungary(i)) break;
			d = 0xfffffff;
			for (int j = 1; j <= N; ++j) {
				if (x[j]) {
					for (int k = 1; k <= N; ++k) {
						if (!y[k]) {
							d = d < lx[j] + ly[k] - W[j][k] ?
								d : lx[j] + ly[k] - W[j][k];
						}
					}
				}
			}

			if (d == 0xfffffff) break;
			for (int j = 1; j <= N; ++j) {
				if (x[j]) lx[j] -= d;
				if (y[j]) ly[j] += d;
			}
		}
	}

	int res = 0;
	for (int i = 1; i <= N; ++i) {
		if (my[i]) {
			res += W[my[i]][i];
		}
	}
	return max(0, res);
}
//PROPERTY: lx[i] + ly[j] >= W[i][j] & sum(lx+ly)=min