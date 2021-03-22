// Copyright 2021 ivan <ikhonyak@gmail.com>
#ifndef INCLUDE_STACK_N_HPP_
#define INCLUDE_STACK_N_HPP_

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
  StructElem<T>* headElem = nullptr;
};

template <typename T>
auto Sstack<T>::operator=(Sstack<T>&& elem) -> Sstack<T>& {
  headElem = std::forward<StructElem<T>>(elem.headElem);
  return *this;
}

template <typename T>
auto Sstack<T>::operator=(Sstack<T>& Elem) -> Sstack<T>& {
  headElem = Elem.headElem;
  Elem.headElem = nullptr;
  return *this;
}

template <typename T>
Sstack<T>::Sstack() {}

template <typename T>
Sstack<T>::Sstack(Sstack<T>& elem) {
  headElem = std::move(elem.headElem);
  elem.headElem = nullptr;
}

template <typename T>
Sstack<T>::Sstack(Sstack<T>&& elem) {
  headElem = new StructElem<T>{std::forward<T>(elem.head()), elem};
  elem.headElem = nullptr;
}

template <typename T>
Sstack<T>::~Sstack<T>() {
  while (headElem != nullptr) pop();
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
  StructElem<T>* link = headElem;
  headElem = new StructElem<T>(std::forward<T>(value), link);
}

template <typename T>
const T& Sstack<T>::head() const {
  if (empty()) {
    throw std::out_of_range("Stack is empty!");
  } else {
    return headElem->elem;
  }
}

template <typename T>
T Sstack<T>::pop() {
  if (headElem == nullptr) throw std::out_of_range("N = 0!");
  StructElem<T>* link = headElem;
  headElem = headElem->previousElem;
  T elem = *link->elem;
  delete link;
  return elem;
}

template <typename T>
size_t Sstack<T>::size() const {
  size_t n = 0;
  StructElem<T>* link = headElem;
  while (link != nullptr) {
    ++n;
    link = link->previousElem;
  }
  return n;
}

template <typename T>
bool Sstack<T>::empty() const {
  return headElem == nullptr;
}

#endif  // INCLUDE_STACK_N_HPP_
