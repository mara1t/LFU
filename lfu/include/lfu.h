#pragma once

#include <iterator>
#include <list>
#include <unordered_map>
#include <iostream>
#include <vector>

namespace cache_name {

template <typename T, typename ListType, typename KeyT =int> 
class freq_node_t_ {
public:
    int value_;
    std::list<ListType> elem_lst_;
    freq_node_t_() : value_{0}, elem_lst_{} {}
};

template <typename T, typename KeyT =int> 
class elem_t_ {
public:    
    KeyT key_;
    T value_;
    using FreqIt = typename std::list<freq_node_t_<T, elem_t_, KeyT>>::iterator;
    FreqIt parent_;
    elem_t_(KeyT key, T value, FreqIt parent) : key_{key}, value_{value}, parent_{parent} {};
};
    

template <typename T, typename KeyT =int> 
class cache_t {
    
    size_t capacity_, size_;  
public:
    int p_hits;
private:
    using elem_lfu_ = elem_t_<T, KeyT>;
    using freq_node_lfu_ = freq_node_t_<T, elem_lfu_, KeyT>;
    using FreqListIt = typename std::list<freq_node_lfu_>::iterator;
    using ListIt = typename std::list<elem_lfu_>::iterator;
    using MapIt = typename std::unordered_map<KeyT, ListIt>::iterator;
    using KeyMapType = typename std::unordered_map<KeyT, T>;

public:    
    std::list<freq_node_lfu_> freq_lst_;
    std::unordered_map<KeyT, ListIt> umap_;


    cache_t(size_t capacity) : p_hits{0}, capacity_{capacity}, size_{0}, freq_lst_{}, umap_{} {}

    void print_hits() const
    {
        std::cout << "lfu hits = " << p_hits << "\n";
    }

    void print_log() 
    {
        FreqListIt it = freq_lst_.begin();
        
        for (auto const &v : it->elem_lst_)
            std::cout << v.key_ << " ";
        std::cout << "\n";
        std::cout<< "size=" << freq_lst_.size() << std::endl << "1lst size =" << freq_lst_.begin()->elem_lst_.size() << "\n"; //<< "2lst size =" << next_it->elem_lst_.size() << std::endl;
    }


    bool full(int size) const { return size == size_; }

    FreqListIt get_new_node(int value, FreqListIt itr)
    {
        freq_node_lfu_ freq_node{};
        freq_node.value_ = value;
        auto freq_node_it = freq_lst_.insert(itr, freq_node);

        return freq_node_it;
    }

    KeyT access(KeyT key, T (*get)(KeyT tmp_key))
    {
        auto tmp = umap_.find(key);
        if (tmp == umap_.end()) {
            insert(key, get(key));
            return key;
        }
    
        FreqListIt freq_it = (tmp->second)->parent_;
        FreqListIt next_freq_it = std::next(freq_it, 1);

        if (next_freq_it == freq_lst_.end() || next_freq_it->value_ != freq_it->value_ + 1) {

            next_freq_it = get_new_node(freq_it->value_ + 1, next_freq_it);

        
        }
        next_freq_it->elem_lst_.splice(next_freq_it->elem_lst_.begin(), freq_it->elem_lst_, tmp->second);
        (tmp->second)->parent_ = next_freq_it;

        if (freq_it->elem_lst_.empty()) {
            freq_lst_.erase(freq_it);
        }
        p_hits++;
        return key;

    }   
    void insert(KeyT key, T value)
    {
        size_++;
        if (size_ == capacity_ + 1) 
        {
            size_--;
            auto map_node_it = umap_.find(freq_lst_.begin()->elem_lst_.begin()->key_);
            ListIt least_elem_it = map_node_it->second;
 
            FreqListIt tmp_freq_it = least_elem_it->parent_;

            umap_.erase(map_node_it);

            tmp_freq_it->elem_lst_.erase(least_elem_it);

            if (tmp_freq_it->elem_lst_.empty())
                freq_lst_.erase(tmp_freq_it);

        }

        FreqListIt freq_it = freq_lst_.begin();
        if (freq_it->value_ != 1 || freq_it == freq_lst_.end()) {
            freq_node_lfu_ tmp_freq_elem{};
            tmp_freq_elem.value_ = 1; 
            freq_lst_.push_front(tmp_freq_elem);
        }
        freq_it = freq_lst_.begin();

        elem_lfu_ list_node{key, value, freq_it}; 

        freq_it->elem_lst_.push_front(list_node);
        umap_.emplace(std::make_pair(key, freq_it->elem_lst_.begin()));
    }
    
};

};  //  namespace cache