///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun 17 2015)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

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
#include <wx/msgdlg.h>
#include "noname.h"



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
		wxListBox* m_listBox1;
	
	public:
		
		Main_GUI( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 503,672 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		
		~Main_GUI();
	
};
///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class Login_GUI
///////////////////////////////////////////////////////////////////////////////
class Login_GUI : public wxFrame 
{
private:
	wxTextCtrl* Login_Usuario_ingresado;
	wxTextCtrl* Login_Contrasenia_ingresado;
	//		Main_GUI::Main_GUI(wxWindow* parent, wxWindowID id, const wxString& title)
	//			: wxFrame(parent, id, title) {
	//			// Aquí puedes inicializar los controles y el diseño de tu ventana principal
	//		}
	
	
	protected:
		wxStaticText* m_staticText1;
		wxStaticText* m_staticText11;
		wxButton* B_Ingresar;
		
		// Virtual event handlers, overide them in your derived class
		void Login_check( wxCommandEvent& event ) { 
			
			// Aquí colocas tu código para manejar el evento de login
			wxString username = Login_Usuario_ingresado->GetValue();
			wxString password = Login_Contrasenia_ingresado->GetValue();
			
			// Lógica de validación simple
			if (username == "admin" && password == "password123") {
				wxMessageBox("Login exitoso", "Info", wxOK | wxICON_INFORMATION);
				Close();// Por ejemplo, cerrar la ventana de login
				Main_GUI* mainFrame = new Main_GUI(nullptr, wxID_ANY, wxT("Ventana Principal"));
				mainFrame->Show(true);
			} else {
				wxMessageBox("Usuario o contraseña incorrecta", "Error", wxOK | wxICON_ERROR);
			}
		} 
		
		
	public:
			
			Login_GUI( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 800,600 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
			
			~Login_GUI();
			
};
#endif //__NONAME_H__
