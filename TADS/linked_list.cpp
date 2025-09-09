#pragma once

#include "./list.cpp"
#include <assert.h>

template <class T>
class linked_list : public list<T>
{
private:
  struct linked_list_node
  {
    T data;
    linked_list_node *next = nullptr;

    linked_list_node(T data)
    {
      this->data = data;
    }
  };
  linked_list_node *head = nullptr;
  int length = 0;

public:
  virtual void insert(T data) override
  {
    linked_list_node *newNode = new linked_list_node(data);
    if (this->head == nullptr)
    {
      head = newNode;
      this->length++;
      return;
    }
    // else head != nullptr

    linked_list_node *aux = this->head;
    while (aux->next != nullptr)
    {
      aux = aux->next;
    }

    aux->next = newNode;
    this->length++;
  }

  virtual int getPos(T data) override {}

  virtual T get(int pos) override
  {
    assert(pos < this->length);

    linked_list_node *aux = this->head;
    for (int i = 0; i < pos; i++)
    {
      aux = aux->next;
    }

    return aux->data;
  }

  virtual void remove(T data) override {}

  virtual void removeAt(int pos) override {}

  virtual int size() override
  {
    return this->length;
  }

  virtual bool isEmpty() override
  {
    return this->length == 0;
  }

  virtual bool contains(T data) override
  {
    linked_list_node *aux = this->head;

    while (aux != nullptr)
    {
      if (aux->data == data)
      {
        return true;
      }
      aux = aux->next;
    }

    return false;
  }
};