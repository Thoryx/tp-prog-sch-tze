
#include "Main_GUI.h"
#include "GestionarUser.h"
//auto id para gestionar eventos
enum {
    ID_ViewBookDetails = 1,
    ID_SearchBook,
    ID_AddToFavorites,
    ID_ViewFavorites,
    ID_ManageBooks,
    ID_ManageUsers
};

wxBEGIN_EVENT_TABLE(Main_GUI, wxFrame)
EVT_BUTTON(ID_ViewBookDetails, Main_GUI::OnViewBookDetails)
EVT_BUTTON(ID_SearchBook, Main_GUI::OnSearchBook)
EVT_BUTTON(ID_AddToFavorites, Main_GUI::OnAddToFavorites)
EVT_BUTTON(ID_ViewFavorites, Main_GUI::OnViewFavorites)
EVT_BUTTON(ID_ManageBooks, Main_GUI::OnManageBooks)
EVT_BUTTON(ID_ManageUsers, Main_GUI::OnManageUsers)
wxEND_EVENT_TABLE()

Main_GUI::Main_GUI(const wxString& title, bool isAdmin, const wxString& activeUser)
    : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(400, 300)),
    userIsAdmin(isAdmin), ActiveUser(activeUser){

    wxPanel* panel = new wxPanel(this, wxID_ANY);

    SetBackgroundColour(wxColour(242, 230, 214));
    // Establecer el ícono de la ventana
    wxIcon icon;
    icon.LoadFile("Icono.ico", wxBITMAP_TYPE_ICO);
    SetIcon(icon);

    // Sizer principal para la disposición vertical de los botones
    wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);

    // Botones para todos los usuarios
    viewBookDetailsBtn = new wxButton(panel, ID_ViewBookDetails, wxT("Ver detalles del libro"));
    searchBookBtn = new wxButton(panel, ID_SearchBook, wxT("Buscar un libro"));
    addToFavoritesBtn = new wxButton(panel, ID_AddToFavorites, wxT("Agregar a favoritos"));
    viewFavoritesBtn = new wxButton(panel, ID_ViewFavorites, wxT("Ver lista de favoritos"));

    // Añadir los botones al sizer
    vbox->Add(viewBookDetailsBtn, 0, wxALL | wxEXPAND, 10);
    vbox->Add(searchBookBtn, 0, wxALL | wxEXPAND, 10);
    vbox->Add(addToFavoritesBtn, 0, wxALL | wxEXPAND, 10);
    vbox->Add(viewFavoritesBtn, 0, wxALL | wxEXPAND, 10);

    // Si el usuario es administrador, agregamos los botones de gestión
    if (userIsAdmin) {
        manageBooksBtn = new wxButton(panel, ID_ManageBooks, wxT("Gestionar libros"));
        manageUsersBtn = new wxButton(panel, ID_ManageUsers, wxT("Gestionar usuarios"));

        vbox->Add(manageBooksBtn, 0, wxALL | wxEXPAND, 10);
        vbox->Add(manageUsersBtn, 0, wxALL | wxEXPAND, 10);
    }

    // Establecer el sizer al panel
    panel->SetSizer(vbox);

    // Centrar la ventana en pantalla
    Centre();
}

void Main_GUI::OnViewBookDetails(wxCommandEvent& event) {
    //En Progreso
}

void Main_GUI::OnSearchBook(wxCommandEvent& event) {
    //En Progreso
}

void Main_GUI::OnAddToFavorites(wxCommandEvent& event) {
    //En Progreso
}

void Main_GUI::OnViewFavorites(wxCommandEvent& event) {
    //En Progreso
}

void Main_GUI::OnManageBooks(wxCommandEvent& event) {
    //En Progreso
}

void Main_GUI::OnManageUsers(wxCommandEvent& event) {
    wxFrame* mainWindow = new GestionarUser("Gestor Usuarios",ActiveUser);
    mainWindow->Show();
    this->Close();
}