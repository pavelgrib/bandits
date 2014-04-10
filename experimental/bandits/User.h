//
//  User.h
//  bandits
//
//  Created by Paul Gribelyuk on 3/29/14.
//  Copyright (c) 2014 Paul Gribelyuk. All rights reserved.
//

#ifndef bandits_User_h
#define bandits_User_h

#include <boost/uuid/uuid.hpp>

namespace sim {

class User {
  
public:
  User(const unsigned long userId);
  ~User();
  
  
  
private:
  boost::uuids::uuid userId;
  
  void emitEvent();
};

}
#endif
