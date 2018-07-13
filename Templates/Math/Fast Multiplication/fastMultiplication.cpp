ll mulmod(ll a, ll b, ll c) {   // returns (a * b) % c, minimize overflow
    if (a <= (ll)2e+9 && b <= (ll)2e+9) return (a * b) % c;
    ll x = 0, y = a % c;
    while (b) {
        if (b & 1ll) x = (x + y) % c;
        y = (y << 1ll) % c;
        b >>= 1ll;
    }
    return x % c;
}