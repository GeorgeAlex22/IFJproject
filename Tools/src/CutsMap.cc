#include "CutsMap.h"

#include <boost/algorithm/string/predicate.hpp>

#include <fstream>
#include <sstream>
#include <iterator>
#include <stdexcept>


using namespace std;

CutsMap::CutsMap(const string& cutsFile)
{
  ifstream cuts(cutsFile.c_str());

  while (true) {
    string line;
    getline(cuts, line);

    if (cuts.eof())
      break;

    if (boost::starts_with(line, "#") || line.empty())
      continue;

    istringstream ss(line);
    istream_iterator<string> it(ss), end;
    const string label(*it++);
    const CutValues values(it, end);
    fCuts[label] = values;
  }
}


const CutsMap::CutValues&
CutsMap::GetValues(const string& name)
  const
{
  Cuts::const_iterator it = fCuts.find(name);

  if (it == fCuts.end()) {
    const string msg = "Unknown cut label (doesn't appear in the input file): ";
    throw std::out_of_range(msg + name);
  }

  return it->second;
}
