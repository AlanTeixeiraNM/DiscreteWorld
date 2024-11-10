#This is a Python wrapper to simplified versions 
#of C++ Planet and Planet_Sequence classes
import sys
sys.path.append("insert here the path to the Python shared module built using pybind11")

import Elite_planets as Elite

class Planets:
    '''Interface for simplified C++ Planet_Sequence class from the 
    shared library Elite_planets'''

    def __init__(self):
        Planets.planet_sequence=Elite.Planets()

    def get_planet(self):
        '''returns the current Planet in the sequence'''
        return self.planet_sequence.get_planet()
    
    def next_planet(self):
        '''go to the next Planet in the sequence. '''
        self.planet_sequence.next_planet()



class Planet:
    '''Interface for simplified C++ Planet class from the shared library
    Elite_planets'''

    def __init__(self,Planet):
        '''Initialize it directly with the return of Planets.get_planet()'''
        self.planet=Planet    
    def set(self,Planet):
        '''Sets new Planet. Also directly from Planets.get_planet()'''
        self.planet=Planet
    def name(self):
        '''returns Planet name'''
        return self.planet.name()
    def government(self):
        '''returns Planet government'''
        return self.planet.government()
    def economy(self):
        '''returns Planet economy'''
        return self.planet.economy()
    def technology(self):
        '''returns Planet technology'''
        return self.planet.technology()
    def population(self):
        '''returns Planet population'''
        return self.planet.population()
    def productivity(self):
        '''returns Planet productivity'''
        return self.planet.productivity()
    def species(self):
        '''returns Planet species'''
        return self.planet.species()
    def radius(self):
        '''returns Planet radius'''
        return self.planet.radius()
    def has_ring(self):
        '''indicates whether Planet has ring or not'''
        return self.planet.has_ring()
    def color(self):
        '''returns Planet color'''
        return self.planet.color()