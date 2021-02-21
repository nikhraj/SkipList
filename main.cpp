#include <bits/stdc++.h>
using namespace std;
class Node{
  public:  
    int data;
    vector <Node*> l;
    Node(int value)
    {
      data=value;
      l.resize(3,NULL);
    }
    
};
vector <Node *> m;
Node *head;
int s;
void insert(int val)
{
  //s++;
  if(!head)
  {
    head=new Node(val);
    m[s++]=head;
    return;
  }
  auto p=head;
  while(p->l[0])
  {
    p=p->l[0];
  }
  p->l[0]=new Node(val);
  m[s++]=p->l[0];

  for(int i=0;i<s;i++)
  {
    for(int j=1;j<3;j++)
    {
      if(m[i]->l[j])
        continue;
      m[i]->l[j] = m[i+(1<<j)+1];
    }
  }
  //s++;

}

bool find(int val)
{
  auto p=head;
  int level=2;
  while(p->l[level]||level)
  {
    if(level==-1)
      return false;
    if(!p->l[level])
    {
      level--;
    }
    if(p->l[level]->data<val)
    {
      p=p->l[level];
    }
    else if(p->l[level]->data==val)
      return true;
    else
    {
      level--;
    }
  }
  return false;
}

int main() {
  //size=0;
  s=0;
  m.resize(100,NULL);
  head=NULL;
  insert(1);
  insert(2);
  insert(4);
  insert(6);
  insert(7);
  /*for(int i=0;i<s;i++)
  {
      cout<<m[i]->data<<" ";
  }*/
  auto  p =head;
  cout<<head->l[1]->data<<" ";
  cout<<find(8)<<endl; 
  /*while(p)
  {
    p=p->l[0];
    cout<<p->data<<" ";
  }*/

  return 0;
}