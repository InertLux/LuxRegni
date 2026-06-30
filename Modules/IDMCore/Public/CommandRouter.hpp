
// DomainRouter.h
#pragma once
#include "CommandDomain.h"
#include <unordered_map>
#include <memory>
#include <shared_mutex>

class DomainRouter {
private:
    mutable std::shared_mutex lock;
    std::unordered_map<std::string, std::shared_ptr<CommandDomain>> domains;

public:
    inline void registerDomain(const std::string& name) {
        std::unique_lock lk(lock);
        if (domains.count(name)) {
            throw std::runtime_error("Domain already exists: " + name);
        }
        domains[name] = std::make_shared<CommandDomain>(name);
    }

    inline std::shared_ptr<CommandDomain> getDomain(const std::string& name) const {
        std::shared_lock lk(lock);
        auto it = domains.find(name);
        if (it == domains.end()) {
            throw std::runtime_error("Domain not found: " + name);
        }
        return it->second;
    }

    inline CommandResult execute(const std::string& domain,
                         const std::vector<std::string>& args,
                         std::map<std::string, std::string>& state) {
        return getDomain(domain)->execute(args, state);
    }
};