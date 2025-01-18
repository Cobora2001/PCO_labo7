#ifndef MODELSAS_H
#define MODELSAS_H

#include <iostream>

#include "pcomodel.h"
#include "pcosynchro/pcosemaphore.h"
#include "pcoconcurrencyanalyzer.h"
#include "sasAccess.h"

static SasAccess sas(3);

class ThreadUnique : public ObservableThread
{
public:
    explicit ThreadUnique(std::string id, int agentType) : ObservableThread(std::move(id)), agentType(agentType)
    {
        scenarioGraph = std::make_unique<ScenarioGraph>();
        auto scenario = scenarioGraph->createNode(this, -1);
        auto p1 = scenarioGraph->createNode(this, 0);
        auto p2 = scenarioGraph->createNode(this, 1);
        scenario->next.push_back(p1);
        p1->next.push_back(p2);
        scenarioGraph->setInitialNode(scenario);

        if(agentType > 1)
          agentType = 1;
        else if(agentType < 0)
          agentType = 0;
    }

private:
    int agentType;
    void run() override
    {
        startSection(1);
        std::cout << "Thread with agents " << agentType << " is accessing the sas" << std::endl;
        sas.access(agentType);
        startSection(2);
        std::cout << "Thread with agents " << agentType << " is leaving the sas" << std::endl;
        sas.leave(agentType);
        endScenario();
    }
};

class ThreadMultiple : public ObservableThread
{
public:
    explicit ThreadMultiple(std::string id, int agentNumber, int agentType) : ObservableThread(std::move(id)), agentNumber(agentNumber), agentType(agentType)
    {
        if(agentNumber < 1)
          agentNumber = 1;
        
        scenarioGraph = std::make_unique<ScenarioGraph>();
        auto scenario = scenarioGraph->createNode(this, -1);
        auto p1 = scenarioGraph->createNode(this, 1);
        auto p2 = scenarioGraph->createNode(this, 2);
        scenario->next.push_back(p1);
        for(int i = 0; i < agentNumber - 1; ++i) {
            p1->next.push_back(p1);
        }
        p1->next.push_back(p2);
        for(int i = 0; i < agentNumber - 1; ++i) {
            p2->next.push_back(p2);
        }
        scenarioGraph->setInitialNode(scenario);

        if(agentType > 1)
          agentType = 1;
        else if(agentType < 0)
          agentType = 0;

    }

private:
    int agentNumber;
    int agentType;

    void run() override
    {
        for(int i = 0; i < agentNumber; ++i) {
            startSection(1);
            sas.access(agentType);
        }
        for(int i = 0; i < agentNumber; ++i) {
            startSection(2);
            sas.leave(agentType);
        }
        endScenario();
    }
};

class ModelSas : public PcoModel
{
    bool checkInvariants() override 
    {
        return true;
    }
    
    
    void build() override
    {
        threads.emplace_back(std::make_unique<ThreadUnique>("1", 0));
        threads.emplace_back(std::make_unique<ThreadUnique>("2", 1));
        scenarioBuilder = std::make_unique<ScenarioBuilderBuffer>();
        scenarioBuilder->init(threads, 10);
    }

    void preRun(Scenario& /*scenario*/) override
    {
    }

    void postRun(Scenario &scenario) override 
    {
        std::cout << "---------------------------------------" << std::endl;
        std::cout << "Scenario : ";
        ScenarioPrint::printScenario(scenario);
        std::cout << "nbIn = " << sas.getNbIn() << std::endl;
        std::cout << "nbOfOneWaiting = " << sas.getNbOfOneWaiting() << std::endl;
        std::cout << "nbOfZerosWaiting = " << sas.getNbOfZerosWaiting() << std::endl;
        std::cout << std::flush;
        possibleNbIn.insert(sas.getNbIn());
        possibleNbOfOneWaiting.insert(sas.getNbOfOneWaiting());
        possibleNbOfZerosWaiting.insert(sas.getNbOfZerosWaiting());
    }

    std::set<int> possibleNbIn;
    std::set<int> possibleNbOfOneWaiting;
    std::set<int> possibleNbOfZerosWaiting;

    void finalReport() override 
    {
        std::cout << "---------------------------------------" << std::endl;
        std::cout << "Final report" << std::endl;
        std::cout << "Possible values for nbIn : ";
        for (const int &value : possibleNbIn)
            std::cout << value << ", ";
        std::cout << std::endl;
        std::cout << "Possible values for nbOfOneWaiting : ";
        for (const int &value : possibleNbOfOneWaiting)
            std::cout << value << ", ";
        std::cout << std::endl;
        std::cout << "Possible values for nbOfZerosWaiting : ";
        for (const int &value : possibleNbOfZerosWaiting)
            std::cout << value << ", ";
        std::cout << std::endl;
        std::cout << std::flush;
    }
};

#endif // MODELTEMPLATE_H
