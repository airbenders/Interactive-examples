#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iterator>
#include <memory>

namespace asd {
    class bar {
    public:
        std::string toBePrinted = "Hello from namespace asd";
    };
    void print_adl(bar foo) {
        std::cout << foo.toBePrinted << std::endl;
    }    
}

// special member functions
//unique_ptr'ları ögrenmek için yaptım ama dogru oldu mu bilmiyorum
class int_vector {
    public: 
        std::unique_ptr<int[]> arr;
        int size; 

        int_vector() {
            arr = std::unique_ptr<int[]>(new int[10]);
            size = 0; 
        }; 
        ~int_vector() { arr.reset(); };
        int_vector(const int_vector& other) : size(other.size) {
            arr = std::unique_ptr<int[]>(new int[other.size]); 
            for(int i = 0; i < other.size; i++) {
                arr.get()[i] = other.arr.get()[i]; 
            }
        }; 
        int_vector& operator=(int_vector& other) {
            size = other.size; 
            arr = std::unique_ptr<int[]>(new int[size]); 
            for(int i = 0; i < other.size; i++) {
                arr.get()[i] = other.arr.get()[i]; 
            }
            return *this; 
        }
        int_vector(int_vector&& other) : size(std::move(other.size)) {
            arr = std::unique_ptr<int[]>(new int[size]);
            for(int i = 0; i < other.size; i++) {
                arr.get()[i] = other.arr.get()[i];
            }
            other.arr.reset(); 
        };
        int_vector& operator=(int_vector&& other) {
            size = std::move(other.size); 
            arr = std::unique_ptr<int[]>(new int[size]);             
            for(int i = 0; i < other.size; i++) {
                arr.get()[i] = other.arr.get()[i]; 
            }
            other.arr.reset(); 
            return *this; 
        }
        int_vector(int size, int default_value) {
            this -> size = size; 
            arr = std::unique_ptr<int[]>(new int[size]);
            for(int i = 0; i < size; i++) {
                arr.get()[i] = default_value; 
            }
        }
};

int main(int argc, char *argv[]){

    print_adl(asd::bar()); // adl arguement defined lookup
    // std::array 
    // smart pointers
    // operator overloading
    // smart pointers

    // testing special member functions 
    int_vector v1(10, 5); 
    int_vector v2; 
    std::cout << v1.size << " " << v2.size << std::endl; 
    v2 = v1;
    std::cout << v1.size << " " << v2.size << std::endl; 
    int_vector v3 = std::move(v2);
    std::cout << v2.size << " " << v3.size << std::endl; 

    std::vector<int> testvector;
    for (int i = 1; i<=10; i++){
        testvector.push_back(pow(i,3));
    }
    std::ostream_iterator<int> print_it (std::cout," ");
    std::copy(testvector.begin(),testvector.end(),print_it);
    return 0;
}
