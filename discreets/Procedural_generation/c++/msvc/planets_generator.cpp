module planets;

//government types
std::unordered_map<uint16_t, const char*> Gov {{0,"Anarchy"},{1,"Feudal"},{2,"Multi-government"},{3,"Dictatorship"}
,{4,"Communist"},{5,"Confederacy"},{6,"Democracy"},{7,"Corporate State"}};

//economy levels
std::unordered_map<uint16_t, const char*> Econ_lvl{{0,"Rich"},{5,"Rich"},{1,"Average"},{6,"Average"},{2,"Poor"}
,{7,"Poor"},{3,"Mainly"},{4,"Mainly"}};

//pairs of letters for planet's name generation
std::unordered_map<uint16_t, const char*> Two_letter
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

planet_generator::Planet::Planet(std::string_view gov, std::string_view econ, uint16_t tech_lvl, 
    uint16_t popu, uint16_t prod, std::string_view speci, uint16_t avr, std::string_view nm,
    const std::array<uint16_t,3>& col)
    :government{gov},economy{econ},technology_lvl{tech_lvl},population{popu},productivity{prod},species{speci},
    av_radius{avr},name{nm},color{col}{}

void planet_generator::Planet::info()const
{
    std::cout<<"Planet name: "<<name<<'\n';
    std::cout<<"Government: "<<government<<'\n';
    std::cout<<"Economy: "<<economy<<'\n';
    std::cout<<"Technology level: "<<technology_lvl <<'\n';
    std::cout<<"Population: "<<static_cast<float>(population)/10<<" billion"<<'\n';
    std::cout<<"Productivity: "<<productivity<<" million credits"<<'\n';
    std::cout<<"Species: "<<species<<'\n';
    std::cout<<"Average radius: "<<av_radius<<" Km"<<'\n';
    std::cout<<"Surface color (RGB): "<<"("<<color[0]/255.0<<","<<color[1]/255.0<<","<<color[2]/255.<<")";
}

uint16_t planet_generator::government(Planet_Sequence& PS)
{
    uint16_t us0=(PS.u1 & 0b0000000000001000);
    uint16_t us1=(PS.u1 & 0b0000000000010000);
    uint16_t us2=(PS.u1 & 0b0000000000100000);
    us0>>=3;
    us1>>=3;
    us2>>=3;
    return us0+us1+us2;
}

uint16_t planet_generator::economy_lvl(Planet_Sequence& PS)
{
    uint16_t gov= government(PS);
    uint16_t us0=(PS.u0 & 0b0000000100000000);
    uint16_t us1=(PS.u0 & 0b0000001000000000);
    uint16_t us2=(PS.u0 & 0b0000010000000000);
    if(gov==0 || gov==1)
    {
        us1 |= 0b0000001000000000;
    }

    us0>>=8;
    us1>>=8;
    us2>>=8;
    return us0+us1+us2;
}

std::string planet_generator::economy(Planet_Sequence& PS)
{
    uint16_t us=(PS.u0 & 0b0000001000000000);
    us>>=9;
    if(us==0)
        return " Industrial";
    else 
        return " Agricultural";
}

uint16_t planet_generator::tech_lvl(Planet_Sequence& PS)
{
    uint16_t eco_lvl=economy_lvl(PS);
    uint16_t flipped_eco_lvl = eco_lvl ^ 0b111;
    uint16_t gov=government(PS);
    uint16_t u1=(PS.u1 & 0b1111111100000000);
    u1>>=8;
    u1 &= 0b11;

    return flipped_eco_lvl + u1 + gov/2;
}

uint16_t planet_generator::population(Planet_Sequence& PS)
{
    return tech_lvl(PS)*4 + economy_lvl(PS) + government(PS) + 1;
}

uint16_t planet_generator::productivity(Planet_Sequence& PS)
{
    uint16_t eco_lvl=economy_lvl(PS);
    uint16_t flipped_eco_lvl = eco_lvl ^ 0b111;
    return (flipped_eco_lvl+3)*(government(PS)+4)*population(PS)*8;
}

std::string planet_generator::species(Planet_Sequence& PS)
{
    uint16_t b7s2_l= PS.u2 & 0b0000000010000000;
    b7s2_l>>=7;
    if(!b7s2_l)
        return "Human Colonials";
    std::string spc;
    uint16_t A=PS.u2 & 0b0001110000000000;
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
    uint16_t tmp = PS.u2 & 0b0000001100000000;
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

uint16_t planet_generator::av_radius(Planet_Sequence& PS)
{
    uint16_t s2_h= (PS.u2 & 0b1111111100000000);
    uint16_t s1_h= (PS.u1 & 0b1111111100000000);
    s2_h>>=8;
    s1_h>>=8;
    s2_h&=0b1111;
    return (s2_h + 11)*256 + s1_h;
}

void planet_generator::twist(Planet_Sequence& PS)
{
    uint16_t tmp=PS.u0;
    PS.u0=PS.u1;
    PS.u1=PS.u2;
    PS.u2=(tmp+ PS.u0+PS.u1)%65536;
}

std::string planet_generator::name(Planet_Sequence& PS)
{
    std::string tl;
    uint16_t s0_l= (PS.u0 & 0b0000000001000000);
    s0_l>>=6;
    uint16_t count{};
    if(s0_l)
        count =4;
    else
        count=3;
    uint16_t s2_h =(PS.u2 & 0b0001111100000000);
    s2_h>>=8;
    if(s2_h)
    {   
        s2_h+=128;
        tl=Two_letter[s2_h];
        --count;
    }
    for(uint16_t i{1};i<=count;++i)
    {
        twist(PS);
        s2_h =(PS.u2 & 0b0001111100000000);
        s2_h>>=8;
        if(s2_h)
        {
            s2_h+=128;
            tl+=Two_letter[s2_h];
        }
    }
    return tl;
}

std::array<uint16_t,3> planet_generator::color(Planet_Sequence& PS)
{
    uint16_t r=(PS.u0 & 0b0000000011111111);
    uint16_t g=(PS.u1 & 0b0000000011111111);
    uint16_t b=(PS.u2 & 0b0000000011111111);
    return std::array<uint16_t,3>{r,g,b};
}

planet_generator::Planet* planet_generator::Planet_Sequence::current_planet()
{
    if(planet_end)
    {
        return P.get();
    }
    std::string gover = Gov[government(*this)];
    std::string econo = Econ_lvl[economy_lvl(*this)]+economy(*this);
    uint16_t technology_lvl = tech_lvl(*this);
    uint16_t popula = population(*this);
    uint16_t producti = productivity(*this);
    std::string spec = species(*this);
    uint16_t av_rad = av_radius(*this);
    std::string nam = name(*this);
    std::array<uint16_t,3> col=color(*this);
    auto ptr= new Planet(gover,econo,technology_lvl,popula,producti,spec,av_rad,nam,col);
    P.reset(ptr);
    planet_end=true;
    return P.get();
}

void planet_generator::Planet_Sequence::next()
{
    if(planet_end)
    {
        twist(*this);
    }
    else
    {
        twist(*this);
        twist(*this);
        twist(*this);
        twist(*this);
    }
    planet_end=false;
}