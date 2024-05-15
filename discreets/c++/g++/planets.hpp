//Implementation of Elite(1984) planet generator algorithm according to the descriptions found
//in https://www.bbcelite.com/
//This version compiles with newer g++ versions

#include <string>

namespace planet_generator
{
//class representing a planet
class Planet
{
public:
    Planet(const std::string& gov, const std::string& econ, unsigned short tech_lvl, unsigned short popu, 
    unsigned short prod, const std::string& speci, unsigned short avr, const std::string& nm);
    Planet(const Planet& P)=default;
    Planet(Planet&& P)=default;
    Planet& operator=(const Planet& P)=default;
    Planet& operator=(Planet&& P)=default;
    void info();
private:
    std::string government;
    std::string economy;
    unsigned short technology_lvl;
    unsigned short population;
    unsigned short productivity;
    std::string species;
    unsigned short av_radius;
    std::string name;
};

//class representing the planet sequence
class Planet_Sequence
{
//government generator
    friend unsigned short government(const Planet_Sequence& PS);

//economy level generetor
    friend unsigned short economy_lvl(const Planet_Sequence& PS);

//economy type generator
    friend std::string economy(const Planet_Sequence& PS);

//technology level generator
    friend unsigned short tech_lvl(const Planet_Sequence& PS);

//population size generator
    friend unsigned short population(const Planet_Sequence& PS);

//productivity points generator
    friend unsigned short productivity(const Planet_Sequence& PS);

//native species generator
    friend std::string species(const Planet_Sequence& PS);

//planet's radius generator
    friend unsigned short av_radius(const Planet_Sequence& PS);

//planet's name generator
    friend std::string name(Planet_Sequence& PS);

//sequence twist algorithm
    friend void twist(Planet_Sequence& PS);
public:
    Planet_Sequence()=default;
    void next();
    Planet current_planet();    
private:
//3 16-bit initial values
    unsigned short u0=0x5a4a;
    unsigned short u1=0x0248;
    unsigned short u2=0xb753;
};

} 