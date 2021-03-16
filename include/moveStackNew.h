// Copyright 2021 ivan <ikhonyak@gmail.com>
#ifndef INCLUDE_MOVESTACKNEW_HPP_
#define INCLUDE_MOVESTACKNEW_HPP_

#include <iostream>
#include <Elem.hpp>
#include <utility>
//Задание 1.
template <typename T>
class moveStackNew{
 public:
  moveStackNew();
  moveStackNew(moveStackNew &elem);//перемещаем stack левосторонней ссылкой.
  moveStackNew(moveStackNew &&elem);//
  ~moveStackNew();

  auto operator =(moveStackNew<T> &Elem) -> moveStackNew<T>&;
  auto operator =(moveStackNew<T> &&Elem) -> moveStackNew<T>&;
  void push(T&& value);
  void push(const T& value);
  void pop();
  const T& head() const;
  [[nodiscard]] size_t size() const;
  [[nodiscard]] bool empty() const;
 private:
  Elem<T>* headElem = nullptr;
};

template <typename T>
auto moveStackNew<T>::operator=(moveStackNew<T>&& elem) -> moveStackNew<T>& {
  headElem = std::forward<Elem<T>>(elem.headElem);
  return *this;
}

template <typename T>
auto moveStackNew<T>::operator =(moveStackNew<T> &Elem) -> moveStackNew<T>&{
  headElem = Elem.headElem;
  Elem.headElem = nullptr;
  return *this;
}

template <typename T>
moveStackNew<T>::moveStackNew() {}

template <typename T>
moveStackNew<T>::moveStackNew(moveStackNew<T>&& elem) {
  headElem = new Elem<T>{std::forward<T>(elem.head()), elem};
  elem.headElem = nullptr;
}

template <typename T>
moveStackNew<T>::moveStackNew(moveStackNew<T>& elem) {
  headElem = std::move(elem.headElem);
  elem.headElem = nullptr;
}

template <typename T>
moveStackNew<T>::~moveStackNew<T>() {
  while (headElem != nullptr)
    pop();
}

template <typename T>
void moveStackNew<T>::push(T&& value) {
  Elem<T>* link = headElem;
  headElem = new Elem<T>{std::forward<T>(value), link};
}

template <typename T>
void moveStackNew<T>::push(const T& value) {
  Elem<T>* link = headElem;
  headElem = new Elem<T>{value, link};
}

template <typename T>
void moveStackNew<T>::pop(){
  if (headElem == nullptr)
    throw std::out_of_range("N = 0!");
  Elem<T>* link = headElem;
  headElem = headElem->previousElem;
  delete link;
}

template <typename T>
const T & moveStackNew<T>::head() const {
  if (empty()){
    throw std::out_of_range("Stack is empty!");
  } else {
    return headElem->elem;
  }
}

template <typename T>
bool moveStackNew<T>::empty() const{
  return headElem == nullptr;
}

template <typename T>
size_t moveStackNew<T>::size() const {
  size_t n = 0;
  Elem<T> *link = headElem;
  while (link != nullptr){
    ++n;
    link = link->previousElem;
  }
  return n;
}

#endif  // INCLUDE_MOVESTACKNEW_HPP_
