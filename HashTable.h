#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "Global.h"

// �ؽ� ���̺� ���ø� Ŭ����
// Ű���� ����, �Ǽ�, ����, ���ڿ� Ÿ�Ը� ���� �� �ִ�.
// ������� � Ÿ���̵� ���� �� �ִ�.
// ������ ����Ʈ ���̺� ũ��� 100
template<typename K, typename V>
class HashTable
{	
private:		
	vector<vector<pair<K, V>>> m_table;	// 2���� �迭 ������ ���̺�
	vector<K> m_keys;					// Ű�� ���� ã�� ���� �迭

private:			
	// Ű���� �ƽ�Ű�ڵ� ������ �����ؼ� ������
	// ex : ABC -> 979899
	static string GetASCII(string _key);

	// �ؽ����� ������ش�.
	// ����
	// 1. Ű���� Ÿ���� �з�, ġȯ�� ���ڿ��� ����
	// 2. Ű���� �ƽ�Ű�ڵ带 ������ ���ڿ��� ����
	// 3-1. ���� �ϳ� Ű���� �ϳ��� ���ڷ� �Ǿ� ���� ��� ���� ó��
	// 3-2. �ؽ� ������ ���� ���� ���� �ƽ�Ű�ڵ尪�� 979899 �� ���
	//      9 * 7 + 9 + 8 + 9 + 9
	// 4. ������� �ؽ����� ��ȯ
	static int GetHash(K _key);

	// ������� �ؽ����� Ű������ ��ȯ���ش�.
	// ������ �ؽ��� % ���̺� ũ��
	int ConvertKey(K _key);

	// Ű�� ���� ã�� ���� �迭 �̺�Ž��
	int BinarySearch_Vector(vector<pair<K, V>> _vec, int _hash);
	int BinarySearch_Vector(vector<K> _vec, K _key);

	// sort compare Ŀ����
	struct Compare
	{
		bool operator()(pair<K, V>& _a, pair<K, V>& _b) const
		{
			return GetHash(_a.first) < GetHash(_b.first);
		}
	};

	// ���� ���̺� ��ġ�� Ű�� ��� ���
	void PrintTable();

public:	
	HashTable(KeyType_ALL(K) = nullptr);
	HashTable(int _capacity, KeyType_ALL(K) = nullptr);
	HashTable(HashTable& _hash, KeyType_ALL(K) = nullptr);
	~HashTable();

public:
	// ���̺� ũ�� �б�
	int Capacity();

	// ���̺� �� �� ����
	int Size();

	// ���̺��� ����ִ� �� Ȯ��
	bool Empty();

	// ���̺� �� �ֱ�
	// ���� ���̺� ������ Ű�� ���� ��� �� Ű�� ��ġ�� �ִ� ���� ����
	// �ƴ� ��� Ű�� ���� ���� �߰�
	void Insert(K _key, V _value);

	// �� ����
	// Ű�� ��ġ�� �ִ� Ű�� ���� ����
	bool Delete(K _key);

	// �� ���
	V GetValue(K _key);

	// Ű ���� Ȯ��
	// Ű�� �ִ� �� ���� �� ���� ���� Ȯ��
	bool EqualKey(K _key);
	bool EqualKey(K _key, int& _pos);

	// ���� ��ϵ� Ű�� ��� ���
	void PrintKey();
};

#include "HashTable.hpp"
#endif HASHTABLE_H