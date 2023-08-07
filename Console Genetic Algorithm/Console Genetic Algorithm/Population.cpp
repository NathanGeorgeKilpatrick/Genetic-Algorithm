#pragma once
#include "Individual.h"
#include <iostream>

// --------------------------------- Globals ------------------------------------ //
const int POPULATION_SIZE = 6;
const double CROSSOVER_RATE = 0.07;
const double MUTATION_RATE = 0.001;

// -------------------------------- declaration -------------------------------- //


double randDouble(double min, double max)// generates random number
{
	static std::default_random_engine ran;
	return std::uniform_real_distribution<>{min, max}(ran);
}

class Population // The population class to hold a population of individuals
{
public:
	
	// initial population
	Population() : population_size(POPULATION_SIZE) {
		generatePopulation(population_size);
		generateFitnessRatio();
	}
	// Repopulate with two carry over
	Population(Bag& p1, Bag& p2) : population_size(POPULATION_SIZE) {
		population.push_back(p1);
		population.push_back(p2);
		generatePopulation(population_size - 2); // rePopulate rest of population
		generateFitnessRatio();
	}


	// == non- modifying operations == //
	int getPopulationSize() const { return population_size; }
	Bag getBag(int i) const { return population[i]; }
	double getSumFitness()const { return sum_of_fitness; }
	Bag getMom() const { return mom; }
	Bag getDad() const { return dad; }

	// == modifying operations == //
	void setPopulationSize(int n) { population_size = n; }
	void addPopulation(Bag p) { population.push_back(p); }
	void setSumFitness(double s) { sum_of_fitness = s; }
	void setMom(Bag m) { mom = m; }
	void setDad(Bag d) { dad = d; }

	//Generate a certain number of individuals
	void generatePopulation(int n) { 
		for (int i = 0; i != n; i++) {
			Bag p;
			population.push_back(p);
		}
	}

	void generateFitnessRatio() // Sets up fitness for each individual ready for roulette wheel selection
	{
		int sum = 0;
		for (int i = 0; i != population_size; i++) { // get sum of all populations fitness
			sum += population[i].getFitness();
		}

		sum_of_fitness = sum;

		for (int i = 0; i != population_size; i++) { // calculates and sets each fitness ratio from sum of fitness
			double fr = population[i].getFitness() / sum_of_fitness;
			population[i].setFitnessratio(fr);
		}
	}

	// ------------------- bubblesort --------------------- //
	void bubblesort()
	{
		for (int i = 0; i != population_size - 1; i++) {
			for (int j = 0; j != population_size - i - 1; j++) {
				if (population[j].getFitnessratio() < population[j + 1].getFitnessratio()) {
					Bag temp = population[j];
					population[j] = population[j + 1];
					population[j + 1] = temp;
				}
			}
		}
	}

private:
	vector<Bag> population;
	int population_size;
	double sum_of_fitness;
	Bag mom, dad;
};

// ---------------------------------- Helper functions ------------------------------------- //
// Print the entire population
void printPopulation(Population& population) 
{
	cout << "-----------------------" << endl;
	for (int i = 0; i != population.getPopulationSize(); i++) {
		Bag p(population.getBag(i));
		cout << p << '\n';
	}
	cout << "-----------------------" << endl;
}

// ---------------------------- Selection Methods -------------------------------------------//

//  Roulette wheel selection
void roulette_wheel(Population& population)
  {
	// Selecting the individual for mom and dad
	double selection_mom = randDouble(0, 1);
	double selection_dad = randDouble(0, 1);

	// Sorting the population based on fitness
	bool momPicked = false, dadPicked = false;
	population.bubblesort();
	printPopulation(population);

	// Cycling through the population until the sum of fitness if bigger than the number selected
	double sumOfFitness = 0;

	for (int i=population.getPopulationSize() - 1; i >= 0; i--)
	{
		sumOfFitness += population.getBag(i).getFitnessratio();

		if (!momPicked)
			if (selection_mom < sumOfFitness)
			{
				Bag tempMom = population.getBag(i); // Setting the chosen individual as mom
				population.setMom(tempMom);
				momPicked = true;
			}
		if (!dadPicked)
			if (selection_dad < sumOfFitness) // Setting the chosen individual as dad
			{
				Bag tempDad = population.getBag(i);
				//cout << "sel dad:" << tempDad << endl;
				population.setDad(tempDad);
				dadPicked = true;
			}
	}
}


// Adding a mutation to the selected chromosomes
Population mutation(Population& population, string childChromo1, string childChromo2)
{
	// Random number decides on if there is a mutation
	double pm = randDouble(0, 1);

	// Which position the mutation takes place
	int randMutMom = randInt(0, CHROMOSOME_SIZE - 1);
	int randMutDad = randInt(0, CHROMOSOME_SIZE - 1);

	if (pm > MUTATION_RATE) { // Switches the chromosome state
		if (childChromo1[randMutMom] == '1')childChromo1[randMutMom] = '0';
		else childChromo1[randMutMom] = '1';
		if (childChromo2[randMutDad] == '1')childChromo1[randMutDad] = '0';
		else childChromo2[randMutDad] = '1';
	}

	// Creating the new chromosomes as indivituals
	Bag offSpring1(childChromo1);
	Bag offSpring2(childChromo2);

	// Putting the two offspring into the new population
	Population rePopulation(offSpring1, offSpring2);
	return rePopulation;
}

// Crossover breeding method
void crossover(Population& population)
{
	// Creating a random number to determine if crossover will take place
	double Pc = randDouble(0, 1);

	// Selecting what section of the chromosome will cross over
	int randSplit = randInt(0, CHROMOSOME_SIZE - 1);

	string childChromo1, childChromo2;

	// Crossing the chromosomes with each other between mom and dad
	if (Pc > CROSSOVER_RATE) {

		for (int i = 0; i != randSplit; i++) {
			childChromo1 += population.getMom().getChromosome()[i];
			childChromo2 += population.getDad().getChromosome()[i];
		}
		for (int i = randSplit; i != CHROMOSOME_SIZE; i++) {
			childChromo1 += population.getDad().getChromosome()[i];
			childChromo2 += population.getMom().getChromosome()[i];
		}
	}
	// Else create a clone if crossover does not happen
	else {
		childChromo1 = population.getMom().getChromosome();
		childChromo2 = population.getDad().getChromosome();
	}

	// Passing new chromosomes through mutation
	population = mutation(population, childChromo1, childChromo2);
}

// To check if the sequence is complete 
bool is_termination(Population& population)
{
	// loop through the population
	for (int i = 0; i != POPULATION_SIZE; i++) {
		// Check decoded integers against the Termination integer
		if (population.getBag(i).getDecodedInt() == TERMINATION)
		{
			return true;
		}
	}
	return false;
}


void reGenerate(Population& population)
{
	roulette_wheel(population);
	Bag m = population.getMom();
	Bag d = population.getDad();
	crossover(population);
}

void RunGA()
{
	Population population;
	int generations = 0;
	while (!is_termination(population)) {
		generations++;
		reGenerate(population);
	}
	printPopulation(population);
	cout << "Generations: " << generations;
}