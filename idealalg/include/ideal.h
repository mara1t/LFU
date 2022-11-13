#pragma once

#include <deque>
#include <cassert>
#include <assert.h>
#include <iterator>
#include <cmath>
#include <unordered_map>
#include <iostream>
#include <vector>
#include <map>


namespace cache {

template <typename T, typename KeyT =int>
struct elem_t {
    KeyT key_;
    T value_;
    std::deque<int> pos_list_;

    elem_t(KeyT key) : pos_list_{}, key_{key}, value_{0} {}
};

template <typename T, typename KeyT =int> 
class cache_t { 
    size_t capacity_, size_;
public:
    int p_hits_;
    
    int IS_WASTED = -1;

private:
    

    using elem_cache = elem_t<T, KeyT>;
    using IntVectorType = typename std::vector<int>;
    using ElemVectorTypeIt = typename std::vector<elem_cache>::iterator;
    using multimap_it = typename std::multimap<int, KeyT>::iterator;

    std::unordered_map<KeyT, elem_cache> all_elem_map_;
    std::unordered_map<KeyT, multimap_it> cache_map_;
    std::multimap<int, KeyT> sorted_map_;

public:
    cache_t(size_t capacity) : capacity_{capacity}, cache_map_{}, sorted_map_{}, all_elem_map_{}, p_hits_{0}, size_{0} {}
    
    void print_hits() const
    {
        std::cout << "ideal cache hits = " << p_hits_ << "\n";
    }

    void fill_all_elem_map(const IntVectorType &buf_vector)
    {
        IS_WASTED = buf_vector.size() + 3;
        KeyT tmp_key;
        int pos_counter = 0;

        for (int pos_counter  = 0; pos_counter < buf_vector.size(); pos_counter++) {
            tmp_key = buf_vector[pos_counter];
            auto tmp = all_elem_map_.find(tmp_key);

            if (tmp == all_elem_map_.end()) {
                elem_t<KeyT, T> tmp_elem_cache{tmp_key}; 
                tmp_elem_cache.pos_list_.push_back(pos_counter);
                all_elem_map_.emplace(std::make_pair(tmp_key, tmp_elem_cache));
            }
            else {
                (tmp->second).pos_list_.push_back(pos_counter);
            }
        }

    }

    int access(KeyT key)
    {
        auto tmp = cache_map_.find(key);
        if (tmp == cache_map_.end()) {
            insert(key, 0);
            return -1;
        }

        assert(!(all_elem_map_.find(key)->second.pos_list_.empty()));

        auto deleteIt = sorted_map_.erase(tmp->second);
        //cache_map_.erase(deleteIt);
        auto tmp_all_map = all_elem_map_.find(key);
        tmp_all_map->second.pos_list_.pop_front();

        multimap_it iter;
        if (tmp_all_map->second.pos_list_.begin() != tmp_all_map->second.pos_list_.end()) 
            iter = sorted_map_.insert(std::make_pair(*(tmp_all_map->second.pos_list_.begin()), key));
        else
            iter = sorted_map_.insert(std::make_pair(IS_WASTED, key));

        cache_map_.find(key)->second = iter;
        p_hits_++;

        return 0;
    }
    void insert(KeyT key, T value)
    {   
        if (size_ == capacity_) {

            auto tmp_elem = all_elem_map_.find(key);
            tmp_elem->second.pos_list_.pop_front();
            if (tmp_elem->second.pos_list_.size() == 0) {
                return;
            }

            auto maxIter = std::prev(sorted_map_.end());

            if (maxIter->first <= *(tmp_elem->second.pos_list_.begin())) {
                return;
            } 
            auto cache_delete_key = maxIter->second;
            auto deletedIter = cache_map_.find(cache_delete_key);
            cache_map_.erase(deletedIter);
            sorted_map_.erase(maxIter);

            auto iter = sorted_map_.insert(std::make_pair(*(tmp_elem->second.pos_list_.begin()), key));
            cache_map_.insert(std::make_pair(key, iter));
        }
        else {
            size_++;
            auto tmp_elem = all_elem_map_.find(key);
            tmp_elem->second.pos_list_.pop_front();
            multimap_it iter;

            if (tmp_elem->second.pos_list_.begin() != tmp_elem->second.pos_list_.end()) 
                iter = sorted_map_.insert(std::make_pair(*(tmp_elem->second.pos_list_.begin()), key));
            else
                iter = sorted_map_.insert(std::make_pair(IS_WASTED, key));

            //uto iter = sorted_map_.insert(std::make_pair(*(tmp_elem.pos_list_.begin()), key));
            cache_map_.insert(std::make_pair(key, iter));
            //all_elem_map_.find(key)->second.pos_list_.pop_front();
        }

        
    }
    
};


};  //  namespace cache