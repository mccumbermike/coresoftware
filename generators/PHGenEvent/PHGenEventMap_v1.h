#ifndef __PHGENEVENTMAP_V1_H__
#define __PHGENEVENTMAP_V1_H__

#include "PHGenEvent.h"
#include "PHGenEventMap.h"

#include <phool/PHObject.h>
#include <map>

class PHGenEventMap_v1 : public PHGenEventMap {
  
public:

  PHGenEventMap_v1();
  PHGenEventMap_v1(const PHGenEventMap_v1& trackmap);
  PHGenEventMap_v1& operator=(const PHGenEventMap_v1& trackmap);
  virtual ~PHGenEventMap_v1();

  void identify(std::ostream &os = std::cout) const;
  void Reset();
  int  isValid() const {return 1;}
  PHGenEventMap* Clone() const {return new PHGenEventMap_v1(*this);}
  
  bool   empty()                   const {return _map.empty();}
  size_t  size()                   const {return _map.size();}
  size_t count(unsigned int idkey) const {return _map.count(idkey);}
  void   clear()                         {Reset();}
  
  const PHGenEvent* get(unsigned int idkey) const;
        PHGenEvent* get(unsigned int idkey); 
        PHGenEvent* insert(const PHGenEvent* track);
        size_t      erase(unsigned int idkey) {
	  delete _map[idkey]; return _map.erase(idkey);
	}

  ConstIter begin()                   const {return _map.begin();}
  ConstIter  find(unsigned int idkey) const {return _map.find(idkey);}
  ConstIter   end()                   const {return _map.end();}

  Iter begin()                   {return _map.begin();}
  Iter  find(unsigned int idkey) {return _map.find(idkey);}
  Iter   end()                   {return _map.end();}
  
private:
  GenEventMap _map;
    
  ClassDef(PHGenEventMap_v1, 1);
};

#endif
