/*
    RAII
    Хранится сам указатель и функция, с помощью которой удаляем

    auto_ptr - копирование с передачей вдаления
    Нельзя хранить вектор auto_ptr, так как при sort - qsort - выбирается пилотный объект и свзь разррушается


    unique_ptr - обеспечивает эксклюзивное владение ресурсом - запрет копирования

    f(T *) - может принимать nullptr
    f(T &)
    f(unique_ptr<T>)

    При new T() утечки памяти не будет
    Аргументы функции вычисляются в произвольном порядке
    C++14 make_unique<T>();
    unique_ptr <T[]>p(new T[5])


    shared_ptr - T* и счетчик ссылок
    При циклических ссылках проблема
    make shared <T>();

    weak_ptr - слабая ссылка - можно копировать - отдельно счетчик ссылок, отдельно указатель
    weak_ptr p; p.lock() -> shared_ptr;
    enable_shared_from_this<A>

    intrusive_ptr - быстрее чем shared_ptr - счетчик ссылок внутри себя - не поддержвает weak_ptr
    shared_ptr - потокобезобасные, но изменение shared_ptr не потокобезопасно



*/

int main(int argc, char const *argv[]) {
    int n = 5, m = 6;
/*
    int **a = new int *[n];
    for (int i = 0; i != n; i++) {
        a[i] = new int[m];
    }
*/

    int **a = new int *[n];
    a[0] = new int[n * m];
    for (int i = 1; i !=n; i++) {
        a[i] = a[0] + i * m;
    }
    return 0;
}
