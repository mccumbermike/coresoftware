#ifndef __PHEVENTGENERATORTRIGGER_H__
#define __PHEVENTGENERATORTRIGGER_H__

#include "PHGenEvent.h"

#include <string>

#include <phool/PHObject.h>

class PHEventGeneratorTrigger : public PHObject {
  
public:

  PHEventGeneratorTrigger(const std::string &name = "PHEVENTGENTRIGGER");
  virtual ~PHEventGeneratorTrigger();

  virtual bool trigger_event(const PHGenEvent* eventdata) {return true;}
  
 protected:
 private:
};

#endif	/* __PHEVENTGENERATORTRIGGER_H__ */

