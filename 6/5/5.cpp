#include <cstdio>
#include <iostream>

using namespace std;

class FWStruct {
public:
    FILE *f;
    int count;
    FWStruct(const char *s) {
        f = fopen(s, "w");
        count = 1;
    }

    void del() {
        count--;
        if (!count) {
            fclose(f);
        }
    }
};

class FileWrapper {
    FWStruct *fws;
public:
    FileWrapper(const char *s) {
        fws = new FWStruct(s);
    }

    FileWrapper (const FileWrapper &a) {
        fws = a.fws;
        fws->count++;
    }

    FileWrapper (FileWrapper &&a) {
        fws = a.fws;
        a.fws = nullptr;
    }

    FileWrapper &operator <<(char c) {
        fprintf(fws->f, "%c", c);
        return *this;
    }

    FileWrapper &operator =(FileWrapper &a) {
        if (&a == this) {
            return *this;
        }
        if (fws) {
            fws -> del();
            if (!fws->count) {
                delete fws;
            }
        }
        fws = a.fws;
        fws->count++;
        return *this;
    }

    FileWrapper &operator =(FileWrapper &&a) {
        swap(fws, a.fws);
        return *this;
    }


    ~FileWrapper() {
        if (fws) {
            fws->del();
            if (!fws->count) {
                delete fws;
            }
        }
    }
};
/*
int main()
{
    return 0;
}
*/
