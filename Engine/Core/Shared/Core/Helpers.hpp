#pragma once

#define NF_NOCOPY(Type)                    \
    Type (const Type&)           = delete; \
    Type& operator=(const Type&) = delete

#define NF_NOMOVE(Type)               \
    Type(Type&&)            = delete; \
    Type& operator=(Type&&) = delete