#ifndef CONTAINER_HPP
#define CONTAINER_HPP

#include "global.hpp"

/*
    Wrapper for vector of pointers.
    It's purpouse is to avoid calling many
    constructors and destructors upon pushing
    new element to vector in case of storing
    raw objects in vector.
*/

template <class T> class container
{
    private:
        std::vector <T*> m_vector;

    public:
        inline size_t size() {return m_vector.size();}

        inline void clear()
        {
            for(size_t i=0; i<m_vector.size(); ++i) {
                delete m_vector[i];
            }
            m_vector.clear();
        }

        inline void push_back(const T &element)
        {
            m_vector.push_back(new T(element));
        }

        inline void resize(size_t newSize)
        {
            if(newSize < m_vector.size()) {
                for(int i=(int)m_vector.size()-1; i>=(int)newSize; --i) {
                    delete m_vector[i];
                }
                m_vector.resize(newSize);
            }
            else {
                for(size_t i=m_vector.size(); i<newSize; ++i) {
                    m_vector.push_back(new T);
                }
            }
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

        ~container()
        {
            for(size_t i=0; i<m_vector.size(); ++i) {
                delete m_vector[i];
            }
        }
};

/*
    Alternative for std::vector,
    which doesn't call billion of constructors
    and destructors upon pushing new element.

    Constructors are called only once per object
    (when adding element).
    Destructors are called only once per object
    (when removing element or whole container).
*/

/*
template <class T> class container
{
    private:
        static const int INITIAL_ELEMENTS_QUANTITY = 8;

        T *m_data;
        size_t m_allocated;
        size_t m_size;

        void add_element(T *element)
        {
            if(m_size >= m_allocated) {
                T *newData = (T*)malloc(sizeof(T)*m_allocated*2);
                _assert(newData, "Could not allocate memory in container add_element.");
                memcpy(newData, m_data, sizeof(T)*m_allocated);
                free(m_data);
                m_data = newData;
                m_allocated *= 2;
            }
            memcpy(&m_data[m_size], element, sizeof(*element));
            ++m_size;
        }

    public:
        inline size_t size()
        {
            return m_size;
        }

        void clear()
        {
            for(size_t i=0; i<m_size; ++i) {
                m_data[i].~T();
            }
            m_size = 0;
        }

        void push_back(const T &element)
        {
            T *copy = new T;
            _assert(copy, "Could not allocate memory in container push_back.");
            *copy = element;
            add_element(copy);
        }

        void resize(size_t newSize)
        {
            if(newSize > m_size) {
                for(size_t i=m_size; i<newSize; ++i) {
                    T *element = new T;
                    _assert(element, "Could not allocate memory in container resize.");
                    add_element(element);
                }
            }
            else {
                for(size_t i=newSize; i<m_size; ++i) {
                    m_data[i].~T();
                }
                m_size = newSize;
            }
        }

        inline T &back()
        {
            #ifdef CONTAINER_CHECK_BOUNDS
            _assert(m_size, "Container is empty in container back.");
            #endif
            return m_data[m_size-1];
        }

        inline T &operator [] (int index)
        {
            #ifdef CONTAINER_CHECK_BOUNDS
            _assert(index >= 0 && index < size, "Index out of bounds in container [] operator.");
            #endif
            return m_data[index];
        }

        container()
            :   m_data((T*)malloc(sizeof(T)*INITIAL_ELEMENTS_QUANTITY)),
                m_allocated(INITIAL_ELEMENTS_QUANTITY),
                m_size(0) {
                    _assert(m_data, "Could not allocate memory in container constructor.");
        }
        ~container()
        {
            for(size_t i=0; i<m_size; ++i) {
                m_data[i].~T();
            }
            free(m_data);
        }
};
*/
#endif
