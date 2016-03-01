#!/usr/bin/env python
# coding=utf-8

"""Iterators are built into the Python language. Anything that is iterable can be iterated,
including dictionaries, lists, tuples, strings, streams, generators, and classes for which
you implement iterator syntax.This example shows a generator that counts by number words."""


"""Implementation of the iterator pattern with a generator"""
def count_to(count):
    """Counts by word numbers, up to a maximum of five"""

    numbers = ["one", "two", "three", "four", "five"]
    # The zip keeps from counting over the limit
    # zip(numbers, range(2)) [('one', 0), ('two', 1)]
    for number, pos in zip(numbers, range(count)):  
        yield number

# Test the generator
count_to_two = lambda : count_to(2)
count_to_five = lambda : count_to(5)

print "Counting to two…"
for number in count_to_two():
    print number,  # one two 
print "\n"
print "Counting to five…"
for number in count_to_five():
    print number,  # one two three four five