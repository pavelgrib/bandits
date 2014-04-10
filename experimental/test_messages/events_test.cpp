#include "events_test.h"

using namespace test;

TestEvents::TestEvents(const string bindAddr, const string connectAddr, const int port) : _bindAddr(bindAddr), _connectAddr(connectAddr), _port(port) {}

void TestEvents::test_publisher(const string address, const int port)
{
  context_t ctx(1);
  socket_t sock(ctx, ZMQ_PUB);

  boost::format formatter("tcp://%s:%d");
  formatter % address;
  formatter % port;
  string name = "click";
 
  _lock.lock();
  std::cout << "binding " << formatter.str() << "... ";
  sock.bind(formatter.str().c_str());
  std::cout << "bound" << std::endl;
  _lock.unlock();

  unsigned int count = 0;
  auto start = high_resolution_clock::now();
  sim::Event e = {.name = (char *) name.c_str(), .name_len = static_cast<unsigned int>(name.size()), .index = 0, .timeOccurred = time(NULL), .eventId = random_generator()()};

  while (1) {
    message_t * message = sim::Event::encode_to_message(&e);
    
    sock.send( message, 0 );
    if ( !(count % 1000000) ) {
      _lock.lock();
      cout << "pub " << duration_cast<milliseconds>(high_resolution_clock::now() - start).count() << " " << e.eventId << " " << count << endl;
      _lock.unlock();
      
    }
    delete message;
    count++;
    
    if (count > 10000000) break;
  }
}

void TestEvents::test_publisher()
{
  test_publisher(_bindAddr, _port);
}

void TestEvents::test_subscriber(const string address, const int port)
{
  zmq::context_t ctx(1);
  zmq::socket_t sock(ctx, ZMQ_SUB);
  sock.setsockopt(ZMQ_SUBSCRIBE, "", 0);
  boost::format formatter("tcp://%s:%d");
  formatter % address;
  formatter % port;
  
  _lock.lock();
  std::cout << "connecting to " << formatter.str() << "... ";
  sock.connect(formatter.str().c_str());
  std::cout << "connected" << std::endl;
  _lock.unlock();
  
  int count = 0;

  while (1) {
    zmq::message_t msg;
    cout << "receiving... " << endl;
    sock.recv(&msg);
    cout << "received" << endl;
      
    sim::Event * e = sim::Event::decode_from_message(&msg);
    count++;
    
    if ( !(count % 1000000) ) {
      std::cout << "rec " << e->eventId << " " << e->timeOccurred << " " << count << std::endl;
    }
    
    delete e;
    if (count > 10000000) break;
  }
}

void TestEvents::test_subscriber()
{
  test_subscriber(_connectAddr, _port);
}

void TestEvents::test_encode_decode()
{
  char name[] = "click";
  sim::Event e = {.name = name, .name_len = 5, .index = 0, .timeOccurred = time(NULL), .eventId = random_generator()()};
  cout << "initial event " << e.name << " " << e.eventId << " " << e.index << " " << e.timeOccurred << endl;
  message_t * msg = sim::Event::encode_to_message(&e);
  sim::Event * e2 = sim::Event::decode_from_message(msg);
  
  cout << "decoded event " << e2->name << " " << e2->eventId << " " << e2->index << " " << e2->timeOccurred << endl;
}

void TestEvents::test_vector()
{
  vector<std::tuple<int, double, string>> v;
  
  for ( int i = 50; i < 100; ++i )
  {
    v.push_back(make_tuple(i, (double) i, "i"));
  }
  
  for( tuple<int, double, string> tup: v )
  {
    cout << get<0>(tup) << " "  << get<1>(tup) << " " << get<2>(tup) << " ";
  }
  cout << endl;
  for( int i = 0; i < 25; ++i )
  {
    v.pop_back();
  }
  cout << endl;
  
  for( auto d: v )
  {
    cout << get<0>(d) << endl;
  }
}