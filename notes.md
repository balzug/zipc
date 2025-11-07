## Introduction
The goal of this assignment is to present an example of inter-process communication in a multi-process, embedded environment.

In this hypothetical embedded system the processes can function mostly independently, but will need information from each other from time to time. If a process crashes it must be able to reacquire the information it needs from the other processes.

## Definition of Task
Let's assume three processes: A, B and C. Each produces information the other two might be interested in. There is no fixed interval when new information comes in. The interval depends entirely on external factors. For the scope of this assignment, please feel free to update at random intervals.

Please provide a C++ project easily buildable on Linux (with instructions included), which demonstrates the following:

A communication message format the processes involved understand.

How the processes exchange information and why you think this implementation is a good fit for the problem.

How does it ensure the processes have the latest information? How do they sync again if one or even multiple processes crash?

## Notes
It would be appreciated if you could provide a high level shell or python script to run the scenario. Text printed by the processes can then show how they are interacting with and updating each other.

The problem description is relatively abstract and does not contain too many exact details. Please take the liberty and implement any details left out as you see fit or get back to us if you have any questions.

Please feel free to use boost libraries or other external dependencies if you deem them suitable for solving the problem presented.