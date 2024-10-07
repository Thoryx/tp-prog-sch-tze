#include "Books.h"
#include "GestionarUser.h"
#include "Main_GUI.h"
#include "Ver_Libro.h"
#include "fstream"
#include "Favorites.h"
#include "Busqueda.h"
#include "Loguin_GUI.h"
#define DATA_FILE "Books.dat"

// Enumeración para gestionar eventos mediante IDs
enum {
    ID_ViewBookDetails = 1,   // ID para ver detalles del libro
    ID_SearchBook,            // ID para buscar un libro
    ID_AddToFavorites,        // ID para agregar a favoritos
    ID_ViewFavorites,         // ID para ver lista de favoritos
    ID_ManageBooks,           // ID para gestionar libros
    ID_ManageUsers,           // ID para gestionar usuarios
    ID_BookList,           // ID para la lista de libros
    ID_Close               // ID para cerrar sesion
};

// Inicialización de la tabla de eventos de wxWidgets para el marco principal
wxBEGIN_EVENT_TABLE(Main_GUI, wxFrame)
EVT_BUTTON(ID_ViewBookDetails, Main_GUI::OnViewBookDetails) // Evento para ver detalles del libro
EVT_BUTTON(ID_SearchBook, Main_GUI::OnSearchBook)           // Evento para buscar un libro
EVT_BUTTON(ID_AddToFavorites, Main_GUI::OnAddToFavorites)   // Evento para agregar a favoritos
EVT_BUTTON(ID_ViewFavorites, Main_GUI::OnViewFavorites)     // Evento para ver favoritos
EVT_BUTTON(ID_ManageBooks, Main_GUI::OnManageBooks)         // Evento para gestionar libros
EVT_BUTTON(ID_ManageUsers, Main_GUI::OnManageUsers)         // Evento para gestionar usuarios
EVT_BUTTON(ID_Close, Main_GUI::OnExit)         // Evento para cerrar sesion
wxEND_EVENT_TABLE()

// Constructor del marco principal de la interfaz gráfica
Main_GUI::Main_GUI(const wxString& title, bool isAdmin, const wxString& activeUser)
    : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(800, 600)),
    userIsAdmin(isAdmin), ActiveUser(activeUser) {

    wxPanel* panel = new wxPanel(this, wxID_ANY); // Crear un nuevo panel

    // Establecer el color de fondo de la ventana
    SetBackgroundColour(wxColour(242, 230, 214));

    // Establecer el ícono de la ventana
    wxIcon icon;
    icon.LoadFile("Icono.ico", wxBITMAP_TYPE_ICO);
    SetIcon(icon);

    // Crear un sizer vertical para organizar los botones
    wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);

    // Agregar botones de gestión si el usuario es administrador
    if (userIsAdmin) {
 
        manageBooksBtn = new wxButton(panel, ID_ManageBooks, wxT("Gestionar libros")); // Botón para gestionar libros
        manageUsersBtn = new wxButton(panel, ID_ManageUsers, wxT("Gestionar usuarios")); // Botón para gestionar usuarios
        CloseSesionBtn = new wxButton(panel, ID_Close, wxT("Cerrar Sesion")); // Botón cerrar sesion
        // Añadir los botones al sizer
        vbox->Add(manageBooksBtn, 0, wxALL | wxEXPAND, 10);
        vbox->Add(manageUsersBtn, 0, wxALL | wxEXPAND, 10);
        vbox->Add(CloseSesionBtn, 0, wxALL | wxEXPAND, 10);
    }
    else {
        // Crear botones para usuarios no administradores
        viewBookDetailsBtn = new wxButton(panel, ID_ViewBookDetails, wxT("Ver detalles del libro")); // Botón para ver detalles
        searchBookBtn = new wxButton(panel, ID_SearchBook, wxT("Buscar un libro")); // Botón para buscar libros
        addToFavoritesBtn = new wxButton(panel, ID_AddToFavorites, wxT("Agregar a favoritos")); // Botón para agregar a favoritos
        viewFavoritesBtn = new wxButton(panel, ID_ViewFavorites, wxT("Ver lista de favoritos")); // Botón para ver favoritos
        CloseSesionBtn = new wxButton(panel, ID_Close, wxT("Cerrar Sesion")); // Botón cerrar sesion
        statusText = new wxStaticText(panel, wxID_ANY, wxT(""), wxDefaultPosition, wxSize(250, 25)); // Texto de estado

        // Añadir los botones al sizer
        vbox->Add(viewBookDetailsBtn, 0, wxALL | wxEXPAND, 10);
        vbox->Add(searchBookBtn, 0, wxALL | wxEXPAND, 10);
        vbox->Add(addToFavoritesBtn, 0, wxALL | wxEXPAND, 10);
        vbox->Add(viewFavoritesBtn, 0, wxALL | wxEXPAND, 10);
        vbox->Add(CloseSesionBtn, 0, wxALL | wxEXPAND, 10);
        vbox->Add(statusText, 0, wxALIGN_CENTER | wxTOP, 10); // Añadir texto de estado
    }

    // Lista de libros solo para usuarios no administradores
    if (!userIsAdmin) {
        bookList = new wxListBox(panel, ID_BookList); // Crear lista de libros
        vbox->Add(bookList, 1, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 10); // Añadir lista al sizer

        // Cargar los libros desde el archivo
        std::vector<Book> books = LoadBooks(); // Cargar libros
        for (const auto& book : books) {
            bookList->Append(wxString(book.title)); // Añadir títulos de libros a la lista
        }
    }

    // Establecer el sizer al panel
    panel->SetSizer(vbox);

    // Centrar la ventana en la pantalla
    Centre();
}

