// Copyright 2021 ivan <ikhonyak@gmail.com>
#ifndef INCLUDE_STACK_N_HPP_
#define INCLUDE_STACK_N_HPP_

#include <Elem.h>
#include <iostream>
#include <utility>
//Задание2
template <typename T>
class stack_n
{
 public:
  stack_n();
  stack_n(stack_n<T>& elem);
  stack_n(stack_n<T>&& elem);
  ~stack_n();

  template <typename ... Args>
  void push_emplace(Args&&... value);
  void push(T&& value);
  const T& head() const;
  T pop();
  [[nodiscard]] bool empty() const;
  [[nodiscard]] size_t size() const;

  auto operator=(stack_n<T>&& elem) -> stack_n<T>&;
  auto operator =(stack_n<T> &Elem) -> stack_n<T>&;
 private:
  Elem<T>* headElem = nullptr;
};

template <typename T>
auto stack_n<T>::operator=(stack_n<T>&& elem) -> stack_n<T>& {
  headElem = std::forward<Elem<T>>(elem.headElem);
  return *this;
}

template <typename T>
auto stack_n<T>::operator =(stack_n<T> &Elem) -> stack_n<T>&{
  headElem = Elem.headElem;
  Elem.headElem = nullptr;
  return *this;
}

template <typename T>
stack_n<T>::stack_n(){}

template <typename T>
stack_n<T>::stack_n(stack_n<T>& elem) {
  headElem = std::move(elem.headElem);
  elem.headElem = nullptr;
}

template <typename T>
stack_n<T>::stack_n(stack_n<T>&& elem) {
  headElem = new Elem<T>{std::forward<T>(elem.head()), elem};
  elem.headElem = nullptr;
}

template <typename T>
stack_n<T>::~stack_n<T>(){
  while (headElem != nullptr)
    pop();
}

template <typename T>
template <typename ... Args>
void stack_n<T>::push_emplace(Args&&... value) {
  if ((std::is_copy_assignable<T>::value) ||
      (std::is_copy_constructible<T>::value))
    throw std::bad_typeid();
  push(value...);
}

template <typename T>
void stack_n<T>::push(T&& value) {
  if ((std::is_copy_assignable<T>::value) || //проверка на то, явл ли тип некопируемым
      (std::is_copy_constructible<T>::value))
    throw std::bad_typeid();
  Elem<T>* link = headElem;
  headElem = new Elem<T>(std::forward<T>(value), link);
}

template <typename T>
const  T& stack_n<T>::head() const {
  if (empty()) {
    throw std::out_of_range("Stack is empty!");
  } else {
    return headElem->elem;
  }
}

template <typename T>
T stack_n<T>::pop() {
  if (headElem == nullptr)
    throw std::out_of_range("N = 0!");
  Elem<T>* link = headElem;
  headElem = headElem->previousElem;
  T elem = *link->elem;
  delete link;
  return elem;
}

template <typename T>
size_t stack_n<T>::size() const {
  size_t n = 0;
  Elem<T> *link = headElem;
  while (link != nullptr){
    ++n;
    link = link->previousElem;
  }
  return n;
}

template <typename T>
bool stack_n<T>::empty() const {
  return headElem == nullptr;
}

#endif  // INCLUDE_STACK_N_HPP_
