# Genetic-Algorithm
A Console based genetic algorithm trying to find the best combination of products that fit within a bag of a certain weight. 

The program starts of by creating a random individual with a number of attributes, that is then expanded to a number of individuals creating a population. 
The individuals in the population are then sorted inorder of their fitness ratio. 
Two individuals are then selected using the roulette wheel method. To keep it simple higher the fitness ratio the higher chance of selection.
The two individuals then create two offspring, these offspring are then inserted into the next generation of the population
Currently the code is terminated when all items are selected in the chromosome. 
However as generatinos are being counted, the termination method can be immediately changed to the number of generaions.
