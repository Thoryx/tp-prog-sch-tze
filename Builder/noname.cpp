#include <vector>
#include <iostream>
#include <fstream>
using namespace std;
struct Usuario {
	char nombre[50];
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
	
	m_staticText11 = new wxStaticText(this, wxID_ANY, "Ingrese Su Contraseña", wxPoint(0,2), wxSize(250,20), wxALIGN_CENTRE);
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
	
	
		vector<Usuario> usuarios;
		ifstream file("Credenciales.bin", std::ios::binary);
		if (file.is_open()) {
			Usuario usuario;
			while (file.read(reinterpret_cast<char*>(&usuario), sizeof(Usuario))) {
				usuarios.push_back(usuario);
			}
			file.close();
		} else {
			cerr << "Error al abrir el archivo para lectura.";
		}
	
	
	// Validación simple (esto es solo un ejemplo, en un caso real debes encriptar y verificar con una base de datos)
	if (usuario == "admin" && contrasenia == "password")
	{
		wxMessageBox("¡Ingreso exitoso!", "Login", wxOK | wxICON_INFORMATION);
		// Aquí puedes crear y mostrar la ventana principal
		Main_GUI* mainWindow = new Main_GUI(NULL);
		mainWindow->Show();
		this->Close();  // Cierra la ventana de login
	}
	else
	{
		wxMessageBox("Usuario o contraseña incorrectos", "Error", wxOK | wxICON_ERROR);
	}
}

// Implementación de Main_GUI

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
	
	b_agregar_fav = new wxButton(this, wxID_ANY, ("Añadir a Favoritos"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer5->Add(b_agregar_fav, 0, wxALL, 5);
	
	bSizer6->Add(bSizer5, 1, wxEXPAND, 5);
	bSizer4->Add(bSizer6, 1, wxEXPAND, 5);
	
	wxBoxSizer* bSizer9 = new wxBoxSizer(wxVERTICAL);
	
	b_fav = new wxButton(this, wxID_ANY, ("Ver Lista de Favoritos"), wxPoint(-1,-1), wxDefaultSize, wxBU_EXACTFIT);
	bSizer9->Add(b_fav, 0, wxALL, 5);
	
	bSizer4->Add(bSizer9, 1, wxEXPAND, 5);
	
	wxBoxSizer* bSizer7 = new wxBoxSizer(wxHORIZONTAL);
	
	b_aniadir = new wxButton(this, wxID_ANY, ("Añadir Libro"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer7->Add(b_aniadir, 0, wxALL, 5);
	
	b_modificar = new wxButton(this, wxID_ANY, ("Modificar Libro"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer7->Add(b_modificar, 0, wxALL, 5);
	
	b_borrar = new wxButton(this, wxID_ANY, ("Borrar Libro"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer7->Add(b_borrar, 0, wxALL, 5);
	
	bSizer4->Add(bSizer7, 1, wxEXPAND, 5);
	
	m_listBox1 = new wxListBox(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, NULL, 0);
	bSizer4->Add(m_listBox1, 5, wxALL|wxEXPAND, 5);
	
	fgSizer2->Add(bSizer4, 1, wxEXPAND, 5);
	
	this->SetSizer(fgSizer2);
	this->Layout();
	
	this->Centre(wxBOTH);
}

Main_GUI::~Main_GUI()
{
}
