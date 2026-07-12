#include <iostream>
using namespace std;

struct node {
  int value;
  node* next;
};

// a)
bool isOdd(int num) {
  return num % 2 == 1;
}

void insertSum(node* head) {
  if (head == nullptr) {
    cout << "List is empty";
    return;
  }

  node* iter = head;

  while (iter && iter->next) {  // it is not a single node
    bool currIsOdd = isOdd(iter->value);
    bool nextIsOdd = isOdd(iter->next->value);

    if (currIsOdd && nextIsOdd) {
      node* tmp = iter->next;

      try {
        iter->next = new node{iter->value + iter->next->value,
                              tmp};  // insert between them
      } catch (const std::bad_alloc&) {
        cerr << "Problem with allocating memory";
        return;
      }

      iter = tmp;
      continue;
    }

    iter = iter->next;
  }
}

// б)
void free(node* head) {
  while (head) {
    node* toDel = head;
    head = head->next;
    delete toDel;
  }
}

void print(node* head) {
  while (head) {
    cout << head->value << ' ';
    head = head->next;
  }
  cout << '\n';
}

node* createList(int itemCnt) {
  node* newNode = nullptr;

  if (itemCnt == 0) {
    return newNode;
  }

  try {
    int value;
    cin >> value;

    newNode = new node{value, createList(itemCnt - 1)};
  } catch (const bad_alloc&) {
    cerr << "Problem with allocating memory";
    return nullptr;
  }

  return newNode;
}

int main() {
  int cnt = 7;
  node* head = createList(cnt);

  print(head);
  insertSum(head);
  print(head);

  free(head);
  return 0;
}
