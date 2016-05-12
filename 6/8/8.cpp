#include <iostream>

using namespace std;

struct StringStruct {
    string *s;
    int count;

    StringStruct(const string &str) {
        s = new string(str);
        count = 1;
    }

    void del() {
        count--;
        if (!count) {
            delete s;
        }
    }
};

class String {
    StringStruct *strstruct;
public:
    String(const char *str = "") {
        strstruct = new StringStruct(string(str));
    }
    String(const String &a) {
        strstruct = a.strstruct;
        strstruct->count++;
    }

    String(String &&a) {
        strstruct = a.strstruct;
        a.strstruct = nullptr;
    }

    operator string() const {
        return *(strstruct->s);
    }

    String & operator +=(const string &str) {
        string tmp = *(strstruct->s) + str;
        strstruct->del();
        if (!strstruct->count) {
            delete strstruct;
        }
        strstruct = new StringStruct(tmp);
        return *this;
    }

    String &operator =(const String &str) {
        if (this == &str) {
            return *this;
        }
        strstruct->del();
        if (!strstruct->count) {
            delete strstruct;
        }
        strstruct = str.strstruct;
        strstruct->count++;
        return *this;
    }

    String &operator =(String &&str) {
        swap(strstruct, str.strstruct);
        return *this;
    }

    char &operator [](int i) {
        string tmp = *(strstruct->s);
        strstruct->del();
        if (!strstruct->count) {
            delete strstruct;
        }
        strstruct = new StringStruct(tmp);
        return (*(strstruct->s))[i];
    }


    char operator [](int i) const {
        return (*(strstruct->s))[i];
    }

    ~String() {
        strstruct->del();
        if (!strstruct->count) {
            delete strstruct;
        }
    }
};
/*
int main()
{
    String c, a = "abc";

    String b = a; // в памяти хранится "abc" в одном экземпляре
    c = a;
    b += "aaa"; // для b создался новый "массив" символов.
    c[1] = 'f'; // a не изменилось
    cout << string(a) << endl;
    cout << string(b) << endl;
    cout << string(c) << endl;
    return 0;
}
*/
