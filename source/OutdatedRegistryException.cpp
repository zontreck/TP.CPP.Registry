#include "OutdatedRegistryException.h"


const char* OutdatedRegistryException::what() const noexcept
{

    return errorMessage.c_str();
}