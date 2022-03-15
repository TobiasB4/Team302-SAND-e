#pragma once

#include <vector>

template<typename T>
std::vector<T> slice(std::vector<T> const &v, int m, int n){
    auto first = v.cbegin() + m;
    auto last = v.cbegin() + n + 1;

    std::vector<T> vec(first, last);
    return vec;
}

template<typename T>
std::vector<T> Concatenate(std::vector<T> const &vec1,std::vector<T> const &vec2){
    std::vector<T> res = vec1;
    res.reserve(vec2.size());
    res.insert(res.end(), vec2.begin(), vec2.end());

    return res;
}