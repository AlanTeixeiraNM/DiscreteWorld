﻿/*These are algorithms for solving basic combinatorics problems. Their main purpose is to be
used as example code in the context of learning modern C++, but can be freely used, copied and modified
for other use cases. More algorithms will be implemented and the implementation may change 
as I find new ways of improving performance and design.

Author: Alan Teixeira

Environment configuration:
-compiler: g++  with the compilation option "-std=c++23"
-editor: VS Code with C/C++ and C/C++ Extension Pack extensions
*/
#ifndef COMBINATORICS_HPP
#define COMBINATORICS_HPP

#include <ranges>//At the time of writing g++ still doesn't fully support module implemmentation of the std
#include <cmath>
#include <stdexcept>
#include <limits>
#include <concepts>
#include <vector>


namespace combinatorics{
//-----------------------------------------concepts------------------------------------------------
//input_set models the set of elements on which the algorithms are applied
template<typename InR>
concept input_rdmacc = std::ranges::random_access_range<InR> && std::ranges::sized_range<InR>&&
std::copy_constructible<std::ranges::range_value_t<InR>> && std::destructible<std::ranges::range_value_t<InR>>;

//input_it models the iterators used to indicate a range of elements
template<typename InIt>
concept input_it= std::input_iterator<InIt> && std::copy_constructible<std::iter_value_t<InIt>> 
&& std::destructible<std::iter_value_t<InIt>>;

//--------------------------------------auxiliary algorithms----------------------------------
//simple factorial function with some values hard-coded, 0 <= N
template<std::integral T>
constexpr double fac(T N)
{
    if(N<0)
    {
        throw std::domain_error{"N must be non-negative"};
    }
    
    double result{1};
    while(N>1)
    {
    switch (N)
    {
        case 0:
        case 1:
            {
                return result;
            }
        case 2:
            {
                return result*2;
            }
        case 3:
            {
                return result*6;
            }
        case 4:
            {
                return result*24;
            }
        case 5:
            {
                return result*120;
            }
        case 6:
            {
                return result*720;
            }
        case 7:
            {
                return result*5'040;
            }
        case 8:
            {
                return result*40'320;
            }
        case 9:
            {
                return result*362'880;
            }
        case 10:
            {
                return result*3'628'800;
            }
        case 11:
            {
                return result*39'916'800;
            }
        case 12:
            {
                return result*479'001'600;
            }
        case 13:
            {
                return result*6'227'020'800;
            }
        case 14:
            {
                return result*87'178'291'200;
            }
        case 15:
            {
                return result*1'307'674'368'000;
            }
        case 16:
            {
                return result*20'922'789'888'000;
            }
        case 17:
            {
                return result*355'687'428'096'000;
            }
        case 18:
            {
                return result*6'402'373'705'728'000;
            }
        case 19:
            {
                return result*121'645'100'408'832'000;
            }
        case 20:
            {
                return result*2'432'902'008'176'640'000;
            }
    }
        result*=N;
        --N;
    }
    return result;
}

//partial factorial. 0 <= stop <= N.
//stop indicates when to stop multiplying. For when dividing factorials.
template<std::integral T>
constexpr double partfac(T N, T stop)
{

    if(N<0 || stop<0)
    {
        throw std::domain_error{"Integers must be non-negative"};
    }
    if(stop > N)
    {
        throw std::logic_error{"K must be smaller or equal to N"};
    }

    double result{1};
    while(N>1)
    {
        if(N==stop)
        {
            return result;
        }
        result*=N;
        --N;
    }
    return result;    
}

//number of K-permutations of N distinct elements without repetition.
//0 <= K <= N.
template<std::integral T>
constexpr double npermutations(T N, T K)
{
    if(N<0 || K<0)
    {
        throw std::domain_error{"Integers must be non-negative"};
    }
    if(K>N)
    {
        throw std::logic_error{"K must be smaller or equal to N"};
    }
    size_t k= static_cast<size_t>(N-K);
    return partfac(static_cast<size_t>(N),k);
}

//number of K-permutations of N distinct elements
//each element may repeat K times
template<std::integral T>
constexpr double npermutations_r(T N, T K)
{
    if(N<0 || K<0)
    {
        throw std::domain_error{"Integers must be non-negative"};
    }
        
    return std::pow(static_cast<double>(N),static_cast<double>(K));
}


//number of K-combinations of N distinct elements without repetition.
//0 <= K <= N.
template<std::integral T>
constexpr double ncombinations(T N, T K)
{
    if(N<0 || K<0)
    {
        throw std::domain_error{"Integers must be non-negative"};
    }
    if(K>N)
    {
        throw std::logic_error{"K must be smaller or equal to N"};
    }
    
    size_t k1= N-K > K? static_cast<size_t>(N-K):static_cast<size_t>(K);
    size_t k2= N-K > K? static_cast<size_t>(K): static_cast<size_t>(N-K);
    return partfac(static_cast<size_t>(N),k1)/fac(k2);
}

//number of K-combinations of N distinct element
//any element may repeat K times
template<std::integral T>
constexpr double ncombinations_r(T N, T K)
{
     if(N<0 || K<0)
    {
        throw std::domain_error{"Integers must be non-negative"};
    }
    
    return ncombinations(N + K -1, K);
}

//input: integral N, initializer_list of integrals {K1,K2,...,Kn}
//number of permutations of N elements where there are
//K1 indistinguishable elements of type 1, K2 indistinguishable elements of type 2, ... and Kn indistinguishable elements of type n.
//0 <= K1,K2,...,Kn <= N. K1+K2+...+Kn = N
template<std::integral T>
double npermutations_lr(T N, std::initializer_list<T> IL)
{
    T s{std::accumulate(IL.begin(),IL.end(),0)};
    if(s>N)
    {
        throw std::logic_error{"K1 + K2 + ... + Kn must be equal to N"};
    }
    double d=1;
    for(auto i:IL)
    {
        d*=fac(i);
    }
    return fac(N)/d;
}

//------------------------------input_set and input_it algorithms------------------------------

template<input_rdmacc In, std::integral T>
void vpermutations(const In& in, std::vector<std::ranges::range_value_t<In>>& pref, 
    std::vector<std::vector<std::ranges::range_value_t<In>>>& out, T K)
{
    if(std::ranges::size(pref) == static_cast<size_t>(K))
    {
        out.push_back(pref);
    }
    else
    {
        for(std::size_t i{};i<std::ranges::size(in);++i)
        {
            std::vector<std::ranges::range_value_t<In>> rem(std::ranges::cbegin(in),std::ranges::cbegin(in)+i);
            rem.insert(rem.cend(),std::ranges::cbegin(in)+i+1,std::ranges::cend(in));
            pref.push_back(*(std::ranges::cbegin(in)+i));
            vpermutations(rem,pref,out,K);
            pref.pop_back();
        }
    }
}

//returns the K-permutations, without repetition, of elements of in
//the elements are considered distincts
//0 <= K <= size(in)
template<input_rdmacc In, std::integral T>
std::vector<std::vector<std::ranges::range_value_t<In>>> vpermutations(const In& in, T K)
{
    std::vector<std::ranges::range_value_t<In>> v;
    v.reserve(static_cast<size_t>(K));
    size_t N{static_cast<size_t>(npermutations(static_cast<size_t>(std::ranges::size(in)),static_cast<size_t>(K)))};
    std::vector<std::vector<std::ranges::range_value_t<In>>> out;
    out.reserve(N);
    vpermutations(in,v,out,K);
    return out;
}

//returns the K-permutations, without repetition, of elements in the range [first,last)
//the elements are considered distincts
//0 <= K <= distance(last,first)
template<input_it In, std::sentinel_for<In>S, std::integral T>
std::vector<std::vector<std::iter_value_t<In>>> vpermutations(const In& first, const S& last, T K)
{
    std::vector<std::iter_value_t<In>> v;
    v.reserve(std::ranges::distance(first,last));
    size_t N{static_cast<size_t>(npermutations(static_cast<size_t>(std::distance(first,last)),static_cast<size_t>(K)))};
    std::vector<std::vector<std::iter_value_t<In>>> out;
    out.reserve(N);
    std::vector<std::iter_value_t<In>> in(first,last);
    vpermutations(in,v,out,K);
    return out;
}

template<input_rdmacc In, std::integral T>
void vcombinations(const In& in, std::vector<std::ranges::range_value_t<In>>& pref, 
    std::vector<std::vector<std::ranges::range_value_t<In>>>& out, T K)
{
    if(std::ranges::size(pref) == static_cast<size_t>(K))
    {
        out.push_back(pref);
    }
    else
    {
        for(std::size_t i{};i<std::ranges::size(in);++i)
        {
            std::vector<std::ranges::range_value_t<In>> rem(std::ranges::cbegin(in)+i+1,std::ranges::cend(in));
            pref.push_back(*(std::ranges::cbegin(in)+i));
            vcombinations(rem,pref,out,K);
            pref.pop_back();
        }
    }
}

//returns the combinations, without repetition, of elements of in taken K to K as a vector of vectors
//the elements are considered distincts
//0 <= K <= size(in)
export template<input_rdmacc In, std::integral T>
std::vector<std::vector<std::ranges::range_value_t<In>>> vcombinations(const In& in, T K)
{
    std::vector<std::ranges::range_value_t<In>> v;
    v.reserve(static_cast<size_t>(K));
    size_t N{static_cast<size_t>(ncombinations(static_cast<size_t>(std::ranges::size(in)),static_cast<size_t>(K)))};
    std::vector<std::vector<std::ranges::range_value_t<In>>> out;
    out.reserve(N);
    vcombinations(in,v,out, K);
    return out;
}

//returns the combinations, without repetition, of elements in the range [first,last) taken K to K
//the elements are considered distincts
//0 <= K <= distance(last,first)
export template<input_it In, std::sentinel_for<In>S, std::integral T>
std::vector<std::vector<std::iter_value_t<In>>> vcombinations(const In& first, const S& last, T K)
{
    std::vector<std::iter_value_t<In>> v;
    v.reserve(static_cast<size_t>(K));
    size_t N{static_cast<size_t>(ncombinations(static_cast<size_t>(std::distance(first,last)),static_cast<size_t>(K)))};
    std::vector<std::vector<std::iter_value_t<In>>> out;
    out.reserve(N);
    std::vector<std::iter_value_t<In>> in(first,last);
    vcombinations(in,v,out,K);
    return out;
}
}

#endif