//
//  main.cpp
//  bandits
//
//  Created by Paul Gribelyuk on 3/15/14.
//  Copyright (c) 2014 Paul Gribelyuk. All rights reserved.
//

#include <time.h>
#include <iostream>
#include <boost/random/uniform_01.hpp>
#include <boost/random/uniform_int.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/math/distributions/beta.hpp>
#include <boost/random/poisson_distribution.hpp>

#include "Simulator.h"

using namespace std;
using namespace boost::math;

int main(int argc, const char * argv[])
{

  boost::random::mt19937 eng((const unsigned int)time(NULL));
  boost::uniform_int<int> randint(1, 10);
  boost::uniform_01<double> unif;
  
  boost::random::poisson_distribution<int, double> p(0.05);
  
  int s1 = 0;
  int M = 100000;
  for ( int i = 0; i < M; ++i ) s1 += p(eng);
  
  p.param(boost::random::poisson_distribution<int, double>::param_type(0.1));

  int s2 = 0;
  for ( int i = 0; i < M; ++i ) s2 += p(eng);

  cout << "s1 " << s1 << endl;
  cout << "s2 " << s2 << endl;
  
  unsigned int N;
  double alpha, beta;
  alpha = randint(eng);
  beta = randint(eng);
  N = 10;
  
  if ( argc > 1 )
  {
    alpha = atof(argv[1]);
  }
  if ( argc > 2 )
  {
    beta = atof(argv[2]);
  }
  if ( argc > 3 ) {
    N = atoi(argv[3]);
  }
  
//  cout << "alpha: " << alpha << " beta: " << beta << " N: " << N << endl;
  
  beta_distribution<> dist(alpha, beta);
  
  for ( int i = 0; i < N; ++i )
  {
//    cout << quantile(dist, unif(eng)) << endl;
  }
  
  Simulator* s = new Simulator(10000, 0.04);
  s->run();
  
  return 0;
  
}

