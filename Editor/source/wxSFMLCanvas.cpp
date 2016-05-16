#include "wxSFMLCanvas.hpp"

#ifdef __WXGTK__
    #include <gdk/gdkx.h>
    #include <gtk/gtk.h>
    #include <wx/gtk/win_gtk.h>
#endif

BEGIN_EVENT_TABLE(wxSFMLCanvas, wxControl)
    EVT_IDLE(wxSFMLCanvas::OnIdle)
    EVT_PAINT(wxSFMLCanvas::OnPaint)
    EVT_ERASE_BACKGROUND(wxSFMLCanvas::OnEraseBackground)
END_EVENT_TABLE()


wxSFMLCanvas::wxSFMLCanvas(wxWindow* Parent, wxWindowID Id, const wxPoint& Position, const wxSize& Size, long Style, sf::RenderWindow *newWindow, bool newResizeFBO)
    :   wxControl(Parent, Id, Position, Size, Style)
{
    window = newWindow;
    #ifdef __WXGTK__
        gtk_widget_realize(m_wxwindow);
        gtk_widget_set_double_buffered(m_wxwindow, false);
        GdkWindow* Win = GTK_PIZZA(m_wxwindow)->bin_window;
        XFlush(GDK_WINDOW_XDISPLAY(Win));
        window->create(GDK_WINDOW_XWINDOW(Win));
    #else
        window->create((HWND__*)GetHandle());
    #endif
    lastWidth = -1;
    lastHeight = -1;
    resizeFBO = newResizeFBO;
    isFocused = false;
}

void wxSFMLCanvas::OnUpdate()
{
}

void wxSFMLCanvas::OnIdle(wxIdleEvent&)
{
    Refresh();
}

void wxSFMLCanvas::OnPaint(wxPaintEvent&)
{
    wxPaintDC Dc(this);
    OnUpdate();
    window->display();

    if(GetSize().x != lastWidth || GetSize().y != lastHeight) {
        window->create((HWND__*)GetHandle());
        if(resizeFBO) {
            colorMapFBO.create(window->getSize().x, window->getSize().y);
            normalMapFBO.create(window->getSize().x, window->getSize().y);
            heightMapFBO.create(window->getSize().x, window->getSize().y);
        }
        lastWidth = GetSize().x;
        lastHeight = GetSize().y;
    }
}

void wxSFMLCanvas::OnEraseBackground(wxEraseEvent&)
{
}

void wxSFMLCanvas::OnInit()
{
}
