

#pragma once

#include "chromosome.hh"

class ClimbChromosome: public Chromosome {
public:
  virtual void mutate() override;

  virtual Chromosome* clone() const override {
    return new ClimbChromosome(*this);
  }
}
