#include "ideal.h"

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
    cache::cache_t<int, int> ideal_cache{cache_size};

    ideal_cache.fill_all_elem_map(vec);

    std::cout << "HERE \n";

    int i = 0;
    for (auto tmp_vector_elem : vec) {
        ideal_cache.access(tmp_vector_elem);
        std::cout << "HERE i = " << i << "\n";
        i++;

    }
    ideal_cache.print_hits();

    return 0;
}
