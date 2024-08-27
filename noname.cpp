#include <vector> //manejo vectores
//librerias de flujos de datos//
#include <iostream>//
#include <fstream>//
/////////////////
#include <iterator> //libreria para manejo de iteradores
using namespace std;

//Struct data para manejo de usuarios
struct Usuario {
	char Usuario[50];
	char contrasena[50];
	char rol[4];
};

#include "noname.h"//se incluye cabecera con las declaraciones de objetos y funciones

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
	
	Label_Estatica_Usuario = new wxStaticText(this, wxID_ANY, ("Ingrese Su Usuario"), wxPoint(0,0), wxSize(250,20), wxALIGN_CENTRE);
	Label_Estatica_Usuario->Wrap(250);
	Grilla_Interior_Usuario->Add(Label_Estatica_Usuario, 0, wxALL, 5);
	
	Login_Usuario_ingresado = new wxTextCtrl(this, wxID_ANY, (""), wxPoint(2,2), wxSize(250,25), wxTE_CENTRE);
	Grilla_Interior_Usuario->Add(Login_Usuario_ingresado, 0, wxALL, 5);
	
	Grilla_Exterior_Loguin->Add(Grilla_Interior_Usuario, wxGBPosition(7, 30), wxGBSpan(1, 1), wxEXPAND, 5);
	
	wxBoxSizer*  Grilla_Interior_Contrasenia = new wxBoxSizer(wxVERTICAL);
	
	Label_Estatica_Contrasenia = new wxStaticText(this, wxID_ANY, "Escriba La Contraseña", wxPoint(0,2), wxSize(250,20), wxALIGN_CENTRE);
	Label_Estatica_Contrasenia->Wrap(250);
	Grilla_Interior_Contrasenia->Add(Label_Estatica_Contrasenia, 0, wxALL, 5);
	
	Login_Contrasenia_ingresado = new wxTextCtrl(this, wxID_ANY, (""), wxPoint(1,1), wxSize(250,25), wxTE_CENTRE | wxTE_PASSWORD);
	Grilla_Interior_Contrasenia->Add(Login_Contrasenia_ingresado, 0, wxALL, 5);
	
	Grilla_Exterior_Loguin->Add(Grilla_Interior_Contrasenia, wxGBPosition(11, 30), wxGBSpan(1, 1), wxEXPAND, 5);
	
	B_Ingresar = new wxButton(this, wxID_ANY, ("Ingresar"), wxDefaultPosition, wxDefaultSize, 0);
	B_Ingresar->SetMinSize(wxSize(250,30));
	
	Grilla_Exterior_Loguin->Add(B_Ingresar, wxGBPosition(15, 30), wxGBSpan(1, 1), wxALL, 5);
	
	this->SetSizer(Grilla_Exterior_Loguin);
	this->Layout();
	
	this->Centre(wxBOTH);
	
	// Bindeo de funciones a botones
	B_Ingresar->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(Login_GUI::Check), NULL, this);
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
	} else {
		cerr << "Error al abrir el archivo para lectura.";
	}
	
	
	for( vector<Usuario>::iterator it=usuarios.begin(); it!=usuarios.end(); ++it ) { //se recorre el vector de credencials 
		if (usuario == it->Usuario && it->contrasena == contrasenia) //se comparan las credenciales
		{
			noencontrado=false;
			wxMessageBox("¡Ingreso exitoso!", "Login", wxOK | wxICON_INFORMATION);
			//abre la ventana main
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

// Implementación de Main_GUI

Main_GUI::Main_GUI(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style)
	: wxFrame(parent, id, title, pos, size, style)
{//Configuraciones de labels y botones
	this->SetSizeHints(wxDefaultSize, wxDefaultSize);
	wxFlexGridSizer* Grilla_Exterior_Main = new wxFlexGridSizer(1, 1, 0, 0);
	Grilla_Exterior_Main->SetFlexibleDirection(wxBOTH);
	Grilla_Exterior_Main->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);
	
	wxBoxSizer* Grilla_Interior_Gral = new wxBoxSizer(wxVERTICAL);
	
	wxBoxSizer* Grilla_Interior_Linea1 = new wxBoxSizer(wxHORIZONTAL);
	
	b_busqueda = new wxButton(this, wxID_ANY, ("Buscar Libro"), wxDefaultPosition, wxDefaultSize, 0);
	Grilla_Interior_Linea1->Add(b_busqueda, 0, wxALL, 5);
	
	b_detalles = new wxButton(this, wxID_ANY, ("Ver Detalles"), wxDefaultPosition, wxDefaultSize, 0);
	Grilla_Interior_Linea1->Add(b_detalles, 0, wxALL, 5);
	
	b_agregar_fav = new wxButton(this, wxID_ANY, ("Añadir a Favoritos"), wxDefaultPosition, wxDefaultSize, 0);
	Grilla_Interior_Linea1->Add(b_agregar_fav, 0, wxALL, 5);
	

	Grilla_Interior_Gral->Add(Grilla_Interior_Linea1, 1, wxEXPAND, 5);
	
	wxBoxSizer* Grilla_Interior_Linea2 = new wxBoxSizer(wxHORIZONTAL);
	
	b_aniadir = new wxButton(this, wxID_ANY, ("Añadir Libro"), wxDefaultPosition, wxDefaultSize, 0);
	Grilla_Interior_Linea2->Add(b_aniadir, 0, wxALL, 5);
	
	b_modificar = new wxButton(this, wxID_ANY, ("Modificar Libro"), wxDefaultPosition, wxDefaultSize, 0);
	Grilla_Interior_Linea2->Add(b_modificar, 0, wxALL, 5);
	
	b_borrar = new wxButton(this, wxID_ANY, ("Borrar Libro"), wxDefaultPosition, wxDefaultSize, 0);
	Grilla_Interior_Linea2->Add(b_borrar, 0, wxALL, 5);
	
	b_AgregarUser = new wxButton( this, wxID_ANY, wxT("Registrar Usuario"), wxDefaultPosition, wxDefaultSize, 0 );
	Grilla_Interior_Linea2->Add( b_AgregarUser, 0, wxALL, 5 );
	
	Grilla_Interior_Gral->Add(Grilla_Interior_Linea2, 1, wxEXPAND, 5);
	
	wxBoxSizer* Grilla_Interior_Linea3 = new wxBoxSizer(wxVERTICAL);
	
	b_fav = new wxButton(this, wxID_ANY, ("Ver Lista de Favoritos"), wxPoint(-1,-1), wxDefaultSize, wxBU_EXACTFIT);
	Grilla_Interior_Linea3->Add(b_fav, 0, wxALL, 5);
	
	Grilla_Interior_Gral->Add(Grilla_Interior_Linea3, 1, wxEXPAND, 5);
	
	Libros_listBox = new wxListBox( this, wxID_ANY, wxDefaultPosition, wxSize( 500,500 ), 0, NULL, 0 ); 
	Grilla_Interior_Gral->Add( Libros_listBox, 0, wxALL, 5 );
	
	Grilla_Exterior_Main->Add(Grilla_Interior_Gral, 1, wxEXPAND, 5);
	
	this->SetSizer(Grilla_Exterior_Main);
	this->Layout();
	
	this->Centre(wxBOTH);
	
	// Bindeo de funciones a botones
	b_AgregarUser->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(Main_GUI::Registrar), NULL, this);
}

