#include "HashTable.h"

int main()
{
    HashTable<string, string> hash(1);

    hash.Insert("3", "hi");
    cout << "Insert >> Key [3] : " << hash.GetValue("3") << endl;
    hash.Insert("1", "bye");
    cout << "Insert >> Key [1] : " << hash.GetValue("1") << endl;
    hash.Insert("2", "hash");
    cout << "Insert >> Key [2] : " << hash.GetValue("2") << endl;
    hash.Insert("2", "table");
    cout << "Insert >> Key [2] : " << hash.GetValue("2") << endl;
    hash.Insert("3", "templete");
    cout << "Insert >> Key [3] : " << hash.GetValue("3") << endl;

    cout << endl;

    if (hash.Empty()) cout << "Empty" << endl;
    else cout << "Count : " << hash.Size() << endl;

    cout << endl;
    hash.PrintKey();
    cout << endl;

    cout << "Key [1] ->" << (hash.EqualKey("1") ? "키 있음" : "키 없음") << endl;
    cout << "Key [2] ->" << (hash.EqualKey("2") ? "키 있음" : "키 없음") << endl;
    cout << "Key [3] ->" << (hash.EqualKey("3") ? "키 있음" : "키 없음") << endl;

    hash.Delete("2");
    cout << endl;
    cout << "Delete >> Key [2] " << endl << "Count : " << hash.Size() << endl;

    cout << endl;
    hash.PrintKey();
    cout << endl;

    cout << "Key [1] ->" << (hash.EqualKey("1") ? "키 있음" : "키 없음") << endl;
    cout << "Key [2] ->" << (hash.EqualKey("2") ? "키 있음" : "키 없음") << endl;
    cout << "Key [3] ->" << (hash.EqualKey("3") ? "키 있음" : "키 없음") << endl;

    return 0;
}