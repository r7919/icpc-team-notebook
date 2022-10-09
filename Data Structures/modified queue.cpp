// usage:
// auto fun = [&](ll x, ll y) { return min(x, y); }; 
// ModifiedQueue<ll, decltype(fun)> mq(fun);

template <typename T, class F = function<T(const T&, const T&)>>
struct ModifiedQueue
{
  stack<pair<T, T>> s1, s2;
  F func;

  ModifiedQueue(const F& f) : func(f) {}

  ModifiedQueue() {}
  // usage -- for vector of mq's
  // vector < ModifiedQueue<ll> > v1(m);
  // v1[i] = ModifiedQueue<ll>(fun);

  void push(T x) // O(1)
  {
    T mval;
    if(s1.empty())
      mval = x;
    else
      mval = func(x, s1.top().ss);
    s1.push({x, mval});
  }

  T pop() // amortized O(1)
  {
    assert(!(s1.empty() && s2.empty()));
    if(s2.empty())
    {
      while(!s1.empty())
      {
        T temp = s1.top().ff;
        s1.pop();
        T mval;
        if(s2.empty())
          mval = temp;
        else
          mval = func(temp, s2.top().ss);
        s2.push({temp, mval});
      }
    }
    T removed = s2.top().ff;
    s2.pop();
    return removed;
  }

  T front() // amortized O(1)
  {
    assert(!(s1.empty() && s2.empty()));
    if(s2.empty())
    {
      while(!s1.empty())
      {
        T temp = s1.top().ff;
        s1.pop();
        T mval;
        if(s2.empty())
          mval = temp;
        else
          mval = func(temp, s2.top().ss);
        s2.push({temp, mval});
      }
    }
    return s2.top().ff;
  }

  T get() // O(1)
  {
    assert(!(s1.empty() && s2.empty()));
    if(s1.empty())
      return s2.top().ss;
    else if(s2.empty())
      return s1.top().ss;
    else
      return func(s1.top().ss, s2.top().ss);
  }

  void clear()
  {
    while(!s1.empty())
      s1.pop();
    while(!s2.empty())
      s2.pop();
  }

  bool empty()
  {
    return (s1.empty() && s2.empty());
  }
};