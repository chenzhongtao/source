#!/usr/bin/env python
# coding=utf-8

# http://ginstrom.com/scribbles/2007/10/08/design-patterns-python-style/

"""
This pattern is a lot simpler to implement than the GoF example, because there's no need to inherit just to satisfy types. In the example below, the PetShop class has an abstract factory as a member (pet_factory). We can configure it at runtime with the desired concrete factory. The pet shop will then generate the appropriate pet type depending on its factory.
"""

#抽象工厂模式 abstract_factory

"""Implementation of the abstract factory pattern"""

import random


class PetShop:
    """A pet shop"""

    def __init__(self, animal_factory=None):
        """pet_factory is our abstract factory.
        We can set it at will."""

        self.pet_factory = animal_factory

    def show_pet(self):
        """Creates and shows a pet using the
        abstract factory"""

        pet = self.pet_factory.get_pet()
        print("This is a lovely", pet)
        print("It says", pet.speak())
        print("It eats", self.pet_factory.get_food())


# Stuff that our factory makes

class Dog:
    def speak(self):
        return "woof"

    def __str__(self):
        return "Dog"


class Cat:
    def speak(self):
        return "meow"

    def __str__(self):
        return "Cat"


# Factory classes

class DogFactory:
    def get_pet(self):
        return Dog()

    def get_food(self):
        return "dog food"


class CatFactory:
    def get_pet(self):
        return Cat()

    def get_food(self):
        return "cat food"


# Create the proper family
def get_factory():
    """Let's be dynamic!"""
    return random.choice([DogFactory, CatFactory])()


# Show pets with various factories
if __name__ == "__main__":
    shop = PetShop()
    for i in range(3):
        shop.pet_factory = get_factory()
        shop.show_pet()
        print("=" * 20)
