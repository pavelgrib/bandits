//
//  Bandit.h
//  bandits
//
//  Created by Paul Gribelyuk on 3/15/14.
//  Copyright (c) 2014 Paul Gribelyuk. All rights reserved.
//

#ifndef bandits_Bandit_h
#define bandits_Bandit_h

#include "Event.h"
#include <boost/tr1/unordered_map.hpp>
#include <vector>

class MultiArmedBandit {
  
public:
  MultiArmedBandit(unsigned int N);
  ~MultiArmedBandit();

  inline unsigned int getNumberOfArms() { return numberOfArms; };
  std::vector<double>& state();
  void reset();
  
  void update(const sim::Event e);
  
  int getVersion();
  
private:
  unsigned int numberOfArms;
  std::vector<double> alphas;
  std::vector<double> betas;
};

#endif
