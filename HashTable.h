#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "Global.h"

// 해쉬 테이블 템플릿 클래스
// 키값은 정수, 실수, 문자, 문자열 타입만 받을 수 있다.
// 밸류값은 어떤 타입이든 받을 수 있다.
// 생성자 디폴트 테이블 크기는 100
template<typename K, typename V>
class HashTable
{	
private:		
	vector<vector<pair<K, V>>> m_table;	// 2차원 배열 형태의 테이블
	vector<K> m_keys;					// 키를 빨리 찾기 위한 배열

private:			
	// 키값을 아스키코드 값으로 나열해서 붙힌다
	// ex : ABC -> 979899
	static string GetASCII(string _key);

	// 해쉬값을 만들어준다.
	// 과정
	// 1. 키값의 타입은 분류, 치환된 문자열을 받음
	// 2. 키값의 아스키코드를 나열한 문자열을 받음
	// 3-1. 만에 하나 키값이 하나의 문자로 되어 있을 경우 예외 처리
	// 3-2. 해쉬 공식은 만일 현재 받은 아스키코드값이 979899 일 경우
	//      9 * 7 + 9 + 8 + 9 + 9
	// 4. 만들어진 해쉬값을 반환
	static int GetHash(K _key);

	// 만들어진 해쉬값을 키값으로 변환해준다.
	// 공식은 해쉬값 % 테이블 크기
	int ConvertKey(K _key);

	// 키를 빨리 찾기 위한 배열 이분탐색
	int BinarySearch_Vector(vector<pair<K, V>> _vec, int _hash);
	int BinarySearch_Vector(vector<K> _vec, K _key);

	// sort compare 커스텀
	struct Compare
	{
		bool operator()(pair<K, V>& _a, pair<K, V>& _b) const
		{
			return GetHash(_a.first) < GetHash(_b.first);
		}
	};

	// 현재 테이블 위치의 키를 모두 출력
	void PrintTable();

public:	
	HashTable(KeyType_ALL(K) = nullptr);
	HashTable(int _capacity, KeyType_ALL(K) = nullptr);
	HashTable(HashTable& _hash, KeyType_ALL(K) = nullptr);
	~HashTable();

public:
	// 테이블 크기 읽기
	int Capacity();

	// 테이블 내 값 개수
	int Size();

	// 테이블이 비어있는 지 확인
	bool Empty();

	// 테이블에 값 넣기
	// 현재 테이블에 동일한 키가 있을 경우 그 키의 위치에 있는 값을 변경
	// 아닌 경우 키와 값의 쌍을 추가
	void Insert(K _key, V _value);

	// 값 삭제
	// 키값 위치에 있는 키와 값을 삭제
	bool Delete(K _key);

	// 값 출력
	V GetValue(K _key);

	// 키 여부 확인
	// 키가 있는 지 없는 지 진위 여부 확인
	bool EqualKey(K _key);
	bool EqualKey(K _key, int& _pos);

	// 현재 등록된 키를 모두 출력
	void PrintKey();
};

#include "HashTable.hpp"
#endif HASHTABLE_H