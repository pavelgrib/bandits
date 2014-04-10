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
#include <tuple>
#include "Event.h"
#include "Bandit.h"
#include <zmq.hpp>
#include <string.h>
#include <stdio.h>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/poisson_distribution.hpp>
#include <boost/uuid/uuid_generators.hpp> // generators
#include <boost/uuid/uuid.hpp>

#define MAX_USERS 1000000

namespace sim {

using namespace boost::random;
using boost::uuids::uuid;
  
class Simulator {

public:
  
  Simulator(const time_t timeToRun,const unsigned int numScenarious, const double userArrival);
  ~Simulator();
  
  void setWinningScenario(const unsigned int idx);
  double percentageSuccess();
  void run();

private:
  unsigned int _numberOfUsers;
  double _possionLambda;
  
  unsigned int _numScenarios;
  unsigned int _winningIndex;
  double _userArrivalLambda;
  time_t _timeToRun;
  mt19937 _mersenneEngine;
  poisson_distribution<int, double> _poisson;
  poisson_distribution<int, double> _userPoisson;
  time_t _currentTime;
  unsigned int _eventIndex;
  std::vector<Event> _events;
  std::unique_ptr<zmq::context_t> _context;
  std::unique_ptr<zmq::socket_t> _eventPubSocket;
  boost::uuids::basic_random_generator<boost::mt19937> _idGenerator;
  std::vector<bool> _userActive;
  std::vector<std::string> _connected;
  std::vector<std::tuple<uuid, time_t, int, int>> _connectedUsers;
  MultiArmedBandit _bandit;
  
  void updateAllUsers();
  void sendEvent(Event & event);
  void sendEndMessage();
  void waitForConnections(std::string address);
};

}

#endif
