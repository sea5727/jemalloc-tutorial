#include <iostream>
#include <jemalloc/jemalloc.h>
#include <thread>
#include <vector>



int main(int argc, char* argv[]) {
    

    if(argc < 4){
        return 0;
    }

    
    int COUNT = ::atoi(argv[1]);
    int SIZE = ::atoi(argv[2]);
    int THREAD = ::atoi(argv[3]);

    printf("COUNT:%d, SIZE:%d, THREAD:%d\n", COUNT, SIZE, THREAD);
    
    std::vector<std::thread> workers;
    std::vector<std::thread> workers2;
    auto start1 = std::chrono::steady_clock::now();

    char ***arr;
    arr = (char ***)malloc(sizeof(char **) * THREAD);

    for(int i = 0 ; i < THREAD ; ++i){
        workers.emplace_back([=]{
            arr[i] = (char **) malloc(sizeof(char *) * COUNT);
            for(int j = 0 ; j < COUNT ; ++j){
                arr[i][j] = (char *)malloc(sizeof(char) * SIZE);
            }            
        });
    }

    for(auto & worker : workers){
        worker.join();
    }

    auto end1 = std::chrono::steady_clock::now();
    auto diff1 = end1 - start1;
    std::cout << std::chrono::duration <double, std::milli> (diff1).count() << " ms" << std::endl;

    
    auto start2 = std::chrono::steady_clock::now();

    for(int i = 0 ; i < THREAD ; ++i){
        workers2.emplace_back([=]{
            for(int j = 0 ; j < COUNT ; ++j){
                free(arr[i][j]);
            }            
            free(arr[i]);
        });
    }
    free(arr);

    for(auto & worker : workers2){
        worker.join();
    }

    auto end2 = std::chrono::steady_clock::now();
    auto diff2 = end2 - start2;
    std::cout << std::chrono::duration <double, std::milli> (diff2).count() << " ms" << std::endl;


    return 0;
}

