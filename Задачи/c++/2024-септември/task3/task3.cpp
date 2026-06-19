template <typename Type>
struct node {
  const Type data;
  node<Type>* next;
};

// а) Обръщане на списък
template <typename Type>
node<Type>* reverse(node<Type>* first) {
  if (first == nullptr) {
    cout << "Empty List" << endl;
    return first;
  }

  if (first && first->next == nullptr) {
    cout << "Single Element list" << endl;
    return first;
  }

  node<Type>* toRev = nullptr;
  node<Type>* prev = nullptr;

  while (first) {
    toRev = first;
    first = first->next;
    toRev->next = prev;
    prev = toRev;
  }

  return prev;
}

// б) Филтриране на елементи
template <typename Type>
node<Type>* filter(node<Type>* first) {
  node<Type>* iter = first;
  node<Type>* toDel = nullptr;

  while (iter && iter->next) {
    if (iter->next->data == first->data) {
      toDel = iter->next;
      iter->next = toDel->next;
      delete toDel;
    } else {
      iter = iter->next;
    }
  }

  return first;
}

// в) Сортиране на списък (Merge Sort - O(n log n))
template <typename Type>
node<Type>* findMiddle(node<Type>* first) {
  node<Type>* slow = first;
  node<Type>* fast = first->next;

  while (fast != nullptr && fast->next != nullptr) {
    slow = slow->next;
    fast = fast->next->next;
  }

  return slow;
}

template <typename Type>
node<Type>* merge(node<Type>* l1, node<Type>* l2) {
  node<Type> dummy{Type{}, nullptr};
  node<Type>* tail = &dummy;

  while (l1 != nullptr && l2 != nullptr) {
    if (l1->data <= l2->data) {
      tail->next = l1;
      l1 = l1->next;
    } else {
      tail->next = l2;
      l2 = l2->next;
    }
    tail = tail->next;
  }

  tail->next = (l1 != nullptr) ? l1 : l2;
  return dummy.next;
}

template <typename Type>
node<Type>* sort(node<Type>* first) {
  if (first == nullptr || first->next == nullptr) {
    return first;  // 0 or 1 elements already sorted
  }

  // split the list into two parts
  node<Type>* middle = findMiddle(first);
  node<Type>* secondHalf = middle->next;
  middle->next = nullptr;

  node<Type>* left = sort(first);
  node<Type>* right = sort(secondHalf);

  return merge(left, right);
}

// в) Алтернативно сортиране (Insertion Sort - O(n²))
template <typename Type>
node<Type>* sortInsertionSort(node<Type>* first) {
  node<Type>* sortedList = nullptr;
  node<Type>* curr = nullptr;

  while (first) {
    curr = first;
    first = first->next;

    // it's the smallest one so far → place it first
    if (sortedList == nullptr || curr->data <= sortedList->data) {
      curr->next = sortedList;
      sortedList = curr;
    } else {  // walk along the sorted part to find where it fits
      node<Type>* iter = sortedList;
      while (iter->next != nullptr && iter->next->data < curr->data) {
        iter = iter->next;
      }

      curr->next = iter->next;
      iter->next = curr;
    }
  }
  return sortedList;
}
