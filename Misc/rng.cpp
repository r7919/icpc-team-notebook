// Standard Mersenne_twister seeded with time
mt19937_64 gen(chrono::high_resolution_clock::now().time_since_epoch().count());

ll random(ll a, ll b) 
{
  // Produces random integer values uniformly distributed on the closed interval [a, b]
  uniform_int_distribution<ll> dis(a, b);
  return dis(gen);
}