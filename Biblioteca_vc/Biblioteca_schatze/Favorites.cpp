#include "Favorites.h"
#include "Main_GUI.h"
#include "Ver_Libro.h"
#include "Books.h"
#include "Busqueda.h"
#include <fstream>

// Identificadores de eventos
enum {
    ID_BackToMain = 1,         // Identificador para el botón de volver al menú principal
    ID_ViewBookDetails,        // Identificador para el botón de ver detalles del libro
    ID_RemoveFavorite          // Identificador para el botón de eliminar de favoritos
};

// Mapa de eventos para vincular botones a funciones de la clase
wxBEGIN_EVENT_TABLE(FavoritesWindow, wxFrame)
EVT_BUTTON(ID_BackToMain, FavoritesWindow::OnBackToMain)              // Evento para el botón "Volver"
EVT_BUTTON(ID_ViewBookDetails, FavoritesWindow::OnViewBookDetails)    // Evento para el botón "Ver detalles del libro"
EVT_BUTTON(ID_RemoveFavorite, FavoritesWindow::OnRemoveFavorite)      // Evento para el botón "Eliminar de Favoritos"
wxEND_EVENT_TABLE()

// Constructor de la ventana de favoritos
FavoritesWindow::FavoritesWindow(const wxString& title, bool isAdmin, const wxString& activeUser, const char& panel_p)
    : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(400, 300)),
    userIsAdmin(isAdmin), ActiveUser(activeUser), panel_padre(panel_p) {

    // Establecer el ícono de la ventana
    wxIcon icon;
    icon.LoadFile("Icono.ico", wxBITMAP_TYPE_ICO);
    SetIcon(icon);

    // Cambiar el color de fondo de la ventana
    SetBackgroundColour(wxColour(242, 230, 214));

    // Crear un contenedor (sizer) vertical para organizar los elementos en la ventana
    wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);

    // Crear un wxListBox para mostrar la lista de libros favoritos
    bookList = new wxListBox(this, wxID_ANY);
    vbox->Add(bookList, 1, wxEXPAND | wxALL, 10);   // Añadir la lista al sizer con margen de 10px

    // Establecer el sizer en la ventana
    SetSizer(vbox);

    // Cargar los libros favoritos del archivo correspondiente al usuario activo
    LoadFavorites(activeUser);

    // Botones para ver detalles del libro, eliminar de favoritos y volver al menú principal
    wxButton* backButton = new wxButton(this, ID_BackToMain, wxT("Volver"));   // Botón para volver al menú
    viewBookDetailsBtn = new wxButton(this, ID_ViewBookDetails, wxT("Ver detalles del libro"));  // Botón para ver detalles
    wxButton* removeFavoriteButton = new wxButton(this, ID_RemoveFavorite, wxT("Eliminar de Favoritos")); // Botón para eliminar de favoritos

    // Añadir los botones al sizer
    vbox->Add(viewBookDetailsBtn, 0, wxALL | wxEXPAND, 10);    // Botón "Ver detalles" con expansión horizontal y margen
    vbox->Add(removeFavoriteButton, 0, wxALL | wxEXPAND, 10);  // Botón "Eliminar de Favoritos" con expansión horizontal y margen
    vbox->Add(backButton, 0, wxCENTER, 5);   // Botón "Volver" centrado
}

// Función para cargar los libros favoritos del usuario desde un archivo binario
void FavoritesWindow::LoadFavorites(const wxString& activeUser) {
    std::vector<Book> favorites;

    // Ruta del archivo que almacena los favoritos del usuario
    wxString filePath = wxString::Format("Listas/favorites_%s.dat", activeUser);
    std::ifstream file(filePath.ToStdString(), std::ios::binary);

    // Si no se puede abrir el archivo, se muestra un mensaje de error
    if (!file) {
        wxMessageBox("No se pudo abrir el archivo de favoritos.", "Error", wxOK | wxICON_ERROR);
        return;
    }

    // Leer los libros desde el archivo binario y agregarlos al vector de favoritos
    Book book;
    while (file.read(reinterpret_cast<char*>(&book), sizeof(Book))) {
        favorites.push_back(book);
    }
    file.close();

    // Llenar el wxListBox con los títulos de los libros favoritos
    for (const auto& book : favorites) {
        bookList->Append(wxString(book.title));  // Se añade solo el título de cada libro a la lista
    }

    // Actualizar el título de la ventana con el número de libros favoritos
    SetTitle(wxString::Format("Favoritos (%d)", favorites.size()));
}

