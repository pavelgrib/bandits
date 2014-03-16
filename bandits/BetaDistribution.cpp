//
//  BetaDistribution.cpp
//  bandits
//
//  Created by Paul Gribelyuk on 3/15/14.
//  Copyright (c) 2014 Paul Gribelyuk. All rights reserved.
//

#include "BetaDistribution.h"


BetaDistribution::BetaDistribution(const double alpha, const double beta, const size_t maxLen) :
_alpha(alpha), _beta(beta), _maxLength(maxLen)
{
  _dist = boost::math::beta_distribution<>(alpha, beta);
}

BetaDistribution::BetaDistribution():
_alpha(0), _beta(0), _maxLength(DEFAULT_LEN_HISTORY)
{
}

BetaDistribution::BetaDistribution(const double alpha, const double beta) :
_alpha(alpha), _beta(beta), _maxLength(DEFAULT_LEN_HISTORY)
{

}

double BetaDistribution::sample()
{
  double value = boost::math::quantile(_dist, _realUniform(_eng));
  _history.push_back(value);
  if ( _history.size() > _maxLength ) {
    _history.erase(_history.begin());
  }
  
  return value;
}

void BetaDistribution::updateAlpha(const double newAlpha)
{
  assert( newAlpha >= 0 );
  this->_alpha = newAlpha;
}

void BetaDistribution::updateBeta(const double newBeta)
{
  assert( newBeta >= 0 );
  this->_beta = newBeta;
}