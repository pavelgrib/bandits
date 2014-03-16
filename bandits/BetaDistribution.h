//
//  BetaDistribution.h
//  bandits
//
//  Created by Paul Gribelyuk on 3/15/14.
//  Copyright (c) 2014 Paul Gribelyuk. All rights reserved.
//

#ifndef bandits_BetaDistribution_h
#define bandits_BetaDistribution_h

#include <boost/math/distributions/beta.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_01.hpp>
#include <vector>

#define DEFAULT_LEN_HISTORY 100

class BetaDistribution {
  
public:
  BetaDistribution();
  BetaDistribution(const double alpha, const double beta);
  BetaDistribution(const double alpha, const double beta, const size_t maxLen);
  ~BetaDistribution();
  
  double sample();
  void updateAlpha(const double newAlpha);
  void updateBeta(const double newBeta);
  
private:
  double _alpha;
  double _beta;
  boost::math::beta_distribution<> _dist;

  boost::random::mt19937 _eng;
  boost::uniform_01<double> _realUniform;
  
  std::vector<double> _history;
  
  size_t _maxLength;
};

#endif
