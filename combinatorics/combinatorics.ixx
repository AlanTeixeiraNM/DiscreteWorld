/*These are algorithms for solving basic combinatorics problems. Their main purpose is to be
used as example code in the context of learning modern C++, but can be freely used, copied and modified
for other use cases. More algorithms will be implemented and the implementation may change 
as I find new ways of improving performance and design.

Author: Alan Teixeira

Environment configuration:
-compiler: msvc using "/std:c++latest" compilation option and C++23 standard
 for Intellisense (which still have problems with modules)
-editor: VS Code with C/C++ and C/C++ Extension Pack extensions
*/

export module combinatorics;
import std;//In order to import the std as a module you need the std.ifc binary file. 
            //You can either compile it or refer to it on the compilation task if you already have it somewhere


namespace combinatorics{
//---------------------------------------concepts-------------------------------------------
//input_set models the set of elements on which the algorithms are applied
template<typename InR>
concept input_set = std::ranges::input_range<InR> && std::ranges::sized_range<InR>&&
std::copy_constructible<std::ranges::range_value_t<InR>> && std::destructible<std::ranges::range_value_t<InR>>;

//--------------------------------------basic algorithms----------------------------------
//simple factorial function with some values hard-coded
constexpr size_t fac(size_t N)
{
    switch (N)
    {
        case 0:
        case 1:
            {
                return 1;
            }
        case 2:
            {
                return 2;
            }
        case 3:
            {
                return 6;
            }
        case 4:
            {
                return 24;
            }
        case 5:
            {
                return 120;
            }
        case 6:
            {
                return 720;
            }
        case 7:
            {
                return 5'040;
            }
        case 8:
            {
                return 40'320;
            }
        case 9:
            {
                return 362'880;
            }
        case 10:
            {
                return 3'628'800;
            }
        case 11:
            {
                return 39'916'800;
            }
        case 12:
            {
                return 479'001'600;
            }
        case 13:
            {
                return 6'227'020'800;
            }
        case 14:
            {
                return 87'178'291'200;
            }
        case 15:
            {
                return 1'307'674'368'000;
            }
        case 16:
            {
                return 20'922'789'888'000;
            }
        case 17:
            {
                return 355'687'428'096'000;
            }
        case 18:
            {
                return 6'402'373'705'728'000;
            }
        case 19:
            {
                return 121'645'100'408'832'000;
            }
        case 20:
            {
                return 2'432'902'008'176'640'000;
            }
    }
    return N*fac(N-1);
}

//returns the number of permutations of elements of an input_set
export template<input_set In>
constexpr size_t npermutations(const In& in)
{
    size_t N{std::ranges::size(in)};
    return fac(N);
}

//---------------------------------------vector based algorithms-----------------------------
//returns the permutations of elements of an input_set as a vector of vectors
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

export template<input_set In>
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

}