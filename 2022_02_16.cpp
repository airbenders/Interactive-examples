#include <exception>
#include <iostream>

#include <thread>
#include <vector>
#include <algorithm>
#include <functional>
#include <chrono>
#include <numeric>


class Matrix_3{
public:
    Matrix_3(int v1, int v2, int v3, int v4, int v5, int v6, int v7, int v8, int v9)
    {
        row_1.push_back(v1);
        row_1.push_back(v2);
        row_1.push_back(v3);
        row_2.push_back(v4);
        row_2.push_back(v5);
        row_2.push_back(v6);
        row_3.push_back(v7);
        row_3.push_back(v8);
        row_3.push_back(v9);
    }

    Matrix_3(std::vector<int> values) : 
    Matrix_3(values[0], values[1], values[2], 
            values[3], values[4], values[5],    
            values[6], values[7], values[8]) {}

    ~Matrix_3(){
        std::cout << row_1[0] << " " << row_1[1] << " " << row_1[2] << std::endl;
    }

    void multiply_rows(int c1, int c2, int c3, int n){
        for (int i=0; i <n*3; i++){
            multiply_row(row_1, c1);
            multiply_row(row_2, c2);
            multiply_row(row_3, c3);
        }
    }

    void multiply_rows_threaded(int c1, int c2, int c3, int n){
        std::vector<std::thread> threads;
        for (int i=0; i <n*3; i++){
            threads.push_back(std::thread(&Matrix_3::multiply_row, this, std::ref(row_1), c1));
            threads.push_back(std::thread(&Matrix_3::multiply_row, this, std::ref(row_2), c2));
            threads.push_back(std::thread(&Matrix_3::multiply_row, this, std::ref(row_3), c3));
        }
        
        std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));

    }

    friend std::ostream& operator<<(std::ostream &stream, const Matrix_3& mat)
    {
        for(auto i : mat.row_1) stream << i << " ";
        stream << "\n";  
        for(auto i : mat.row_2) stream << i << " "; 
        stream << "\n";  
        for(auto i : mat.row_3) stream << i << " ";
        stream << "\n";  
        return stream;
    }
private:
    void multiply_row(std::vector<int>& row, int c){
        std::for_each(row.begin(), row.end(), [&row, &c](int& number){
            number *= c;
        });
    }

    std::vector<int> row_1;
    std::vector<int> row_2;
    std::vector<int> row_3;
};

//Virtual Override
struct Account {
    virtual void withdraw(double amount){
        std::cout << "In Account::withdraw" << std::endl;
    }
};

struct Checking : public Account {
    virtual void withdraw(double amount) {
        std::cout << "In Checking::withdraw" << std::endl;
    }
};


int main(){
    try
    {
        Matrix_3 matrix_1(1231, 4562, 7893, 2344, 5675, 8996, 3457, 6788, 9999);
        Matrix_3 matrix_2(1231, 4562, 7893, 2344, 5675, 8996, 3457, 6788, 9999);

        std::chrono::steady_clock::time_point begin_2 = std::chrono::steady_clock::now();
        matrix_2.multiply_rows_threaded(117, 128, 139, 2);
        std::chrono::steady_clock::time_point end_2 = std::chrono::steady_clock::now();
        std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::nanoseconds> (end_2 - begin_2).count() << "[ns]" << std::endl;

        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        matrix_1.multiply_rows(117, 128, 139, 2);
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count() << "[ns]" << std::endl;
    
        auto values = [](auto initial_value) {
            std::vector<int> v(9); 
            std::iota(v.begin(), v.end(), initial_value); 
            return v; 
        };
        Matrix_3 mat1(values(1)); 
        Matrix_3 mat2(values(-10)); 
        Matrix_3 mat3(values(10)); 
        
        //burada hepsini bir kez deconstruct ediyor nedenini anlamadım
        std::vector<Matrix_3> matrices{mat1, mat2, mat3};

        for(auto& mat: matrices) std::cout << mat << "\n"; 
        auto multiply_row = std::mem_fn(&Matrix_3::multiply_rows); 
        std::for_each(matrices.begin(), matrices.end(), [&] (auto& mat) {
            multiply_row(mat, 5, 5, 5, 1); 
        });
        for(auto& mat: matrices) std::cout << mat << "\n"; 

        std::cout << "end of program" << "\n"; 
    }
    catch(std::exception& e) {
        std::cout << e.what() << std::endl;
    }
    
    //Virtual Override
    Account *p1 = new Account();
    Account *p2 = new Checking();

    p1->withdraw(1000);
    p2->withdraw(1000);
    std::cout << "---Pointers are over---" << std::endl;

    Account p3 = Account();
    Account p4 = Checking(); //Pointers�z neden olmuyor anlamad�m.

    p3.withdraw(1000);
    p4.withdraw(1000);
}

