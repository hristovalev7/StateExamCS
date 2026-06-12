#include <iostream>
using namespace std;

// a)
struct node {
  int value;
  node* next;
};

bool contains(const node* what, int fromVal) {
  while (what) {
    if (what->value == fromVal) {
      return true;
    }
    what = what->next;
  }

  return false;
}

void removeIf(node*& from, const node* what) {
  // remove matches from begining
  while (from && contains(what, from->value)) {
    node* toDel = from;
    from = from->next;
    delete toDel;
  }

  // remove the rest
  node* iter = from;
  while (iter && iter->next) {
    if (contains(what, iter->next->value)) {
      node* toDel = iter->next;
      iter->next = toDel->next;
      delete toDel;
    } else {
      iter = iter->next;
    }
  }
}

node* merge(node* first, node* second) {
  node* head = nullptr;
  node* tail = nullptr;

  while (first && second) {
    node* chosen = nullptr;
    if (first->value <= second->value) {
      chosen = first;
      first = first->next;
    } else {
      chosen = second;
      second = second->next;
    }

    if (head == nullptr) {
      head = chosen;
    } else {
      tail->next = chosen;
    }

    tail = chosen;
  }

  node* rest = first ? first : second;

  if (head == nullptr) {
    head = rest;
  } else {
    tail->next = rest;
  }

  return head;
}

node* removeDuplicates(node* head) {
  node* iter = head;

  while (iter && iter->next) {
    if (iter->value == iter->next->value) {
      node* toDel = iter->next;
      iter->next = toDel->next;
      delete toDel;
    } else {
      iter = iter->next;
    }
  }

  return head;
}