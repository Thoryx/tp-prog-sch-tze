#include <vector> //manejo vectores
//librerias de flujos de datos//
#include <iostream>//
#include <fstream>//
#include "Loguin_GUI.h"//se incluye cabecera con las declaraciones de objetos y funciones
#include "Main_GUI.h"

using namespace std;

//Struct data para manejo de usuarios
struct Usuario {
	char Usuario[50];
	char contrasena[50];
	char rol[4];
};


//implementacion del constructor
Login_GUI::Login_GUI(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style)
	: wxFrame(parent, id, title, pos, size, style)
{
	//Seteo de tamaños
	this->SetSizeHints(wxDefaultSize, wxDefaultSize);
	//Configuraciones de labels y botones
	wxGridBagSizer* Grilla_Exterior_Loguin = new wxGridBagSizer(0, 0);
	Grilla_Exterior_Loguin->SetFlexibleDirection(wxBOTH);
	Grilla_Exterior_Loguin->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

	wxBoxSizer* Grilla_Interior_Usuario = new wxBoxSizer(wxVERTICAL);

	Label_Estatica_Usuario = new wxStaticText(this, wxID_ANY, ("Ingrese Su Usuario"), wxPoint(0, 0), wxSize(250, 20), wxALIGN_CENTRE);
	Label_Estatica_Usuario->Wrap(250);
	Grilla_Interior_Usuario->Add(Label_Estatica_Usuario, 0, wxALL, 5);

	Login_Usuario_ingresado = new wxTextCtrl(this, wxID_ANY, (""), wxPoint(2, 2), wxSize(250, 25), wxTE_CENTRE);
	Grilla_Interior_Usuario->Add(Login_Usuario_ingresado, 0, wxALL, 5);

	Grilla_Exterior_Loguin->Add(Grilla_Interior_Usuario, wxGBPosition(7, 30), wxGBSpan(1, 1), wxEXPAND, 5);

	wxBoxSizer* Grilla_Interior_Contrasenia = new wxBoxSizer(wxVERTICAL);

	Label_Estatica_Contrasenia = new wxStaticText(this, wxID_ANY, "Escriba La Contraseña", wxPoint(0, 2), wxSize(250, 20), wxALIGN_CENTRE);
	Label_Estatica_Contrasenia->Wrap(250);
	Grilla_Interior_Contrasenia->Add(Label_Estatica_Contrasenia, 0, wxALL, 5);

	Login_Contrasenia_ingresado = new wxTextCtrl(this, wxID_ANY, (""), wxPoint(1, 1), wxSize(250, 25), wxTE_CENTRE | wxTE_PASSWORD);
	Grilla_Interior_Contrasenia->Add(Login_Contrasenia_ingresado, 0, wxALL, 5);

	Grilla_Exterior_Loguin->Add(Grilla_Interior_Contrasenia, wxGBPosition(11, 30), wxGBSpan(1, 1), wxEXPAND, 5);

	B_Ingresar = new wxButton(this, wxID_ANY, ("Ingresar"), wxDefaultPosition, wxDefaultSize, 0);
	B_Ingresar->SetMinSize(wxSize(250, 30));

	Grilla_Exterior_Loguin->Add(B_Ingresar, wxGBPosition(15, 30), wxGBSpan(1, 1), wxALL, 5);

	this->SetSizer(Grilla_Exterior_Loguin);
	this->Layout();

	this->Centre(wxBOTH);

	// Bindeo de funciones a botones
	B_Ingresar -> Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(Login_GUI::Check), NULL, this);
}

Login_GUI::~Login_GUI()
{
	// desbindeo de funciones a botones
	B_Ingresar->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(Login_GUI::Check), NULL, this);
}

void Login_GUI::Check(wxCommandEvent& event)
{

	// Obtener los valores ingresados por el usuario
	wxString usuario = Login_Usuario_ingresado->GetValue();
	wxString contrasenia = Login_Contrasenia_ingresado->GetValue();
	bool noencontrado = true;

	vector<Usuario> usuarios; //creacion de vector de struc usuario
	ifstream file("Credenciales.dat", std::ios::binary);//se abre archivo en formato lectura y binario
	if (file.is_open()) {
		Usuario usuario;
		while (file.read(reinterpret_cast<char*>(&usuario), sizeof(Usuario))) {
			usuarios.push_back(usuario);//mientras la lectura sea posible se agrega al final del vector
		}
		file.close();
	}
	else {
		cerr << "Error al abrir el archivo para lectura.";
	}


	for (vector<Usuario>::iterator it = usuarios.begin(); it != usuarios.end(); ++it) { //se recorre el vector de credencials 
		if(usuario == it->Usuario && it->contrasena == contrasenia) //se comparan las credenciales
		{
			noencontrado = false;
			wxMessageBox("¡Ingreso exitoso!", "Login", wxOK | wxICON_INFORMATION);
			//abre la ventana main
			esAdmin = true;
			Main_GUI* mainWindow = new Main_GUI(NULL);
			mainWindow->Show();
			this->Close();  // Cierra la ventana de login
		}
	}
	if (noencontrado)
	{
		wxMessageBox("Usuario o contraseña incorrectos", "Error", wxOK | wxICON_ERROR);
	}
}