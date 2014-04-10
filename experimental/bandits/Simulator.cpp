//
//  Simulator.cpp
//  bandits
//
//  Created by Paul Gribelyuk on 3/17/14.
//  Copyright (c) 2014 Paul Gribelyuk. All rights reserved.
//

#include "Simulator.h"


using namespace sim;

//Simulator::Simulator(const time_t timeToRun, const unsigned int numberOfUsers, const double poissonLambda) :
//_numberOfUsers(numberOfUsers), _timeToRun(timeToRun), _possionLambda(poissonLambda), _userActive(numberOfUsers, false)
//{
//  for ( int i = 0; i < _numberOfUsers; ++i ) _userActive.push_back(false);
//  _context = std::unique_ptr<zmq::context_t>(new zmq::context_t(1));
//  _eventPubSocket = std::unique_ptr<zmq::socket_t>(new zmq::socket_t( *_context, ZMQ_PUB ));
//  _currentTime = time(NULL);
//  _eventIndex = 0;
//  assert(_numberOfUsers > 0);
//  
//  _poisson.param(poisson_distribution<int, double>::param_type(poissonLambda));
//}

Simulator::Simulator(const time_t timeToRun, const unsigned int numScenarios, const double userArrival): _timeToRun(timeToRun), _numScenarios(numScenarios), _winningIndex(0), _numberOfUsers(MAX_USERS), _userArrivalLambda(userArrival), _bandit(numScenarios)
{
  _userPoisson.param(poisson_distribution<int, double>::param_type(userArrival));
}

Simulator::~Simulator()
{
  this->sendEndMessage();
  
  _context->close();
}

void Simulator::setWinningScenario(const unsigned int idx)
{
  assert( idx < _numScenarios );
  _winningIndex = idx;
}

void Simulator::waitForConnections(std::string address)
{
  zmq::socket_t connectionSocket( *this->_context, ZMQ_REP );
  connectionSocket.connect(address.c_str());
  zmq::pollitem_t items [] = { { connectionSocket,  0, ZMQ_POLLIN, 0 } };
  zmq::poll (items, 1);
  
  if (items[0].revents & ZMQ_POLLIN) {
    zmq::message_t incomingMessage;
    this->_connected.push_back(std::string((char *) incomingMessage.data()));
  }
}

void Simulator::sendEndMessage()
{
  // send a non-blocking message
  zmq::message_t endMessage(4);
  snprintf((char *) endMessage.data(), 4, "end");
  _eventPubSocket->send(endMessage);
}

void Simulator::sendEvent(Event & event)
{
  zmq::message_t * msg = Event::encode_to_message(&event);
  _eventPubSocket->send(*msg);
  delete msg;
}

void Simulator::run()
{
  time_t t = time(NULL);
  time_t endTime = t + _timeToRun;
  
  for ( ; time(NULL) < endTime; ) {

    for (auto user: _connectedUsers) {

//      if( _poisson(_mersenneEngine) ) {
//        // user departed
//      } else {
//        
//      }
    }
    
    for ( int i = 0; i < _numberOfUsers; ++i ) {
      if( _userPoisson(_mersenneEngine) ) {
        // user arrived
        auto userId = _idGenerator();
        auto now = time(NULL);
        auto siteVersion = _bandit.getVersion();
        auto userTup = std::make_tuple(userId, now, siteVersion, 0);
        _connectedUsers.push_back(userTup);
      }
    }
  }
}

void Simulator::updateAllUsers()
{
  for( int i = 0; i < _numberOfUsers; ++i ) {
    if( _poisson(_mersenneEngine) ) {
      Event e = {.name = (char *) CLICK, .eventId = _idGenerator(), .index = 0, .timeOccurred = time(NULL) };
      this->sendEvent(e);
    }
  }
}

double Simulator::percentageSuccess() {
  unsigned int count = 0;
  for (Event evt: _events)
  {
    if (strcmp(evt.name, (char *) CLICK) == 0) {
      count++;
    }
  }
  
  return (double) count / _timeToRun;
}

