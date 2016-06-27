#include "PHEventGenerator.h"

#include <fun4all/Fun4AllReturnCodes.h>
#include <phool/getClass.h>
#include <phool/PHCompositeNode.h>

using namespace std;

PHEventGenerator::PHEventGenerator(PHEventGeneratorMethod* generator,
				   PHEventGeneratorTrigger* trigger,
				   const std::string &name): 
  PHEventGeneratorBase(generator,trigger,name) {}

PHEventGenerator::~PHEventGenerator() {}

