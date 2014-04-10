//
//  main.cpp
//  bandits
//
//  Created by Paul Gribelyuk on 3/15/14.
//  Copyright (c) 2014 Paul Gribelyuk. All rights reserved.
//

#include <time.h>
#include <chrono>
#include <thread>
#include <unistd.h>
#include <iostream>

#include <boost/random/uniform_01.hpp>
#include <boost/random/uniform_int.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/math/distributions/beta.hpp>
#include <boost/random/poisson_distribution.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/random_generator.hpp>
#include <boost/lexical_cast.hpp>

#include "Simulator.h"
#include "../test_messages/events_test.h"

using namespace std;
using namespace boost::math;
using namespace boost::uuids;

void publishFunction();
void subscribeFunction();

int main(int argc, const char * argv[])
{
//  auto start = chrono::high_resolution_clock::now();
//  boost::random::mt19937 eng((const unsigned int)time(NULL));
//  boost::uniform_int<int> randint(1, 10);
//  boost::uniform_01<double> unif;
//  boost::random::poisson_distribution<int, double> p(0.05);
//  
//  int s1 = 0;
//  int M = 100000;
//  for ( int i = 0; i < M; ++i ) s1 += p(eng);
//  
//  p.param(boost::random::poisson_distribution<int, double>::param_type(0.1));
//
//  int s2 = 0;
//  for ( int i = 0; i < M; ++i ) s2 += p(eng);
//
//  cout << "s1 " << s1 << endl;
//  cout << "s2 " << s2 << endl;
//  
//  unsigned int N;
//  double alpha, beta;
//  alpha = randint(eng);
//  beta = randint(eng);
//  N = 10;
//  
//  if ( argc > 1 )
//  {
//    alpha = atof(argv[1]);
//  }
//  if ( argc > 2 )
//  {
//    beta = atof(argv[2]);
//  }
//  if ( argc > 3 ) {
//    N = atoi(argv[3]);
//  }
//  
////  cout << "alpha: " << alpha << " beta: " << beta << " N: " << N << endl;
//  
//  beta_distribution<> dist(alpha, beta);
//  
//  for ( int i = 0; i < N; ++i )
//  {
////    cout << quantile(dist, unif(eng)) << endl;
//  }
//  
////  sim::Simulator* s = new sim::Simulator(10000, 100000, 0.04);
////  s->run();
////  
////  time_t t = time(NULL);
////  cout << t << endl;
//  
//  auto finish = chrono::high_resolution_clock::now();
//  cout << chrono::duration_cast<chrono::nanoseconds>(finish-start).count() << "ns\n";
//  
// 
//  random_generator gen;
//  uuid id = gen();
//  
//  cout << id << endl;
  
  auto t = test::TestEvents("*", "localhost", 5556);
  t.test_vector();

//  auto pid = fork();
//  
//  if ( pid == 0 ) {
//    t.test_publisher();
//  } else {
//    t.test_subscriber();
//  }
//  std::thread publisher(publishFunction);
//  std::thread subscriber(subscribeFunction);

//  sleep(10);
  
//  publisher.join();
//  subscriber.join();
//  t.test_encode_decode();
  
  return 0;
}

void publishFunction()
{
//  auto t = test::TestEvents("127.0.0.1", "127.0.0.1", 8889);
  test::TestEvents::test_publisher("*", 8888);
}

void subscribeFunction()
{
//  auto t = test::TestEvents("127.0.0.1", "localhost", 8889);
  test::TestEvents::test_subscriber("localhost", 8888);
}

void basicPublish()
{
  zmq::context_t ctx(1);
  zmq::socket_t sock(ctx, ZMQ_PUB);
  
  sock.bind("tcp://*:5556");
  
  
}