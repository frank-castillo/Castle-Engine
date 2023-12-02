#pragma once

#include "BlockAllocator.h"

namespace CASTLEEngine::Core
{
    template<class DataType>
    class TypedAllocator : private BlockAllocator
    {
    public:
        TypedAllocator(const char* name, size_t capacity)
            : BlockAllocator(name, sizeof(DataType), capacity)
        {

        }

        // This syntax allows us to have unlimited Args
        template<class... Args>
        DataType* New(Args&&... args) //Parameters we pass into the constructor
        {
            // Give a chunk for the data I want to allocate
            auto* instance = static_cast<DataType*>(Allocate());
            //Placement new, calls constructor on a designated location based on the DataType and number of arguments
            new(instance) DataType(std::forward<Args>(args)...);

            return instance;
        }

        void Delete(DataType* ptr)
        {
            if (ptr == nullptr)
            {
                return;
            }

            ptr->~DataType();
            Free(ptr);
        }
    };
}