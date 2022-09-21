#include "..//include//lfu.h"


int LfuCache(int page_num, size_t cache_size, const std::vector<int>& vec)
{
    cache_name::cache_t<int, int> lfu_cache{cache_size};
    
    for (const auto tmp_vec_elem : vec) {
        lfu_cache.access(tmp_vec_elem);
    }

    return lfu_cache.p_hits;
}