/**
  Link nodes of the tree that are at the same depth
  Using queues. Can also use linked lists
*/
#include <cstdio>
#include <iostream>
#include <queue>

using namespace std;

// Tree of nodes
class Tree {
private:
  struct node {
    int data;
    struct node *left, *right, *nRight = nullptr;
  };
  node *root;

public:
  Tree(vector<int> v) {
    // insert root
    insert(nullptr, v[0]);

    for (int i = 1; i < v.size(); i++)
      insert(&root, v[i]);
  }

  void insert(node **l, int x) {
    node *p;
    if ((root == nullptr) || (*l == nullptr)) {
      // allocate new node
      p = new node;
      p->data = x;
      p->left = p->right = nullptr;

      // 1st node to be added to the node
      if (root == nullptr)
        root = p;
      else
        *l = p;

      return;
    }

    p = (*l);
    if (!p->left)
      insert(&(p->left), x);
    else {
      insert(&(p->right), x);
    }
  }

// BFS ?
  void Linknodes() {
    if (root == nullptr)
      return;

    int count = 0;
    queue<node *> q;
    q.push(root);

    for (;;) {
      count = q.size();
      if (count == 0)
        break;

      node *prev = q.front();
      int n = count;
      while (count > 0) {
        node *next = q.front();
        q.pop();

        if (count != n)
          prev->nRight = next;
        else if (count == 1)
          next->nRight = nullptr;

        if (next->left)
          q.push(next->left);
        if (next->right)
          q.push(next->right);

        prev = next;
        count--;
      }
    }
  }

  void Print() {
    if (root == nullptr)
      return;

    queue<node *> q;
    q.push(root);

    while (!q.empty()) {
      node *next = q.front();
      q.pop();
      //printf("Elem: %d \n", next->data);

      if (next->nRight != nullptr)
        printf("%d right -> %d\n", next->data, next->nRight->data);

      if (next->left)
        q.push(next->left);
      if (next->right)
        q.push(next->right);
    }
  }
};

int main() {
  vector<int> v{20, 8, 2, 3, 5, 6, 9, 10};

  auto t = new Tree(v);
  // Link nodes with the same depth
  t->Linknodes();
  t->Print();
  return 0;
}
