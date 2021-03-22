// Copyright 2021 ivan <ikhonyak@gmail.com>
#ifndef INCLUDE_SSTACK_HPP_
#define INCLUDE_SSTACK_HPP_

#include <StructElem.h>
#include <iostream>
#include <utility>
template <typename T>
class Sstack {
 public:
  Sstack();
  Sstack(Sstack<T>& elem);
  Sstack(Sstack<T>&& elem);
  ~Sstack();

  template <typename... Args>
  void push_emplace(Args&&... value);
  void push(T&& value);
  const T& head() const;
  T pop();
  [[nodiscard]] bool empty() const;
  [[nodiscard]] size_t size() const;

  auto operator=(Sstack<T>&& elem) -> Sstack<T>&;
  auto operator=(Sstack<T>& Elem) -> Sstack<T>&;

 private:
  StructElem<T>* head_Elem = nullptr;
};

template <typename T>
auto Sstack<T>::operator=(Sstack<T>&& elem) -> Sstack<T>& {
  head_Elem = std::forward<StructElem<T>>(elem.head_Elem);
  return *this;
}

template <typename T>
auto Sstack<T>::operator=(Sstack<T>& Elem) -> Sstack<T>& {
  head_Elem = Elem.head_Elem;
  Elem.head_Elem = nullptr;
  return *this;
}

template <typename T>
Sstack<T>::Sstack() {}

template <typename T>
Sstack<T>::Sstack(Sstack<T>& elem) {
  head_Elem = std::move(elem.head_Elem);
  elem.head_Elem = nullptr;
}

template <typename T>
Sstack<T>::Sstack(Sstack<T>&& elem) {
  head_Elem = new StructElem<T>{std::forward<T>(elem.head()), elem};
  elem.head_Elem = nullptr;
}

template <typename T>
Sstack<T>::~Sstack<T>() {
  while (head_Elem != nullptr) pop();
}

template <typename T>
template <typename... Args>
void Sstack<T>::push_emplace(Args&&... value) {
  if ((std::is_copy_assignable<T>::value) ||
      (std::is_copy_constructible<T>::value))
    throw std::bad_typeid();
  push(value...);
}

template <typename T>
void Sstack<T>::push(T&& value) {
  if ((std::is_copy_assignable<T>::value) ||
      (std::is_copy_constructible<T>::value))
    throw std::bad_typeid();
  StructElem<T>* link = head_Elem;
  head_Elem = new StructElem<T>(std::forward<T>(value), link);
}

template <typename T>
const T& Sstack<T>::head() const {
  if (empty()) {
    throw std::out_of_range("Stack is empty!");
  } else {
    return head_Elem->elem;
  }
}

template <typename T>
T Sstack<T>::pop() {
  if (head_Elem == nullptr) throw std::out_of_range("N = 0!");
  StructElem<T>* link = head_Elem;
  head_Elem = head_Elem->early_Elem;
  T elem = *link->elem;
  delete link;
  return elem;
}

template <typename T>
size_t Sstack<T>::size() const {
  size_t n = 0;
  StructElem<T>* link = head_Elem;
  while (link != nullptr) {
    ++n;
    link = link->early_Elem;
  }
  return n;
}

template <typename T>
bool Sstack<T>::empty() const {
  return head_Elem == nullptr;
}

#endif  // INCLUDE_SSTACK_HPP_"
