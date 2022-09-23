#include "..//include//lfu.h"
#include <chrono>

int main()
{
    int page_num = 0;
    size_t cache_size = 0;
    std::cin >> cache_size >> page_num;

    std::vector<int> vec(page_num);
    
    for (int i = 0; i < page_num; i++) {

        int temp_page;
        std::cin >> temp_page;

        if (std::cin.fail()) {
            abort();
        }

        vec[i] = temp_page;
    }
    cache_name::cache_t<int, int> lfu_cache{cache_size};
    

    for (const auto tmp_vec_elem : vec) {
        lfu_cache.access(tmp_vec_elem);
    }

    lfu_cache.print_hits();

    return 0;
}

