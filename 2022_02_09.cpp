#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iterator>
#include <memory>

namespace asd {

    class Bar {
    public:
        std::string to_be_printed = "Hello from namespace asd";
    };

    void print_adl(const Bar& foo) {
        std::cout << foo.to_be_printed << std::endl;
    }

} // namespace adl

// special member functions
//unique_ptr'ları ögrenmek için yaptım ama dogru oldu mu bilmiyorum
class IntVector {
public:
    int size;
    int reserved;
    std::unique_ptr<int[]> arr;

    IntVector()
        : size(0), reserved(10)
    {
        arr = std::unique_ptr<int[]>(new int[reserved]);
    };

    ~IntVector() = default;

    IntVector(const IntVector& other)
        : size(other.size), reserved(other.reserved)
    {
        arr = std::unique_ptr<int[]>(new int[other.reserved]);
        std::copy(other.arr.get(), other.arr.get() + size, arr.get());
    }

    IntVector& operator=(const IntVector& other) {
        size = other.size;
        reserved = other.reserved;
        arr = std::unique_ptr<int[]>(new int[size]);
        std::copy(other.arr.get(), other.arr.get() + size, arr.get());
        return *this;
    }

    IntVector(IntVector&& other) : size(std::move(other.size)), reserved(std::move(other.reserved)), arr(std::move(other.arr)) {
        other.size = 0;
        other.reserved = 0;
    }

    IntVector& operator=(IntVector&& other) {
        size = std::move(other.size);
        reserved = std::move(other.reserved);
        arr = std::move(other.arr);
        other.size = 0;
        other.reserved = 0;
        return *this; 
    }

    IntVector(int size, int default_value)
        : size(size), reserved(size)
    {
        arr = std::unique_ptr<int[]>(new int[reserved]);
        for(int i = 0; i < size; i++) {
            arr.get()[i] = default_value;
        }
    }
};

std::ostream& operator<<(std::ostream &stream, const IntVector& vector)
{
    if (vector.size == 0) {
        stream << "empty";
    }
    else {
        std::copy(vector.arr.get(), vector.arr.get() + vector.size, std::ostream_iterator<int>(stream, " "));
    }
    return stream;
}

std::istream& operator>>(std::istream &stream, IntVector& vector)
{
    int size, value;
    stream >> size >> value;
    IntVector temp(size, value);
    vector = std::move(temp);
    return stream;
}

int main()
{
    // adl argument dependent lookup
    print_adl(asd::Bar());

    // std::array 
    
    
    // operator overloading
    // smart pointers
    //special member functions testing
    IntVector v1(10, 5); 
    IntVector v2, v4; 
    std::cout << v1.size << " " << v2.size << std::endl; 
    v2 = v1;
    std::cout << v1.size << " " << v2.size << std::endl; 
    IntVector v3 = std::move(v2);
    std::cout << v2.size << " " << v3.size << std::endl;
    std::cout << "v1:" << v1 << std::endl;
    std::cout << "v2:" << v2 << std::endl;
    std::cout << "v3:" << v3 << std::endl;
    std::cout << "Enter an IntVector: ";
    std::cin >> v4;
    std::cout << "v4:" << v4 << std::endl;

    //std::copy, ostream_iterator
    std::vector<int> testvector;
    for (int i = 1; i <= 10; i++) {
        testvector.push_back(i * i * i);
    }
    std::ostream_iterator<int> print_it(std::cout, " ");
    std::copy(testvector.begin(), testvector.end(), print_it);

    return 0;
}
