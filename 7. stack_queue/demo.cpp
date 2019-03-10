#include <iostream>
#include <stack>
#include <queue>

using namespace std;
class A {
  public:
    A(int v) { val = v;}
    int getval(void) const { return val;}
    friend bool operator<(const A& a, const A& b);
  private:
    int val;
};
bool operator<(const A& a, const A& b)
{
  return a.getval()<b.getval();
}

int main(void)
{
  int a[] = {4,5,1,2,3};
  stack<A> s;
  queue<A> q;
  priority_queue<A> pq;
  for(int i=0; i<5; ++i) {
    q.push(A(a[i]));
    s.push(A(a[i]));
    pq.push(A(a[i])); // max heap
  }
  while(!q.empty()) {cout << q.front().getval(); q.pop();}
  cout << endl; // 45123
  while(!s.empty()) {cout << s.top().getval(); s.pop();} 
  cout << endl; // 32154
  while(!pq.empty()) {cout << pq.top().getval(); pq.pop();} 
  cout << endl; // 54321

  return 0;
}

