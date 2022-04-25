# hw10
Adam Snelling
Kavi Wilson

Here's some of the issues we ran into along the way and how we solved them:

Our main issue after typing everything out was that the part of the program
responsible for making children wasn't always making legitimate ones. After some
debugging, we found a couple issues with create_crossover_child, which was
rather unexpected, since that code was provided to us by the instructor.
It may have been that we were using the method wrong, but either way, it's
fixed now.

results of tests here
In ten trials with 700 pop_size and .45 mut_rate, the shortest distance achieved was 6563.4

The mean of 10 trials with the same specifications was 8279.058. The standard deviation was 858.526.

The mean of 10 trials of the random search was 19080.46. The standard deviation was 304.224.

A t-test shewed that the p value that there was no difference between the distributions was less than 0.0001. Thus, it is confirmed that the genetic algorithm performs substantially better than the random search.
