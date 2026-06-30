#include <iostream>
#include <stdexcept>
#include "WrenEngine.h"
// ============================================================================
// Wren C API - Must wrap in extern "C"
// ============================================================================
extern "C" {
    #include "wren.h"
}

// ============================================================================
// Wren Callbacks (file scope)
// ============================================================================

static void wrenWriteFn(WrenVM* vm, const char* text) {
    std::cout << "[Wren] " << text;
}

static void wrenErrorFn(WrenVM* vm, WrenErrorType errorType,
                       const char* module, int line,
                       const char* message) {
    std::cerr << "[Wren Error] ";
    switch (errorType) {
        case WREN_ERROR_COMPILE:
            std::cerr << "Compile Error at " << module << ":" << line << " - " << message;
            break;
        case WREN_ERROR_STACK_TRACE:
            std::cerr << "Stack Trace: " << message;
            break;
        case WREN_ERROR_RUNTIME:
            std::cerr << "Runtime Error - " << message;
            break;
    }
    std::cerr << std::endl;
}

// Forward declaration for use in binding function
static void wrenEngineCommandCallback(WrenVM* vm);

static WrenForeignMethodFn wrenBindForeignMethodFn(
    WrenVM* vm, const char* module, const char* className,
    bool isStatic, const char* signature) {
    
    if (std::string(module) == "main" &&
        std::string(className) == "Dom" &&
        std::string(signature) == "command(_,_,_)") {
        return wrenEngineCommandCallback;
    }
    
    return nullptr;
}

static WrenForeignClassMethods wrenBindForeignClassFn(
    WrenVM* vm, const char* module, const char* className) {
    
    WrenForeignClassMethods methods = {};
    return methods;
}

// Static member initialization
WrenEngine* WrenEngine::instancePtr = nullptr;

// ============================================================================
// WrenEngine Implementation
// ============================================================================

WrenEngine::WrenEngine() {
    WrenConfiguration config;
    wrenInitConfiguration(&config);
    
    // Set the write function to capture prints
    config.writeFn = [](WrenVM* vm, const char* text) {
        if (WrenEngine::instancePtr) {
            WrenEngine::instancePtr->lastOutput += text;
        }
    };
    
    vm = wrenNewVM(&config);
    WrenEngine::instancePtr = this;
}

WrenEngine::~WrenEngine() {
    if (vm) {
        wrenFreeVM((WrenVM*)vm);
        vm = nullptr;
    }
    instancePtr = nullptr;
}

void WrenEngine::loadScript(const std::string& name, const std::string& source) {
    scripts[name] = source;
    std::cout << "[WrenEngine] Loaded script: " << name << std::endl;
}

std::vector<Command> WrenEngine::execute(const std::string& scriptName, 
                                         const std::string& stateSnapshot) {
    commandQueue.clear();
    
    auto it = scripts.find(scriptName);
    if (it == scripts.end()) {
        throw std::runtime_error("Script not found: " + scriptName);
    }
    
    std::string wrappedSource = 
        "var __state = \"" + stateSnapshot + "\"\n" +
        it->second;
    
    WrenInterpretResult result = wrenInterpret((WrenVM*)vm, "main", wrappedSource.c_str());
    
    if (result == WREN_RESULT_COMPILE_ERROR || result == WREN_RESULT_RUNTIME_ERROR) {
        throw std::runtime_error("Wren script failed to execute");
    }
    
    std::cout << "[WrenEngine] Executed script: " << scriptName 
              << " (queued " << commandQueue.size() << " commands)" << std::endl;
    
    return commandQueue;
}

void WrenEngine::queueCommand(const std::string& type, 
                              const std::map<std::string, std::string>& params) {
    Command cmd;
    cmd.type = type;
    cmd.params = params;
    commandQueue.push_back(cmd);
    
    std::cout << "[WrenEngine] Queued command: " << type << std::endl;
}

// Static callback - free function, not a class member
static void wrenEngineCommandCallback(WrenVM* vm) {
    if (!WrenEngine::instancePtr) {
        std::cerr << "[WrenEngine] instancePtr is null in callback" << std::endl;
        return;
    }
    
    wrenEnsureSlots(vm, 4);
    
    const char* type = wrenGetSlotString(vm, 1);
    const char* key = wrenGetSlotString(vm, 2);
    const char* value = wrenGetSlotString(vm, 3);
    
    if (!type || !key || !value) {
        std::cerr << "[WrenEngine] Invalid arguments to Dom.command()" << std::endl;
        return;
    }
    
    std::map<std::string, std::string> params;
    params[key] = value;
    
    WrenEngine::instancePtr->queueCommand(type, params);
}

std::string WrenEngine::wrenToString(void* vmPtr, int slot) {
    WrenVM* vm = (WrenVM*)vmPtr;
    const char* str = wrenGetSlotString(vm, slot);
    return str ? std::string(str) : "";
}
