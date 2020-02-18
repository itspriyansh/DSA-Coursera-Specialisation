#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> fast_count_segments(vector<int> starts, vector<int> ends, vector<int> points) {
  vector<int> cnt(points.size(),0);
  //write your code here
  int n = starts.size()+ends.size()+points.size();
  pair<int, pair<int, int>> line[n];
  int index = 0;
  for(size_t i=0;i<starts.size();i++){
    line[index].first = starts[i];
    line[index].second.second = i;
    line[index++].second.first = 0;
  }
  for(size_t i=0;i<points.size();i++){
    line[index].first = points[i];
    line[index].second.second = i;
    line[index++].second.first = 1;
  }
  for(size_t i=0;i<ends.size();i++){
    line[index].first = ends[i];
    line[index].second.second = i;
    line[index++].second.first = 2;
  }
  sort(line, line+n);
  int left =0, right = 0, point = 0;
  for(size_t i=0;i<n;i++){
    if(line[i].second.first==0)
      left++;
    else if(line[i].second.first==1){
      if(left>right)
        cnt[line[i].second.second] = left-right;
      if(++point>=points.size())
        break;
    }else if(line[i].second.first==2)
      right++;
  }
  return cnt;
}

vector<int> naive_count_segments(vector<int> starts, vector<int> ends, vector<int> points) {
  vector<int> cnt(points.size());
  for (size_t i = 0; i < points.size(); i++) {
    for (size_t j = 0; j < starts.size(); j++) {
      cnt[i] += starts[j] <= points[i] && points[i] <= ends[j];
    }
  }
  return cnt;
}

int main() {
  int n, m;
  std::cin >> n >> m;
  vector<int> starts(n), ends(n);
  for (size_t i = 0; i < starts.size(); i++) {
    std::cin >> starts[i] >> ends[i];
  }
  vector<int> points(m);
  for (size_t i = 0; i < points.size(); i++) {
    std::cin >> points[i];
  }
  //use fast_count_segments
  vector<int> cnt = fast_count_segments(starts, ends, points);
  for (size_t i = 0; i < cnt.size(); i++) {
    std::cout << cnt[i] << ' ';
  }
}
