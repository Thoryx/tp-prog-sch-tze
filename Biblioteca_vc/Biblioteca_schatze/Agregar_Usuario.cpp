#include <vector> //manejo vectores
//librerias de flujos de datos//
#include <iostream>//
#include <fstream>//
/////////////////
#include <cstring> // Para usar strcpy
#include "Agregar_Usuario.h"//se incluye cabecera con las declaraciones de objetos y funciones
#include "Main_GUI.h"

using namespace std;

//Struct data para manejo de usuarios
struct Usuario {
	char Usuario[50];
	char contrasena[50];
	char rol[4];
};



//implementacion ventana Agregar_Usuario
Agregar_Usuario::Agregar_Usuario(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style) : wxFrame(parent, id, title, pos, size, style)
{
	this->SetSizeHints(wxDefaultSize, wxDefaultSize);

	wxBoxSizer* Grilla_Exterior_Agregar;
	Grilla_Exterior_Agregar = new wxBoxSizer(wxVERTICAL);

	Label_Estatica_Agregar_Usuario = new wxStaticText(this, wxID_ANY, wxT("Ingrese Su Usuario"), wxPoint(0, 0), wxSize(250, 20), wxALIGN_CENTRE);
	Label_Estatica_Agregar_Usuario->Wrap(250);
	Grilla_Exterior_Agregar->Add(Label_Estatica_Agregar_Usuario, 0, wxALL, 5);

	Agregar_Usuario_Ingresado = new wxTextCtrl(this, wxID_ANY, wxT(""), wxPoint(2, 2), wxSize(250, 25), wxTE_CENTRE);
	Grilla_Exterior_Agregar->Add(Agregar_Usuario_Ingresado, 0, wxALL, 5);

	Label_Estatica_Agregar_Contrasenia = new wxStaticText(this, wxID_ANY, "Escriba La Contraseña", wxPoint(0, 2), wxSize(250, 20), wxALIGN_CENTRE);
	Label_Estatica_Agregar_Contrasenia->Wrap(250);
	Grilla_Exterior_Agregar->Add(Label_Estatica_Agregar_Contrasenia, 0, wxALL, 5);

	Agregar_Contrasenia_Ingresado = new wxTextCtrl(this, wxID_ANY, wxT(""), wxPoint(1, 1), wxSize(250, 25), wxTE_CENTRE | wxTE_PASSWORD);
	Grilla_Exterior_Agregar->Add(Agregar_Contrasenia_Ingresado, 0, wxALL, 5);


	Label_Estatica_Agregar_Role = new wxStaticText(this, wxID_ANY, wxT("Ingrese El Rol (User/Adm)"), wxPoint(0, 2), wxSize(250, 20), wxALIGN_CENTRE);
	Label_Estatica_Agregar_Role->Wrap(250);
	Grilla_Exterior_Agregar->Add(Label_Estatica_Agregar_Role, 0, wxALL, 5);

	Agregar_Role_Ingresado = new wxTextCtrl(this, wxID_ANY, wxT(""), wxPoint(1, 1), wxSize(250, 25), wxTE_CENTRE);
	Grilla_Exterior_Agregar->Add(Agregar_Role_Ingresado, 0, wxALL, 5);

	wxBoxSizer* Grilla_Interior_Botones_Agregar;
	Grilla_Interior_Botones_Agregar = new wxBoxSizer(wxHORIZONTAL);

	B_Agregar = new wxButton(this, wxID_ANY, wxT("Ingresar"), wxDefaultPosition, wxDefaultSize, 0);
	B_Agregar->SetMinSize(wxSize(250, 30));

	B_Volver = new wxButton(this, wxID_ANY, wxT("Volver"), wxDefaultPosition, wxDefaultSize, 0);
	B_Volver->SetMinSize(wxSize(250, 30));


	Grilla_Interior_Botones_Agregar->Add(B_Agregar, 1, wxALL, 5);
	Grilla_Interior_Botones_Agregar->Add(B_Volver, 1, wxALL, 5);

	Grilla_Exterior_Agregar->Add(Grilla_Interior_Botones_Agregar, 0, wxALL, 5);





	this->SetSizer(Grilla_Exterior_Agregar);
	this->Layout();
	this->Centre(wxBOTH);


	B_Agregar->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(Agregar_Usuario::Agregar), NULL, this);
	B_Volver->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(Agregar_Usuario::Volver), NULL, this);
}

Agregar_Usuario::~Agregar_Usuario()
{

	B_Agregar->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(Agregar_Usuario::Agregar), NULL, this);
	B_Volver->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(Agregar_Usuario::Volver), NULL, this);

}
void Agregar_Usuario::Agregar(wxCommandEvent& event) {


	wxString usuario = Agregar_Usuario_Ingresado->GetValue();
	wxString contrasenia = Agregar_Contrasenia_Ingresado->GetValue();
	wxString rol = Agregar_Role_Ingresado->GetValue();



	vector<Usuario> Usuarios;
	string filename = "Credenciales.dat";

	// Abrir y cargar usuarios existentes desde el archivo binario
	ifstream fileIn(filename, std::ios::binary);

	if (fileIn.is_open()) {
		Usuario tempUser;
		while (fileIn.read(reinterpret_cast<char*>(&tempUser), sizeof(Usuario))) {
			Usuarios.push_back(tempUser);
		}
		fileIn.close();
	}

	// Crear un nuevo usuario con los datos proporcionados
	Usuario nuevoUsuario;
	strcpy(nuevoUsuario.Usuario, usuario.mb_str());
	strcpy(nuevoUsuario.contrasena, contrasenia.mb_str());
	strcpy(nuevoUsuario.rol, rol.mb_str());

	// Agregar el nuevo usuario al vector
	Usuarios.push_back(nuevoUsuario);

	// Guardar todos los usuarios en el archivo binario
	ofstream fileOut(filename, std::ios::binary | std::ios::trunc);

	if (fileOut.is_open()) {
		for (const auto& user : Usuarios) {
			fileOut.write(reinterpret_cast<const char*>(&user), sizeof(Usuario));
		}
		fileOut.close();
	}





	//cierra ventana y vuelve a main
	Main_GUI* mainWindow = new Main_GUI(NULL);
	mainWindow->Show();
	this->Close();
}
void Agregar_Usuario::Volver(wxCommandEvent& event) {

	Main_GUI* mainWindow = new Main_GUI(NULL);
	mainWindow->Show();
	this->Close();
}