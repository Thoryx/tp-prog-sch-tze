#ifndef __NONAME_H__
#define __NONAME_H__

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
	
	// Virtual event handlers
	virtual void Check(wxCommandEvent& event);  
	
public:
	//Constructor
	Login_GUI( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 800,600 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
	//destructor
	~Login_GUI();
};

///////////////////////////////////////////////////////////////////////////////
/// Class Main_GUI
///////////////////////////////////////////////////////////////////////////////
class Main_GUI : public wxFrame 
{
private:
	
protected:
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
	
	virtual void Registrar(wxCommandEvent& event);  
public:
	//Constructor
	Main_GUI( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 503,672 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
	//destructor
	~Main_GUI();
};

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
	virtual void Agregar( wxCommandEvent& event );
	virtual void Volver( wxCommandEvent& event );
	
	
public:
	//Constructor
	Agregar_Usuario( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Agregar Usuario"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,300 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
	//destructor
	~Agregar_Usuario();
	
};

#endif //__NONAME_H__
