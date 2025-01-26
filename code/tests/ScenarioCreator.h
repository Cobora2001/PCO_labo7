// ScenarioCreator.h
#ifndef SCENARIOCREATOR_H
#define SCENARIOCREATOR_H

#include <vector>
#include "../src/observablethread.h"
#include "../src/scenario.h"

class ScenarioCreator
{
private:
    std::vector<ObservableThread*> threads;
    std::vector<std::vector<int>> linkedSections;

    // Recursive backtracking helper function
    void backtrack(
        Scenario& currentScenario, 
        const std::vector<std::vector<int>>& linkedSections, 
        std::vector<int>& threadSectionIndices, 
        std::vector<Scenario>& scenarios
    ) const;

public:

    /**
     * @brief ScenarioCreator constructor
     * @param threads The threads to create scenarios for
     * @param linkedSections The sections that are linked between threads
     */
    ScenarioCreator(std::vector<ObservableThread*> threads, std::vector<std::vector<int>> linkedSections)
        : threads(threads), linkedSections(linkedSections) {}

    std::vector<Scenario> createScenarios();
};

#endif // SCENARIOCREATOR_H
