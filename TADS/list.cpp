#pragma once

template <class T>
class list
{
public:
  virtual void insert(T data) = 0;

  virtual int getPos(T data) = 0;

  virtual T get(int pos) = 0;

  virtual void remove(T data) = 0;

  virtual void removeAt(int pos) = 0;

  virtual bool contains(T data) = 0;

  virtual int size() = 0;

  virtual bool isEmpty() = 0;
};