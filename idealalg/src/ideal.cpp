#include "..//include//ideal.h"


int IdealCache(int page_num, size_t cache_size, const std::vector<int>& vec)
{
    cache::cache_t<int, int> ideal_cache{cache_size};
    
    for (const auto tmp_vec_elem : vec) {
        ideal_cache.access(tmp_vec_elem);
    }

    return ideal_cache.p_hits;
}