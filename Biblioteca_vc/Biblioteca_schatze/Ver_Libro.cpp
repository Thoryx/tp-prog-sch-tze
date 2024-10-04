#include "Ver_Libro.h"
#include "Main_GUI.h"
#include "Favorites.h"
#include "Books.h"
#include <fstream>
#include <vector>

enum {
    ID_Back = wxID_HIGHEST + 1
};

wxBEGIN_EVENT_TABLE(Ver_Libro, wxFrame)
EVT_BUTTON(ID_Back, Ver_Libro::OnBack)
wxEND_EVENT_TABLE()

Ver_Libro::Ver_Libro(const wxString& title, bool isAdmin, const wxString& activeUser, const int& seleccion, const char& panel_p)
    : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(400, 400)), userIsAdmin(isAdmin), ActiveUser(activeUser), selection(seleccion), panel_padre(panel_p) {

    wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);

    // Ajustar estilo de fuente y tamaño
    wxFont fontTitulo(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    wxFont fontNormal(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);

    // Crear los controles como miembros de la clase
    Titulo = new wxStaticText(this, wxID_ANY, wxT(""));
    Titulo->SetFont(fontTitulo);  // Aumentar tamaño de fuente del título

    Autor = new wxStaticText(this, wxID_ANY, wxT(""));
    Autor->SetFont(fontNormal);

    Genero = new wxStaticText(this, wxID_ANY, wxT(""));
    Genero->SetFont(fontNormal);

    anio = new wxStaticText(this, wxID_ANY, wxT(""));
    anio->SetFont(fontNormal);

    backButton = new wxButton(this, ID_Back, "Volver", wxDefaultPosition, wxSize(150, 40));

    SetLabels();

    // Establecer color de fondo
    SetBackgroundColour(wxColour(242, 230, 214));

    // Establecer el ícono
    wxIcon icon;
    icon.LoadFile("Icono.ico", wxBITMAP_TYPE_ICO);
    SetIcon(icon);

    // Añadir los controles al sizer con margen y centrado
    vbox->Add(Titulo, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 20);
    vbox->Add(Autor, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 10);
    vbox->Add(Genero, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 10);
    vbox->Add(anio, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 10);
    vbox->Add(backButton, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 20);

    SetSizer(vbox);  // Establecer el sizer para la ventana
}

std::vector<Book> Ver_Libro::LoadBooks() {
    std::vector<Book> books;
    std::ifstream file("books.dat", std::ios::binary);
    if (!file) return books;

    Book book;
    while (file.read(reinterpret_cast<char*>(&book), sizeof(Book))) {
        books.push_back(book);
    }
    file.close();
    return books;
}

void Ver_Libro::SetLabels() {
    if (selection != wxNOT_FOUND) {
        std::vector<Book> books = LoadBooks();
        if (!books.empty() && selection < books.size()) {
            const Book& selectedBook = books[selection];
            Titulo->SetLabel("Titulo: "+ wxString(selectedBook.title));
            Autor->SetLabel("Autor: " + wxString(selectedBook.author));
            Genero->SetLabel("Genero: " + wxString(selectedBook.genre));
            anio->SetLabel("Año de publicacion: " + wxString::Format(wxT("%d"), selectedBook.year));
        }
        else {
            // Si no se encuentra el libro, muestra un mensaje por defecto
            Titulo->SetLabel("Título no encontrado");
            Autor->SetLabel("Autor no encontrado");
            Genero->SetLabel("Género no encontrado");
            anio->SetLabel("Año no encontrado");
        }
    }
}

void Ver_Libro::OnBack(wxCommandEvent& event) {
    if (panel_padre == 'M') {
        wxFrame* mainWindow = new Main_GUI("Main Window", userIsAdmin, ActiveUser);  // Crear instancia de Main_GUI
        mainWindow->Show();
        this->Close();
    }
    else {
        wxFrame* mainWindow = new FavoritesWindow("Favorites", userIsAdmin, ActiveUser);  // Crear instancia de Main_GUI
        mainWindow->Show();
        this->Close();

    }
}
