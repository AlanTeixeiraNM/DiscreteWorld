#include "planets.hpp"
#include <unordered_map>
#include <iostream>

//government types
std::unordered_map<unsigned short,std::string> Gov {{0,"Anarchy"},{1,"Feudal"},{2,"Multi-government"},{3,"Dictatorship"}
,{4,"Communist"},{5,"Confederacy"},{6,"Democracy"},{7,"Corporate State"}};

//economy levels
std::unordered_map<unsigned short, std::string> Econ_lvl{{0,"Rich"},{5,"Rich"},{1,"Average"},{6,"Average"},{2,"Poor"}
,{7,"Poor"},{3,"Mainly"},{4,"Mainly"}};

//pair of letters for planet's name generation
std::unordered_map<unsigned short, std::string> Two_letter
{{128,"AL"},
 {129,"LE"},
 {130,"XE"},
 {131,"GE"},
 {132,"ZA"},
 {133,"CE"},
 {134,"BI"},
 {135,"SO"},
 {136,"US"},
 {137,"ES"},
 {138,"AR"},
 {139,"MA"},
 {140,"IN"},
 {141,"DI"},
 {142,"RE"},
 {143,"A?"},
 {144,"ER"},
 {145,"AT"},
 {146,"EN"},
 {147,"BE"},
 {148,"RA"},
 {149,"LA"},
 {150,"VE"},
 {151,"TI"},
 {152,"ED"},
 {153,"OR"},
 {154,"QU"},
 {155,"AN"},
 {156,"TE"},
 {157,"IS"},
 {158,"RI"},
 {159,"ON"}
};

planet_generator::Planet::Planet(const std::string& gov, const std::string& econ, unsigned short tech_lvl, 
    unsigned short popu, unsigned short prod, const std::string& speci, unsigned short avr, const std::string& nm)
    :government{gov},economy{econ},technology_lvl{tech_lvl},population{popu},productivity{prod},species{speci},
    av_radius{avr},name{nm}{}

void planet_generator::Planet::info()
{
    std::cout<<"Planet name: "<<name<<'\n';
    std::cout<<"Government: "<<government<<'\n';
    std::cout<<"Economy: "<<economy<<'\n';
    std::cout<<"Technology level: "<<technology_lvl <<'\n';
    std::cout<<"Population: "<<static_cast<float>(population)/10<<" billion"<<'\n';
    std::cout<<"Productivity: "<<productivity<<" million credits"<<'\n';
    std::cout<<"Species: "<<species<<'\n';
    std::cout<<"Average radius: "<<av_radius<<" Km"<<'\n';
}

unsigned short planet_generator::government(const Planet_Sequence& PS)
{
    unsigned short us0=(PS.u1 & 0b0000000000001000);
    unsigned short us1=(PS.u1 & 0b0000000000010000);
    unsigned short us2=(PS.u1 & 0b0000000000100000);
    us0>>=3;
    us1>>=3;
    us2>>=3;
    return us0+us1+us2;
}

unsigned short planet_generator::economy_lvl(const Planet_Sequence& PS)
{
    unsigned short gov= government(PS);
    unsigned short us0=(PS.u0 & 0b0000000100000000);
    unsigned short us1=(PS.u0 & 0b0000001000000000);
    unsigned short us2=(PS.u0 & 0b0000010000000000);
    if(gov==0 || gov==1)
    {
        us1 |= 0b0000001000000000;
    }

    us0>>=8;
    us1>>=8;
    us2>>=8;
    return us0+us1+us2;
}

std::string planet_generator::economy(const Planet_Sequence& PS)
{
    unsigned short us=(PS.u0 & 0b0000001000000000);
    us>>=9;
    if(us==0)
        return " Industrial";
    else 
        return " Agricultural";
}

unsigned short planet_generator::tech_lvl(const Planet_Sequence& PS)
{
    unsigned short eco_lvl=economy_lvl(PS);
    unsigned short flipped_eco_lvl = eco_lvl ^ 0b111;
    unsigned short gov=government(PS);
    unsigned short u1=(PS.u1 & 0b1111111100000000);
    u1>>=8;
    u1 &= 0b11;

    return flipped_eco_lvl + u1 + gov/2;
}

unsigned short planet_generator::population(const Planet_Sequence& PS)
{
    return tech_lvl(PS)*4 + economy_lvl(PS) + government(PS) + 1;
}

unsigned short planet_generator::productivity(const Planet_Sequence& PS)
{
    unsigned short eco_lvl=economy_lvl(PS);
    unsigned short flipped_eco_lvl = eco_lvl ^ 0b111;
    return (flipped_eco_lvl+3)*(government(PS)+4)*population(PS)*8;
}

