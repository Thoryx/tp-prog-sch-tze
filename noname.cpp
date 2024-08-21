#include <vector>
#include <iostream>
#include <fstream>
using namespace std;
struct Usuario {
	char Usuario[50];
	char contrasena[50];
	char rol[4];
};

#include "noname.h"

Login_GUI::Login_GUI(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style)
	: wxFrame(parent, id, title, pos, size, style)
{
	this->SetSizeHints(wxDefaultSize, wxDefaultSize);
	
	wxGridBagSizer* gbSizer1 = new wxGridBagSizer(0, 0);
	gbSizer1->SetFlexibleDirection(wxBOTH);
	gbSizer1->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);
	
	wxBoxSizer* bSizer1 = new wxBoxSizer(wxVERTICAL);
	
	m_staticText1 = new wxStaticText(this, wxID_ANY, ("Ingrese Su Usuario"), wxPoint(0,0), wxSize(250,20), wxALIGN_CENTRE);
	m_staticText1->Wrap(250);
	bSizer1->Add(m_staticText1, 0, wxALL, 5);
	
	Login_Usuario_ingresado = new wxTextCtrl(this, wxID_ANY, ("Escriba Aqui..."), wxPoint(2,2), wxSize(250,25), wxTE_CENTRE);
	bSizer1->Add(Login_Usuario_ingresado, 0, wxALL, 5);
	
	gbSizer1->Add(bSizer1, wxGBPosition(7, 30), wxGBSpan(1, 1), wxEXPAND, 5);
	
	wxBoxSizer* bSizer11 = new wxBoxSizer(wxVERTICAL);
	
	m_staticText11 = new wxStaticText(this, wxID_ANY, "Ingrese Su Contrase�a", wxPoint(0,2), wxSize(250,20), wxALIGN_CENTRE);
	m_staticText11->Wrap(250);
	bSizer11->Add(m_staticText11, 0, wxALL, 5);
	
	Login_Contrasenia_ingresado = new wxTextCtrl(this, wxID_ANY, ("Escriba Aqui..."), wxPoint(1,1), wxSize(250,25), wxTE_CENTRE | wxTE_PASSWORD);
	bSizer11->Add(Login_Contrasenia_ingresado, 0, wxALL, 5);
	
	gbSizer1->Add(bSizer11, wxGBPosition(11, 30), wxGBSpan(1, 1), wxEXPAND, 5);
	
	B_Ingresar = new wxButton(this, wxID_ANY, ("Ingresar"), wxDefaultPosition, wxDefaultSize, 0);
	B_Ingresar->SetMinSize(wxSize(250,30));
	
	gbSizer1->Add(B_Ingresar, wxGBPosition(15, 30), wxGBSpan(1, 1), wxALL, 5);
	
	this->SetSizer(gbSizer1);
	this->Layout();
	
	this->Centre(wxBOTH);
	
	// Connect Events
	B_Ingresar->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(Login_GUI::Check), NULL, this);
}

Login_GUI::~Login_GUI()
{
	// Disconnect Events
	B_Ingresar->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(Login_GUI::Check), NULL, this);
}

void Login_GUI::Check(wxCommandEvent& event)
{
	
	// Obtener los valores ingresados por el usuario
	wxString usuario = Login_Usuario_ingresado->GetValue();
	wxString contrasenia = Login_Contrasenia_ingresado->GetValue();
	bool noencontrado = true;
	
	vector<Usuario> usuarios;
	ifstream file("Credenciales.dat", std::ios::binary);
	if (file.is_open()) {
		Usuario usuario;
		while (file.read(reinterpret_cast<char*>(&usuario), sizeof(Usuario))) {
			usuarios.push_back(usuario);
		}
		file.close();
	} else {
		cerr << "Error al abrir el archivo para lectura.";
	}
	
	
	for( vector<Usuario>::iterator it=usuarios.begin(); it!=usuarios.end(); ++it ) {  
		if (usuario == it->Usuario && it->contrasena == contrasenia)
		{
			noencontrado=false;
			wxMessageBox("�Ingreso exitoso!", "Login", wxOK | wxICON_INFORMATION);
			// Aqu� puedes crear y mostrar la ventana principal
			Main_GUI* mainWindow = new Main_GUI(NULL);
			mainWindow->Show();
			this->Close();  // Cierra la ventana de login
		}
	}
	if (noencontrado)
	{
		wxMessageBox("Usuario o contrase�a incorrectos", "Error", wxOK | wxICON_ERROR);
	}
}

// Implementaci�n de Main_GUI

