//
//  Simulator.h
//  bandits
//
//  Created by Paul Gribelyuk on 3/17/14.
//  Copyright (c) 2014 Paul Gribelyuk. All rights reserved.
//

#ifndef bandits_Simulator_h
#define bandits_Simulator_h

#include <memory>
#include <time.h>
#include <vector>
#include "Event.h"
#include <zmq.hpp>
#include <string.h>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/poisson_distribution.hpp>

namespace sim {

using namespace boost::random;

class Simulator {

public:
  Simulator(const time_t timeToRun, const unsigned int numberOfUsers, const double poissonLambda);
  ~Simulator();
  
  double percentageSuccess();
  void run();

private:
  unsigned int _numberOfUsers;
  double _possionLambda;
  time_t _timeToRun;
  mt19937 _mersenneEngine;
  poisson_distribution<int, double> _poisson;
  time_t _currentTime;
  unsigned int _eventIndex;
  std::vector<Event> _events;
  std::unique_ptr<zmq::context_t> _context;
  std::unique_ptr<zmq::socket_t> _eventPubSocket;
  
  void update();
  void sendEvent(Event & event);
  void sendEndMessage();
  void waitForConnections();
};

}

#endif
