#include <exception>
#include <iostream>

#include <thread>
#include <vector>
#include <algorithm>
#include <functional>

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

    ~Matrix_3(){
        std::cout << row_1[0] << " " << row_1[1] << " " << row_1[2] << std::endl;
    }

    void multiply_rows(int c1, int c2, int c3, int n){
        for (int i=0; i <n; i++){
            multiply_row(row_1, c1);
            multiply_row(row_2, c2);
            multiply_row(row_3, c3);
        }
    }

    void multiply_rows_threaded(int c1, int c2, int c3, int n){
        std::vector<std::thread> threads;
        for (int i=0; i <n; i++){
            threads.push_back(std::thread(&Matrix_3::multiply_row, this, std::ref(row_1), c1));
            threads.push_back(std::thread(&Matrix_3::multiply_row, this, std::ref(row_2), c2));
            threads.push_back(std::thread(&Matrix_3::multiply_row, this, std::ref(row_3), c3));
        }
        
        for(int i = 0; i < 3*n; i++){
            threads[i].join();
         }

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
    }
    catch(std::exception& e) {
        std::cout << e.what() << std::endl;
    }
}

