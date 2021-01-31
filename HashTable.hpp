#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

#include "HashTable.h"

// 정수, 실수, 문자, 문자열 키값 타입을 분류해서 문자열로 캐스팅
// is_string, is_const_character_pointer 등등 몇몇 함수는 커스텀
// ---------------------------------------------------------
template <typename K>
KeyType_String(K)
KeyType(K _type, string& _key)
{
	_key = _type;
}

template <typename K>
KeyType_Float(K)
KeyType(K _type, string& _key)
{
	_key = to_string(static_cast<double>(_type));
}

template <typename K>
KeyType_Int(K)
KeyType(K _type, string& _key)
{
	_key = to_string(static_cast<int>(_type));
}

// ---------------------------------------------------------

template<typename K, typename V>
HashTable<K, V>::HashTable(KeyType_ALL(K))
{
	m_table = vector<vector<pair<K, V>>>(DEFAULT_SIZE);
}

template<typename K, typename V>
HashTable<K, V>::HashTable(int _capacity, KeyType_ALL(K))
{
	if (_capacity <= 0) m_table = vector<vector<pair<K, V>>>(DEFAULT_SIZE);
	else m_table = vector<vector<pair<K, V>>>(_capacity + 1); 
}

template<typename K, typename V>
HashTable<K, V>::HashTable(HashTable& _hash, KeyType_ALL(K))
{
	*this = _hash; 
}

template<typename K, typename V>
HashTable<K, V>::~HashTable()
{
	m_table.clear(); 
	m_keys.clear();
}

template<typename K, typename V>
int HashTable<K, V>::Capacity()
{
	return m_table.size();
}

template<typename K, typename V>
int HashTable<K, V>::Size()
{
	return m_keys.size();
}

template<typename K, typename V>
bool HashTable<K, V>::Empty()
{
	return m_keys.empty();
}

template<typename K, typename V>
string HashTable<K, V>::GetASCII(string _key)
{
	string key;
	for (int i = 0; i < _key.size(); i++)
	{
		int asc = _key[i];
		key += to_string(asc);
	}
	return key;
}

template<typename K, typename V>
int HashTable<K, V>::GetHash(K _key)
{
	string key;

	KeyType(_key, key);
	key = GetASCII(key);
	if (key.size() <= 1) return key[0];

	int hash = key[0] * key[1];
	for (int i = 2; i < key.size(); i++)
		hash += key[i];

	return hash;
}

template<typename K, typename V>
int HashTable<K, V>::ConvertKey(K _key)
{
	return GetHash(_key) % Capacity();
}

template<typename K, typename V>
int HashTable<K, V>::BinarySearch_Vector(vector<pair<K, V>> _vec, int _hash)
{
	int max = _vec.size() - 1;
	int min = 0;
	int middle = (max % 2 == 0 ? max / 2 : (max / 2) + 1);

	while (GetHash(_vec[middle].first) != _hash)
	{
		if (GetHash(_vec[middle].first) < _hash)
		{
			min = middle;
			middle = max + min;
		}
		else
		{
			middle = min + middle;
			if (middle == 1)
				middle = 0;
		}

		middle = (middle % 2 == 0 ? middle / 2 : (middle / 2) + 1);

		if (middle == max || middle != 0) break;
	}

	if (GetHash(_vec[middle].first) == _hash)
		return middle;
	else
		return -1;
}

template<typename K, typename V>
int HashTable<K, V>::BinarySearch_Vector(vector<K> _vec, K _key)
{
	int max = _vec.size() - 1;
	int min = 0;
	int middle = (max % 2 == 0 ? max / 2 : (max / 2) + 1);

	while (_vec[middle] != _key)
	{
		if (_vec[middle] < _key)
		{
			min = middle;
			middle = max + min;
		}
		else
		{
			middle = min + middle;
			if (middle == 1)
				middle = 0;
		}

		middle = (middle % 2 == 0 ? middle / 2 : (middle / 2) + 1);

		if (middle == max || middle != 0) break;
	}

	if (_vec[middle] == _key)
		return middle;
	else
		return -1;
}

template<typename K, typename V>
void HashTable<K, V>::Insert(K _key, V _value)
{
	int pos;
	if (EqualKey(_key, pos))
	{		
		if (pos != -1 && m_table[ConvertKey(_key)][pos].first == _key)
		{
			m_table[ConvertKey(_key)][pos].second = _value;
			sort(m_table[ConvertKey(_key)].begin(), m_table[ConvertKey(_key)].end(), Compare());
			return;
		}
	}

	m_table[ConvertKey(_key)].push_back(make_pair(_key, _value));
	sort(m_table[ConvertKey(_key)].begin(), m_table[ConvertKey(_key)].end(), Compare());
	m_keys.push_back(_key);
	sort(m_keys.begin(), m_keys.end());
}

template<typename K, typename V>
bool HashTable<K, V>::Delete(K _key)
{
	vector<pair<K, V>> v = m_table[ConvertKey(_key)];
	if (v.empty()) return false;

	int pos = BinarySearch_Vector(v, GetHash(_key));
	if (pos != -1 && v[pos].first == _key)
	{
		m_table[ConvertKey(_key)].erase(m_table[ConvertKey(_key)].begin() + pos);

		pos = BinarySearch_Vector(m_keys, _key);
		m_keys.erase(m_keys.begin() + pos);
		return true;
	}
	return false;
}

template<typename K, typename V>
V HashTable<K, V>::GetValue(K _key)
{
	vector<pair<K, V>> v = m_table[ConvertKey(_key)];
	if (v.empty()) return V();

	int pos = BinarySearch_Vector(v, GetHash(_key));
	if (pos != -1)
		return v[pos].second;
	return V();
}

template<typename K, typename V>
bool HashTable<K, V>::EqualKey(K _key)
{
	vector<pair<K, V>> v = m_table[ConvertKey(_key)];
	if (v.empty()) return false;

	int pos = BinarySearch_Vector(v, GetHash(_key));
	if (pos != -1 && v[pos].first == _key)
		return true;	

	return false;
}

template<typename K, typename V>
bool HashTable<K, V>::EqualKey(K _key, int& _pos)
{
	vector<pair<K, V>> v = m_table[ConvertKey(_key)];
	if (v.empty()) return false;

	int pos = BinarySearch_Vector(v, GetHash(_key));
	if (pos != -1 && v[pos].first == _key)
	{
		_pos = pos;
		return true;
	}

	return false;
}

template<typename K, typename V>
void HashTable<K, V>::PrintKey()
{
	cout << "Keys" << endl << "[ ";
	for (int i = 0; i < m_keys.size(); i++)
	{
		cout << m_keys[i];
		if (i != m_keys.size() - 1) cout << " , ";
	}
	cout << " ]" << endl;
}

template<typename K, typename V>
void HashTable<K, V>::PrintTable()
{
	for (int i = 0; i < m_table.size(); i++)
	{
		printf("[ %d ]\n", i);
		for (int j = 0; j < m_table[i].size(); j++)
			cout << m_table[i][j].first << ",";
		cout << endl;
	}
}

#endif  HASHTABLE_HPP