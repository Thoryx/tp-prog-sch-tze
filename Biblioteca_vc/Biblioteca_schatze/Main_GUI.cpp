
#include "Books.h"
#include "GestionarUser.h"
#include "Main_GUI.h"
#include "Ver_Libro.h"
#include "fstream"
#include "Favorites.h"
#define DATA_FILE "Books.dat"

//auto id para gestionar eventos
enum {
    ID_ViewBookDetails = 1,
    ID_SearchBook,
    ID_AddToFavorites,
    ID_ViewFavorites,
    ID_ManageBooks,
    ID_ManageUsers,
    ID_BookList
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
    : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(800, 600)),
    userIsAdmin(isAdmin), ActiveUser(activeUser){

    wxPanel* panel = new wxPanel(this, wxID_ANY);

    SetBackgroundColour(wxColour(242, 230, 214));
    // Establecer el ícono de la ventana
    wxIcon icon;
    icon.LoadFile("Icono.ico", wxBITMAP_TYPE_ICO);
    SetIcon(icon);

    // Sizer principal para la disposición vertical de los botones
    wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);

    

    // Si el usuario es administrador, agregamos los botones de gestión
    if (userIsAdmin) {
        manageBooksBtn = new wxButton(panel, ID_ManageBooks, wxT("Gestionar libros"));
        manageUsersBtn = new wxButton(panel, ID_ManageUsers, wxT("Gestionar usuarios"));

        vbox->Add(manageBooksBtn, 0, wxALL | wxEXPAND, 10);
        vbox->Add(manageUsersBtn, 0, wxALL | wxEXPAND, 10);
       
    }
    else {
        // Botones para todos los usuarios
        viewBookDetailsBtn = new wxButton(panel, ID_ViewBookDetails, wxT("Ver detalles del libro"));
        searchBookBtn = new wxButton(panel, ID_SearchBook, wxT("Buscar un libro"));
        addToFavoritesBtn = new wxButton(panel, ID_AddToFavorites, wxT("Agregar a favoritos"));
        viewFavoritesBtn = new wxButton(panel, ID_ViewFavorites, wxT("Ver lista de favoritos"));
        statusText = new wxStaticText(panel, wxID_ANY, wxT(""), wxDefaultPosition, wxSize(250, 25));
        

        // Añadir los botones al sizer
        vbox->Add(viewBookDetailsBtn, 0, wxALL | wxEXPAND, 10);
        vbox->Add(searchBookBtn, 0, wxALL | wxEXPAND, 10);
        vbox->Add(addToFavoritesBtn, 0, wxALL | wxEXPAND, 10);
        vbox->Add(viewFavoritesBtn, 0, wxALL | wxEXPAND, 10);
        vbox->Add(statusText, 0, wxALIGN_CENTER | wxTOP, 10);
    }

    // Lista de libros
  
        
    if  (!userIsAdmin) {
        bookList = new wxListBox(panel, ID_BookList);
        vbox->Add(bookList, 1, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 10);

        // Cargar los libros desde el archivo
        std::vector<Book> books = LoadBooks();
        for (const auto& book : books) {
            bookList->Append(wxString(book.title));
        }
    }

    // Establecer el sizer al panel
    panel->SetSizer(vbox);

    // Centrar la ventana en pantalla
    Centre();
}

void Main_GUI::OnViewBookDetails(wxCommandEvent& event) {
    OnSelectBook();
    wxFrame* mainWindow = new Ver_Libro("Ver detalles", userIsAdmin, ActiveUser , BookSelected,'M');
    mainWindow->Show();
    this->Close();
}

void Main_GUI::OnSearchBook(wxCommandEvent& event) {
    //En Progreso
}

void Main_GUI::OnAddToFavorites(wxCommandEvent& event) {
    int selection = bookList->GetSelection();
    if (selection != wxNOT_FOUND) {
        // Cargar los libros favoritos actuales del usuario
        std::vector<Book> favorites = LoadFavorites(ActiveUser);

        // Cargar el libro seleccionado
        std::vector<Book> books = LoadBooks();
        if (selection < books.size()) {
            Book favoriteBook = books[selection];

            // Verificar si el libro ya está en favoritos
            bool alreadyInFavorites = false;
            for (const auto& favBook : favorites) {
                if (strcmp(favBook.title, favoriteBook.title) == 0 &&
                    strcmp(favBook.author, favoriteBook.author) == 0) {
                    alreadyInFavorites = true;
                    break;
                }
            }

            if (!alreadyInFavorites) {
                // Añadir el libro a favoritos
                favorites.push_back(favoriteBook);
                SaveFavorites(favorites, ActiveUser);

                // Mostrar mensaje de éxito
                statusText->SetLabel("¡Libro añadido a favoritos!");
            }
            else {
                statusText->SetLabel("Este libro ya está en tus favoritos.");
            }
        }
    }
    else {
        statusText->SetLabel("No se ha seleccionado ningún libro.");
    }
}


void Main_GUI::OnViewFavorites(wxCommandEvent& event) {
    wxFrame* mainWindow = new FavoritesWindow("Favoritos", userIsAdmin, ActiveUser);
    mainWindow->Show();
    this->Close();
}

void Main_GUI::OnManageBooks(wxCommandEvent& event) {
    wxFrame* mainWindow = new Books("Gestor Libros", userIsAdmin, ActiveUser);
    mainWindow->Show();
    this->Close();
}

void Main_GUI::OnManageUsers(wxCommandEvent& event) {
    wxFrame* mainWindow = new GestionarUser("Gestor Usuarios", userIsAdmin, ActiveUser);
    mainWindow->Show();
    this->Close();
}

std::vector<Book> Main_GUI::LoadBooks() {
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

void Main_GUI::OnSelectBook() {
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

std::vector<Book> Main_GUI::LoadFavorites(const wxString& username) {
    std::vector<Book> favorites;
    wxString filePath = wxString::Format("Listas/favorites_%s.dat", username);
    std::ifstream file(filePath.ToStdString(), std::ios::binary);

    if (!file) {
        return favorites;  // Devuelve un vector vacío si no existe el archivo
    }

    Book book;
    while (file.read(reinterpret_cast<char*>(&book), sizeof(Book))) {
        favorites.push_back(book);
    }
    file.close();
    return favorites;
}

void Main_GUI::SaveFavorites(const std::vector<Book>& favorites, const wxString& username) {
    // Cargar libros favoritos existentes
    std::vector<Book> existingFavorites = LoadFavorites(username);

    // Verificar si el nuevo libro ya está en la lista
    for (const auto& favorite : existingFavorites) {
        if (strcmp(favorite.title, favorites.back().title) == 0) {  // Comparar por título
            wxMessageBox("Este libro ya está en la lista de favoritos.", "Duplicado", wxOK | wxICON_WARNING);
            return; // Salir si ya existe
        }
    }

    // Agregar el nuevo libro a la lista de favoritos
    existingFavorites.push_back(favorites.back());

    // Guardar la lista actualizada
    std::ofstream file("Listas/favorites_" + username.ToStdString() + ".dat", std::ios::binary | std::ios::trunc);
    if (!file) {
        wxLogError("Error al abrir el archivo de favoritos para guardar.");
        return;
    }

    for (const auto& book : existingFavorites) {
        file.write(reinterpret_cast<const char*>(&book), sizeof(Book));
    }
    file.close();
}

