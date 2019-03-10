#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(void)
{
/*
1.push_back 在数组的最后添加一个数据
2.pop_back 去掉数组的最后一个数据
3.at 得到编号位置的数据
4.begin 得到数组头的指针
5.end 得到数组的最后一个单元+1的指针
6.front 得到数组头的引用
7.back 得到数组的最后一个单元的引用
8.max_size 得到vector最大可以是多大
9.capacity 当前vector分配的大小
10.size 当前使用数据的大小
11.resize 改变当前使用数据的大小，如果它比当前使用的大，者填充默认值
12.reserve 改变当前vecotr所分配空间的大小
13.erase 删除指针指向的数据项
14.clear 清空当前的vector
15.rbegin 将vector反转后的开始指针返回(其实就是原来的end-1)
16.rend 将vector反转构的结束指针返回(其实就是原来的begin-1)
17.empty 判断vector是否为空
18.swap 与另一个vector交换数据
*/
  int a[] = {1, 20, 3, 40};
  vector<int> v_a(a, a+4);
  for(int i=0; i<v_a.size(); ++i)
    cout << v_a[i] << ", ";
/*
  vector<int> v_a; // an empty vector
  for(int i=0; i<4; ++i)
    v_a.push_back(a[i]);
*/
  cout << endl;
  sort(v_a.begin(), v_a.end()); 
  reverse(v_a.begin(), v_a.end()); // decrease sort
  for(vector<int>::iterator i=v_a.begin(); i!=v_a.end(); ++i)
    cout << *i << ", ";
  cout << endl;

#define ROW 2
#define COL 2
  //2-dim array
  int a2[ROW][COL] = {{1, 20},
                      {3, 40}};
  vector< vector<int> > mat(ROW, vector<int>(COL));
  for(int i=0; i<mat.size(); ++i)
  {
    for(int j=0; j<mat[i].size(); ++j)
    {
      mat[i][j] = a2[i][j];
      cout << mat[i][j] << " ";
    }
    cout << endl;
  }

  return 0;
}
