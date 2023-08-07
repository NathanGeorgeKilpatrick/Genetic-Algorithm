# Genetic-Algorithm
A Console based genetic algorithm trying to find the best combination of products that fit within a bag of a certain weight. 

Thank you for looking at my genetic algorithms code. This was one of the projects created at univeristy during my third year. I hope you enjoy.
This code was created within Visual Studios.


The program starts of by creating a random individual with a number of attributes, that is then expanded to a number of individuals creating a population. 
The individuals in the population are then sorted inorder of their fitness ratio. 
Two individuals are then selected using the roulette wheel method. To keep it simple higher the fitness ratio the higher chance of selection.
The two individuals then create two offspring, these offspring are then inserted into the next generation of the population
Currently the code is terminated when all items are selected in the chromosome. 
However as generatinos are being counted, the termination method can be immediately changed to the number of generaions


How to read the output??

----------------- these lines split on generation from another.

Example - 
10110101:181:1500:3684:0.140187

The first number 10110101 this number is a individuals chromosome. Each integer depicts a items that can go into the bag. A 1 means that the item is in the bag and a 0 means the item is not in the bag. 

The second nubmber is the decoded int created by the chromosome. When the example binary number is decoded it represents the number 181. As explained before the current termination number is 225.

The third number (1500) is the combined fitness of all items in the bag. 

The fourth number (3684) is the combined weight of all items in the bag.

The last number (0.140187) is the fitness ratio of the individual in this generation. This fitness ratio displays the chance of the individual to be selected for mating. 
