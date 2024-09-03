
#include "Main_GUI.h"
#include "Agregar_Usuario.h"
#include "Loguin_GUI.h"


using namespace std;

// Implementación de Main_GUI

Main_GUI::Main_GUI(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style) :wxFrame(parent, id, title, pos, size, style)
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

	b_AgregarUser = new wxButton(this, wxID_ANY, wxT("Registrar Usuario"), wxDefaultPosition, wxDefaultSize, 0);
	Grilla_Interior_Linea2->Add(b_AgregarUser, 0, wxALL, 5);

	Grilla_Interior_Gral->Add(Grilla_Interior_Linea2, 1, wxEXPAND, 5);

	wxBoxSizer* Grilla_Interior_Linea3 = new wxBoxSizer(wxVERTICAL);
	b_fav = new wxButton(this, wxID_ANY, ("Ver Lista de Favoritos"), wxPoint(-1, -1), wxDefaultSize, wxBU_EXACTFIT);
	Grilla_Interior_Linea3->Add(b_fav, 0, wxALL, 5);

	Grilla_Interior_Gral->Add(Grilla_Interior_Linea3, 1, wxEXPAND, 5);

	Libros_listBox = new wxListBox(this, wxID_ANY, wxDefaultPosition, wxSize(500, 500), 0, NULL, 0);
	Grilla_Interior_Gral->Add(Libros_listBox, 0, wxALL, 5);

	Grilla_Exterior_Main->Add(Grilla_Interior_Gral, 1, wxEXPAND, 5);

	this->SetSizer(Grilla_Exterior_Main);
	this->Layout();

	this->Centre(wxBOTH);

	// Bindeo de funciones a botones
	b_AgregarUser->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(Main_GUI::Registrar), NULL, this);
	if (!(esAdmin)) {

		b_aniadir->Show(false);
		b_modificar->Show(false);
		b_borrar->Show(false);
		b_AgregarUser->Show(false);


	}
}

Main_GUI::~Main_GUI()
{
	b_AgregarUser->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(Main_GUI::Registrar), NULL, this);
}
void Main_GUI::Registrar(wxCommandEvent& event) {
	//abre Ventana Agregar usuario y cierra main
	Agregar_Usuario* mainWindow = new Agregar_Usuario(NULL);
	mainWindow->Show();
	this->Close();
}