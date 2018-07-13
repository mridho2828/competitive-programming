typedef long long ll;

ll gcd(ll a, ll b) {
	return (b == 0 ? a : gcd(b, a % b));
}

void simp(ll& a, ll& b) {
	ll f = gcd(a, b);
	a /= f;
	b /= f;
}

ll C(ll n, ll k) {
	if (n < 2 * k) {
		k = n - k;
	}
	ll num = 1, denum = 1, to_mul, to_div;
	for (ll i = k; i; --i) {
		to_mul = n - k + 1;
		to_div = i;
		simp(to_mul, to_div);
		simp(num, to_div);
		simp(denum, to_mul);
		num *= to_mul;
		denum *= to_div;
	}
	return num / denum;
}

inline ll lucas(ll a, ll b, ll mod) {
	if (a == 0 && b == 0) return 1;
	ll n = a % mod, k = b % mod;
	if (n < k) return 0;
	return (nCk(n, k, mod) * lucas(a / mod, b / mod, mod) % mod);
}
// nCk must be precomputed