#ifndef __PHEVENTGENERATOR_H__
#define __PHEVENTGENERATOR_H__

#include "PHEventGeneratorBase.h"
#include "PHEventGeneratorMethod.h"
#include "PHEventGeneratorTrigger.h"

class PHEventGenerator : public PHEventGeneratorBase {
 public:
  
  PHEventGenerator(PHEventGeneratorMethod* generator,
                   PHEventGeneratorTrigger* trigger = NULL,
                   const std::string& name = "PHEVENTGEN");
  virtual ~PHEventGenerator();

};

#endif /* __PHEVENTGENERATOR_H__ */
