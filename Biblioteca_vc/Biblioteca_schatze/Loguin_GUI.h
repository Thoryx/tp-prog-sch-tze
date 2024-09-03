#ifndef __Logui_GUI__
#define __Logui_GUI__

#include <wx/artprov.h> //configuracionesVentana
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/textctrl.h>
#include <wx/sizer.h>
#include <wx/button.h>
#include <wx/gbsizer.h>
#include <wx/frame.h>
#include <wx/listbox.h>//endconfiguracionesventana

#include <wx/msgdlg.h>  // Para wxMessageBox




///////////////////////////////////////////////////////////////////////////////
/// Class Login_GUI
///////////////////////////////////////////////////////////////////////////////
class Login_GUI : public wxFrame
{
private:
	//declaracion de cajas de texto para extraer datos
	wxTextCtrl* Login_Usuario_ingresado;
	wxTextCtrl* Login_Contrasenia_ingresado;
	

protected:
	//declaracion de cajas de texto estatico
	wxStaticText* Label_Estatica_Usuario;
	wxStaticText* Label_Estatica_Contrasenia;
	wxButton* B_Ingresar;
	bool esAdmin = false;

	// Virtual event handlers
	virtual void Check(wxCommandEvent& event);

public:
	//Constructor
	Login_GUI(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(800, 600), long style = wxDEFAULT_FRAME_STYLE | wxTAB_TRAVERSAL);
	static bool Ver_Rol() { return esAdmin; }
	//destructor
	~Login_GUI();
};
#endif //__NONAME_H__