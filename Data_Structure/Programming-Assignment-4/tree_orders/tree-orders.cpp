#include <iostream>
#include <vector>
#include <algorithm>
#if defined(__unix__) || defined(__APPLE__)
#include <sys/resource.h>
#endif

using namespace std;

class TreeOrders {
  int n;
  vector <int> key;
  vector <int> left;
  vector <int> right;

public:
  void read() {
    cin >> n;
    key.resize(n);
    left.resize(n);
    right.resize(n);
    for (int i = 0; i < n; i++) {
      cin >> key[i] >> left[i] >> right[i];
    }
  }


  void in_order(vector<int> &result, int index=0) {
    // Finish the implementation
    // You may need to add a new recursive method to do that
    if(index == -1)
      return;
    in_order(result, left[index]);
    result.push_back(key[index]);
    in_order(result, right[index]);
  }

  void pre_order(vector<int> &result, int index=0) {
    // Finish the implementation
    // You may need to add a new recursive method to do that
    if(index == -1)
      return;
    result.push_back(key[index]);
    pre_order(result, left[index]);
    pre_order(result, right[index]);
  }

  void post_order(vector<int> &result, int index=0) {
    // Finish the implementation
    // You may need to add a new recursive method to do that
    if(index == -1)
      return;
    post_order(result, left[index]);
    post_order(result, right[index]);
    result.push_back(key[index]);
  }
};

void print(vector <int> a) {
  for (size_t i = 0; i < a.size(); i++) {
    if (i > 0) {
      cout << ' ';
    }
    cout << a[i];
  }
  cout << '\n';
}

int main_with_large_stack_space() {
  ios_base::sync_with_stdio(0);
  TreeOrders t;
  t.read();
  vector<int> in, pre, post;
  t.in_order(in);
  t.pre_order(pre);
  t.post_order(post);
  // cout<<in.size()<<" "<<pre.size()<<" "<<post.size()<<endl;
  print(in);
  print(pre);
  print(post);
  return 0;
}

int main (int argc, char **argv)
{
#if defined(__unix__) || defined(__APPLE__)
  // Allow larger stack space
  const rlim_t kStackSize = 16 * 1024 * 1024;   // min stack size = 16 MB
  struct rlimit rl;
  int result;

  result = getrlimit(RLIMIT_STACK, &rl);
  if (result == 0)
  {
      if (rl.rlim_cur < kStackSize)
      {
          rl.rlim_cur = kStackSize;
          result = setrlimit(RLIMIT_STACK, &rl);
          if (result != 0)
          {
              std::cerr << "setrlimit returned result = " << result << std::endl;
          }
      }
  }
#endif

  return main_with_large_stack_space();
}

