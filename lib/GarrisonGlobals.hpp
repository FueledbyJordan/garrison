#pragma once

#include <string>

namespace Garrison
{

	const std::string VERSION = "0.0.1";

    enum ERROR_TYPES
    {
        NO_ERR = 0,
        CLI_ARG_ERR,
        CONFIG_MISSING_ERR,
        CONFIG_INVALID_ERR,
        INPUT_MISSING_ERR,
        OUTPUT_PERMISSION_ERR,
        OUTPUT_FILE_EXISTS
    };

//Possibly need to add an ignore operation.
    enum OPERATION_TYPE
    {
        NO_OP = 0,
        LINK,
        COPY
    };

}
