/**
* @file ModuleManager.h
*
* @author <a href="mailto:mellmann@informatik.hu-berlin.de">Heinrich Mellmann</a>
* Declaration of class ModuleManager (base class for ModuleManagers)
*/

#ifndef __ModuleManager_h_
#define __ModuleManager_h_

#include <map>
#include <set>
#include <string>
#include <list>
#include <vector>
#include <limits>

#include "Module.h"
#include "BlackBoard.h"
#include "ModuleClassWraper.h"

using namespace std;

class ModuleManager: virtual public BlackBoardInterface
{
public:
  virtual ~ModuleManager()
  {
    map<string, AbstractModuleCreator* >::iterator iter;
    for(iter = moduleExecutionMap.begin(); iter != moduleExecutionMap.end(); iter++)
    {
      delete (iter->second);
    }//end for
  }//end destructor

protected:

  /**
   * register a module
   * registration of different instances of the same class 
   * with different names is alowed
   */
  template<class T>
  ModuleCreator<T>* registerModule(std::string name)
  {
    // module does not exist
    if(moduleExecutionMap.find(name) == moduleExecutionMap.end())
    {
      moduleExecutionList.push_back(name);
      moduleExecutionMap[name] = createModule<T>();
    }

    AbstractModuleCreator* module = moduleExecutionMap.find(name)->second;
    ModuleCreator<T>* typedModule = dynamic_cast<ModuleCreator<T>*>(module);

    // check the type
    if(typedModule == NULL)
    {
      std::cerr << "Module type mismatch: " << name << " is already registered as "
                // HACK: getModuleName doesn't necessary return the type of the module
                << module->getModule()->getModuleName() << ", but "
                << typeid(T).name() << " requested." << std::endl;
      assert(false);
    }//end if

    return typedModule;
  }//end registerModule


  /**
   * enables or disables the module 'moduleName'
   * if the module 'moduleName' doesn't exist
   * no action is done
   */
  void setModuleEnabled(string moduleName, bool value, bool recalculateExecutionList=false)
  {
    if(moduleExecutionMap.find(moduleName) != moduleExecutionMap.end())
    {
      moduleExecutionMap[moduleName]->setEnabled(value);
      if(recalculateExecutionList)
      {
        calculateExecutionList();
      }
    }
  }//end setModuleEnabled

  /**
   *
   */
  AbstractModuleCreator* getModule(string name)
  {
    map<string, AbstractModuleCreator* >::iterator iter = moduleExecutionMap.find(name);
    if(iter != moduleExecutionMap.end())
    {
      return iter->second;
    }

    // TODO: assert?
    return NULL;
  }//end getModule


  const list<string>& getExecutionList()
  {
    return moduleExecutionList;
  }//end getExecutionList
  
