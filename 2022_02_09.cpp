#include <iostream>
#include <string>

namespace asd {
    class bar {
    public:
        std::string toBePrinted = "Hello from namespace asd";
    };
    void print_adl(bar foo) {
        std::cout << foo.toBePrinted << std::endl;
    }    
}

int main(int argc, char *argv[]){

    print_adl(asd::bar()); // adl arguement defined lookup
    // std::array 
    // special member functions
    // smart pointers
    // operator overloading
    // smart pointers
    // std::copy, ostream_iterator
    return 0;
}
