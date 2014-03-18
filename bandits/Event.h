//
//  Event.h
//  bandits
//
//  Created by Paul Gribelyuk on 3/15/14.
//  Copyright (c) 2014 Paul Gribelyuk. All rights reserved.
//

#ifndef bandits_Event_h
#define bandits_Event_h

#include <string>
#include <MurmurHash3.h>
#include <cstdlib>
#include <time.h>


typedef struct Event
{
  std::string name;
  unsigned int index;
  time_t timeOccurred;
} Event;


typedef struct {
  
  long operator() (const Event& e) const
  {
    long out;
    uint32_t seed = (uint32_t) time(NULL);
    MurmurHash3_x86_32(&e.name, 32, seed, &out);
    return out;
  }
} EventHash;


typedef struct {
  
  long operator() ( const Event& e1, const Event& e2) const
  {
    return e1.name == e2.name;
  }
} EventEq;


#endif
