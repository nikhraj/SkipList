#include <bits/stdc++.h>
using namespace std;
// Node structure of skip list
class Node{
  public:  
    int data;
    vector <Node*> l;
    Node(int value)
    {
      data=value;
      l.resize(4,NULL);
    }
};
// Map to store pointers
vector <Node *> m;
// head pointer of skip list
Node *head;
// Size of skip list
int s;

// Insert function
void insert(int val)
{
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

/*for(int i=0;i<s;i++)
  {
    for(int j=3;j>=1;j--)
    {
      if(m[i]->l[j])
        break;
      m[i]->l[j] = m[i+(1<<j)+1];
    }
  }*/

  for(int j=1;j<4;j++)
  {
    int i=s-(1<<j)-2;
    if(i>=0)
    {
      m[i]->l[j]=m[s-1];
    }
  }
}

// Find function
Node* find(int val)
{
  auto p=head;
  int level=3;
  while(p->l[level]||level>-1)
  {
    while(!p->l[level])
    {
      level--;
      if(level==-1)
        return NULL; 
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
      if(level==-1)
        return NULL;
    }
  }
  return NULL;
}

// Delete function
void delete_val(int val)
{
    Node *deleteNode = find(val);
    if(!deleteNode)
    {
      cout<<"Element is not present, can't deleted."<<endl;
      return;
    }
    auto it = find(m.begin(),m.end(),deleteNode);
    int index = it-m.begin();
    m[index-1]->l[0]=m[index]->l[0];
  /// delete m[index]->l[0];
    m.erase(it);
    for(int i=0;i<index;i++)
    {
      for(int j=1;j<4;j++)
      {
        m[i]->l[j] = m[i+(1<<j)+1];
      }
    }
    cout<<"Element "<<val<<" is deleted."<<endl;
    s--;
}

// Display function
void display()
{
  int level=0;
  while(level<=3)
  {
    auto p=head;
    cout<<"Level "<<level<<" : ";
    while(p)
    {
      cout<<p->data<<" ";
      p=p->l[level];
    }
    level++;
    cout<<endl;
  }
}

int main() {
  s=0;
  m.resize(100,NULL);
  head=NULL;
  ifstream input;
  input.open("data3.txt");
  int val;
  int choice;
  int file=1;
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
            cout<<val<<" is found in the skip list."<<endl;
        else
            cout<<val<<" is not found."<<endl;
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
        display();
        break;
      case 4 :
          display();
          break;
      case 5:
          break;
      }
  } while (choice!=5);
  input.close();
  return 0;
}