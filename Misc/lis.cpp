  vector<ll> v;
 
  for (auto x: arr)
  {
    if (v.empty())
      v.push_back(x);
    else
    {
      if (x > v.back())
        v.push_back(x);
      else
      {
        auto it = lower_bound(v.begin(), v.end(), x);
        *it = x;
      }
    }
  }
 
  cout << v.size() << "\n";