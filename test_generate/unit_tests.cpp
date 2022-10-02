#include "lfu.h"
#include "ideal.h"

#include <chrono>
#include <stdio.h>
#include <gtest/gtest.h>



struct page_t {
    int id;
    char data[60];
    page_t (int key) : id{key} {}
};

page_t get(int key) {
    page_t tmp_page {key};
    return tmp_page;
}

TEST(LfuTest, test1) {

    
    int page_num = 10;
    size_t cache_size = 3;
    
    std::vector<int> vec(page_num);
    
    for (int j = 0; j < page_num; j++) {

        int temp_page = j;

        vec[j] = temp_page;
    }

    cache_name::cache_t<page_t, int> lfu_cache{cache_size};
    
    auto lfu_start = std::chrono::high_resolution_clock::now();

    for (const auto tmp_vec_elem : vec) 
        lfu_cache.access(tmp_vec_elem, &get);

    auto lfu_finish = std::chrono::high_resolution_clock::now();
    auto lfu_elapsed = std::chrono::duration<double, std::milli>(lfu_finish - lfu_start);
    

    std::cout << "Time elapsed for lfu: " << lfu_elapsed.count() << " lfu hits = " << lfu_cache.p_hits << std::endl;
    EXPECT_EQ(0, lfu_cache.p_hits);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}