// Función que maneja el evento del botón "Volver al menú"
void FavoritesWindow::OnBackToMain(wxCommandEvent& event) {
    // Según el valor de 'panel_padre', decide a cuál ventana volver
    if (panel_padre == 'M') {  // Si el panel padre es el menú principal
        wxFrame* mainWindow = new Main_GUI("Main Window", userIsAdmin, ActiveUser);
        mainWindow->Show();
        this->Close();  // Cerrar la ventana actual
    }
    else if (panel_padre == 'B') {  // Si proviene de la ventana de búsqueda
        wxFrame* mainWindow = new Busqueda("Busqueda", userIsAdmin, ActiveUser);
        mainWindow->Show();
        this->Close();
    }
    else if (panel_padre == 'V') {  // Si proviene de la ventana de ver libro
        wxFrame* mainWindow = new Ver_Libro("Busqueda", userIsAdmin, ActiveUser, BookSelected, 'F');
        mainWindow->Show();
        this->Close();
    }
}

// Función que maneja el evento del botón "Ver detalles del libro"
void FavoritesWindow::OnViewBookDetails(wxCommandEvent& event) {
    // Llama a la función para seleccionar un libro de la lista
    OnSelectBook();

    // Abre la ventana de detalles del libro seleccionado
    wxFrame* mainWindow = new Ver_Libro("Ver Detalles", userIsAdmin, ActiveUser, BookSelected, 'F');
    mainWindow->Show();
}

// Función que maneja el evento del botón "Eliminar de Favoritos"
void FavoritesWindow::OnRemoveFavorite(wxCommandEvent& event) {
    int selection = bookList->GetSelection();  // Obtener el índice seleccionado en la lista de favoritos

    if (selection != wxNOT_FOUND) {  // Verifica que haya una selección válida
        // Confirmar la eliminación
        int confirm = wxMessageBox("¿Está seguro de que desea eliminar este libro de favoritos?", "Confirmar eliminación", wxYES_NO | wxICON_QUESTION);
        if (confirm == wxYES) {
            // Cargar los favoritos actuales
            std::vector<Book> favorites;
            LoadFavoritesFromFile(favorites, ActiveUser);

            // Eliminar el libro de la lista de favoritos
            favorites.erase(favorites.begin() + selection);

            // Guardar la lista actualizada de favoritos
            SaveFavoritesToFile(favorites, ActiveUser);

            // Actualizar la lista mostrada en la ventana
            bookList->Delete(selection);
            SetTitle(wxString::Format("Favoritos (%d)", favorites.size()));  // Actualiza el título
        }
    }
    else {
        wxMessageBox("No se ha seleccionado ningún libro.", "Error", wxOK | wxICON_ERROR);
    }
}

// Función para cargar los libros favoritos desde el archivo
void FavoritesWindow::LoadFavoritesFromFile(std::vector<Book>& favorites, const wxString& activeUser) {
    wxString filePath = wxString::Format("Listas/favorites_%s.dat", activeUser);
    std::ifstream file(filePath.ToStdString(), std::ios::binary);

    if (!file) return;  // Si no se puede abrir el archivo, sale de la función

    Book book;
    while (file.read(reinterpret_cast<char*>(&book), sizeof(Book))) {
        favorites.push_back(book);  // Agregar cada libro leído al vector
    }
    file.close();
}

// Función para guardar la lista actualizada de favoritos
void FavoritesWindow::SaveFavoritesToFile(const std::vector<Book>& favorites, const wxString& activeUser) {
    wxString filePath = wxString::Format("Listas/favorites_%s.dat", activeUser);
    std::ofstream file(filePath.ToStdString(), std::ios::binary | std::ios::trunc);  // Abrir archivo en modo binario y truncar

    if (file.is_open()) {
        for (const auto& book : favorites) {
            file.write(reinterpret_cast<const char*>(&book), sizeof(Book));  // Escribir cada libro
        }
        file.close();
    }
}

// Función que carga todos los libros desde el archivo binario
std::vector<Book> FavoritesWindow::LoadBooks() {
    std::vector<Book> books;
    std::ifstream file("books.dat", std::ios::binary);  // Abrir el archivo en modo binario
    if (!file) return books;  // Si no se puede abrir el archivo, devuelve un vector vacío

    // Leer los libros desde el archivo binario
    Book book;
    while (file.read(reinterpret_cast<char*>(&book), sizeof(Book))) {
        books.push_back(book);  // Agregar cada libro leído al vector
    }
    file.close();
    return books;  // Devuelve el vector con los libros cargados
}

// Función que selecciona un libro de la lista
void FavoritesWindow::OnSelectBook() {
    int selection = bookList->GetSelection();  // Obtener el índice seleccionado en la lista de favoritos

    if (selection != wxNOT_FOUND) {  // Verifica que haya una selección válida
        std::vector<Book> books = LoadBooks();  // Carga todos los libros disponibles

        // Recorre los libros y selecciona el que corresponde a la selección en la lista
        for (size_t i = 0; i < books.size(); ++i) {
            if (i == selection) {
                set_BookSelected(i);  // Almacena el índice del libro seleccionado
                break;
            }
        }
    }
}
