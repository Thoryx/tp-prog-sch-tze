#ifndef __Agregar_Usuario__
#define __Agregar_Usuario__
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
class Agregar_Usuario : public wxFrame
{
private:
	//declaracion de cajas de texto para extraer datos
	wxTextCtrl* Agregar_Usuario_Ingresado;
	wxTextCtrl* Agregar_Contrasenia_Ingresado;
	wxTextCtrl* Agregar_Role_Ingresado;

protected:
	wxStaticText* Label_Estatica_Agregar_Usuario;
	wxStaticText* Label_Estatica_Agregar_Contrasenia;
	wxStaticText* Label_Estatica_Agregar_Role;
	wxButton* B_Agregar;
	wxButton* B_Volver;

	// Virtual event handlers
	virtual void Agregar(wxCommandEvent& event);
	virtual void Volver(wxCommandEvent& event);


public:
	//Constructor
	Agregar_Usuario(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Agregar Usuario"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(500, 300), long style = wxDEFAULT_FRAME_STYLE | wxTAB_TRAVERSAL);
	//destructor
	~Agregar_Usuario();

};

#endif 
