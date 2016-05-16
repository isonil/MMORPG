/***************************************************************
 * Name:      LauncherMain.cpp
 * Purpose:   Code for Application Frame
 * Author:     ()
 * Created:   2012-08-30
 * Copyright:  ()
 * License:
 **************************************************************/

#include "LauncherMain.h"
#include "md5.h"
#include <wx/msgdlg.h>
#include <wx/event.h>
#include <curl/curl.h>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <process.h>

//(*InternalHeaders(LauncherFrame)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(LauncherFrame)
const long LauncherFrame::ID_GAUGE1 = wxNewId();
const long LauncherFrame::ID_STATICTEXT1 = wxNewId();
const long LauncherFrame::ID_CUSTOM1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(LauncherFrame,wxFrame)
    //(*EventTable(LauncherFrame)
    //*)
END_EVENT_TABLE()

class ClientFileClass
{
    public:
        std::string path;
        std::string md5;
        int size;
        bool download;

        ClientFileClass() {}
        ClientFileClass(const std::string &newPath, const std::string &newMd5, int newSize)
            :   path(newPath), md5(newMd5), size(newSize), download(false) {
        }
};

struct MemoryStruct {
    char *memory;
    size_t size;
};

CURL *curl;
CURLcode status;
std::string serverAddress;
MemoryStruct chunk;
std::vector <ClientFileClass> clientFile;
double toDownloadSize = 0;
double downloadedSize = 0;
double downloadedSizeBase = 0;
wxGauge *wxProgressBar;
wxStaticText *wxDownloadStatus;
HtmlWindow *wxNews;

void getFilesList(char *ptr)
{
    std::istringstream iss(ptr);
    std::string tag;
    iss >> tag;
    if(tag == "files") {
        std::string newPath, newMd5;
        int newSize;
        while(iss >> newPath >> newMd5 >> newSize) {
            clientFile.push_back(ClientFileClass(newPath, newMd5, newSize));
        }
    }
    else {
        char *buff = new char[strlen(ptr)+100];
        sprintf(buff, "No valid files list found on this server. Address may be invalid. Server response:\n%s", ptr);
        wxMessageBox(buff, _("Error"));
        delete []buff;
        exit(0);
    }
}

