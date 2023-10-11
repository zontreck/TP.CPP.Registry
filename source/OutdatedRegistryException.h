#ifndef OUTDATED_REGISTRY_EXCEPTION_H
#define OUTDATED_REGISTRY_EXCEPTION_H

#include <exception>
#include <string>

class OutdatedRegistryException : public std::exception {
public:
    OutdatedRegistryException(const std::string& message) : errorMessage(message) {}

    const char *what() const noexcept override;

private:
    std::string errorMessage;
};


#endif