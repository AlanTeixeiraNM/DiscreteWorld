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
#include <exception>
#include <limits>
#include <cassert>
#include <concepts>
#include <vector>


namespace combinatorics{
//-----------------------------------------concepts------------------------------------------------
//input_set models the set of elements on which the algorithms are applied
template<typename InR>
concept input_set = std::ranges::input_range<InR> && std::ranges::sized_range<InR>&&
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
constexpr double partfac(T N, T stop=0)
{

    if(N<0 || stop<0)
    {
        throw std::domain_error{"Integers must be non-negative"};
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

//number of permutations of N distinct elements taken K to K without repetition.
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

//number of permutations of N distinct elements taken K to K 
//where each element may repeat K times
template<std::integral T>
constexpr double npermutations_r(T N, T K)
{
    if(N<0 || K<0)
    {
        throw std::domain_error{"Integers must be non-negative"};
    }
        
    return std::pow(static_cast<double>(N),static_cast<double>(K));
}


//number of combinations of N distinct elements taken K to K without repetition.
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

//------------------------------input_set and input_it algorithms------------------------------
//returns the number of permutations of elements of an input_set.
//see that it returns size_t instead of double as the basic algorithms
//this is because I think vectors with size_t size are enough for practical purposes
template<input_set In>
constexpr size_t npermutations(const In& in)
{
    size_t N{std::ranges::size(in)};
    return static_cast<size_t>(fac(N));
}

//return the number of permutations of elements of the range [first,last)
template<input_it In, std::sentinel_for<In>S>
constexpr size_t npermutations(const In& first, const S& last)
{
    auto d{std::ranges::distance(first,last)};
    size_t N{static_cast<size_t>(d)};
    return static_cast<size_t>(fac(N));
}


template<input_set In>
void vpermutations(const In& in, std::vector<std::ranges::range_value_t<In>>& pref, 
    std::vector<std::vector<std::ranges::range_value_t<In>>>& R)
{
    if(std::ranges::empty(in))
    {
        R.push_back(pref);
    }
    for(std::size_t i{};i<std::ranges::size(in);++i)
    {
        std::vector<std::ranges::range_value_t<In>> rem(std::ranges::cbegin(in),std::ranges::cbegin(in)+i);
        rem.insert(rem.cend(),std::ranges::cbegin(in)+i+1,std::ranges::cend(in));
        pref.push_back(*(std::ranges::cbegin(in)+i));
        vpermutations(rem,pref,R);
        pref.pop_back();
    }
}

//returns the permutations of elements of an input_set as a vector of vectors
template<input_set In>
std::vector<std::vector<std::ranges::range_value_t<In>>> vpermutations(const In& in)
{
    std::vector<std::ranges::range_value_t<In>> v;
    v.reserve(std::ranges::size(in));
    size_t N{npermutations(in)};
    std::vector<std::vector<std::ranges::range_value_t<In>>> R;
    R.reserve(N);
    vpermutations(in,v,R);
    return R;
}

//returns the permutations of elements of an range [first,last) as a vector of vectors
template<input_it In, std::sentinel_for<In>S>
std::vector<std::vector<std::iter_value_t<In>>> vpermutations(const In& first, const S& last)
{
    std::vector<std::iter_value_t<In>> v;
    v.reserve(std::ranges::distance(first,last));
    size_t N{npermutations(first,last)};
    std::vector<std::vector<std::iter_value_t<In>>> R;
    R.reserve(N);
    std::vector<std::iter_value_t<In>> in(first,last);
    vpermutations(in,v,R);
    return R;
}

}

#endif