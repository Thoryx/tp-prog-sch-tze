#include "Favorites.h"
#include "Main_GUI.h"
#include "Ver_Libro.h"
#include "Books.h"
#include <fstream>

// Identificadores de eventos
enum {
    ID_BackToMain = 1,
    ID_ViewBookDetails
};

wxBEGIN_EVENT_TABLE(FavoritesWindow, wxFrame)
EVT_BUTTON(ID_BackToMain, FavoritesWindow::OnBackToMain)
EVT_BUTTON(ID_ViewBookDetails, FavoritesWindow::OnViewBookDetails)
wxEND_EVENT_TABLE()

FavoritesWindow::FavoritesWindow(const wxString& title, bool isAdmin, const wxString& activeUser)
    : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(400, 300)),
    userIsAdmin(isAdmin), ActiveUser(activeUser) {
    wxIcon icon;
    icon.LoadFile("Icono.ico", wxBITMAP_TYPE_ICO);
    SetIcon(icon);
    SetBackgroundColour(wxColour(242, 230, 214));

    // Crear un sizer vertical
    wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);

    // Crear el wxListBox para mostrar los libros
    bookList = new wxListBox(this, wxID_ANY);
    vbox->Add(bookList, 1, wxEXPAND | wxALL, 10);

    // Establecer el sizer
    SetSizer(vbox);

    // Cargar los libros favoritos del usuario
    LoadFavorites(activeUser);

    wxButton* backButton = new wxButton(this, ID_BackToMain, wxT("Volver a la ventana principal"));
    viewBookDetailsBtn = new wxButton(this, ID_ViewBookDetails, wxT("Ver detalles del libro"));

    vbox->Add(backButton, 0, wxRIGHT, 5);
    vbox->Add(viewBookDetailsBtn, 0, wxALL | wxEXPAND, 10);
}

void FavoritesWindow::LoadFavorites(const wxString& activeUser) {
    std::vector<Book> favorites;

    // Ruta del archivo de favoritos
    wxString filePath = wxString::Format("Listas/favorites_%s.dat", activeUser);
    std::ifstream file(filePath.ToStdString(), std::ios::binary);

    if (!file) {
        wxMessageBox("No se pudo abrir el archivo de favoritos.", "Error", wxOK | wxICON_ERROR);
        return;
    }

    Book book;
    while (file.read(reinterpret_cast<char*>(&book), sizeof(Book))) {
        favorites.push_back(book);
    }
    file.close();

    // Llenar el wxListBox con los títulos de los libros favoritos
    for (const auto& book : favorites) {
        bookList->Append(wxString(book.title));
    }

    // Actualizar el título de la ventana con la cantidad de favoritos
    SetTitle(wxString::Format("Favoritos (%d)", favorites.size()));
}
void FavoritesWindow::OnBackToMain(wxCommandEvent& event) {
    wxFrame* mainWindow = new Main_GUI("Main Window", userIsAdmin, ActiveUser);  // Crear instancia de Main_GUI
    mainWindow->Show();
    this->Close();  // Cerrar la ventana actual (Books)
}
void FavoritesWindow::OnViewBookDetails(wxCommandEvent& event) {
    OnSelectBook();
    
    wxFrame* mainWindow = new Ver_Libro("Ver Detalles", userIsAdmin, ActiveUser, BookSelected, 'F');
    mainWindow->Show();
    this->Close();
}
std::vector<Book> FavoritesWindow::LoadBooks() {
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
void FavoritesWindow::OnSelectBook() {
    int selection = bookList->GetSelection();  // Obtén el índice seleccionado en el control de la lista

    if (selection != wxNOT_FOUND) {  // Verifica que haya una selección válida
        std::vector<Book> books = LoadBooks();  // Carga los libros desde el archivo o fuente

        // Recorre el vector de libros
        for (size_t i = 0; i < books.size(); ++i) {
            if (i == selection) {  // Si el índice coincide con la selección
                // Pasa el índice encontrado a la función set_TitleDetails o haz otra acción
                set_BookSelected(i);
                break;  // Detén el bucle una vez encontrado el índice correspondiente
            }
        }
    }
}