// Método para manejar el evento de ver detalles del libro
void Main_GUI::OnViewBookDetails(wxCommandEvent& event) {
    OnSelectBook(); // Seleccionar el libro para ver detalles
    wxFrame* mainWindow = new Ver_Libro("Ver detalles", userIsAdmin, ActiveUser, BookSelected, 'M'); // Crear ventana de detalles
    mainWindow->Show(); // Mostrar la ventana de detalles
   
}

// Método para manejar el evento de buscar un libro
void Main_GUI::OnSearchBook(wxCommandEvent& event) {
    Busqueda* searchWindow = new Busqueda("Buscar", userIsAdmin, ActiveUser); // Crear ventana de búsqueda
    searchWindow->Show(); // Mostrar ventana de búsqueda
    this->Close(); // Cerrar la ventana principal
}

// Método para manejar el evento de agregar a favoritos
void Main_GUI::OnAddToFavorites(wxCommandEvent& event) {
    int selection = bookList->GetSelection(); // Obtener selección de la lista de libros
    if (selection != wxNOT_FOUND) { // Verificar que haya una selección válida
        // Cargar los libros favoritos actuales del usuario
        std::vector<Book> favorites = LoadFavorites(ActiveUser);

        // Cargar el libro seleccionado
        std::vector<Book> books = LoadBooks(); // Cargar libros
        if (selection < books.size()) { // Asegurarse de que la selección sea válida
            Book favoriteBook = books[selection]; // Obtener libro seleccionado

            // Verificar si el libro ya está en favoritos
            bool alreadyInFavorites = false;
            for (const auto& favBook : favorites) {
                if (strcmp(favBook.title, favoriteBook.title) == 0 &&
                    strcmp(favBook.author, favoriteBook.author) == 0) {
                    alreadyInFavorites = true; // El libro ya está en favoritos
                    break;
                }
            }

            // Si el libro no está en favoritos, agregarlo
            if (!alreadyInFavorites) {
                favorites.push_back(favoriteBook); // Añadir libro a favoritos
                SaveFavorites(favorites, ActiveUser); // Guardar lista de favoritos

                // Mostrar mensaje de éxito
                statusText->SetLabel("¡Libro añadido a favoritos!");
            }
            else {
                statusText->SetLabel("Este libro ya está en tus favoritos."); // Mensaje de libro ya en favoritos
            }
        }
    }
    else {
        statusText->SetLabel("No se ha seleccionado ningún libro."); // Mensaje de error si no hay selección
    }
}

// Método para manejar el evento de ver la lista de favoritos
void Main_GUI::OnViewFavorites(wxCommandEvent& event) {
    wxFrame* mainWindow = new FavoritesWindow("Favoritos", userIsAdmin, ActiveUser, 'M'); // Crear ventana de favoritos
    mainWindow->Show(); // Mostrar ventana de favoritos
    this->Close(); // Cerrar ventana principal
}

