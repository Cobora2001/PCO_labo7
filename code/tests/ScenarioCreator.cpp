// ScenarioCreator.cpp
#include "ScenarioCreator.h"

// Recursive backtracking function to generate all interleaved scenarios
void ScenarioCreator::backtrack(
    Scenario& currentScenario,
    const std::vector<std::vector<int>>& linkedSections,
    std::vector<int>& threadSectionIndices, // Current section index for each thread
    std::vector<Scenario>& scenarios
) const
{
    // Check if all threads have completed their sections
    bool allCompleted = true;
    for (size_t i = 0; i < threads.size(); ++i) {
        if (threadSectionIndices[i] < linkedSections.size()) {
            allCompleted = false;
            break;
        }
    }

    if (allCompleted) {
        scenarios.push_back(currentScenario);
        return;
    }

    // Iterate over each thread to choose who makes the next stride
    for (size_t i = 0; i < threads.size(); ++i) {
        if (threadSectionIndices[i] < linkedSections.size()) {
            // Get the next section for thread i
            const std::vector<int>& currentSection = linkedSections[threadSectionIndices[i]];

            // Add all points in the current section as ScenarioPoints
            for (int point : currentSection) {
                ScenarioPoint sp;
                sp.thread = threads[i];
                sp.number = point;
                currentScenario.push_back(sp);
            }

            // Update the thread's section index
            threadSectionIndices[i]++;

            // Recurse
            backtrack(currentScenario, linkedSections, threadSectionIndices, scenarios);

            // Backtrack: remove the added points and reset the thread's section index
            for (size_t j = 0; j < currentSection.size(); ++j) {
                currentScenario.pop_back();
            }
            threadSectionIndices[i]--;
        }
    }
}

// Implement the createScenarios method
std::vector<Scenario> ScenarioCreator::createScenarios()
{
    std::vector<Scenario> scenarios;

    // Initialize threadSectionIndices
    std::vector<int> threadSectionIndices(threads.size(), 0);

    // Initialize current scenario
    Scenario currentScenario;

    // Start backtracking
    backtrack(currentScenario, linkedSections, threadSectionIndices, scenarios);

    return scenarios;
}
