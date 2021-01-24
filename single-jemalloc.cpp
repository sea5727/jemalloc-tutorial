#include <jemalloc/jemalloc.h>
#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <chrono>


int main(int argc, char* argv[]) {

    if(argc < 3){
        return 0;
    }

    int COUNT = ::atoi(argv[1]);
    int SIZE = ::atoi(argv[2]);

    printf("COUNT:%d, SIZE:%d\n", COUNT, SIZE);

    auto start = std::chrono::steady_clock::now();

    char * arr[COUNT];
    for(int i = 0 ; i < COUNT ; ++i){
        arr[i] = (char * )malloc(SIZE);
    }
    auto end1 = std::chrono::steady_clock::now();

    for(int i = 0 ; i < COUNT ; ++i){
        free(arr[i]);
    }
    auto end2 = std::chrono::steady_clock::now();

    
    auto diff1 = end1 - start;
    auto diff2 = end2 - end1;
    std::cout << std::chrono::duration <double, std::milli> (diff1).count() << " ms" << std::endl;
    std::cout << std::chrono::duration <double, std::milli> (diff2).count() << " ms" << std::endl;
    return 0;
}
