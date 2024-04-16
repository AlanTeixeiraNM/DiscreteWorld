/*These are algorithms for solving basic combinatorics problems. Their main purpose is to be
used as example code in the context of learning modern C++, but can be freely used, copied and modified
for other use cases. They may change as I find new ways of improving performance and design.

Author: Alan Teixeira
*/
#ifndef COMBINATORICS_HPP
#define COMBINATORICS_HPP

#include <ranges>
#include <concepts>
#include <vector>
#include <iostream>
#include <span>

namespace combinatorics{
//-----------------------------------------range_base------------------------------------------------
template<typename OutR,typename T>
concept pushing_back_range = std::ranges::output_range<OutR,std::ranges::range_value_t<OutR>>&&
std::same_as<std::ranges::range_value_t<OutR>,T>&& std::copy_constructible<T>&&
requires(T t, OutR r)
{
    {r.push_back(t)};
};

template<typename T,pushing_back_range<std::vector<T>> PBR>
void vpermutations(const std::vector<T>& vi, std::vector<T>& pref, PBR& R)
{
    if(vi.empty())
    {
        R.push_back(pref);
    }
    for(std::size_t i{};i<vi.size();++i)
    {
        std::vector<T> rem(vi.begin(),vi.begin()+i);
        rem.insert(rem.end(),vi.begin()+i+1,vi.end());
        pref.push_back(*(vi.begin()+i));
        vpermutations(rem,pref, R);
        pref.pop_back();
    }
}

template<typename T,pushing_back_range<std::vector<T>> PBR>
void vpermutations(const std::vector<T>& vi, PBR& R)
{
    std::vector<T> v;
    v.reserve(vi.size());
    vpermutations(vi,v, R);
}

//----------------------------------------stream_base---------------------------------------------------
template<typename T>
concept ostream_insertable = 
requires(T t, std::basic_ostream<char>& oss)
{
    {oss<<t}->std::same_as<std::basic_ostream<char>&>;
};

template<ostream_insertable T>
std::basic_ostream<char>& operator<<(std::basic_ostream<char>& oss,const std::vector<T>& v)
{
    for(auto a :v)
    {
        oss<<a;
    }
    oss<<'\n';
    return oss;
}

template<std::copy_constructible T>
requires std::destructible<T>
void vpermutations(const std::vector<T>& vi, std::vector<T>& pref, std::basic_ostream<char>& oss)
{
    if(vi.empty())
    {
        oss<<pref;
    }
    for(std::size_t i{};i<vi.size();++i)
    {
        std::vector<T> rem(vi.begin(),vi.begin()+i);
        rem.insert(rem.end(),vi.begin()+i+1,vi.end());
        pref.push_back(*(vi.begin()+i));
        vpermutations(rem,pref, oss);
        pref.pop_back();
    }
}

template<std::copy_constructible T>
void vpermutations(const std::vector<T>& vi, std::basic_ostream<char>& oss)
{
    std::vector<T> v;
    v.reserve(vi.size());
    vpermutations(vi,v, oss);
}
}

#endif