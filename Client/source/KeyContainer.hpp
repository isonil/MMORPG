#ifndef KEY_CONTAINER_HPP
#define KEY_CONTAINER_HPP

#include "global.hpp"

template <class T> class KeyContainer
{
    private:
        std::map <int, T*> m_map;

    public:
        inline size_t size() {return m_map.size();}

        inline void clear()
        {
            for(std::map <int, T*>::iterator it=m_map.begin(); it!=m_map.end(); ++it) {
                delete *it;
            }
            m_map.clear();
        }

        inline void insert(const T &element, int key)
        {
            if(m_map.find(key) == m_map.end()) {
                m_map[key] = new T(element);
            }
            else *m_map[key] = element;
        }

        inline void erase(int key)
        {
            std::set <int, T*>::iterator it = m_map.find(key);
            if(it != m_map.end()) {
                delete *it;
                m_map.erase(it)
            }
        }

        inline bool exists(int key)
        {
            return m_map.find(key) != m_map.end();
        }

        inline T &operator [] (int key)
        {
            if(m_map.find(key) == m_map.end()) {
                m_map[key] = new T;
            }
            return *m_map[key];
        }

        ~KeyContainer()
        {
            for(std::map <int, T*>::iterator it=m_map.begin(); it!=m_map.end(); ++it) {
                delete *it;
            }
        }
};

#endif
