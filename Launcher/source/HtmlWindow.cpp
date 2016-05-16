#include "HtmlWindow.hpp"

BEGIN_EVENT_TABLE(HtmlWindow, wxHtmlWindow)
    EVT_ERASE_BACKGROUND(HtmlWindow::OnEraseBackground)
    EVT_PAINT(HtmlWindow::OnPaint)
    EVT_SIZE(HtmlWindow::OnSize)
END_EVENT_TABLE()

void HtmlWindow::OnEraseBackground(wxEraseEvent& event)
{
    if ( !m_bmpBg.Ok() )
    {
        // don't even skip the event, if we don't have a bg bitmap we're going
        // to overwrite background in OnPaint() below anyhow, so letting the
        // default handling take place would only result in flicker, just set a
        // flag to erase the background below
        m_eraseBgInOnPaint = true;
        return;
    }

    wxDC& dc = *event.GetDC();

    // if the image is not fully opaque, we have to erase the background before
    // drawing it, however avoid doing it for opaque images as this would just
    // result in extra flicker without any other effect as background is
    // completely covered anyhow
    if ( m_bmpBg.GetMask() )
    {
        dc.SetBackground(wxBrush(GetBackgroundColour(), wxSOLID));
        dc.Clear();
    }
	dc.DrawBitmap(m_bmpBg, 0, 0, true /* use mask */);
}

void HtmlWindow::OnPaint(wxPaintEvent& WXUNUSED(event))
{
    wxPaintDC dc(this);

    if (/*m_tmpCanDrawLocks > 0 || */m_Cell == NULL)
        return;

    int x, y;
    GetViewStart(&x, &y);
    wxRect rect = GetUpdateRegion().GetBox();
    wxSize sz = GetSize();

    wxMemoryDC dcm;
    if ( !m_backBuffer )
		m_backBuffer = new wxBitmap(sz.x, sz.y);
    dcm.SelectObject(*m_backBuffer);

    if ( m_eraseBgInOnPaint )
    {
        dcm.SetBackground(wxBrush(GetBackgroundColour(), wxSOLID));
        dcm.Clear();
        m_eraseBgInOnPaint = false;
    }
    else // someone has already erased the background, keep it
    {
        // preserve the existing background, otherwise we'd erase anything the
        // user code had drawn in its EVT_ERASE_BACKGROUND handler when we do
        // the Blit back below
		dcm.Blit(0, rect.GetTop(),
				sz.x, rect.GetBottom() - rect.GetTop() + 1,
				&dc,
				0, rect.GetTop());
		dcm.DrawBitmap(m_bmpBg, 0, -(y * wxHTML_SCROLL_STEP), true /* use mask */);
    }

    PrepareDC(dcm);
    dcm.SetMapMode(wxMM_TEXT);
    dcm.SetBackgroundMode(wxTRANSPARENT);

    wxHtmlRenderingInfo rinfo;
    wxDefaultHtmlRenderingStyle rstyle;
    rinfo.SetSelection(m_selection);
    rinfo.SetStyle(&rstyle);
    m_Cell->Draw(dcm, 0, 0,
                 y * wxHTML_SCROLL_STEP + rect.GetTop(),
                 y * wxHTML_SCROLL_STEP + rect.GetBottom(),
                 rinfo);

//#define DEBUG_HTML_SELECTION
#ifdef DEBUG_HTML_SELECTION
    {
    int xc, yc, x, y;
    wxGetMousePosition(&xc, &yc);
    ScreenToClient(&xc, &yc);
    CalcUnscrolledPosition(xc, yc, &x, &y);
    wxHtmlCell *at = m_Cell->FindCellByPos(x, y);
    wxHtmlCell *before =
        m_Cell->FindCellByPos(x, y, wxHTML_FIND_NEAREST_BEFORE);
    wxHtmlCell *after =
        m_Cell->FindCellByPos(x, y, wxHTML_FIND_NEAREST_AFTER);

    dcm.SetBrush(*wxTRANSPARENT_BRUSH);
    dcm.SetPen(*wxBLACK_PEN);
    if (at)
        dcm.DrawRectangle(at->GetAbsPos(),
                          wxSize(at->GetWidth(),at->GetHeight()));
    dcm.SetPen(*wxGREEN_PEN);
    if (before)
        dcm.DrawRectangle(before->GetAbsPos().x+1, before->GetAbsPos().y+1,
                          before->GetWidth()-2,before->GetHeight()-2);
    dcm.SetPen(*wxRED_PEN);
    if (after)
        dcm.DrawRectangle(after->GetAbsPos().x+2, after->GetAbsPos().y+2,
                          after->GetWidth()-4,after->GetHeight()-4);
    }
#endif

    dcm.SetDeviceOrigin(0,0);
    dc.Blit(0, rect.GetTop(),
            sz.x, rect.GetBottom() - rect.GetTop() + 1,
            &dcm,
            0, rect.GetTop());
}

void HtmlWindow::OnSize(wxSizeEvent& event)
{
    wxDELETE(m_backBuffer);
    wxHtmlWindow::OnSize(event);
}
