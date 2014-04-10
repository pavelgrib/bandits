//
//  basic_test.cpp
//  bandits
//
//  Created by paul on 4/4/14.
//  Copyright (c) 2014 Paul Gribelyuk. All rights reserved.
//

#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/random_generator.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/lexical_cast.hpp>

#include <../bandits/Event.h>

using namespace boost::property_tree;
using namespace std;
using namespace boost::uuids;

typedef struct my_struct_t {
  string s;
  int ival;
  double dval;
  uuid uuid_val;
} my_struct_t;


int basic(int argc, char * argv[])
{
  char * buf = new char[20];
  int i1, i2;
  string i3 = "aaa";
  i1 = 100;
  i2 = 200;
  snprintf( buf, 20, "%d %s %d", i1, i3.c_str(), i2);
  int i4, i5;
  string i6;
  cout << buf << endl;
  istringstream iss(buf);
  
  iss >> i4 >> i6 >> i5;
  
  cout << i4 << i5 << i6 << endl;

  uuid id = random_generator()();
  string str = "hello world";
  int i = 5;
  double d = 5.8;
  
  my_struct_t x = {.ival = i, .dval = d, .s = str, .uuid_val = id};
  ostringstream oss;
  oss << x.ival << " " << x.dval << " " << x.s << " " << x.uuid_val;

  cout << oss.str() << endl;
  ptree pt;

  pt.put("ival", i);
  pt.put("dval", d);
  pt.put("s", str);
  pt.put("uuid_val", boost::lexical_cast<string>(id));
  istringstream iss2(oss.str());

  iss2 >> x.ival >> x.dval >> x.s >> x.uuid_val;

  cout << x.uuid_val << " " << x.dval << " " << x.s << endl;
  
  ostringstream oss2;
  write_json(oss2, pt, false);

  cout << oss2.str() << endl;

  cout << "sizeof(char) " << sizeof(char) << endl;
  cout << "sizeof(int) " << sizeof(int) << endl;
  cout << "sizeof(short) " << sizeof(short) << endl;
  cout << "sizeof(uuid) " << sizeof(x.uuid_val) << endl;
  cout << "sizeof(float) " << sizeof(float) << endl;
  cout << "sizeof(double) " << sizeof(double) << endl;
  cout << "sizeof(char *) " << sizeof(char *) << endl;
  cout << "sizeof(time_t) " << sizeof(time_t) << endl;
  cout << "sizeof(char) " << sizeof(char) << endl;

  return 0;
}

