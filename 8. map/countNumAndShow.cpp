#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <map>

// [0](http://c.biancheng.net/view/518.html)
using namespace std;
using Record_t = pair<string, string>;
int main(void)
{
  const Record_t _records[] = {{"10.3.8.211", "weisong"},
                               {"10.3.8.211", "weisong"},
                               {"10.3.8.211", "other"},
                               {"127.0.0.1", "adamin"}};
  unordered_multimap<string, string> records;
  for(int i=0; i<sizeof(_records)/sizeof(Record_t); ++i)
    records.insert(_records[i]);
  string ip1("10.3.8.211");
  string ip2("127.0.0.1");
  cout << ip1+" 访问次数 " << records.count(ip1) << endl;
  auto pr = records.equal_range(ip1);
  for(auto p=pr.first; p!=pr.second; ++p) {
    cout << p->second << ", ";
  }
  cout << endl;
  cout << endl;
  cout << endl;

  multimap<string, string> records2;
  for(int i=0; i<sizeof(_records)/sizeof(Record_t); ++i)
    records2.insert(_records[i]);
  auto p=records2.begin();
  while(p!=records2.end()) {
    cout << p->first << " 访问次数: " << records2.count(p->first) << endl;
    auto pr2 = records2.equal_range(p->first);
    // cout << distance(pr2.first, pr2.second) << endl;
    for(auto p2=pr2.first; p2!=pr2.second; ++p2)
      cout << p2->second << ", ";
    cout << endl;
    p = pr2.second;
  }

  return 0;
}

