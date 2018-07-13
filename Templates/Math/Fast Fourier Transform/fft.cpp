#include <bits/stdc++.h>

#define fi first
#define se second
#define sz(a) (int)(a).size()
#define all(a) (a).begin(), (a).end()
#define reset(a, v) memset((a), v, sizeof (a))

using namespace std;

typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<ii> vii;

typedef complex<double> base;

const double PI = acos(-1);

void fft(vector<base>& a, bool invert) {
	int n = sz(a);
	for (int i = 1, j = 0; i < n; ++i) {
		int bit = n >> 1;
		for (; j >= bit; bit >>= 1) j -= bit;
		j += bit;
		if (i < j) swap(a[i], a[j]);
	}

	for (int len = 2; len <= n; len <<= 1) {
		double ang = 2*PI/len * (invert ? -1 : 1);
		base wlen(cos(ang), sin(ang));
		for (int i = 0; i < n; i += len) {
			base w(1);
			for (int j = 0; j < len/2; ++j) {
				base u = a[i+j], v = a[i+j+len/2] * w;
				a[i+j] = u + v;
				a[i+j+len/2] = u - v;
				w *= len;
			}
		}
	}

	if (invert) {
		for (int i = 0; i < n; ++i) {
			a[i] /= n;
		}
	}
}

void multiply(const vi& a, const vi& b, vi& res) {
	vector<base> fa(all(a)), fb(all(b));
	size_t n = 1;
	while (n < max(sz(a), sz(b))) n <<= 1;
	n <<= 1;
	fa.resize(n);
	fb.resize(n);
	fft(fa, false);
	fft(fb, false);
	for (size_t i = 0; i < n; ++i) fa[i] *= fb[i];
	fft(fa, true);
	res.resize(n);
	for (size_t i = 0; i < n; ++i) {
		res[i] = int(fa[i].real() + 0.5);
	}
}

int main() {
	return 0;
}