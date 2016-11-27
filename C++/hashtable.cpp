/**
Custom implementation of a Generic Hash Table
M < N : mapping large input range into a smaller range for fast retrieval

Could use FNV, Mersenne prime or Horner's method for hashing but chose the last
few chars of the key...
as if e.g. mapping phone numbers, the last few digits would generate less
collisions; as the initial digits would likely correlate.

http://en.cppreference.com/w/cpp/utility/hash
http://www.cs.princeton.edu/courses/archive/spr10/cos226/lectures/10-34HashTables-2x2.pdf
http://en.algoritmy.net/article/50101/Hash-table

Makhtar
*/
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <functional> // std::hash
#include <iostream>
#include <list>
#include <sstream>
#include <utility> // pair

using namespace std;

template <typename KeyT, typename ValT>
class HashTab
{
  private:
    // Number of KeyVals and Hash table size
    uint N, M;

    typedef pair<KeyT, ValT> kvpair;

    // std hashing utility, generates ulong values
    std::hash<KeyT> hashFunc;

    // Custom hash function
    uint hash(KeyT key)
    {
        uint hashCode = 0;
        string s = (string)key;
        for (uint i = 1; i < 4; i++)
            hashCode += s[s.size() - i];

        hashCode = (97 * hashCode) % M;
        return hashCode;
    }

    // Dynamic array of kv's lists
    list<kvpair> **table;

  public:
    uint nCollisions, tableSize;

    HashTab(uint n = 100)
    {
        this->N = n;
        this->M = n / 5;
        this->nCollisions = 0;

        table = new list<kvpair> *[M];
        for (uint i = 0; i < M; i++)
            table[i] = new list<kvpair>();
    }

    /**
  Map a key-val pair
  If the key exist, updates the value
  If collided, push_back in a list of siblings
  */
    void put(KeyT key, ValT val)
    {
        uint idx = hashFunc(key) % M; // hash(key);
        auto spot = table[idx];

        // Check duplicates - O(n) sequential search
        for (auto it = spot->begin(); it != spot->end(); it++)
        {
            if (it->first == key)
            {
                it->second = val;
                printf("Hash idx: %02d updated key: %s -> %02d\n", idx, key.c_str(), val);
                return;
            }
        }
        string msg = "Hash idx: %02d mapped %s -> %02d\n";
        if (spot->size() > 1)
        {
            this->nCollisions++;
            msg = "Hash idx: %02d mapped siblings %s -> %02d\n";
        }
        kvpair kv(key, val);
        // O(1) insertion and removal
        spot->push_back(kv);
        printf(msg.c_str(), idx, key.c_str(), val);
    }

    ValT get(KeyT key)
    {
        uint idx = hashFunc(key) % M; // hash(key);
        auto spot = table[idx];
        for (auto it = spot->begin(); it != spot->end(); it++)
        {
            if (it->first == key)
            {
                printf("Found key %s -> %d, at index %d\n", key.c_str(), it->second, idx);
                return it->second;
            }
        }
        return (ValT)-1;
    }

    void listTable();
};

int main()
{
    auto m = new HashTab<string, uint>();
    stringstream ss;
    uint items = 0;
    for (char c = 'a'; c <= 'z'; c++)
    {
        ss << c;
        printf("%d\t", items);
        m->put(ss.str(), rand() % 100);
        items++;
    }
    // Test key update
    m->put("abc", 10);
    m->get("abcdefg");
    printf("Items: %d, Collisions: %d %.2f\% \n", items, m->nCollisions,
           (float)(m->nCollisions * 100 / items));
    return 0;
}
