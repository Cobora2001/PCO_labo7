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
    

    /**
     * @brief The run function of the thread that will be called by the model checker
     *        This function will call the access and leave functions of the SAS
     */
    void run() override
    {
        startSect(0); // This section is so that we can check who takes the mutex, and define valid scenarios
        endSect();
        sas->access(agent, this);
        startSect(2); // This section is so that we can check who takes the mutex, and define valid scenarios
        endSect();
        sas->leave(agent, this);
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
    int currentTest = 3; // MODIFY THIS VALUE TO TEST THE DIFFERENT SCENARIOS
    /**
     * @brief Checks the invariants of the model
     * @return True if the invariants are respected, false otherwise
     */
    bool checkInvariants() override 
    {
        return true;
    }
    
    /**
     * @brief Builds the threads and scenariobuilder
     */
    void build() override
    {
    // Lets suppose that we want to test the SAS with the following scenarios:
    // 1. Size = 2, 2 threads
    // 2. Size = 2, 3 threads
    // 3. Size = 3, 4 threads

    auto builder = std::make_unique<PredefinedScenarioBuilderIter>();
    std::vector<std::vector<int>> linkedSections = {
        {0, 1}, 
        {2, 3}
    };
    std::vector<ObservableThread*> threadPtrs;

    // TEST 1 :
    if (currentTest == 1) {
        threads.emplace_back(std::make_unique<ThreadZero>("0"));
        threads.emplace_back(std::make_unique<ThreadOne>("1"));
        for (const auto& thread : threads) {
            threadPtrs.push_back(thread.get());
        }

    }

    // TEST 2 :
    if (currentTest == 2) {
    // Creation of 3 threads (2 of type 0 and 1 of type 1)
    for (int i = 0; i < 2; ++i) {
        threads.emplace_back(std::make_unique<ThreadZero>(std::to_string(i)));
    }

    threads.emplace_back(std::make_unique<ThreadOne>("2"));

    for (const auto& thread : threads) {
        threadPtrs.push_back(thread.get());
    }

    }

    // TEST 3 :
    if (currentTest == 3) {

    // Creation of 4 threads (2 of each type)
    for (int i = 0; i < 2; ++i) {
        threads.emplace_back(std::make_unique<ThreadZero>(std::to_string(i)));
    }

    for (int i = 2; i < 4; ++i) {
        threads.emplace_back(std::make_unique<ThreadOne>(std::to_string(i)));
    }

    // Add the threads to the vector of thread pointers
    for (const auto& thread : threads) {
        threadPtrs.push_back(thread.get());
    }
 
    }

    ScenarioCreator scenarioCreator(threadPtrs, linkedSections);
    std::vector<Scenario> scenarios = scenarioCreator.createScenarios();
    builder->setScenarios(scenarios);
    scenarioBuilder = std::move(builder);

    }

    /**
     * @brief Function called by the model checker before running a scenario.
     *        This function initializes the SAS.
     * @param scenario The scenario that will be run.
     */
    void preRun(Scenario& /*scenario*/) override
    {
        delete sas; // Free the previous SAS
        if (currentTest == 1 || currentTest == 2) {
            sas = new SasAccess(2);
        } else if (currentTest == 3) {
            sas = new SasAccess(3); 
        }
        std::cout << std::endl; // Just for the formatting of the output
    }

    /**
     * @brief Function called by the model checker after running a scenario.
     *        This function shows the information about our scenario.
     * @param scenario The scenario that has been run.
     */
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
