/*
 * Declarations for Deme class to evolve a genetic algorithm for the
 * travelling-salesperson problem.  A deme is a population of individuals.
 */

#include "chromosome.hh"
#include "deme.hh"

// Generate a Deme of the specified size with all-random chromosomes.
// Also receives a mutation rate in the range [0-1].
Deme::Deme(const Cities* cities_ptr, unsigned pop_size, double mut_rate)
{
    mut_rate_ = mut_rate;
    while (pop_size > 0)
    {
        auto tmp = Chromosome(cities_ptr);
        pop_.push_back(&tmp);
        pop_size--;
    }
}

/*/ Clean up as necessary
Deme::~Deme()
{
  // Add your implementation here
}*/

// Evolve a single generation of new chromosomes, as follows:
// We select pop_size/2 pairs of chromosomes (using the select() method below).
// Each chromosome in the pair can be randomly selected for mutation, with
// probability mut_rate, in which case it calls the chromosome mutate() method.
// Then, the pair is recombined once (using the recombine() method) to generate
// a new pair of chromosomes, which are stored in the Deme.
// After we've generated pop_size new chromosomes, we delete all the old ones.
void Deme::compute_next_generation()
{
    std::vector<Chromosome*> newchroms;
    while (newchroms.size() < pop_.size())
    {
        auto chrom1 = select_parent();
        auto chrom2 = select_parent();
        if (rand() < mut_rate_)
        {
            chrom1->mutate();
        }
        if (rand() < mut_rate_)
        {
            chrom2->mutate();
        }
        auto tempchroms = chrom1->recombine(chrom2);
        newchroms.push_back(tempchroms.first);
        newchroms.push_back(tempchroms.second);
    }

    if (newchroms.size() > pop_.size())
    {
        newchroms.pop_back();
    }
    pop_ = newchroms;
}

// Return a copy of the chromosome with the highest fitness.
const Chromosome* Deme::get_best() const
{
    if (pop_.size() >= 1)
    {
        auto bestfitness = pop_[0]->get_fitness();
        auto best = pop_[0];
        for (auto iter = pop_.begin(); iter != pop_.end(); ++iter)
        {
            if ((*iter)->get_fitness() > bestfitness)
            {
                bestfitness = (*iter)->get_fitness();
                best = *iter;
            }
        }
        return best;
        }
    else
    {
        return nullptr;
    }
}

// Randomly select a chromosome in the population based on fitness and
// return a pointer to that chromosome.
Chromosome* Deme::select_parent()
{
    double total_fitness = 0.0;
    for (auto iter = pop_.begin(); iter != pop_.end(); ++iter)
    {
        total_fitness+= (*iter)->get_fitness();
    }
    auto randsel = rand() * total_fitness;
    double last = 0.0;
    double curr = 0.0;
    for (auto iter = pop_.begin(); iter != pop_.end(); ++iter)
    {
        curr = last + (*iter)->get_fitness();
        if ((randsel >= last) and (randsel <= curr))
        {
            return *iter;
        }
        last = curr;
    }
    return nullptr; //this line should never be reached but putting it in for the sake of compiler errors
}
