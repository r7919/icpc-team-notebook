// generator
#ifdef LOCAL
  freopen("input.txt", "w", stdout);
#endif

// fast i/o
ios::sync_with_stdio(false);
cin.tie(0);

// file
#ifdef LOCAL
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif


// optimizations
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,popcnt,lzcnt")

// precision
cout << fixed << setprecision(15);