#include <algorithm>
#include <iostream>
#include <climits>
#include <vector>
#include <algorithm>

using namespace std;

struct Segment {
  int start, end;
};

vector<int> optimal_points(vector<Segment> &segments) {
  vector<int> points;
  //write your code here
  int l=segments.size(), current=-1;
  for(size_t i=0;i<l;i++){
    for(size_t j=i+1;j<l;j++){
      if(segments[i].end>segments[j].end)
        swap(segments[i],segments[j]);
    }
  }
  for (size_t i = 0; i < l; ++i) {
    if(current<segments[i].start || current>segments[i].end){
      current = segments[i].end;
      points.push_back(current);
    }
  }
  return points;
}

int main() {
  int n;
  std::cin >> n;
  vector<Segment> segments(n);
  for (size_t i = 0; i < segments.size(); ++i) {
    std::cin >> segments[i].start >> segments[i].end;
  }
  vector<int> points = optimal_points(segments);
  std::cout << points.size() << "\n";
  for (size_t i = 0; i < points.size(); ++i) {
    std::cout << points[i] << " ";
  }
}
