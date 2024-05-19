//Implementation of Elite(1984) planet generator algorithm according to the descriptions found
//in https://www.bbcelite.com/
//This version compiles with newer g++ versions

//Author: Alan Teixeira

#include <string>
#include <string_view>
#include <cstdint>//for the integer type uint16_t that is guaranteed to have exactly 16 bit
//provided it is supported by the implementation

namespace planet_generator
{
//class representing a planet
class Planet
{
public:
    Planet(const std::string& gov, std::string_view econ, uint16_t tech_lvl, uint16_t popu, 
    uint16_t prod, std::string_view speci, uint16_t avr, std::string_view nm);
    Planet(const Planet& P)=default;
    Planet(Planet&& P)=default;
    Planet& operator=(const Planet& P)=default;
    Planet& operator=(Planet&& P)=default;
    void info()const;
private:
    std::string government;
    std::string economy;
    uint16_t technology_lvl;
    uint16_t population;
    uint16_t productivity;
    std::string species;
    uint16_t av_radius;
    std::string name;
};

//class representing the planet sequence
class Planet_Sequence
{
//government generator
    friend uint16_t government(const Planet_Sequence& PS);

//economy level generetor
    friend uint16_t economy_lvl(const Planet_Sequence& PS);

//economy type generator
    friend std::string economy(const Planet_Sequence& PS);

//technology level generator
    friend uint16_t tech_lvl(const Planet_Sequence& PS);

//population size generator
    friend uint16_t population(const Planet_Sequence& PS);

//productivity points generator
    friend uint16_t productivity(const Planet_Sequence& PS);

//native species generator
    friend std::string species(const Planet_Sequence& PS);

//planet's radius generator
    friend uint16_t av_radius(const Planet_Sequence& PS);

//planet's name generator
    friend std::string name(const Planet_Sequence& PS);

//sequence twist algorithm
    friend void twist(const Planet_Sequence& PS);
public:
    Planet_Sequence()=default;
    void next()const;
    Planet current_planet()const;    
private:
//3 16-bit initial values
    mutable uint16_t u0=0x5a4a;
    mutable uint16_t u1=0x0248;
    mutable uint16_t u2=0xb753;
};

} 