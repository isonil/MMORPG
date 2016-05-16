#ifndef WXHTMLWINDOWMY_H
#define WXHTMLWINDOWMY_H

#include "wx/wxhtml.h"
#include "wx/dcclient.h"
#include "wx/dcmemory.h"

class HtmlWindow : public wxHtmlWindow
{
	public:
		HtmlWindow(wxWindow *parent, wxWindowID id = wxID_ANY,
                 const wxPoint& pos = wxDefaultPosition,
                 const wxSize& size = wxDefaultSize,
                 long style = wxHW_DEFAULT_STYLE,
                 const wxString& name = wxT("htmlWindow"))
		: wxHtmlWindow(parent, id, pos, size, style, name)
		{
			m_backBuffer = NULL;
			wxPaintEvent event;
		}

		~HtmlWindow() {}

		void SetBackgroundImage(const wxBitmap& bmp) {m_bmpBg = bmp;}
	protected:
		wxBitmap m_bmpBg;
		bool m_eraseBgInOnPaint;
		wxBitmap *m_backBuffer;

		void OnEraseBackground(wxEraseEvent& event);
		void OnPaint(wxPaintEvent& event);
		void OnSize(wxSizeEvent& event);

		DECLARE_EVENT_TABLE()
};

#endif
