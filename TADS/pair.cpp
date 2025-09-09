#pragma once

template <class T1, class T2>
class pair
{
public:
  T1 fst;
  T2 snd;

  bool operator==(const pair<T1, T2> &other)
  {
    return this->fst == other.fst;
  }

  pair()
  {
  }

  pair(T1 fst)
  {
    this->fst = fst;
  }

  pair(T1 fst, T2 snd)
  {
    this->fst = fst;
    this->snd = snd;
  }
};