

#ifndef events_Test_h
#define events_Test_h

#include <iomanip>
#include <cstdio>
#include <chrono>
#include <vector>
#include <stdlib.h>

#include "../cppzmq/zmq.hpp"
#include <unistd.h>
#include <iostream>
#include <tuple>
#include <string>
#include <boost/format.hpp>
#include <boost/lexical_cast.hpp>
#include <sstream>
#include <mutex>

#include "../bandits/Event.h"

using namespace std::chrono;
using namespace std;
using namespace zmq;


namespace test {

static std::mutex _lock;

class TestEvents {
  
public:
  TestEvents();
  TestEvents(const string bindAddr, const string connectAddr, const int port);
  
  void test_publisher();
  void test_subscriber();
  static void test_publisher(const string address, const int port);
  static void test_subscriber(const string address, const int port);

  void test_encode_decode();
  void test_vector();
  
  inline void setBindAddress(const string newAddress)
  { _bindAddr = newAddress; };
  
  inline void setConnectAddress(const string newAddress)
  { _connectAddr = newAddress; };
  
  inline void setPort(const int newPort)
  { _port = newPort; };
  
private:
  string _bindAddr;
  string _connectAddr;
  int _port;
};

}
#endif