std::string planet_generator::species(const Planet_Sequence& PS)
{
    unsigned short b7s2_l= PS.u2 & 0b0000000010000000;
    b7s2_l>>=7;
    if(!b7s2_l)
        return "Human Colonials";
    std::string spc;
    unsigned short A=PS.u2 & 0b0001110000000000;
    A>>=10;
    switch (A)
    {
    case 0:
        spc+="Large ";
        break;
    case 1:
        spc+="Fierce ";
        break;
    case 2:
        spc+="Small ";
        break;
    default:
        break;
    }
    A= PS.u2 & 0b1110000000000000;
    switch (A)
    {
    case 0:
        spc+="Green ";
        break;
    case 1:
        spc+="Red ";
        break;
    case 2:
        spc+="Yellow ";
        break;
    case 3:
        spc+="Blue ";
        break;
    case 4:
        spc+="Black ";
        break;
    case 5:
        spc+="Harmless ";
        break;
    default:
        break;
    }
    A= (PS.u1 ^ PS.u0) & 0b0000011100000000;
    A>>=8;
    switch (A)
    {
    case 0:
        spc+="Slimy ";
        break;
    case 1:
        spc+="Bug-Eyed ";
        break;
    case 2:
        spc+="Horned ";
        break;
    case 3:
        spc+="Bony ";
        break;
    case 4:
        spc+="Fat ";
        break;
    case 5:
        spc+="Furry ";
        break;
    default:
        break;
    }
    unsigned short tmp = PS.u2 & 0b0000001100000000;
    tmp>>=8;
    A+=tmp;
    tmp= (A & 0b0000000000000111);
    switch (tmp)
    {
    case 0:
        spc+="Rodents";
        break;
    case 1:
        spc+="Frogs";
        break;
    case 2:
        spc+="Lizards";
        break;
    case 3:
        spc+="Lobsters";
        break;
    case 4:
        spc+="Birds";
        break;
    case 5:
        spc+="Humanoids";
        break;
    case 6:
        spc+="Felines";
        break;
    case 7:
        spc+="Insects";
        break;
    default:
        break;
    }
    return spc;
}

unsigned short planet_generator::av_radius(const Planet_Sequence& PS)
{
    unsigned short s2_h= (PS.u2 & 0b1111111100000000);
    unsigned short s1_h= (PS.u1 & 0b1111111100000000);
    s2_h>>=8;
    s1_h>>=8;
    s2_h&=0b1111;
    return (s2_h + 11)*256 + s1_h;
}

void planet_generator::twist(Planet_Sequence& PS)
{
    //std::cout<<std::setbase(16)<<PS.u0<<" "<<PS.u1<<" "<<PS.u2<<'\n';
    unsigned short tmp=PS.u0;
    PS.u0=PS.u1;
    PS.u1=PS.u2;
    PS.u2=(tmp+ PS.u0+PS.u1)%65536;
    //std::cout<<std::setbase(16)<<PS.u0<<" "<<PS.u1<<" "<<PS.u2<<'\n';
}

std::string planet_generator::name(Planet_Sequence& PS)
{
    std::string tl;
    unsigned short s0_l= (PS.u0 & 0b0000000001000000);
    s0_l>>=6;
    unsigned short count{};
    if(s0_l)
        count =4;
    else
        count=3;
    unsigned short s2_h =(PS.u2 & 0b0001111100000000);
    s2_h>>=8;
    if(s2_h)
    {   
        s2_h+=128;
        tl=Two_letter[s2_h];
        --count;
    }
    for(unsigned short i{1};i<=count;++i)
    {
        twist(PS);
        s2_h =(PS.u2 & 0b0001111100000000);
        s2_h>>=8;
        if(s2_h)
            s2_h+=128;
            tl+=Two_letter[s2_h];
    }
    //std::cout<<tl;
    return tl;
}

planet_generator::Planet planet_generator::Planet_Sequence::current_planet()
{
    std::string gover = Gov[government(*this)];
    std::string econo = Econ_lvl[economy_lvl(*this)]+economy(*this);
    unsigned short technology_lvl = tech_lvl(*this);
    unsigned short popula = population(*this);
    unsigned short producti = productivity(*this);
    std::string spec = species(*this);
    unsigned short av_rad = av_radius(*this);
    std::string nam = name(*this);
    return Planet(gover,econo,technology_lvl,popula,producti,spec,av_rad,nam);
}

void planet_generator::Planet_Sequence::next()
{
    twist(*this);
}