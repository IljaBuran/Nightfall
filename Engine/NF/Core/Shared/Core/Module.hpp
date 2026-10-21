#pragma once

#include "Utility/Helpers.hpp"

#define NF_MODULE(x)                \
    friend class ::NF::Application;  \
    NF_NOCOPY(x);                   \
    NF_NOMOVE(x)

namespace NF { class Application; }