// Método para manejar el evento de gestionar libros
void Main_GUI::OnManageBooks(wxCommandEvent& event) {
    wxFrame* mainWindow = new Books("Gestor Libros", userIsAdmin, ActiveUser); // Crear ventana para gestionar libros
    mainWindow->Show(); // Mostrar ventana de gestión
    this->Close(); // Cerrar ventana principal
}

// Método para manejar el evento de gestionar usuarios
void Main_GUI::OnManageUsers(wxCommandEvent& event) {
    wxFrame* mainWindow = new GestionarUser("Gestor Usuarios", userIsAdmin, ActiveUser); // Crear ventana para gestionar usuarios
    mainWindow->Show(); // Mostrar ventana de gestión
    this->Close(); // Cerrar ventana principal
}

// Método para cargar libros desde un archivo
std::vector<Book> Main_GUI::LoadBooks() {
    std::vector<Book> books; // Vector para almacenar libros
    std::ifstream file("books.dat", std::ios::binary); // Abrir archivo en modo binario
    if (!file) return books; // Devolver vector vacío si no se puede abrir el archivo

    Book book;
    while (file.read(reinterpret_cast<char*>(&book), sizeof(Book))) { // Leer libros del archivo
        books.push_back(book); // Añadir libro al vector
    }
    file.close(); // Cerrar archivo
    return books; // Devolver vector de libros
}

// Método para seleccionar un libro
void Main_GUI::OnSelectBook() {
    int selection = bookList->GetSelection(); // Obtener índice seleccionado en la lista de libros

    if (selection != wxNOT_FOUND) { // Verificar que haya una selección válida
        std::vector<Book> books = LoadBooks(); // Cargar libros desde el archivo

        // Recorrer el vector de libros
        for (size_t i = 0; i < books.size(); ++i) {
            if (i == selection) { // Si el índice coincide con la selección
                // Establecer el libro seleccionado
                set_BookSelected(i);
                break; // Detener el bucle una vez encontrado el índice correspondiente
            }
        }
    }
}

// Método para cargar la lista de favoritos de un usuario
std::vector<Book> Main_GUI::LoadFavorites(const wxString& username) {
    std::vector<Book> favorites; // Vector para almacenar libros favoritos
    wxString filePath = wxString::Format("Listas/favorites_%s.dat", username); // Formatear la ruta del archivo de favoritos
    std::ifstream file(filePath.ToStdString(), std::ios::binary); // Abrir archivo en modo binario

    if (!file) {
        return favorites; // Devolver vector vacío si no existe el archivo
    }

    Book book;
    while (file.read(reinterpret_cast<char*>(&book), sizeof(Book))) { // Leer libros favoritos del archivo
        favorites.push_back(book); // Añadir libro a la lista de favoritos
    }
    file.close(); // Cerrar archivo
    return favorites; // Devolver vector de favoritos
}

// Método para guardar la lista de libros favoritos
void Main_GUI::SaveFavorites(const std::vector<Book>& favorites, const wxString& username) {
    // Cargar libros favoritos existentes
    std::vector<Book> existingFavorites = LoadFavorites(username);

    // Verificar si el nuevo libro ya está en la lista
    for (const auto& favorite : existingFavorites) {
        if (strcmp(favorite.title, favorites.back().title) == 0) {  // Comparar por título
            wxMessageBox("Este libro ya está en la lista de favoritos.", "Duplicado", wxOK | wxICON_WARNING); // Mensaje de duplicado
            return; // Salir si ya existe
        }
    }

    // Agregar el nuevo libro a la lista de favoritos
    existingFavorites.push_back(favorites.back());

    // Guardar la lista actualizada
    std::ofstream file("Listas/favorites_" + username.ToStdString() + ".dat", std::ios::binary | std::ios::trunc); // Abrir archivo en modo binario y truncar
    if (!file) {
        wxLogError("Error al abrir el archivo de favoritos para guardar."); // Mensaje de error al abrir el archivo
        return; // Salir si no se puede abrir el archivo
    }

    for (const auto& book : existingFavorites) {
        file.write(reinterpret_cast<const char*>(&book), sizeof(Book)); // Escribir libros en el archivo
    }
    file.close(); // Cerrar archivo
}
void  Main_GUI::OnExit(wxCommandEvent& event) {

    wxFrame* mainWindow = new Loguin_GUI("Iniciar Sesion"); // Crear ventana para gestionar usuarios
    mainWindow->Show(); // Mostrar ventana de log
    this->Close(); // Cerrar ventana principal
}