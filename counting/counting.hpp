/*These are algorithms for solving basic combinatorics problems. Their main purpose is to be
used as example code in the context of learning modern C++, but can be freely used, copied and modified
for other use cases. More algorithms will be implemented and the implementation may change 
as I find new ways of improving performance and design.

Author: Alan Teixeira
*/
#ifndef COUNTING_HPP
#define COUNTING_HPP

#include <ranges>//At the time of writing g++ still doesn't fully support module implemmentation of the std
#include <cmath>
#include <stdexcept>
#include <limits>
#include <concepts>
#include <vector>


namespace counting{
//-----------------------------------------concepts------------------------------------------------
//input_set models a set of elements on which the algorithms are applied
template<typename InR>
concept input_rdmacc = std::ranges::iterator_range<InR> &&
std::copy_constructible<std::ranges::range_value_t<InR>> && std::destructible<std::ranges::range_value_t<InR>>;

//input_it models iterators on a range of elements
template<typename InIt>
concept input_it= std::input_iterator<InIt> && std::copy_constructible<std::iter_value_t<InIt>> 
&& std::destructible<std::iter_value_t<InIt>>;

//--------------------------------------auxiliary algorithms----------------------------------
//simple factorial function with some values hard-coded. 0 <= N
template<std::integral T>
constexpr double fac(T N)
{
    if(N<0)
    {
        throw std::domain_error{"N must be nonnegative"};
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
//stop indicates when to K multiplying. It represents N!/K!
//pay attention to T value range implementation limits.
template<std::integral T>
constexpr double partfac(T N, T K)
{
    if(N == 0 && K == 0)
    {
        return 1;
    }
    if(N<0 || K<0)
    {
        throw std::domain_error{"Integers must be nonnegative"};
    }
    if(K > N)
    {
        throw std::logic_error{"K must be smaller or equal to N"};
    }

    double result{1};
    while(N>1)
    {
        if(N==K)
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
    if(N == 0 && K == 0)
    {
        return 1;
    }
    if(N<0 || K<0)
    {
        throw std::domain_error{"Integers must be nonnegative"};
    }
    if(K>N)
    {
        throw std::logic_error{"K must be smaller or equal to N"};
    }
    return partfac(N,N-K);
}

//number of permutations of N distinct elements taken K to K 
//where each element may repeat K times
template<std::integral T>
constexpr double npermutations_r(T N, T K)
{
    if(N == 0 && K == 0)
    {
        return 1;
    }
    if(N<0 || K<0)
    {
        throw std::domain_error{"Integers must be nonnegative"};
    }
        
    return std::pow(static_cast<double>(N),static_cast<double>(K));
}

//number of combinations of N distinct elements taken K to K without repetition.
//0 <= K <= N.
template<std::integral T>
constexpr double ncombinations(T N, T K=0)
{
    if(N == 0 && K == 0)
    {
        return 1;
    }
    if(N<0 || K<0)
    {
        throw std::domain_error{"Integers must be nonnegative"};
    }
    if(K>N)
    {
        throw std::logic_error{"K must be smaller or equal to N"};
    }
    
    T k1= N-K > K? N-K:K;
    T k2= N-K > K? K:N-K;
    return partfac(N,k1)/fac(k2);
}

//number of combinations of N distinct elements taken K to K
//where any element may repeat K times
template<std::integral T>
constexpr double ncombinations_r(T N, T K)
{
    if(N == 0 && K == 0)
    {
        return 1;
    }
    if(N<0 || K<0)
    {
        throw std::domain_error{"Integers must be nonnegative"};
    }
    
    return ncombinations(N + K -1, K);
}

//input: integral N, initializer_list of integrals {K1,K2,...,Kn}
//number of permutations of N elements where there are
//K1 indistinguishable elements of type 1, K2 indistinguishable elements of type 2, ...
//and Kn indistinguishable elements of type n.
//0 <= K1,K2,...,Kn. K1+K2+...+Kn = N
template<std::integral T>
double npermutations_lr(T N, std::initializer_list<T> IL)
{
    if(N == 0 && IL.size() == 0)
    {
        return 1;
    }
    T s{std::accumulate(IL.begin(),IL.end(),static_cast<T>(0))};
    if(s!=N)
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

//------------------------------lazy generators------------------------------

//combinations class lazily generates a sequence of all combinations of an input_set taken K to K
//it can be used in range-for loops
//comb_it is a class of iterators that "traverses" all combinations
//begin(), end() are iterators that marks the start and the end of the generated sequence
//the sequence restarts when comb_it passes end()
template<input_set In, std::integral T>
class combinations
{
public:
    combinations(const In &in, T K):
    v(std::ranges::begin(in),std::ranges::end(in)),k{K}
    ,sz{static_cast<size_t>(ncombinations(static_cast<T>(v.size()),k))}
    {
        
    }
    
    combinations() = delete;
    combinations(const combinations& P) = delete;
    combinations& operator =(const combinations& P) = delete;
    combinations& operator =(const combinations&& P) = delete;
    size_t size(){return sz;}
    class comb_it
    {
     public:
        comb_it(const std::vector<std::ranges::range_value_t<In>>& vr,
        unsigned K,size_t idx = 0):itv{vr},itmask(static_cast<size_t>(K),1),index{idx}
        {
            if(idx == 0)
            {   
                sz = vr.size();
                itmask.resize(sz,0);    
                ittmp.reserve(static_cast<size_t>(K));
                value.reserve(static_cast<size_t>(K));
                for (size_t i = 0; i < sz; ++i) // [0..N-1] integers
                {
                    if (itmask[i]) ittmp.push_back(i);
                }
            }   
        }
        comb_it& operator ++()
        {
            index++;
            ittmp.clear();
            std::prev_permutation(itmask.begin(),itmask.end());
            //{
                for (size_t i = 0; i < sz; ++i) // [0..N-1] integers
                {
                    if (itmask[i]) ittmp.push_back(i);
                }    
            //}
            return *this;
        }
        bool operator == (comb_it & c)
        {
            return (itv == c.itv) and (index == c.index);
        }
        bool operator != (comb_it& c)
        {
            return !(*this == c);
        }
        std::vector<std::ranges::range_value_t<In>> operator *()
        {
            value.clear();
            for(size_t i: ittmp)
            {
                value.push_back(itv[i]);
            }
            ittmp.clear();
            return value;
        }
     private:
        size_t index;
        size_t sz;
        std::vector<size_t> itmask;
        std::vector<size_t> ittmp;
        std::vector<std::ranges::range_value_t<In>> value;
        const std::vector<std::ranges::range_value_t<In>> itv;

    };

    comb_it begin(){return comb_it(v, k, 0);}
    comb_it end(){return comb_it(v, k, ncombinations(static_cast<T>(v.size()),static_cast<T>(k)));}
private:
    const std::vector<std::ranges::range_value_t<In>> v;
    T k;
    size_t sz;
};

//permutations class lazily generates a sequence of all permutations of an input_set taken K to K
//it can be used in range-for loops
//comb_it is a class of iterators that "traverses" all combinations
//begin(), end() are iterators that marks the start and the end of the generated sequence
//the sequence restarts when comb_it passes end()
template<input_set In, std::integral T>
class permutations
{
public:
    permutations(const In &in, T K):
    v(std::ranges::begin(in),std::ranges::end(in)),k{K},indexes(std::ranges::size(in),0)
    ,sz{static_cast<size_t>(npermutations(static_cast<T>(v.size()),k))}
    {
        std::iota(indexes.begin(),indexes.end(),0);
    }
    
    permutations() = delete;
    permutations(const permutations& P) = delete;
    permutations& operator =(const permutations& P) = delete;
    permutations& operator =(const permutations&& P) = delete; 
    double size(){return sz;}
    class perm_it
    {
     public:
        perm_it(const std::vector<std::ranges::range_value_t<In>>& vr,
        std::vector<size_t>& vl,
        T K,size_t idx = 0):
        itv{vr},comb(vl,K),index{idx},comb_begin{comb.begin()}
        {
            if(idx == 0)
            {
                value.resize(K);
                ittmp = *comb_begin;
            }
        }
        perm_it& operator ++ ()
        {
            index++;
            if(std::next_permutation(ittmp.begin(),ittmp.end()))
            {
            }
            else
            {
                ++comb_begin;
                ittmp = *comb_begin;
            }
            return *this;
        }
        bool operator == (perm_it & c)
        {
            return (itv == c.itv) and (index == c.index);
        }
        bool operator != (perm_it& c)
        {
            return !(*this == c);
        }
        std::vector<std::ranges::range_value_t<In>> operator *()
        {
            value.clear();
            for(T i: ittmp)
            {
                value.push_back(itv[i]);
            }
            return value;
        }
     private:
        size_t index;
        std::vector<size_t> ittmp;
        std::vector<std::ranges::range_value_t<In>> value;
        const std::vector<std::ranges::range_value_t<In>> itv;
        combinations<std::vector<size_t>,size_t> comb;
        combinations<std::vector<size_t>,size_t>::comb_it comb_begin;

    };

    perm_it begin(){return perm_it(v, indexes, k);}
    perm_it end(){return perm_it(v, indexes, k, npermutations(static_cast<T>(v.size()),k));}
private:
    const std::vector<std::ranges::range_value_t<In>> v;
    std::vector<size_t> indexes;
    T k;
    size_t sz;
};

}
#endif