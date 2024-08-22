#ifndef __NONAME_H__
#define __NONAME_H__

#include <wx/artprov.h>
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
#include <wx/listbox.h>
#include <wx/msgdlg.h>  // Para wxMessageBox

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class Login_GUI
///////////////////////////////////////////////////////////////////////////////
class Login_GUI : public wxFrame 
{
private:
	wxTextCtrl* Login_Usuario_ingresado;
	wxTextCtrl* Login_Contrasenia_ingresado;
	
protected:
	wxStaticText* m_staticText1;
	wxStaticText* m_staticText11;
	wxButton* B_Ingresar;
	
	// Virtual event handlers
	virtual void Check(wxCommandEvent& event);  
	
public:
	
	Login_GUI( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 800,600 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
	
	~Login_GUI();
};

///////////////////////////////////////////////////////////////////////////////
/// Class Main_GUI
///////////////////////////////////////////////////////////////////////////////
class Main_GUI : public wxFrame 
{
private:
	
protected:
	wxButton* b_busqueda;
	wxButton* b_detalles;
	wxButton* b_agregar_fav;
	wxButton* b_fav;
	wxButton* b_aniadir;
	wxButton* b_modificar;
	wxButton* b_borrar;
	wxButton* b_AgregarUser;
	wxListBox* m_listBox1;
	
	virtual void Registrar(wxCommandEvent& event);  
public:
	
	Main_GUI( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 503,672 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
	
	~Main_GUI();
};

class Agregar_Usuario : public wxFrame 
{
private:
	wxTextCtrl* Login_Usuario_ingresado;
	wxTextCtrl* Login_Contrasenia_ingresado;
	
protected:
	wxStaticText* m_staticText1;
	wxStaticText* m_staticText11;
	wxButton* B_Agregar;
	
	// Virtual event handlers, overide them in your derived class
	virtual void Agregar( wxCommandEvent& event );
	
	
public:

	Agregar_Usuario( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Agregar Usuario"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,300 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

	~Agregar_Usuario();
	
};

#endif //__NONAME_H__
