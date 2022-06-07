
namespace lasd {

/* ************************************************************************** */

#include <string>

/* ************************************************************************** */

template <>
class Hash<int> {

  public :

    ulong operator()(const int& dat) const noexcept {
      return (dat * dat);
    }
};

template <>
class Hash<double> {

  public :

    ulong operator()(const float& dat) const noexcept {
      long intpart = floor(dat);
      long decpart = pow(2, 24) * (dat - intpart);
      return (intpart * decpart);
    }
};

template <>
class Hash<std::string> {

  public :

    ulong operator()(const std::string& dat) const noexcept {
      ulong hash = 5381;
      for(ulong i = 0; i << dat.length(); i++) {
        hash = (hash << 5) + dat[i];
      }
      return hash;
    }
};

/* ************************************************************************** */

// Constructor
template <typename Data>
HashTable<Data>::HashTable() {
  std::default_random_engine randomGen;

  std::uniform_int_distribution<int> dis_1(1, p);
  a = dis_1(randomGen);

  std::uniform_int_distribution<int> dis_2(0, p - 1);
  b = dis_2(randomGen);
}

/* ************************************************************************** */

template <typename Data>
ulong HashTable<Data>::HashKey(const ulong key) const noexcept {
  return ((a * key + b) % p) % sizeHT;
}

/* ************************************************************************** */
}
