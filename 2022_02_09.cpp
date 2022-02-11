#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iterator>

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
    std::vector<int> testvector;
    for (int i = 1; i<=10; i++){
        testvector.push_back(pow(i,3));
    }
    std::ostream_iterator<int> print_it (std::cout," ");
    std::copy(testvector.begin(),testvector.end(),print_it);
    return 0;
}
