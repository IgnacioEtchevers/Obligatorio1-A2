#pragma once

template <class K, class V>
class map
{
public:
  // pos: map contiene valor "value" asociado a la clave "key"
  virtual void set(K key, V value) = 0;
  // pre: map contiene clave "key"
  // ret: devuelve el valor "value" asociado a la clave "key"
  virtual V get(K key) = 0;
  // ret: true sii map contiene clave "key"
  virtual bool contains(K key) = 0;
  // pos: map NO contiene clave "key"
  virtual void remove(K key) = 0;
  // ret: cantidad de elementos en map
  virtual int size() = 0;
};
