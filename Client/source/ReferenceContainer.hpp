#ifndef REFERENCE_CONTAINER_HPP
#define REFERENCE_CONTAINER_HPP

#include "global.hpp"

/*
    Wrapper for vector of pointers.
    It's purpouse is to avoid calling many
    constructors and destructors upon pushing
    new element to vector in case of storing
    raw objects in vector.
*/

template <class T> class ReferenceContainer
{
    private:
        std::vector <T*> m_vector;

    public:
        inline size_t size() {return m_vector.size();}

        inline void clear()
        {
            m_vector.clear();
        }

        inline void push_back(T &element)
        {
            m_vector.push_back(&element);
        }

        inline T &back()
        {
            #ifdef CONTAINER_CHECK_BOUNDS
            _assert(m_size, "Container is empty in container back.");
            #endif
            return *m_vector.back();
        }

        inline T &operator [] (int index)
        {
            #ifdef CONTAINER_CHECK_BOUNDS
            _assert(index >= 0 && index < m_vector.size(), "Index out of bounds in container [] operator.");
            #endif
            return *m_vector[index];
        }
};

#endif