size_t writeMemoryCallback(void *content, size_t size, size_t nmemb, void *data)
{
    size_t realsize = size*nmemb;
    MemoryStruct *mem = (MemoryStruct*)data;
    mem->memory = (char*)realloc(mem->memory, mem->size+realsize+1);
    if(mem->memory == NULL) {
        wxMessageBox(_("Not enough memory (realloc failed)."), _("Error"));
        exit(1);
    }
    memcpy(&(mem->memory[mem->size]), content, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;
    return realsize;
}

int progressBarCallback(void *p, double dltotal, double dlnow, double ult, double uln)
{
    downloadedSize = downloadedSizeBase + dlnow;
    char label[200];
    sprintf(label, "Downloading %.2lf/%.2lf MiB", downloadedSize/(1024.0*1024.0), toDownloadSize/(1024.0*1024.0));
    wxNews->Update();
    wxDownloadStatus->SetLabel(label);
    int value = downloadedSize/toDownloadSize*100.0;
    if(value > 100) value = 100;
    if(value < 0) value = 0;
    wxProgressBar->SetValue(value);
    return 0;
}

void downloadThread(void *)
{
    for(size_t i=0; i<clientFile.size(); ++i) {
        std::ifstream in(clientFile[i].path.c_str(), std::ios::binary);
        if(!in) clientFile[i].download = true;
        else {
            std::string buffStr;
            unsigned char fileChar;
            while(in >> std::noskipws >> fileChar) {
                buffStr += fileChar;
            }
            if(md5(buffStr) != clientFile[i].md5) {
                clientFile[i].download = true;
            }
            in.close();
        }
    }

    for(size_t i=0; i<clientFile.size(); ++i) {
        if(clientFile[i].download) {
            toDownloadSize += clientFile[i].size;
        }
    }

    if(toDownloadSize) {
        char label[200];
        sprintf(label, "Downloading 0.00/%.2lf MiB", toDownloadSize/(1024.0*1024.0));
        wxDownloadStatus->SetLabel(label);
    }

    for(size_t i=0; i<clientFile.size(); ++i) {
        if(clientFile[i].download) {
            char *url = new char[serverAddress.size()+clientFile[i].path.size()+10];
            sprintf(url,"%s%s", serverAddress.c_str(), clientFile[i].path.c_str());
            chunk.memory = (char*)malloc(1);
            chunk.size = 0;
            curl_easy_setopt(curl, CURLOPT_URL, url);
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeMemoryCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)&chunk);
            curl_easy_setopt(curl, CURLOPT_NOPROGRESS, false);
            curl_easy_setopt(curl, CURLOPT_PROGRESSFUNCTION, progressBarCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)&chunk);
            curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcurl-agent/1.0");
            status = curl_easy_perform(curl);
            if(status != CURLE_OK) {
                char error[100];
                sprintf(error, "Could not download one of listed files. Curl error code: %d.", status);
                wxMessageBox(error, _("Error"));
                exit(0);
            }

            std::ofstream out(clientFile[i].path.c_str(), std::ios::binary);
            if(out) {
                for(size_t j=0; j<chunk.size; ++j) {
                    out << chunk.memory[j];
                }
                out.close();
            }
            else {
                std::vector <std::string> pathSegment;
                pathSegment.resize(1);
                for(size_t j=0; j<clientFile[i].path.size(); ++j) {
                    if(clientFile[i].path[j] == '/' ||
                       clientFile[i].path[j] == '\\') {
                        pathSegment.resize(pathSegment.size()+1);
                    }
                    else pathSegment.back() += clientFile[i].path[j];
                }
                std::string currentDir;
                for(size_t j=0; j<pathSegment.size()-1; ++j) {
                    if(j) currentDir += '/';
                    currentDir += pathSegment[j];
                    mkdir(currentDir.c_str());
                }
                out.open(clientFile[i].path.c_str(), std::ios::binary);
                if(out) {
                    for(size_t j=0; j<chunk.size; ++j) {
                        out << chunk.memory[j];
                    }
                    out.close();
                }
                else {
                    char *buff = new char[clientFile[i].path.size()+100];
                    sprintf(buff, "Could not create file '%s'.", clientFile[i].path.c_str());
                    wxMessageBox(buff, _("Error"));
                    delete []buff;
                    exit(0);
                }
            }

            delete []url;
            if(chunk.memory) free(chunk.memory);

            downloadedSizeBase += clientFile[i].size;
            downloadedSize = downloadedSizeBase;
        }
    }

    curl_easy_cleanup(curl);

    wxDownloadStatus->SetLabel("Update completed.");
    wxProgressBar->SetValue(100);

    Sleep(500);
    ShellExecute(NULL, NULL, "Client.exe", "-launcher", NULL, SW_SHOWNORMAL);
    exit(0);
}

