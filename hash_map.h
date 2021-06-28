#pragma once
#include <utility>

namespace dani {

	template<typename TKey, typename TValue, typename Hash>
	class hash_map {
		using PairType = std::pair<TKey, TValue>;

		class iterator {
			PairType* ptr;
		public:
			iterator(PairType pair) {
				ptr = &pair;
			}
			iterator(PairType* pair) {
				ptr = pair;
			}
			iterator& operator++() {
				ptr++;
				return *this;
			}

			iterator operator++(int x) {
				iterator temp = *this;
				++* this;
				return temp;
			}
			iterator& operator--() {
				ptr--;
				return *this;
			}

			iterator operator--(int x) {
				iterator temp = *this;
				--* this;
				return temp;
			}
			bool operator==(void* other) {
				return ptr == other;
			}
			bool operator==(iterator other) {
				return ptr == other.ptr;
			}
			bool operator!=(iterator other) {
				return ptr != other.ptr;
			}

			PairType* operator->() {
				return ptr;
			}
		};
		PairType* data;
		Hash hasher;
		unsigned long m_size;
		unsigned long num_items = 0;
		unsigned long min_index = 0;
		unsigned long max_index = 0;
		void rehash() {
			PairType* newData = new PairType[m_size * (unsigned long)2];
			for (int i = 0; i < m_size; i++) {
				size_t hash = hasher(data[i].first);
				newData[hash % (m_size * 2)] = data[i];
			}
			delete[] data;
			data = newData;
			m_size = m_size * 2;
		}
	public:
		hash_map() {
			data = new PairType[100];
			m_size = 100;
		}
		hash_map(int m_size) {
			data = new PairType[size];
			m_size = size;
		}
		~hash_map() {
			delete[] data;
		}
		iterator find(TKey key) {
			size_t hash = hasher(key);
			for (unsigned long i = 0; i < m_size; i++) {
				if (hash == hasher(data[i].first))
					return data[i];
			}
			return end();
		}
		TValue& operator[](TKey key) {
			return find(key)->second;
		}
		void insert(TKey key, TValue value) {
			size_t hash = hasher(key);
			while (data[hash % m_size].first == key) {
				rehash();
			}

			if ((float)num_items / m_size > 0.8) {
				rehash();
			}

			data[hash % m_size] = { key, value };
			num_items++;
			if (hash % m_size <= min_index)
				min_index = hash % m_size;
			if (hash % m_size > max_index)
				max_index = hash % m_size + 1;
		}
		void insert(PairType element) {
			insert(element.first, element.second);
		}
		void remove(TKey key) {
			iterator it = find(key);

			num_items--;
		}
		void remove(iterator it) {
			remove(it->first);
		}
		iterator begin() {
			return data + min_index;
		}
		iterator end() {
			return data + max_index;
		}
		unsigned long size() {
			unsigned long a = num_items;
			return a;
		}
	};
}