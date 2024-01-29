#include "InputHandler.hpp"

InputHandler::InputHandler() {}

InputHandler::InputHandler(const std::string& filename) {
    readInput(filename);
}

Process* InputHandler::readOneLine(std::string line, int id) {
    std::stringstream ss(line);
    int arrTime;
    ss >> arrTime;
    Process* result = new Process();
    result->ID = id;
    result->arrivalTime = arrTime;

    int temp;
    int index = 0;
    while (ss >> temp) {
        if (index % 2 == 0) {
            result->CPUBurst.push_back(temp);
        } else {
            result->resourceBurst.push_back(temp);
        }
        
        ++index;
    }
    return result;
}

void InputHandler::readInput(const std::string& filename) {
    std::ifstream is(filename);
    if (!is.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return;
    }
    
    int numProcess;
    
    is >> algorithmID;

    if (algorithmID == 2) {
        is >> timeQuantum;
    }
    
    is >> numProcess;

    is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    int id = 1;
    while (numProcess) {
        std::string line;
        if (!std::getline(is, line)) {
            std::cerr << "Error: Invalid format in input file." << std::endl;
            return;
        }
        Process* process = readOneLine(line, id++);
        processes.push_back(process);
        --numProcess;
    }

    is.close();
}