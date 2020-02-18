#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;
class CompareTime{
  public:
    bool operator() (pair<int, long long> &a, pair<int, long long> &b){
      if(a.second == b.second)
        return a.first > b.first;
      return a.second > b.second;
    }
};
class JobQueue {
 private:
  int num_workers_;
  vector<int> jobs_;

  vector<int> assigned_workers_;
  vector<long long> start_times_;

  void WriteResponse() const {
    for (int i = 0; i < jobs_.size(); ++i) {
      cout << assigned_workers_[i] << " " << start_times_[i] << "\n";
    }
  }

  void ReadData() {
    int m;
    cin >> num_workers_ >> m;
    jobs_.resize(m);
    for(int i = 0; i < m; ++i)
      cin >> jobs_[i];
  }

  void AssignJobs() {
    assigned_workers_.resize(jobs_.size());
    start_times_.resize(jobs_.size());
    priority_queue<pair<int, long long>, vector<pair<int, long long>>, CompareTime> list;
    for(int i=0;i<num_workers_;i++)
      list.push(make_pair(i, 0));
    for(int i=0;i<jobs_.size();i++){
      assigned_workers_[i] = list.top().first;
      start_times_[i] = list.top().second;
      list.pop();
      list.push(make_pair(assigned_workers_[i], start_times_[i]+jobs_[i]));
    }
  }

 public:
  void Solve() {
    ReadData();
    AssignJobs();
    WriteResponse();
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  JobQueue job_queue;
  job_queue.Solve();
  return 0;
}
