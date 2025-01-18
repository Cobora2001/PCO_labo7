#ifndef MODELSAS_H
#define MODELSAS_H

#include <iostream>

#include "pcomodel.h"
#include "pcosynchro/pcosemaphore.h"
#include "pcoconcurrencyanalyzer.h"
#include "sasAccess.h"

static SasAccess sas(3);

class Thread1 : public ObservableThread
{
public:
    explicit Thread1(std::string id = "") : ObservableThread(std::move(id))
    {
        scenarioGraph = std::make_unique<ScenarioGraph>();
        auto scenario = scenarioGraph->createNode(this, -1);
        auto p1 = scenarioGraph->createNode(this, 0);
        auto p2 = scenarioGraph->createNode(this, 1);
        scenario->next.push_back(p1);
        p1->next.push_back(p2);
        scenarioGraph->setInitialNode(scenario);
    }

private:
    void run() override
    {
        startSection(1);
        sas.access(1);
        startSection(2);
        sas.leave(1);
        endScenario();
    }
};

class Thread2 : public ObservableThread
{
public:
    explicit Thread2(std::string id = "") : ObservableThread(std::move(id))
    {
        scenarioGraph = std::make_unique<ScenarioGraph>();
        auto scenario = scenarioGraph->createNode(this, -1);
        auto p1 = scenarioGraph->createNode(this, 0);
        auto p2 = scenarioGraph->createNode(this, 1);
        scenario->next.push_back(p1);
        p1->next.push_back(p2);
        scenarioGraph->setInitialNode(scenario);
    }

private:
    void run() override
    {
        startSection(1);
        sas.access(0);
        startSection(2);
        sas.leave(0);
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
        threads.emplace_back(std::make_unique<Thread1>("1"));
        threads.emplace_back(std::make_unique<Thread2>("2"));
        scenarioBuilder = std::make_unique<ScenarioBuilderBuffer>();
        scenarioBuilder->init(threads, 2);
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
