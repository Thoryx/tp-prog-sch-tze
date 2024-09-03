#ifndef __Main_GUI__
#define __Main_GUI__
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
#include "Loguin_GUI.h"

class Main_GUI : public wxFrame
{
private:

	//declaracion de botones y listbox(a implementar)
	wxButton* b_busqueda;
	wxButton* b_detalles;
	wxButton* b_agregar_fav;
	wxButton* b_fav;
	wxButton* b_aniadir;
	wxButton* b_modificar;
	wxButton* b_borrar;
	wxButton* b_AgregarUser;
	wxListBox* Libros_listBox;
	bool esAdmin;

	virtual void Registrar(wxCommandEvent& event);
	
public:
	//Constructor
	Main_GUI(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(503, 672), long style = wxDEFAULT_FRAME_STYLE | wxTAB_TRAVERSAL) {
		esAdmin = Login_GUI::Ver_Rol();
	};
	//destructor
	~Main_GUI();
};
#endif //__Main_GUI__