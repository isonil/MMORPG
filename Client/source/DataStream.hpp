#ifndef DATA_STREAM_HPP
#define DATA_STREAM_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

class DataStreamFileClass
{
    public:
        std::string name;
        std::string data;

        DataStreamFileClass()
            :   name("undefined") {
        }
        DataStreamFileClass(const std::string &newName)
            :   name(newName) {
        }
};

class DataStreamDirectoryClass
{
    public:
        std::string name;
        std::vector <DataStreamDirectoryClass> dataStreamDirectory;
        std::vector <DataStreamFileClass> dataStreamFile;

        DataStreamDirectoryClass()
            :   name("undefined") {
        }
        DataStreamDirectoryClass(const std::string &newName)
            :   name(newName) {
        }
};

class DataStreamClass
{
    private:
        DataStreamFileClass *currentFile;
        DataStreamDirectoryClass rootDirectory;
        size_t currentFileReadPos;

        void addFile(const std::string &virtualPath, char *buff, size_t buffSize);

    public:
        bool openDataFile(const std::string &path);

        bool openVirtualFile(const std::string &virtualPath);
        bool loadText(const std::string &virtualPath, std::string &data, bool checkIfExists = false);
        bool loadTexture(const std::string &virtualPath, sf::Texture &tex, bool checkIfExists = false);

        sf::Int64 read(void *data, sf::Int64 size);
        sf::Int64 seek(sf::Int64 position);
        sf::Int64 tell();
        sf::Int64 getSize();

        DataStreamClass(const std::string &path)
            :   currentFile(NULL),
                currentFileReadPos(0) {
            openDataFile(path);
        }
        DataStreamClass()
            :   currentFile(NULL),
                currentFileReadPos(0) {
        }
};

#endif