Main_GUI::~Main_GUI()
{
	b_AgregarUser->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(Main_GUI::Registrar), NULL, this);
}
void Main_GUI::Registrar(wxCommandEvent& event){
	//abre Ventana Agregar usuario y cierra main
	Agregar_Usuario* mainWindow = new Agregar_Usuario(NULL);
	mainWindow->Show();
	this->Close();
}

//implementacion ventana Agregar_Usuario
Agregar_Usuario::Agregar_Usuario( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* Grilla_Exterior_Agregar;
	Grilla_Exterior_Agregar = new wxBoxSizer( wxVERTICAL );
	
	Label_Estatica_Agregar_Usuario = new wxStaticText( this, wxID_ANY, wxT("Ingrese Su Usuario"), wxPoint( 0,0 ), wxSize( 250,20 ), wxALIGN_CENTRE );
	Label_Estatica_Agregar_Usuario->Wrap( 250 );
	Grilla_Exterior_Agregar->Add( Label_Estatica_Agregar_Usuario, 0, wxALL, 5 );
	
	Agregar_Usuario_Ingresado = new wxTextCtrl( this, wxID_ANY, wxT(""), wxPoint( 2,2 ), wxSize( 250,25 ), wxTE_CENTRE );
	Grilla_Exterior_Agregar->Add( Agregar_Usuario_Ingresado, 0, wxALL, 5 );
	
	Label_Estatica_Agregar_Contrasenia = new wxStaticText( this, wxID_ANY, "Escriba La Contraseña", wxPoint( 0,2 ), wxSize( 250,20 ), wxALIGN_CENTRE );
	Label_Estatica_Agregar_Contrasenia->Wrap( 250 );
	Grilla_Exterior_Agregar->Add( Label_Estatica_Agregar_Contrasenia, 0, wxALL, 5 );
	
	Agregar_Contrasenia_Ingresado = new wxTextCtrl( this, wxID_ANY, wxT(""), wxPoint( 1,1 ), wxSize( 250,25 ), wxTE_CENTRE | wxTE_PASSWORD);
	Grilla_Exterior_Agregar->Add( Agregar_Contrasenia_Ingresado, 0, wxALL, 5 );
	
	
	Label_Estatica_Agregar_Role = new wxStaticText( this, wxID_ANY, wxT("Ingrese El Rol (User/Adm)"), wxPoint( 0,2 ), wxSize( 250,20 ), wxALIGN_CENTRE );
	Label_Estatica_Agregar_Role->Wrap( 250 );
	Grilla_Exterior_Agregar->Add( Label_Estatica_Agregar_Role, 0, wxALL, 5 );
	
	Agregar_Role_Ingresado = new wxTextCtrl( this, wxID_ANY, wxT(""), wxPoint( 1,1 ), wxSize( 250,25 ), wxTE_CENTRE );
	Grilla_Exterior_Agregar->Add( Agregar_Role_Ingresado, 0, wxALL, 5 );
	
	wxBoxSizer* Grilla_Interior_Botones_Agregar;
	Grilla_Interior_Botones_Agregar = new wxBoxSizer( wxHORIZONTAL );
	
	B_Agregar = new wxButton( this, wxID_ANY, wxT("Ingresar"), wxDefaultPosition, wxDefaultSize, 0 );
	B_Agregar->SetMinSize( wxSize( 250,30 ) );
	
	B_Volver = new wxButton( this, wxID_ANY, wxT("Volver"), wxDefaultPosition, wxDefaultSize, 0 );
	B_Volver->SetMinSize( wxSize( 250,30 ) );
	
	
	Grilla_Interior_Botones_Agregar->Add( B_Agregar, 1, wxALL, 5 );
	Grilla_Interior_Botones_Agregar->Add( B_Volver, 1, wxALL, 5 );
	
	Grilla_Exterior_Agregar->Add( Grilla_Interior_Botones_Agregar, 0, wxALL, 5 );
	
	
	
	
	
	this->SetSizer( Grilla_Exterior_Agregar );
	this->Layout();
	this->Centre( wxBOTH );
	
	
	B_Agregar->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( Agregar_Usuario::Agregar ), NULL, this );
	B_Volver->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( Agregar_Usuario::Volver ), NULL, this );
}

Agregar_Usuario::~Agregar_Usuario()
{
	
	B_Agregar->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( Agregar_Usuario::Agregar ), NULL, this );
	B_Volver->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( Agregar_Usuario::Volver ), NULL, this );
	
}
void Agregar_Usuario::Agregar(wxCommandEvent& event){
	
	
	//a implementar
	
	
	//cierra ventana y vuelve a main
	Main_GUI* mainWindow = new Main_GUI(NULL);
	mainWindow->Show();
	this->Close();
}
void Agregar_Usuario::Volver(wxCommandEvent& event){
	
	Main_GUI* mainWindow = new Main_GUI(NULL);
	mainWindow->Show();
	this->Close();
}
