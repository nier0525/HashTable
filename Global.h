#pragma once
#include <stdio.h>
#include <stdlib.h>

#include <iostream>
#include <algorithm>
#include <string>
#include <type_traits>

#include <set>
#include <vector>
#include <queue>
#include <stack>
#include <list>

using namespace std;

template<typename T>
struct is_string : is_same<T, string> {};

template<typename T>
struct is_const_character_pointer : is_same<T, const char*> {};

template<typename T>
struct is_const_character : is_same<T, const char> {};

template<typename T>
struct is_character_pointer : is_same<T, char*> {};

template<typename T>
struct is_character : is_same<T, char> {};

#define KeyType_ALL(T) typename enable_if<is_arithmetic<T>::value || is_const_character_pointer<T>::value || is_const_character<T>::value || is_character<T>::value || is_character_pointer<T>::value || is_string<T>::value>::type*
#define KeyType_String(K) typename enable_if<is_string<K>::value || is_const_character_pointer<K>::value || is_character_pointer<K>::value>::type
#define KeyType_Float(K) typename enable_if<is_floating_point<K>::value>::type
#define KeyType_Int(K) typename enable_if<is_integral<K>::value>::type

#define DEFAULT_SIZE 1000

typedef int ElementType;

typedef struct SingleNode
{
	struct SingleNode* path;

	ElementType Data;
} SNode;

typedef struct DoubleNode
{
	struct DoubleNode* Left;
	struct DoubleNode* Right;

	ElementType Data;
} DNode;

typedef struct tagBSTNode
{
	struct tagBSTNode* Left;
	struct tagBSTNode* Right;

	ElementType Data;
} BSTNode;