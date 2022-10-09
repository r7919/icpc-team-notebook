// version xor 

// usage:
// trie t(32);
// Note: Insert 0 if needed

struct trie
{
  ll MX; // max number of bits (constant for all bit strings)

  struct node
  {
    node *child[2];
    ll cnt;  // number of bit strings ending in the subtree(node) including this node        

    node()
    {
      cnt = 0;  
      for (ll i = 0; i < 2; i++)
        child[i] = NULL;
    }
  };

  node *root;

  trie(ll m)
  {
    MX = m;
    root = new node;
  }

  void insert(ll n) // msb to lsb
  {
    node *cur = root;
    for (ll i = MX - 1; i >= 0; i--)
    {
      cur->cnt++;
      ll x = (n & (1ll << i)) ? 1 : 0;
      if (cur->child[x] == NULL)
        cur->child[x] = new node;
      cur = cur->child[x];
    }
    cur->cnt++;
  }

  void remove(ll n)
  {
    node *cur = root;
    for (ll i = MX - 1; i >= 0; i--)
    {
      cur->cnt--;
      ll x = (n & (1ll << i)) ? 1 : 0;
      cur = cur->child[x];
    }
    cur->cnt--;
  }

  ll max_xor(ll n) // returns max(n ^ t_i)
  {
    assert(root->cnt > 0);

    ll ans = 0;
    node *cur = root;
    for (ll i = MX - 1; i >= 0; i--)
    {
      ll x = (n & (1ll << i)) ? 1 : 0;
      if (cur->child[!x] != NULL && cur->child[!x]->cnt > 0)
      {
        ans += (1ll << i);
        cur = cur->child[!x];
      }
      else
        cur = cur->child[x];
    }
    return ans;
  }

  ll xor_less_equal_k(ll n, ll k) // returns number of trie elements t_i such that (n ^ t_i) <= k
  {
    ll ans = 0;
    node *cur = root;
    for (ll i = MX - 1; i >= 0; i--)
    {
      if (cur == NULL)
        break;
      ll x = (n & (1ll << i)) ? 1 : 0;
      ll z = (k & (1ll << i)) ? 1 : 0;
      if (x == 1)
      {
        if (z == 1) // 1 ^ y <= 1
        {
          if (cur->child[1])
            ans += cur->child[1]->cnt;
          cur = cur->child[0];
        }
        else // 1 ^ y <= 0
          cur = cur->child[1];
      }
      else 
      {
        if (z == 1) // 0 ^ y <= 1
        {
          if (cur->child[0])
            ans += cur->child[0]->cnt;
          cur = cur->child[1];
        }
        else  // 0 ^ y <= 0
          cur = cur->child[0];
      }
    }
    if (cur) // (n ^ t_i) == k
      ans += cur->cnt;
    return ans;
  }
};


// version alphabet [a-z]

// usage:
// trie t;

struct trie
{
  struct node
  {
    ll cnt;  // number of strings ending in the subtree(node) including this node        
    vector<string> wend;
    node *child[26];

    node()
    {
      for (ll i = 0; i < 26; i++)
        child[i] = NULL;
      cnt = 0;
    }    
  };

  node *root;

  trie()
  {
    root = new node;
  }

  void insert(string s)
  {
    node *cur = root;
    for (ll i = 0; i < (ll) s.size(); i++)
    {
      cur->cnt++;
      ll x = s[i] - 'a';
      if (cur->child[x] == NULL)
        cur->child[x] = new node;
      cur = cur->child[x];
    }
    cur->cnt++;
    cur->wend.push_back(s);
  }

  ll dfs(node *cur) // counts number of nodes other than root
  {
    if (cur == NULL) 
      return 0ll;
    ll ans = (cur != root);
    for (ll i = 0; i < 26; i++)
      ans += dfs(cur->child[i]);
    return ans;
  }
};