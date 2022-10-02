#include "lfu.h"
#include "ideal.h"
#include <chrono>
#include <stdio.h>

int get(int key)
{
    return key;
};

int main()
{
    int page_num = 0;
    size_t cache_size = 0;
    std::cin >> cache_size >> page_num;
    
    std::vector<int> vec(page_num);
    
    for (int j = 0; j < page_num; j++) {

        int temp_page;
        std::cin >> temp_page;

        vec[j] = temp_page;
    }

    cache_name::cache_t<int, int> lfu_cache{cache_size};
    
    auto lfu_start = std::chrono::high_resolution_clock::now();

    for (const auto tmp_vec_elem : vec) 
        lfu_cache.access(tmp_vec_elem, &get);

    auto lfu_finish = std::chrono::high_resolution_clock::now();
    auto lfu_elapsed = std::chrono::duration<double, std::milli>(lfu_finish - lfu_start);
    

    std::cout << "Time elapsed for lfu: " << lfu_elapsed.count() << " lfu hits = " << lfu_cache.p_hits << std::endl;

    cache::cache_t<int, int> ideal_cache{cache_size};

    auto ideal_start = std::chrono::high_resolution_clock::now();

    ideal_cache.fill_all_elem_map(vec);

    for (auto tmp_vector_elem : vec) {
        ideal_cache.access(tmp_vector_elem);
    }

    auto ideal_finish = std::chrono::high_resolution_clock::now();
    auto ideal_elapsed = std::chrono::duration<double, std::milli>(ideal_finish - ideal_start);

    std::cout << "Time elapsed for ideal: " << ideal_elapsed.count() << " ideal hits = " << ideal_cache.p_hits_ << std::endl;

    return 0;
}


