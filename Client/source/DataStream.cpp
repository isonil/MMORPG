#include "DataStream.hpp"
#include "global.hpp"

void DataStreamClass::addFile(const std::string &virtualPath, char *buff, size_t buffSize)
{
    std::vector <std::string> pathPart(1);
    for(size_t i=0; i<virtualPath.size(); ++i) {
        if(virtualPath[i] == '/' || virtualPath[i] == '\\') {
            pathPart.resize(pathPart.size()+1);
        }
        else pathPart.back() += virtualPath[i];
    }

    DataStreamDirectoryClass *currentDirectory;
    currentDirectory = &rootDirectory;

    for(size_t i=0; i<pathPart.size(); ++i) {
        if(i != pathPart.size()-1) {
            bool found = false;
            for(size_t j=0; j<currentDirectory->dataStreamDirectory.size(); ++j) {
                if(currentDirectory->dataStreamDirectory[j].name == pathPart[i]) {
                    currentDirectory = &currentDirectory->dataStreamDirectory[j];
                    found = true;
                    break;
                }
            }
            if(!found) {
                currentDirectory->dataStreamDirectory.push_back(DataStreamDirectoryClass(pathPart[i]));
                currentDirectory = &currentDirectory->dataStreamDirectory.back();
            }
        }
        else {
            currentDirectory->dataStreamFile.push_back(DataStreamFileClass(pathPart[i]));
            for(size_t j=0; j<buffSize; ++j) {
                currentDirectory->dataStreamFile.back().data += buff[j];
            }
        }
    }
}

bool DataStreamClass::openDataFile(const std::string &path)
{
    currentFile = NULL;
    rootDirectory = DataStreamDirectoryClass();
    currentFileReadPos = 0;

    std::ifstream in(path.c_str(), std::ios::binary);
    if(!in) {
        error("Could not load DataStream data file '%s'.", path.c_str());
    }

    static const std::string keys[5] = {"fL# 43    $  b Pl3 4@$&@ 6 : ,,> \"l,./,ll   i n bB dv l []e w4'lt [ GK   YG]dE:;KS",
                                        "g{ [p?<>,;",
                                        "78E%Yi   5   45  i     j ** #$%@   ]';.<",
                                        ",.. 5$&  *&^( )_*() *( &*              tyh fg         n.    |./",
                                        ">'<: \" 73 3 h bb      z p   , M  ! # =     - ++"};

    in >> std::noskipws;
    std::string data((std::istreambuf_iterator <char> (in)), std::istreambuf_iterator <char> ());
    in.close();
    for(size_t i=0; i<data.size(); ++i) {
        data[i] ^= keys[0][i%keys[0].size()];
    }
    std::istringstream in_ss(data);

    int checkNum = 0;
    int version = 0;
    int fileQuantity = 0;
    in_ss >> checkNum >> version >> fileQuantity;
    version ^= 934713;
    fileQuantity ^= 345234889;
    if(checkNum != 1961363) error("Corrupted DataStream data file (#1).");
    if(version < 1) error("Unsupported DataStream data file version.");
    if(fileQuantity < 0) error("Corrupted DataStream data file (#2).");

    for(int i=0; i<fileQuantity; ++i) {
        in_ss >> std::skipws;
        std::string filePath;
        int fileSize = 0;
        in_ss >> filePath >> fileSize;
        fileSize ^= 785322797;
        if(fileSize < 0) error("Corrupted DataStream data file (#3).");
        std::string temp;
        std::getline(in_ss, temp);

        char *data = new char[fileSize];
        in_ss >> std::noskipws;
        in_ss.read(data, fileSize);
        if(in.fail()) {
            error("File '%s' is corrupted in '%s' - reached end of file.", filePath.c_str(), path.c_str());
        }
        for(size_t j=0; j<fileSize; ++j) {
            data[j] ^= keys[1+i%4][j%keys[1+i%4].size()];
        }
        addFile(filePath, data, fileSize);
        delete []data;
    }

    return true;
}

bool DataStreamClass::openVirtualFile(const std::string &virtualPath)
{
    std::vector <std::string> pathPart(1);
    for(size_t i=0; i<virtualPath.size(); ++i) {
        if(virtualPath[i] == '/' || virtualPath[i] == '\\') {
            pathPart.resize(pathPart.size()+1);
        }
        else pathPart.back() += virtualPath[i];
    }

    DataStreamDirectoryClass *currentDirectory;
    currentDirectory = &rootDirectory;
    currentFile = NULL;
    currentFileReadPos = 0;
    for(size_t i=0; i<pathPart.size(); ++i) {
        if(i != pathPart.size()-1) {
            bool found = false;
            for(size_t j=0; j<currentDirectory->dataStreamDirectory.size(); ++j) {
                if(currentDirectory->dataStreamDirectory[j].name == pathPart[i]) {
                    currentDirectory = &currentDirectory->dataStreamDirectory[j];
                    found = true;
                    break;
                }
            }
            if(!found) return false;
        }
        else {
            for(size_t j=0; j<currentDirectory->dataStreamFile.size(); ++j) {
                if(currentDirectory->dataStreamFile[j].name == pathPart[i]) {
                    currentFile = &currentDirectory->dataStreamFile[j];
                    break;
                }
            }
        }
    }

    if(currentFile == NULL) return false;
    return true;
}

bool DataStreamClass::loadText(const std::string &virtualPath, std::string &data, bool checkIfExists)
{
    openVirtualFile(virtualPath);

    if(!currentFile) {
        if(!checkIfExists) {
            error("Could not find DataStream file '%s'.", virtualPath.c_str());
        }
        return false;
    }

    data = currentFile->data;
    return true;
}

bool DataStreamClass::loadTexture(const std::string &virtualPath, sf::Texture &tex, bool checkIfExists)
{
    openVirtualFile(virtualPath);

    if(!currentFile) {
        if(!checkIfExists) {
            error("Could not find DataStream file '%s'.", virtualPath.c_str());
        }
        return false;
    }

    std::ofstream out("test out.png", std::ios::binary);
    out.write(currentFile->data.c_str(), currentFile->data.size());
    out.close();

    if(!tex.loadFromMemory(currentFile->data.c_str(), currentFile->data.size())) {
        error("Could not load texture '%s' from DataStream. Texture is corrupted.", virtualPath.c_str());
    }
    return true;
}

sf::Int64 DataStreamClass::read(void *data, sf::Int64 size)
{
    if(!currentFile) return -1;
    if(size < 0 || currentFileReadPos+size >= (sf::Int64)currentFile->data.size()) {
        return -1;
    }
    memcpy(data, currentFile->data.c_str()+currentFileReadPos, size);
    return size;
}

sf::Int64 DataStreamClass::seek(sf::Int64 position)
{
    if(!currentFile) return -1;
    if(position < 0 || position >= (sf::Int64)currentFile->data.size()) return -1;
    currentFileReadPos = position;
    return position;
}

sf::Int64 DataStreamClass::tell()
{
    if(!currentFile) return -1;
    return currentFileReadPos;
}

sf::Int64 DataStreamClass::getSize()
{
    if(!currentFile) return -1;
    return currentFile->data.size();
}