  /**
   * Calculate the execution list automatically from the dependencies
   */
  void calculateExecutionList()
  {
    map<string,string> providerForRepresentation;
    map<string, list<string> > required;
    map<string, list<string> > provided;
    
    // first fill the map with providers and the module graph
    for(map<string, AbstractModuleCreator* >::const_iterator it=moduleExecutionMap.begin(); 
      it != moduleExecutionMap.end(); it++)
    {
      // only include enabled modules
      if(it->second->isEnabled())
      {
        Module* m = it->second->getModule();
        
        for(std::list<Representation*>::const_iterator itProv = m->getProvidedRepresentations().begin();
          itProv != m->getProvidedRepresentations().end(); itProv++)
        {
          std::string repName = (*itProv)->getName();
          
          if(providerForRepresentation.find(repName) == providerForRepresentation.end())
          {
            providerForRepresentation[repName] = it->first;
            provided[it->first].push_back(repName);
          }
          else
          {
            std::cerr << "ERROR: " << repName << " provided by both " << providerForRepresentation[repName]
              << " and " << it->first;
          }
        }
        
        for(std::list<Representation*>::const_iterator itReq = m->getRequiredRepresentations().begin();
          itReq != m->getRequiredRepresentations().end(); itReq++)
        {
          std::string repName = (*itReq)->getName();
          required[it->first].push_back(repName);
        }
        
      } // if module enabled
    }
    
    // solve this constraint problem
    vector<string> oldExecutionList(moduleExecutionList.begin(), moduleExecutionList.end());
    unsigned int oldErrors = countExecutionListErrors(oldExecutionList, required, provided, false);
    unsigned int unsuccessfulAttempts = 0;
    
    const unsigned int maxAttempts = oldExecutionList.size()*10;
    
    // init to same seed to get "reliable" results
    srand(100);
    
    while(oldErrors != 0 && unsuccessfulAttempts < maxAttempts)
    {
      vector<string> newExecutionList = oldExecutionList;
      // switch randomly
      int left = 0;
      int right = 0;
      
      while(left == right)
      {
        left = rand() % newExecutionList.size();
        right = rand() % newExecutionList.size();
      }
      
      string buffer = newExecutionList[right];
      newExecutionList[right] = newExecutionList[left];
      newExecutionList[left] = buffer;
      
      unsigned int newErrors = countExecutionListErrors(newExecutionList, required, provided, false);
      //cerr << "new error = " << newErrors << " | old = " << oldErrors << " | no success = " << unsuccessfulAttempts << endl;
      if(newErrors < oldErrors)
      {
        oldErrors = newErrors;
        oldExecutionList = newExecutionList;
        unsuccessfulAttempts = 0;
      }
      else
      {
        unsuccessfulAttempts++;
      }
    }
    
    // reset random seed if another one is using it
    srand(time(NULL));
    
    moduleExecutionList.clear();
    copy(oldExecutionList.begin(), oldExecutionList.end(), back_inserter(moduleExecutionList));
    
    // print execution list
    cout << "automatic module execution list" << endl;
    cout << "-------------------------------" << endl;
    for(list<string>::const_iterator itExec = moduleExecutionList.begin(); 
      itExec != moduleExecutionList.end(); itExec++
    )
    {
      cout << *itExec << endl;
    }
    cout << "-------------------------------" << endl;
    cout << endl;
    
    // output missing dependencies
    countExecutionListErrors(oldExecutionList, required, provided, true);
    
  }
  
  virtual string getSensorModuleName() { return "Sensor";}
  virtual string getActuatorModuleName() { return "Actuator";}

private:
  template<class T>
  ModuleCreator<T>* createModule()
  {
    return new ModuleCreator<T>(getBlackBoard());
  }//end createModule


  /** */
  //BlackBoard theBlackBoard;

  /** store the mapping name->module */
  map<string, AbstractModuleCreator* > moduleExecutionMap;

  /** list of names of modules in the order of registration */
  list<string> moduleExecutionList;
  
  void internalAddModuleToExecutionList(string name, set<string>& availableRepresentations, map<string,string>& providerForRepresentation)
  {
    AbstractModuleCreator* am = getModule(name);
    if(am != NULL && am->isEnabled() && am->getModule() != NULL)
    {
      bool addModuleToList = true;
      Module* m = am->getModule();
      
      // add all provided representations of this module to our known set
      const list<Representation*> provided = m->getProvidedRepresentations(); 
      for(list<Representation*>::const_iterator itProv=provided.begin(); itProv != provided.end(); itProv++)
      {
        string repName = (*itProv)->getName();
        if(availableRepresentations.find(repName) == availableRepresentations.end())
        { 
          availableRepresentations.insert(repName);
          providerForRepresentation[repName] = name;
        }
        else
        {
          cerr << "ERROR when calculating execution order: " << repName << " provided more than once "
            << "(" << name << " and " << providerForRepresentation[repName] << ")" << endl;
            addModuleToList = false;
        }
      } // end for all provided representations
      if(addModuleToList)
      {
        moduleExecutionList.push_back(name);        
      }
    }
  } // end internalAddModuleToExecutionList
  
  unsigned int countExecutionListErrors(const vector<string>& order, 
    map<string, list<string> >& required, map<string, list<string> >& provided, bool outputError)
  {
    unsigned int errors = 0;
    
    set<string> availableRepresentations;
    
    for(vector<string>::const_iterator it = order.begin(); it != order.end(); it++)
    {
      string module = *it;
      const list<string>& req = required[module];
      const list<string>& prov = provided[module];
      
      for(list<string>::const_iterator itReq = req.begin(); itReq != req.end(); itReq++)
      {
        if(availableRepresentations.find(*itReq) == availableRepresentations.end())
        {
          errors++;
          if(outputError)
          {
            cerr << "ERROR: no provider for " << *itReq << " in " << module << endl;
          }
        }
      }
      
      for(list<string>::const_iterator itProv = prov.begin(); itProv != prov.end(); itProv++)
      {
        availableRepresentations.insert(*itProv);
      }
    }
    
    return errors;
  }
  
};

#endif //__ModuleManager_h_