LauncherFrame::LauncherFrame(wxWindow* parent,wxWindowID id)
{
    std::ifstream serverAddressIn("updaterAddress.cfg");
    if(serverAddressIn) {
        serverAddressIn >> serverAddress;
        serverAddressIn.close();
    }
    else {
        wxMessageBox(_("Could not open 'updaterAddress.cfg'."), _("Error"));
        exit(0);
    }

    if(!serverAddress.size()) {
        wxMessageBox(_("No server address specified in 'updaterAddress.cfg'."), _("Error"));
        exit(0);
    }
    else {
        if(serverAddress[serverAddress.size()-1] != '/') {
            serverAddress += '/';
        }
    }

    if(!(curl = curl_easy_init())) {
        wxMessageBox(_("Could not init curl."), _("Error"));
        exit(0);
    }

    char *url = new char[serverAddress.size()+30];
    std::ofstream out;

    sprintf(url, "%snews.html", serverAddress.c_str());
    chunk.memory = (char*)malloc(1);
    chunk.size = 0;
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeMemoryCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)&chunk);
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcurl-agent/1.0");
    status = curl_easy_perform(curl);
    if(status != CURLE_OK) {
        char error[100];
        sprintf(error, "Could not download 'news.html'. Server may be offline. Curl error code: %d.", status);
        wxMessageBox(error, _("Error"));
        exit(0);
    }
    out.open("news.html", std::ios::binary);
    if(!out) {
        wxMessageBox(_("Could not create 'news.html'."), _("Error"));
        exit(0);
    }
    for(size_t i=0; i<chunk.size; ++i) {
        out << chunk.memory[i];
    }
    out.close();
    if(chunk.memory) free(chunk.memory);

    bool download = false;
    std::ifstream in("background.png");
    if(!in) download = true;
    else in.close();
    if(download) {
        sprintf(url, "%sbackground.png", serverAddress.c_str());
        chunk.memory = (char*)malloc(1);
        chunk.size = 0;
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeMemoryCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)&chunk);
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcurl-agent/1.0");
        CURLcode status = curl_easy_perform(curl);
        if(status != CURLE_OK) {
            char error[100];
            sprintf(error, "Could not download 'background.png'. Curl error code: %d.", status);
            wxMessageBox(error, _("Error"));
            exit(0);
        }
        out.open("background.png", std::ios::binary);
        if(!out) {
            wxMessageBox(_("Could not create 'background.png'."), _("Error"));
            exit(0);
        }
        for(size_t i=0; i<chunk.size; ++i) {
            out << chunk.memory[i];
        }
        out.close();
        if(chunk.memory) free(chunk.memory);
    }

    sprintf(url, "%sfiles.txt", serverAddress.c_str());
    chunk.memory = (char*)malloc(1);
    chunk.size = 0;
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeMemoryCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)&chunk);
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcurl-agent/1.0");
    status = curl_easy_perform(curl);
    if(status != CURLE_OK) {
        char error[100];
        sprintf(error, "Could not download 'files.txt'. Curl error code: %d.", status);
        wxMessageBox(error, _("Error"));
        exit(0);
    }
    getFilesList(chunk.memory);
    if(chunk.memory) free(chunk.memory);

    //(*Initialize(LauncherFrame)
    Create(parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSTATIC_BORDER, _T("wxID_ANY"));
    SetClientSize(wxSize(600,260));
    SetBackgroundColour(wxColour(0,0,0));
    Gauge1 = new wxGauge(this, ID_GAUGE1, 100, wxPoint(0,232), wxSize(600,28), 0, wxDefaultValidator, _T("ID_GAUGE1"));
    StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Checking files"), wxPoint(0,218), wxSize(80,14), 0, _T("ID_STATICTEXT1"));
    StaticText1->SetForegroundColour(wxColour(255,255,255));
    StaticText1->SetBackgroundColour(wxColour(0,0,0));
    Custom1 = new HtmlWindow(this,ID_CUSTOM1,wxPoint(0,0),wxSize(600,218),,_T("ID_CUSTOM1"));
    Center();
    //*)

    wxProgressBar = Gauge1;
    wxDownloadStatus = StaticText1;
    wxNews = Custom1;
    Custom1->SetBackgroundImage(wxBitmap("background.png", wxBITMAP_TYPE_PNG));
    Custom1->LoadPage(_("news.html"));

    _beginthread(downloadThread, 0, NULL);
}

LauncherFrame::~LauncherFrame()
{
    //(*Destroy(LauncherFrame)
    //*)
}

void LauncherFrame::OnQuit(wxCommandEvent& event)
{
    Close();
}
