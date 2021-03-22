// Copyright 2021 ivan <ikhonyak@gmail.com>
#ifndef INCLUDE_FSTACK_HPP_
#define INCLUDE_FSTACK_HPP_

#include <StructElem.h>
#include <iostream>
#include <utility>

template <typename T>
class FStack {
 public:
  FStack();
  FStack(FStack&elem);
  FStack(FStack&&elem);
  ~FStack();
  auto operator =(FStack<T> &Elem) -> FStack<T>&;
  auto operator =(FStack<T> &&Elem) -> FStack<T>&;
  void push(T&& value);
  void push(const T& value);
  void pop();
  const T& head() const;
  [[nodiscard]] size_t size() const;
  [[nodiscard]] bool empty() const;
 private:
  StructElem<T>* headElem = nullptr;
};

template <typename T>
auto FStack<T>::operator=(FStack<T>&& elem) -> FStack<T>& {
  headElem = std::forward<StructElem<T>>(elem.headElem);
  return *this;
}

template <typename T>
auto FStack<T>::operator =(FStack<T> &Elem) -> FStack<T>&{
  headElem = Elem.headElem;
  Elem.headElem = nullptr;
  return *this;
}

template <typename T>
FStack<T>::FStack() {}

template <typename T>
FStack<T>::FStack(FStack<T>&& elem) {
  headElem = new StructElem<T>{std::forward<T>(elem.head()), elem};
  elem.headElem = nullptr;
}

template <typename T>
FStack<T>::FStack(FStack<T>& elem) {
  headElem = std::move(elem.headElem);
  elem.headElem = nullptr;
}

template <typename T>
FStack<T>::~FStack<T>() {
  while (headElem != nullptr)
    pop();
}

template <typename T>
void FStack<T>::push(T&& value) {
  StructElem<T>* link = headElem;
  headElem = new StructElem<T>{std::forward<T>(value), link};
}

template <typename T>
void FStack<T>::push(const T& value) {
  StructElem<T>* link = headElem;
  headElem = new StructElem<T>{value, link};
}

template <typename T>
void FStack<T>::pop(){
  if (headElem == nullptr)
    throw std::out_of_range("N = 0!");
  StructElem<T>* link = headElem;
  headElem = headElem->previousElem;
  delete link;
}

template <typename T>
const T & FStack<T>::head() const {
  if (empty()){
    throw std::out_of_range("Stack is empty!");
  } else {
    return headElem->elem;
  }
}

template <typename T>
bool FStack<T>::empty() const{
  return headElem == nullptr;
}

template <typename T>
size_t FStack<T>::size() const {
  size_t n = 0;
  StructElem<T> *link = headElem;
  while (link != nullptr){
    ++n;
    link = link->previousElem;
  }
  return n;
}

#endif  // INCLUDE_FSTACK_HPP_"
