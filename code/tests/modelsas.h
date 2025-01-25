#ifndef MODELSAS_H
#define MODELSAS_H

#include <iostream>

#include "pcomodel.h"
#include "pcosynchro/pcosemaphore.h"
#include "pcoconcurrencyanalyzer.h"
#include "sasAccess.h"
#include "ScenarioCreator.h"

static SasAccess* sas;

// Parent thread, children will define their agent type
class ThreadParent : public ObservableThread
{
public:
    explicit ThreadParent(std::string id, int agentType) : ObservableThread(std::move(id)), agent(agentType) {
        scenarioGraph = std::make_unique<ScenarioGraph>();
        auto scenario = scenarioGraph->createNode(this, -1);
        auto p0 = scenarioGraph->createNode(this, 0);
        auto p1 = scenarioGraph->createNode(this, 1);
        auto p2 = scenarioGraph->createNode(this, 2);
        auto p3 = scenarioGraph->createNode(this, 3);
        scenario->next.push_back(p0);
        p0->next.push_back(p1);
        p1->next.push_back(p2);
        p2->next.push_back(p3);
        scenarioGraph->setInitialNode(scenario);

        if(agent > 1)
          agent = 1;
        else if(agent < 0)
          agent = 0;
    }

    void startSect(int section) {
        startSection(section);
    }

    void endSect() {
        endSection();
    }

    void endScen() {
        endScenario();
    }

private:
    int agent;
    void run() override
    {
        startSect(0); // This section is so that we can check who takes the mutex, and define valid scenarios
        endSect();
        sas->access(agent, this);
        startSect(2); // This section is so that we can check who takes the mutex, and define valid scenarios
        endSect();
        sas->leave(agent, this);
        endScenario();
    }
};

// Thread with agent type 0
class ThreadZero : public ThreadParent
{
public:
    explicit ThreadZero(std::string id) : ThreadParent(std::move(id), 0) {}
};

// Thread with agent type 1
class ThreadOne : public ThreadParent
{
public:
    explicit ThreadOne(std::string id) : ThreadParent(std::move(id), 1) {}
};

class ModelSas : public PcoModel
{
    bool checkInvariants() override 
    {
        return true;
    }
    
    
    void build() override
    {
        threads.emplace_back(std::make_unique<ThreadZero>("0"));
        threads.emplace_back(std::make_unique<ThreadOne>("1"));
 
        auto t0 = threads[0].get();
        auto t1 = threads[1].get();
        auto builder = std::make_unique<PredefinedScenarioBuilderIter>();

        ScenarioCreator scenarioCreator({t0, t1}, {{0, 1}, {2, 3}});
        std::vector<Scenario> scenarios = scenarioCreator.createScenarios();
        builder->setScenarios(scenarios);
        scenarioBuilder = std::move(builder);
    }

    void preRun(Scenario& /*scenario*/) override
    {
        sas = new SasAccess(2);
        std::cout << std::endl; // Just for the formatting of the output
    }

    void postRun(Scenario &scenario) override 
    {
        std::cout << "Scenario : ";
        ScenarioPrint::printScenario(scenario);
        std::cout << "nbIn = " << sas->getNbIn() << std::endl;
        std::cout << "nbOfOneWaiting = " << sas->getNbOfOneWaiting() << std::endl;
        std::cout << "nbOfZerosWaiting = " << sas->getNbOfZerosWaiting() << std::endl;
        std::cout << "---------------------------------------" << std::endl;
        std::cout << std::flush;
        possibleNbIn.insert(sas->getNbIn());
        possibleNbOfOneWaiting.insert(sas->getNbOfOneWaiting());
        possibleNbOfZerosWaiting.insert(sas->getNbOfZerosWaiting());
    }

    std::set<int> possibleNbIn;
    std::set<int> possibleNbOfOneWaiting;
    std::set<int> possibleNbOfZerosWaiting;

    void finalReport() override 
    {
        std::cout << "---------------------------------------" << std::endl;
        std::cout << "Final report" << std::endl;
        std::cout << "---------------------------------------" << std::endl;
        std::cout << "Possible values for nbIn : ";
        for(int i = 0; i < possibleNbIn.size(); ++i) {
            std::cout << i;
            if(i < possibleNbIn.size() - 1)
                std::cout << ", ";
        }
        std::cout << std::endl;
        std::cout << "Possible values for nbOfOneWaiting : ";
        for(int i = 0; i < possibleNbOfOneWaiting.size(); ++i) {
            std::cout << i;
            if(i < possibleNbOfOneWaiting.size() - 1)
                std::cout << ", ";
        }
        std::cout << std::endl;
        std::cout << "Possible values for nbOfZerosWaiting : ";
        for(int i = 0; i < possibleNbOfZerosWaiting.size(); ++i) {
            std::cout << i;
            if(i < possibleNbOfZerosWaiting.size() - 1)
                std::cout << ", ";
        }
        std::cout << std::endl;
        std::cout << std::flush;
    }
};

#endif // MODELSAS_H
