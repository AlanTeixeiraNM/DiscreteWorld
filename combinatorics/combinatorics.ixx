export module combinatorics;
import std;

//---------------------------------------concepts-------------------------------------------
template<typename OutR,typename T>
concept pushing_back_range = std::ranges::output_range<OutR,std::ranges::range_value_t<OutR>>&&
std::same_as<std::ranges::range_value_t<OutR>,T>&& std::copy_constructible<T>&&
requires(T t, OutR r)
{
    {r.push_back(t)};
};

template<typename T>
concept ostream_insertable = 
requires(T t, std::basic_ostream<char>& oss)
{
    {oss<<t}->std::same_as<std::basic_ostream<char>&>;
};

//---------------------------------------auxiliar functions---------------------------------
template<ostream_insertable T>
std::basic_ostream<char>& operator<<(std::basic_ostream<char>& oss,const std::vector<T>& v)
{
    for(auto i:v)
    {
        oss<<i;
    }
    oss<<'\n';
    return oss;
}

//---------------------------------------range based algorithms-----------------------------

export template<typename T,pushing_back_range<std::vector<T>> PBR>
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


export template<typename T,pushing_back_range<std::vector<T>> PBR>
void vpermutations(const std::vector<T>& vi, PBR& R)
{
    std::vector<T> v;
    v.reserve(vi.size());
    vpermutations(vi,v, R);
}
//---------------------------------------stream based algorithms----------------------------
export template<std::copy_constructible T>
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


export template<std::copy_constructible T>
void vpermutations(const std::vector<T>& vi, std::basic_ostream<char>& oss)
{
    std::vector<T> v;
    v.reserve(vi.size());
    vpermutations(vi,v, oss);
}
