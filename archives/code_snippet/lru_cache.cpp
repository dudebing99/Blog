#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

template <class K, class T>
struct LRUCacheEntry {
    K key;
    T data;
    LRUCacheEntry *prev;
    LRUCacheEntry *next;
};

template <class K, class T>
class LRUCache {
   private:
    unordered_map<K, LRUCacheEntry<K, T> *> mapping;
    vector<LRUCacheEntry<K, T> *> freeEntries;
    LRUCacheEntry<K, T> *head;
    LRUCacheEntry<K, T> *tail;

    LRUCacheEntry<K, T> *entries;

   public:
    LRUCache(size_t size) {
        entries = new LRUCacheEntry<K, T>[size];
        for (int i = 0; i < size; i++) {
            freeEntries.push_back(entries + i);
        }
        head       = new LRUCacheEntry<K, T>;
        tail       = new LRUCacheEntry<K, T>;
        head->prev = NULL;
        head->next = tail;
        tail->next = NULL;
        tail->prev = head;
    }
    ~LRUCache() {
        delete head;
        delete tail;
        delete[] entries;
    }
    void Debug() {
        cout << "All cached elements:" << endl;
        LRUCacheEntry<K, T> *ptr = head;
        while ((ptr = ptr->next) != tail) {
            cout << ptr->key << " ==> " << ptr->data << endl;
        }
    }
    void Put(K key, T data) {
        LRUCacheEntry<K, T> *node = mapping[key];
        if (node) {
            // refresh the link list
            detach(node);
            node->data = data;
            attach(node);
        } else {
            // cache is full
            if (freeEntries.empty()) {
                node = tail->prev;
                detach(node);
                mapping.erase(node->key);
                node->data = data;
                node->key  = key;
                attach(node);
            } else {
                node = freeEntries.back();
                freeEntries.pop_back();
                node->key    = key;
                node->data   = data;
                mapping[key] = node;
                attach(node);
            }
        }
    }

    T Get(K key) {
        LRUCacheEntry<K, T> *node = mapping[key];
        if (node) {
            detach(node);
            attach(node);
            return node->data;
        } else {
            return T();
        }
    }

   private:
    void detach(LRUCacheEntry<K, T> *node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }
    void attach(LRUCacheEntry<K, T> *node) {
        node->next       = head->next;
        node->prev       = head;
        head->next       = node;
        node->next->prev = node;
    }
};

int main() {
    LRUCache<int, string> lruCache(3);
    lruCache.Put(1, "one");
    lruCache.Debug();
    lruCache.Put(2, "two");
    lruCache.Debug();
    lruCache.Put(3, "three");
    lruCache.Debug();
    lruCache.Put(2, "two");
    lruCache.Debug();
    lruCache.Put(4, "four");
    lruCache.Put(1, "one");
    lruCache.Debug();

    return 0;
}