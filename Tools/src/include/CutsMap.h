#ifndef _CutsMap_h_
#define _CutsMap_h_

#include <map>
#include <vector>

#include <boost/lexical_cast.hpp>



class CutsMap {
public:
  CutsMap(const std::string& cutsFile);

  template<typename T>
  T
  Get(const std::string& name, const int i = 0)
    const
  {
    const std::string& s = GetValues(name).at(i);
    return boost::lexical_cast<T>(s);
  }

private:
  typedef std::vector<std::string> CutValues;
  typedef std::map<std::string, CutValues> Cuts;

  const CutValues& GetValues(const std::string& name) const;

  Cuts fCuts;
};


#endif
