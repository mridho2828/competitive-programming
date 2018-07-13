/* C++ program to find a prime factor of composite using
   Pollard's Rho algorithm */
#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

/* Function to calculate (base^exponent)%modulus */
ll fastExp(ll base, ll exponent, ll modulus){
    /* initialize result */
    ll result = 1;
 
    while (exponent > 0) {
        /* if y is odd, multiply base with result */
        if (exponent & 1)
            result = (result * base) % modulus;
 
        /* exponent = exponent/2 */
        exponent = exponent >> 1;
 
        /* base = base * base */
        base = (base * base) % modulus;
    }
    return result;
}
 
/* method to return prime divisor for n */
ll pollardsRho(ll n) {
    /* no prime divisor for 1 */
    if (n == 1) return n;
 
    /* even number means one of the divisors is 2 */
    if (n % 2 == 0) return 2;
 
    /* we will pick from the range [2, N) */
    ll x = (rand()%(n-2))+2;
    ll y = x;
 
    /* the constant in f(x).
     * Algorithm can be re-run with a different c
     * if it throws failure for a composite. */
    ll c = (rand()%(n-1))+1;
 
    /* Initialize candidate divisor (or result) */
    ll d = 1;  
 
    /* until the prime factor isn't obtained.
       If n is prime, return n */
    while (d == 1) {
        /* Tortoise Move: x(i+1) = f(x(i)) */
        x = (fastExp(x, 2, n) + c + n)%n;
 
        /* Hare Move: y(i+1) = f(f(y(i))) */
        y = (fastExp(y, 2, n) + c + n)%n;
        y = (fastExp(y, 2, n) + c + n)%n;
 
        /* check gcd of |x-y| and n */
        d = __gcd(abs(x-y), n);
 
        /* retry if the algorithm fails to find prime factor
         * with chosen x and c */
        if (d == n) return pollardsRho(n);
    }
 
    return d;
}
 
/* driver function */
int main() {
    ll n = 10967535067;
    printf("One of the divisors for %lld is %lld.", n, pollardsRho(n));
    return 0;
}