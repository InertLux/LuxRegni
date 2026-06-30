#pragma once
#include <string>
#include <vector>
#include <map>
#include <memory>

extern "C" {
    #include "wren.h"
}

// Forward declarations
struct WrenVM;

struct Command {
    std::string type;
    std::map<std::string, std::string> params;
};
class WrenEngine {
public:
    WrenEngine();
    ~WrenEngine();
    
    void loadScript(const std::string& name, const std::string& source);
    std::vector<Command> execute(const std::string& scriptName, const std::string& stateSnapshot);
    void queueCommand(const std::string& type, const std::map<std::string, std::string>& params);
    
    // NEW: Get captured print output
    std::string getLastOutput() const { return lastOutput; }
    void clearOutput() { lastOutput.clear(); }
    
    static WrenEngine* instancePtr;

private:
    WrenVM* vm;
    std::map<std::string, std::string> scripts;
    std::vector<Command> commandQueue;
    std::string lastOutput;  // Capture print output
    
    static void commandCallback(WrenVM* vm);
    static void printCallback(WrenVM* vm, const char* text);  // NEW
    std::string wrenToString(void* vmPtr, int slot);
};

