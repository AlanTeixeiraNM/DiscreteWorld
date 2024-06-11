//Implementation of Elite(1984) planet generator algorithm according to the descriptions found
//in https://www.bbcelite.com/. Code for generating RGB colors is added in this implementation
//this was not in the original version.

//Author: Alan Teixeira

//This version compiles with newer msvc versions


module;
#include <cstdint>//for the integer type uint16_t that is guaranteed to have exactly 16 bit
//provided it is supported by the implementation

export module planets;
import std;

namespace planet_generator
{
//class representing a planet
export class Planet
{
    friend class Planet_Sequence;
    
    Planet(std::string_view gov, std::string_view econ, uint16_t tech_lvl, uint16_t popu, 
    uint16_t prod, std::string_view speci, uint16_t avr, std::string_view nm,const std::array<uint16_t,3>& col);
    Planet(const Planet& P)=delete;
    Planet(Planet&& P)=delete;
    Planet& operator=(const Planet& P)=delete;
    Planet& operator=(Planet&& P)=delete;
public:
    void info()const;
    std::string gov(){return government;}
    std::string eco(){return economy;}
    uint16_t tech(){return technology_lvl;}
    uint16_t pop(){return population;}
    uint16_t produc(){return productivity;}
    std::string spec(){return species;}
    uint16_t radi(){return av_radius;}
    std::string nm(){return name;}
    bool has_ring();
    std::array<uint16_t,3> col(){return color;}
private:
    std::string government;
    std::string economy;
    uint16_t technology_lvl;
    uint16_t population;
    uint16_t productivity;
    std::string species;
    uint16_t av_radius;
    std::string name;
    std::array<uint16_t,3> color{0,0,0};
};

//class representing the sequence of planets
export class Planet_Sequence
{
//government generator
    friend uint16_t government(Planet_Sequence& PS);

//economy level generetor
    friend uint16_t economy_lvl(Planet_Sequence& PS);

//economy type generator
    friend std::string economy(Planet_Sequence& PS);

//technology level generator
    friend uint16_t tech_lvl(Planet_Sequence& PS);

//population size generator
    friend uint16_t population(Planet_Sequence& PS);

//productivity points generator
    friend uint16_t productivity(Planet_Sequence& PS);

//native species generator
    friend std::string species(Planet_Sequence& PS);

//planet's radius generator
    friend uint16_t av_radius(Planet_Sequence& PS);

//planet's name generator
    friend std::string name(Planet_Sequence& PS);

//sequence twist algorithm
    friend void twist(Planet_Sequence& PS);

//planet's color
    friend std::array<uint16_t,3> color(Planet_Sequence& PS);
public:
    Planet_Sequence()=default;
    void next();
    Planet* current_planet();    
private:
//3 16-bit initial values
    uint16_t u0=0x5a4a;
    uint16_t u1=0x0248;
    uint16_t u2=0xb753;
    std::unique_ptr<Planet> P;
    bool planet_end{false};
};

} 