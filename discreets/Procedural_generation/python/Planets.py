#This is a Python wrapper to simplified versions 
#of C++ Planet and Planet_Sequence classes
import sys
sys.path.append("insert the path to the Python shared module built using pybind11")

import Elite_planets as Elite

class Planets:
    '''Interface for simplified C++ Planet_Sequence class from the 
    shared library Elite_planets'''

    def __init__(self):
        Planets.planet_sequence=Elite.Planets()

    def get_planet(self):
        '''get the current Planet in the sequence'''
        return self.planet_sequence.get_planet()
    
    def next_planet(self):
        '''advance to the nexte Planet in the sequence. 
        In order to access the new Planet user needs to get it using get_planet()'''
        self.planet_sequence.next_planet()



class Planet:
    '''Interface for simplified C++ Planet class from the shared library
    Elite_planets'''

    def __init__(self,Planet):
        '''Initialize it directly with the return of Planets.get_planet()'''
        self.planet=Planet    
    def set(self,Planet):
        '''Set new Planet. Also directly from Planets.get_planet()'''
        self.planet=Planet
    def name(self):
        '''return Planet name'''
        return self.planet.name()
    def government(self):
        '''return Planet government'''
        return self.planet.government()
    def economy(self):
        '''return Planet economy'''
        return self.planet.economy()
    def technology(self):
        '''return Planet technology'''
        return self.planet.technology()
    def population(self):
        '''return Planet population'''
        return self.planet.population()
    def productivity(self):
        '''return Planet productivity'''
        return self.planet.productivity()
    def species(self):
        '''return Planet species'''
        return self.planet.species()
    def radius(self):
        '''return Planet radius'''
        return self.planet.radius()
    def has_ring(self):
        '''indicates whether Planet has ring or not'''
        return self.planet.has_ring()
    def color(self):
        '''return Planet color'''
        return self.planet.color()