Main_GUI::Main_GUI(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style)
	: wxFrame(parent, id, title, pos, size, style)
{
	this->SetSizeHints(wxDefaultSize, wxDefaultSize);
	wxFlexGridSizer* fgSizer2 = new wxFlexGridSizer(1, 1, 0, 0);
	fgSizer2->SetFlexibleDirection(wxBOTH);
	fgSizer2->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);
	
	wxBoxSizer* bSizer4 = new wxBoxSizer(wxVERTICAL);
	
	wxBoxSizer* bSizer6 = new wxBoxSizer(wxHORIZONTAL);
	
	wxBoxSizer* bSizer5 = new wxBoxSizer(wxHORIZONTAL);
	
	b_busqueda = new wxButton(this, wxID_ANY, ("Buscar Libro"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer5->Add(b_busqueda, 0, wxALL, 5);
	
	b_detalles = new wxButton(this, wxID_ANY, ("Ver Detalles"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer5->Add(b_detalles, 0, wxALL, 5);
	
	b_agregar_fav = new wxButton(this, wxID_ANY, ("A�adir a Favoritos"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer5->Add(b_agregar_fav, 0, wxALL, 5);
	
	bSizer6->Add(bSizer5, 1, wxEXPAND, 5);
	bSizer4->Add(bSizer6, 1, wxEXPAND, 5);
	
	wxBoxSizer* bSizer9 = new wxBoxSizer(wxVERTICAL);
	
	b_fav = new wxButton(this, wxID_ANY, ("Ver Lista de Favoritos"), wxPoint(-1,-1), wxDefaultSize, wxBU_EXACTFIT);
	bSizer9->Add(b_fav, 0, wxALL, 5);
	
	bSizer4->Add(bSizer9, 1, wxEXPAND, 5);
	
	wxBoxSizer* bSizer7 = new wxBoxSizer(wxHORIZONTAL);
	
	b_aniadir = new wxButton(this, wxID_ANY, ("A�adir Libro"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer7->Add(b_aniadir, 0, wxALL, 5);
	
	b_modificar = new wxButton(this, wxID_ANY, ("Modificar Libro"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer7->Add(b_modificar, 0, wxALL, 5);
	
	b_borrar = new wxButton(this, wxID_ANY, ("Borrar Libro"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer7->Add(b_borrar, 0, wxALL, 5);
	
	b_AgregarUser = new wxButton( this, wxID_ANY, wxT("Registrar Usuario"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer7->Add( b_AgregarUser, 0, wxALL, 5 );
	
	bSizer4->Add(bSizer7, 1, wxEXPAND, 5);
	
	m_listBox1 = new wxListBox( this, wxID_ANY, wxDefaultPosition, wxSize( 500,500 ), 0, NULL, 0 ); 
	bSizer4->Add( m_listBox1, 0, wxALL, 5 );
	
	fgSizer2->Add(bSizer4, 1, wxEXPAND, 5);
	
	this->SetSizer(fgSizer2);
	this->Layout();
	
	this->Centre(wxBOTH);
	
	b_AgregarUser->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(Main_GUI::Registrar), NULL, this);
}

Main_GUI::~Main_GUI()
{
	b_AgregarUser->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(Main_GUI::Registrar), NULL, this);
}
void Main_GUI::Registrar(wxCommandEvent& event){
	Agregar_Usuario* mainWindow = new Agregar_Usuario(NULL);
	mainWindow->Show();
	this->Close();
}

Agregar_Usuario::Agregar_Usuario( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer8;
	bSizer8 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText1 = new wxStaticText( this, wxID_ANY, wxT("Ingrese Su Usuario"), wxPoint( 0,0 ), wxSize( 250,20 ), wxALIGN_CENTRE );
	m_staticText1->Wrap( 250 );
	bSizer1->Add( m_staticText1, 0, wxALL, 5 );
	
	Login_Usuario_ingresado = new wxTextCtrl( this, wxID_ANY, wxT("Escriba Aqui..."), wxPoint( 2,2 ), wxSize( 250,25 ), wxTE_CENTRE );
	bSizer1->Add( Login_Usuario_ingresado, 0, wxALL, 5 );
	
	
	bSizer8->Add( bSizer1, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer11;
	bSizer11 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText11 = new wxStaticText( this, wxID_ANY, wxT(""), wxPoint( 0,2 ), wxSize( 250,20 ), wxALIGN_CENTRE );
	m_staticText11->Wrap( 250 );
	bSizer11->Add( m_staticText11, 0, wxALL, 5 );
	
	Login_Contrasenia_ingresado = new wxTextCtrl( this, wxID_ANY, wxT(""), wxPoint( 1,1 ), wxSize( 250,25 ), wxTE_CENTRE );
	bSizer11->Add( Login_Contrasenia_ingresado, 0, wxALL, 5 );
	
	
	bSizer8->Add( bSizer11, 1, wxEXPAND, 5 );
	
	B_Agregar = new wxButton( this, wxID_ANY, wxT("Ingresar"), wxDefaultPosition, wxDefaultSize, 0 );
	B_Agregar->SetMinSize( wxSize( 250,30 ) );
	
	bSizer8->Add( B_Agregar, 0, wxALL, 5 );
	
	
	this->SetSizer( bSizer8 );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	B_Agregar->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( Agregar_Usuario::Agregar ), NULL, this );
}

Agregar_Usuario::~Agregar_Usuario()
{
	// Disconnect Events
	B_Agregar->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( Agregar_Usuario::Agregar ), NULL, this );
	
}
void Agregar_Usuario::Agregar(wxCommandEvent& event){
	
	
	
	
	
	
	Main_GUI* mainWindow = new Main_GUI(NULL);
	mainWindow->Show();
	this->Close();
}
