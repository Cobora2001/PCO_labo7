#ifndef MODELSAS_H
#define MODELSAS_H

#include <iostream>

#include "pcomodel.h"
#include "pcosynchro/pcosemaphore.h"
#include "pcoconcurrencyanalyzer.h"
#include "sasAccess.h"

static int number = 0;

int getNumber()
{
    return number;
}

class ThreadA : public ObservableThread
{
public:
    explicit ThreadA(std::string id = "") :
        ObservableThread(std::move(id))
    {
        scenarioGraph = std::make_unique<ScenarioGraph>();
        auto scenario = scenarioGraph->createNode(this, -1);
        auto p1 = scenarioGraph->createNode(this, 1);
        auto p2 = scenarioGraph->createNode(this, 2);
        auto p3 = scenarioGraph->createNode(this, 3);
        scenario->next.push_back(p1);
        p1->next.push_back(p2);
        p2->next.push_back(p3);
        scenarioGraph->setInitialNode(scenario);
    }

private:
    void run() override
    {
        startSection(1);
        number = 0;
        startSection(2);
        int reg = number;
        startSection(3);
        number = reg + 7;
        endScenario();
    }
};

static SasAccess sas(3);

class ThreadUnique : public ObservableThread
{
public:
    ThreadUnique(std::string id, int agentType) : ObservableThread(std::move(id))
    {
        scenarioGraph = std::make_unique<ScenarioGraph>();
        auto scenario = scenarioGraph->createNode(this, -1);
        auto p1 = scenarioGraph->createNode(this, 0);
        auto p2 = scenarioGraph->createNode(this, 1);
        scenario->next.push_back(p1);
        p1->next.push_back(p2);
        scenarioGraph->setInitialNode(scenario);

        if(agentType > 1)
          agent = 1;
        else if(agentType < 0)
          agent = 0;
    }

private:
    int agent;
    void run() override
    {
        startSection(1);
        std::cout << "Thread with agents " << agent << " is accessing the sas" << std::endl;
        // sas.access(agent);
        startSection(2);
        std::cout << "Thread with agents " << agent << " is leaving the sas" << std::endl;
        // sas.leave(agent);
        endScenario();
    }
};

class ThreadMultiple : public ObservableThread
{
public:
    explicit ThreadMultiple(std::string id, int agentNumber, int agentType) : ObservableThread(std::move(id)), agentNb(agentNumber)
    {
        if(agentNumber < 1)
          agentNb = 1;
        
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
          agent = 1;
        else if(agentType < 0)
          agent = 0;

    }

private:
    int agentNb;
    int agent;

    void run() override
    {
        for(int i = 0; i < agentNb; ++i) {
            startSection(1);
            sas.access(agent);
        }
        for(int i = 0; i < agentNb; ++i) {
            startSection(2);
            sas.leave(agent);
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
        // threads.emplace_back(std::make_unique<ThreadUnique>("1", 0));
        // threads.emplace_back(std::make_unique<ThreadUnique>("2", 1));
        threads.emplace_back(std::make_unique<ThreadA>("1"));
        threads.emplace_back(std::make_unique<ThreadA>("2"));
        scenarioBuilder = std::make_unique<ScenarioBuilderBuffer>();
        scenarioBuilder->init(threads, 100);
    }

    void preRun(Scenario& /*scenario*/) override
    {
    }

    void postRun(Scenario &scenario) override 
    {
        std::cout << "---------------------------------------" << std::endl;
        std::cout << "Scenario : ";
        ScenarioPrint::printScenario(scenario);
        // std::cout << "nbIn = " << sas.getNbIn() << std::endl;
        // std::cout << "nbOfOneWaiting = " << sas.getNbOfOneWaiting() << std::endl;
        // std::cout << "nbOfZerosWaiting = " << sas.getNbOfZerosWaiting() << std::endl;
        // std::cout << std::flush;
        // possibleNbIn.insert(sas.getNbIn());
        // possibleNbOfOneWaiting.insert(sas.getNbOfOneWaiting());
        // possibleNbOfZerosWaiting.insert(sas.getNbOfZerosWaiting());
    }

    std::set<int> possibleNbIn;
    std::set<int> possibleNbOfOneWaiting;
    std::set<int> possibleNbOfZerosWaiting;

    void finalReport() override 
    {
        std::cout << "---------------------------------------" << std::endl;
        std::cout << "Final report" << std::endl;
        // std::cout << "Possible values for nbIn : ";
        // for (const int &value : possibleNbIn)
        //     std::cout << value << ", ";
        // std::cout << std::endl;
        // std::cout << "Possible values for nbOfOneWaiting : ";
        // for (const int &value : possibleNbOfOneWaiting)
        //     std::cout << value << ", ";
        // std::cout << std::endl;
        // std::cout << "Possible values for nbOfZerosWaiting : ";
        // for (const int &value : possibleNbOfZerosWaiting)
        //     std::cout << value << ", ";
        // std::cout << std::endl;
        // std::cout << std::flush;
    }
};

#endif // MODELTEMPLATE_H
