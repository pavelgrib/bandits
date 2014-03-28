//
//  Simulator.cpp
//  bandits
//
//  Created by Paul Gribelyuk on 3/17/14.
//  Copyright (c) 2014 Paul Gribelyuk. All rights reserved.
//

#include "Simulator.h"

Simulator::Simulator(const time_t timeToRun, const double poissonLambda) :
_poissonLambda(poissonLambda), _timeToRun(timeToRun)
{
  _context = std::unique_ptr<zmq::context_t>(new zmq::context_t(1));
  _eventPubSocket = std::unique_ptr<zmq::socket_t>(new zmq::socket_t( *_context, ZMQ_PUB ));

  _currentTime = 0;
  _eventIndex = 0;
  assert(_poissonLambda > 0);
  _poisson.param(poisson_distribution<int, double>::param_type(_poissonLambda));
}


Simulator::~Simulator()
{
  this->sendEndMessage();
}


void Simulator::waitForConnections()
{
  
}

void Simulator::sendEndMessage()
{
  _eventPubSocket->send("end", 4);
}

void Simulator::sendEvent(Event &event)
{
  
}

void Simulator::run()
{
  for ( time_t t = _timeToRun; t > 0; --t ) {
    this->update();
  }
}


void Simulator::update()
{
  unsigned int numNewEvents = _poisson(_mersenneEngine);

  for ( int i = 0; i < numNewEvents; ++i )
  {
    Event evt;
    evt.timeOccurred = _currentTime;
    evt.index = ++_eventIndex;
    evt.name = "click";
  }
  
  _currentTime += 1;
}


double Simulator::percentageSuccess() {
  double count = 0;
  for (Event evt: _events)
  {
    count += 1.;
  }
  
  return count / _timeToRun;
}

