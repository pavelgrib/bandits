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
#include <stdio.h>
#include <MurmurHash3.h>
#include <cstdlib>
#include <stdlib.h>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/random_generator.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/lexical_cast.hpp>
#include <chrono>
#include <zmq.hpp>
#include <sstream>

#define CLICK "click"

using namespace boost::uuids;
using namespace std::chrono;
using namespace boost::property_tree;

namespace sim {
  
typedef struct Event
{
  char * name;  // flexible: can reflect any meta information
  unsigned int name_len;
  uuid eventId;  // unique event ID (always length 16 bytes)
  unsigned int index;  // if this is in a sequence of events, indicates location
  time_t timeOccurred;  // time(NULL)
  uuid userId;
  
  static zmq::message_t * encode_to_message(const Event * e)
  {
    int len = 2 * sizeof(int) + e->name_len + sizeof(uuid) + sizeof(time_t);
    char * msg = (char *) malloc(sizeof(char) * len);
    memcpy(msg, &e->name_len, sizeof(unsigned int));
    msg += sizeof(int);
    memcpy(msg, e->name, e->name_len);
    msg += e->name_len;
    memcpy(msg, &e->eventId, sizeof(uuid));
    msg += sizeof(uuid);
    memcpy(msg, &e->index, sizeof(unsigned int));
    msg += sizeof(int);
    memcpy(msg, &e->timeOccurred, sizeof(time_t));
    zmq::message_t * message = new zmq::message_t(len);
    msg -= (len - sizeof(time_t));
    memcpy((char *) message->data(), msg, len);
    free(msg);
    return message;
  }
  
  static Event * decode_from_message(zmq::message_t * message)
  {
    Event * e = new Event;
    char * dataptr = static_cast<char *>(message->data());
    unsigned int sz = 0;
    sz = *((int*) dataptr);
    e->name_len = sz;
    dataptr += sizeof(unsigned int);

    e->name = new char[e->name_len];
    memcpy((void *) e->name, dataptr, sz);
    dataptr += sz;

    memcpy((void *) &e->eventId, dataptr, sizeof(uuid));
    dataptr += sizeof(uuid);

    memcpy(&e->index, dataptr, sizeof(int));
    dataptr += sizeof(unsigned int);
    
    memcpy(&e->timeOccurred, dataptr, sizeof(time_t));
    
    return e;
  }
  
  static zmq::message_t * encode_to_message_json(const Event * e)
  {
    std::ostringstream oss;
    ptree pt;
    pt.put("name", e->name);
    pt.put("eventId", boost::lexical_cast<std::string>(e->eventId));
    pt.put("index", e->index);
    pt.put("timeOccurred", e->timeOccurred);
    write_json(oss, pt, false);
    std::string messageStr = oss.str();
    zmq::message_t * message = new zmq::message_t( messageStr.size() );
    memcpy((char *) message->data(), messageStr.c_str(), messageStr.size());
    return message;
  }
  
  static Event * decode_from_message_json( zmq::message_t * message )
  {
    std::istringstream iss( (char *) message->data() );
    ptree pt;
    read_json(iss, pt);
    Event * e = new Event;
    e->name = pt.get<char *>("name");
    e->eventId = boost::lexical_cast<uuid>(pt.get<std::string>("eventId"));
    e->index = pt.get<int>("index");
    e->timeOccurred = pt.get<time_t>("timeOccurred");
    return e;
  }

} Event;


typedef struct
{
  long operator() (const Event& e) const
  {
    long out;
    uint32_t seed = (uint32_t) time(NULL);
    MurmurHash3_x86_32(&e.name, 32, seed, &out);
    return out;
  }
} EventHash;


typedef struct
{
  long operator() ( const Event& e1, const Event& e2) const
  {
    return e1.name == e2.name;
  }
} EventEq;

}  // sim namespace

#endif
