#include "PHGenEventMap_v1.h"

#include "PHGenEvent.h"

using namespace std;

ClassImp(PHGenEventMap_v1)

PHGenEventMap_v1::PHGenEventMap_v1()
: _map() {
}

PHGenEventMap_v1::PHGenEventMap_v1(const PHGenEventMap_v1& trackmap)
  : _map() {  
  for (ConstIter iter = trackmap.begin();
       iter != trackmap.end();
       ++iter) {
    const PHGenEvent *track = iter->second;
    _map.insert(make_pair(track->get_id(),track->Clone()));
  }  
}

PHGenEventMap_v1& PHGenEventMap_v1::operator=(const PHGenEventMap_v1& trackmap) {
  Reset();
  for (ConstIter iter = trackmap.begin();
       iter != trackmap.end();
       ++iter) {
    const PHGenEvent *track = iter->second;
    _map.insert(make_pair(track->get_id(),track->Clone()));
  }  
  return *this;
}

PHGenEventMap_v1::~PHGenEventMap_v1() {
  Reset();
}

void PHGenEventMap_v1::Reset() {
  for (Iter iter = _map.begin();
       iter != _map.end();
       ++iter) {
    PHGenEvent *track = iter->second;
    delete track;
  }
  _map.clear();
}

void PHGenEventMap_v1::identify(ostream& os) const {
  os << "PHGenEventMap_v1: size = " << _map.size() << endl;
  return;  
}

const PHGenEvent* PHGenEventMap_v1::get(unsigned int id) const {
  ConstIter iter = _map.find(id);
  if (iter == _map.end()) return NULL;  
  return iter->second;
}

PHGenEvent* PHGenEventMap_v1::get(unsigned int id) {
  Iter iter = _map.find(id);
  if (iter == _map.end()) return NULL;
  return iter->second;
}

PHGenEvent* PHGenEventMap_v1::insert(const PHGenEvent* track) {
  unsigned int index = 0;
  if (!_map.empty()) index = _map.rbegin()->first + 1;
  _map.insert(make_pair( index , track->Clone() ));
  _map[index]->set_id(index);
  return _map[index];
}
