  #pragma once

  #include "./map.cpp"
  #include "./pair.cpp"
  // #include "../functions/hash/hash_func.cpp"
  #include "./linked_list.cpp"

  template <class K, class V>
  class open_hash_map : map<K, V>
  {
  private:
    list<pair<K, V>> *arr;
    int arrSize;
    int count = 0;
    hash_func<K> *h;

    int abs(int x)
    {
      if (x < 0)
      {
        return -x;
      }

      return x;
    }

    int getPos(K key)
    {
      return abs(h->hash(key) % this->arrSize);
    }

  public:
    open_hash_map(int expectedSize, hash_func<K> *h)
      {
      this->h = h;
      this->arrSize = 2 * expectedSize - 1;
      this->arr = new list<pair<K, V>>[this->arrSize];
      for (int i = 0; i < this->arrSize; i++)
      {
        arr[i] = nullptr;
      }
    }

    // -------- Redefinicion de Funciones del map.cpp --------

    virtual void set(K key, V value) override
    {
      remove(key);

      int pos = getPos(key);

      if (this->arr[pos] == nullptr) {
        this->arr[pos] = new linked_list<pair<K, V>>();
      }

      list<pair<K, V>> *bucket = this->arr[pos];
      bucket->insert(pair<K, V>(key, value));
      this->count++;
    }

  virtual V get(K key) override {
      int pos = getPos(key);

      // Si el bucket está vacio, la clave no existe
      if (this->arr[pos] == nullptr) {
          throw std::out_of_range("clave no encontrada");
      }

      list<pair<K, V>>* bucket = this->arr[pos];

      // Recorremos todos los pares dentro del bucket
      for (int i = 0; i < bucket->size(); i++) {
          pair<K, V> actual = bucket->get(i);

          if (actual.fst == key) {   // comparamos directamente la clave
              return actual.snd;     // devolvemos el valor asociado
          }
      }

      // Si no lo encontramos
      throw std::out_of_range("clave no encontrada");
  }

    virtual bool contains(K key) override
    {
      int pos = getPos(key);

      if (this->arr[pos] == nullptr)
      {
        return false;
      }

      list<pair<K, V>> *l = this->arr[pos];
      return l->contains(pair<K, V>(key));
    }

  virtual void remove(K key) override {
      int pos = getPos(key);

      if (this->arr[pos] == nullptr) {
          throw std::out_of_range("clave no encontrada");
      }

      list<pair<K, V>>* bucket = this->arr[pos];

      if (!bucket->contains(pair<K, V>(key))) {
          throw std::out_of_range("clave no encontrada");
      }

      // Borramos el par que tenga esa clave
      bucket->remove(pair<K, V>(key));
      this->count--;
  }

    virtual int size() override
    {
      return this->count;
    }

  };
