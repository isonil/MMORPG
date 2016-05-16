#ifndef WXSFMLCANVAS_HPP
#define WXSFMLCANVAS_HPP

#include "Editor.hpp"
#include "global.hpp"
#include <SFML/Graphics.hpp>
#include <wx/wx.h>

class wxSFMLCanvas : public wxControl, public sf::RenderWindow
{
    public:
        wxSFMLCanvas(wxWindow* Parent = NULL, wxWindowID Id = -1, const wxPoint& Position = wxDefaultPosition, const wxSize& Size = wxDefaultSize, long Style = 0, sf::RenderWindow *newWindow = NULL, bool newResizeFBO = false);
        sf::RenderWindow *window;
        bool isFocused;

    private:
        int lastWidth;
        int lastHeight;
        bool resizeFBO;

        DECLARE_EVENT_TABLE()
        virtual void OnInit();
        virtual void OnUpdate();
        void OnIdle(wxIdleEvent&);
        void OnPaint(wxPaintEvent&);
        void OnEraseBackground(wxEraseEvent&);
};

class WorldRenderCanvas : public wxSFMLCanvas
{
    public:
        WorldRenderCanvas(wxWindow*  Parent,
                          wxWindowID Id,
                          const wxPoint&   Position,
                          const wxSize&    Size,
                          long       Style,
                          const wxValidator&,
                          const char*)
            :   wxSFMLCanvas(Parent, Id, Position, Size, Style, Editor::getInstance().getWindow(), true) {
        }

    private:
        virtual void OnUpdate()
        {
            Editor::getInstance().updateDelta();
            if(isFocused) {
                Editor::getInstance().logicInterface();
            }
            Editor::getInstance().renderAll();
        }
};

class EntitySelectCanvas : public wxSFMLCanvas
{
    public:
        EntitySelectCanvas(wxWindow*  Parent,
                           wxWindowID Id,
                           const wxPoint&   Position,
                           const wxSize&    Size,
                           long       Style,
                           const wxValidator&,
                           const char*)
            :   wxSFMLCanvas(Parent, Id, Position, Size, Style, new sf::RenderWindow, false) {
        }

    private:
        virtual void OnUpdate()
        {
            window->clear(sf::Color::White);
            if(wxEntitySelection1->GetSelection() == 0) {
                Editor::getInstance().renderTileTypes(*window);
            }
            else if(wxEntitySelection1->GetSelection() == 1) {
                Editor::getInstance().renderSceneryTypes(*window);
            }
            else if(wxEntitySelection1->GetSelection() == 2) {
                Editor::getInstance().renderObjectTypes(*window);
            }
            else if(wxEntitySelection1->GetSelection() == 3) {
                Editor::getInstance().renderNPCTypes(*window);
            }
            else if(wxEntitySelection1->GetSelection() == 4) {
                Editor::getInstance().renderLightSourceTypes(*window);
            }
            else if(wxEntitySelection1->GetSelection() == 5) {
                Editor::getInstance().renderTriggers(*window);
            }
            else if(wxEntitySelection1->GetSelection() == 6) {
                Editor::getInstance().renderEffects(*window);
            }
            else if(wxEntitySelection1->GetSelection() == 7) {
                Editor::getInstance().renderZoneTypes(*window);
            }
        }
};


#endif
