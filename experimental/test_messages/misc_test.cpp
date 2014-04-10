#include <iostream>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/random_generator.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <sstream>
#include <string>
#include <boost/lexical_cast.hpp>

using namespace std;
using namespace boost::uuids;

int main(int argc, char * argv[])
{
  random_generator gen;
  uuid id = gen();

  string idStr = boost::lexical_cast<string>(id);
  cout << idStr << endl;

  istringstream iss("434kj3rf2342kakd34kj3kj4h3kj43ke");
  uuid id2 = boost::lexical_cast<uuid>(iss.str());

  cout << iss.str().size() << " " << iss.str() << endl << id2 << endl;

}
