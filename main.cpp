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

Node* find(int val)
{
  auto p=head;
  int level=2;
  while(p->l[level]||level)
  {
    if(level==-1)
      return NULL;
    if(!p->l[level])
    {
      level--;
    }
    if(p->l[level]->data<val)
    {
      p=p->l[level];
    }
    else if(p->l[level]->data==val)
      return p->l[level];
    else
    {
      level--;
    }
  }
  return NULL;
}

void delete_val(int val)
{
    Node *deleteNode = find(val);
    if(!deleteNode)
      return;
    auto it = find(m.begin(),m.end(),deleteNode);
    int index = it-m.begin();
    m[index-1]->l[0]=m[index]->l[0];
    m.erase(it);
    for(int i=0;i<index;i++)
    {
      for(int j=1;j<3;j++)
      {
        m[i]->l[j] = m[i+(1<<j)+1];
      }
    }
    cout<<"Element "<<val<<"is deleted."<<endl;
    s--;
}

void display()
{
  int level=0;
  while(level<=2)
  {
    auto p=head;
    cout<<"Level "<<level<<" : ";
    while(p)
    {
      cout<<p->data<<" ";
      p=p->l[level];
    }
    level++;
  }

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
  ifstream input;
	input.open("data.txt");
  int val;
  int choice;
  int file=0;
  do
  {
      if(file)
      {
        input>>choice;
      }
      else
      {
        cout<<"\nSkipList Operations\n";
        cout<<"1. Insert"<<endl;
        cout<<"2. Search"<<endl;
        cout<<"3. Delete"<<endl;
        cout<<"4. Display"<<endl;
        cout<<"5. End"<<endl;
        cout<<"Enter your Choice: ";
        cin>>choice;
      }
      switch (choice)
      {
      case 1 :
        if(file)
        {
          input>>val;
        }
        else{
          cout<<"Enter integer element to insert: ";
          cin>>val;
        }
        insert(val);
        break;
      case 2 :
        if(file)
        {
          input>>val;
        }
        else
        {
          cout<<"Enter integer element to search: ";
          cin>>val;
        }
        if (find(val)!=NULL)
            cout<<val<<"Element is found in the skip list"<<endl;
        else
            cout<<val<<"Element is not found"<<endl;
        break;
      case 3:
        if(file)
        {
          input>>val;
        }
        else{
          cout<<"Enter integer element to delete: ";
          cin>>val;
        }
        delete_val(val);
        break;
      case 4 :
          display();
          break;
      case 5:
          break;
      }
  } while (choice!=5);
  input.close();

  //auto  p =head;
  //cout<<head->l[1]->data<<" ";
  //cout<<find(8)<<endl; 
  /*while(p)
  {
    p=p->l[0];
    cout<<p->data<<" ";
  }*/

  return 0;
}