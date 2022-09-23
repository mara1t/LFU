#include "lfu//include//lfu.h"
#include "idealalg//include//ideal.h"
#include <chrono>
#include <stdio.h>


int main()
{
    char str_in[100];
    char str_out[100];
    for (int i = 0; i < 1000; i++) {
        
        sprintf(str_in, "%s%d%s", "test_generate/tests/data", i, ".dat");
        FILE *tmp_file = fopen(str_in, "r");

        int page_num = 0;
        size_t cache_size = 0;
        fscanf(tmp_file, "%ld %d", &cache_size, &page_num);

        std::vector<int> vec(page_num);
        
        for (int j = 0; j < page_num; j++) {

            int temp_page;
            fscanf(tmp_file, "%d", &temp_page);

            vec[j] = temp_page;
        }
        cache_name::cache_t<int, int> lfu_cache{cache_size};
        
        auto lfu_start = std::chrono::high_resolution_clock::now();

        for (const auto tmp_vec_elem : vec) {
            lfu_cache.access(tmp_vec_elem);
        }

        auto lfu_finish = std::chrono::high_resolution_clock::now();
        auto lfu_elapsed = std::chrono::duration<double, std::milli>(lfu_finish - lfu_start);
        
        
        sprintf(str_out, "%s%d%s", "test_generate/tests_ans/ans", i, ".dat");
        FILE *tmp_out_file = fopen(str_out, "w");

        fprintf(tmp_out_file, "Time elapsed for lfu: %lg\n lfu hits = %d\n", lfu_elapsed.count(), lfu_cache.p_hits);
        //lfu_cache.print_hits();

        cache::cache_t<int, int> ideal_cache{cache_size};

        auto ideal_start = std::chrono::high_resolution_clock::now();

        ideal_cache.fill_all_elem_map(vec);

        for (auto tmp_vector_elem : vec) {
            ideal_cache.access(tmp_vector_elem);
        }

        auto ideal_finish = std::chrono::high_resolution_clock::now();
        auto ideal_elapsed = std::chrono::duration<double, std::milli>(ideal_finish - ideal_start);

        fprintf(tmp_out_file, "Time elapsed for ideal: %lg\n ideal hits = %d\n", ideal_elapsed.count(), ideal_cache.p_hits_);
        //ideal_cache.print_hits();
        
        fclose(tmp_out_file);
        fclose(tmp_file);
    }

    return 0;
}

