#include <iostream>
#include <vector>

struct foo {
    foo(std::initializer_list<int> items) 
    : size(items.size())
    , arr(new int[items.size()])
    {
        std::cout << "foo consdtructed from init_list\n";
        for (int i = 0; auto item : items)
            arr[i++] = item;
    }

    foo(const foo& other)
    : size(other.size)
    , arr(new int[other.size])
    {
        std::cout << "foo copyed\n";
        for (size_t i = 0; i < size; ++i)
            arr[i] = other.arr[i];
    }

    foo(foo&& other)
    : size(other.size)
    , arr(other.arr)
    {
        std::cout << "foo moved\n";
        other.size = 0;
        other.arr = nullptr;
        other.~foo();
    }

    ~foo() {
        if (arr != nullptr) {
            std::cout << "foo destroyed\n";
            delete[] arr;
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const foo& foo);

    size_t size;
    int* arr;
};

std::ostream& operator<<(std::ostream& os, const foo& foo) {
    os << '[';
    if (foo.size > 0)
        os << foo.arr[0];
    for (size_t i = 1; i < foo.size; ++i) {
        os << ',' << foo.arr[i];
    }
    os << ']';
    
    return os;
}

int main() {
    foo f = {1,2,3,4,5};

    std::cout << "f: " << f << '\n';

    foo f2 = std::move(f);

    f2.arr[0] = 42;

    std::cout << "f: " << f << '\n';
    std::cout << "f2: " << f2 << '\n';
}