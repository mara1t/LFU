#pragma once

#include <deque>
#include <cassert>
#include <assert.h>
#include <iterator>
#include <list>
#include <unordered_map>
#include <iostream>
#include <vector>


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
private:
    using elem_cache = elem_t<T, KeyT>;
    using IntVectorType = typename std::vector<int>;
    using ElemVectorTypeIt = typename std::vector<elem_cache>::iterator;


    std::unordered_map<KeyT, elem_cache> all_elem_map_;
    std::unordered_map<KeyT, KeyT> cache_map_;

public:
    cache_t(size_t capacity) : capacity_{capacity}, cache_map_{}, all_elem_map_{}, p_hits_{0}, size_{0} {}
    
    void print_hits() const
    {
        std::cout << "ideal cache hits = " << p_hits_ << "\n";
    }

    void fill_all_elem_map(IntVectorType buf_vector)
    {
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

        all_elem_map_.find(key)->second.pos_list_.pop_front();
        
        p_hits_++;

        return 0;
    }
    void insert(KeyT key, T value)
    {   
        if (size_ == capacity_) {

            auto tmp_elem = all_elem_map_.find(key)->second;
            if (tmp_elem.pos_list_.size() == 1) {
                tmp_elem.pos_list_.pop_front();
                return;
            }

            KeyT least_used_elem_key = cache_map_.begin()->first;
        
            for (auto tmp_cache_elem : cache_map_) {
                if (all_elem_map_.find(tmp_cache_elem.first)->second.pos_list_.empty()) {
                    least_used_elem_key = tmp_cache_elem.first;
                    break;
                }
                else if (*(all_elem_map_.find(tmp_cache_elem.first)->second.pos_list_.begin()) > *(all_elem_map_.find(least_used_elem_key)->second.pos_list_.begin())) {
                    least_used_elem_key = tmp_cache_elem.first;
                }      
            }
            cache_map_.erase(cache_map_.find(least_used_elem_key));
            cache_map_[key] = key;

            all_elem_map_.find(key)->second.pos_list_.pop_front();

        }
        else {
            size_++;
            cache_map_[key] = key;
            all_elem_map_.find(key)->second.pos_list_.pop_front();
        }

        
    }
    
};


};  //  namespace cache