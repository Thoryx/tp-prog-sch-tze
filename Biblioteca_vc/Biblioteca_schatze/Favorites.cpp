#include "Favorites.h"
#include "Main_GUI.h"
#include "Ver_Libro.h"
#include "Books.h"
#include "Busqueda.h"
#include <fstream>

// Identificadores de eventos
enum {
    ID_BackToMain = 1,         // Identificador para el bot�n de volver al men� principal
    ID_ViewBookDetails,        // Identificador para el bot�n de ver detalles del libro
    ID_RemoveFavorite          // Identificador para el bot�n de eliminar de favoritos
};

// Mapa de eventos para vincular botones a funciones de la clase
wxBEGIN_EVENT_TABLE(FavoritesWindow, wxFrame)
EVT_BUTTON(ID_BackToMain, FavoritesWindow::OnBackToMain)              // Evento para el bot�n "Volver"
EVT_BUTTON(ID_ViewBookDetails, FavoritesWindow::OnViewBookDetails)    // Evento para el bot�n "Ver detalles del libro"
EVT_BUTTON(ID_RemoveFavorite, FavoritesWindow::OnRemoveFavorite)      // Evento para el bot�n "Eliminar de Favoritos"
wxEND_EVENT_TABLE()

// Constructor de la ventana de favoritos
FavoritesWindow::FavoritesWindow(const wxString& title, bool isAdmin, const wxString& activeUser, const char& panel_p)
    : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(400, 300)),
    userIsAdmin(isAdmin), ActiveUser(activeUser), panel_padre(panel_p) {

    // Establecer el �cono de la ventana
    wxIcon icon;
    icon.LoadFile("Icono.ico", wxBITMAP_TYPE_ICO);
    SetIcon(icon);

    // Cambiar el color de fondo de la ventana
    SetBackgroundColour(wxColour(242, 230, 214));

    // Crear un contenedor (sizer) vertical para organizar los elementos en la ventana
    wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);

    // Crear un wxListBox para mostrar la lista de libros favoritos
    bookList = new wxListBox(this, wxID_ANY);
    vbox->Add(bookList, 1, wxEXPAND | wxALL, 10);   // A�adir la lista al sizer con margen de 10px

    // Establecer el sizer en la ventana
    SetSizer(vbox);

    // Cargar los libros favoritos del archivo correspondiente al usuario activo
    LoadFavorites(activeUser);

    // Botones para ver detalles del libro, eliminar de favoritos y volver al men� principal
    wxButton* backButton = new wxButton(this, ID_BackToMain, wxT("Volver"));   // Bot�n para volver al men�
    viewBookDetailsBtn = new wxButton(this, ID_ViewBookDetails, wxT("Ver detalles del libro"));  // Bot�n para ver detalles
    wxButton* removeFavoriteButton = new wxButton(this, ID_RemoveFavorite, wxT("Eliminar de Favoritos")); // Bot�n para eliminar de favoritos

    // A�adir los botones al sizer
    vbox->Add(viewBookDetailsBtn, 0, wxALL | wxEXPAND, 10);    // Bot�n "Ver detalles" con expansi�n horizontal y margen
    vbox->Add(removeFavoriteButton, 0, wxALL | wxEXPAND, 10);  // Bot�n "Eliminar de Favoritos" con expansi�n horizontal y margen
    vbox->Add(backButton, 0, wxCENTER, 5);   // Bot�n "Volver" centrado
}

// Funci�n para cargar los libros favoritos del usuario desde un archivo binario
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

    // Llenar el wxListBox con los t�tulos de los libros favoritos
    for (const auto& book : favorites) {
        bookList->Append(wxString(book.title));  // Se a�ade solo el t�tulo de cada libro a la lista
    }

    // Actualizar el t�tulo de la ventana con el n�mero de libros favoritos
    SetTitle(wxString::Format("Favoritos (%d)", favorites.size()));
}

// Funci�n que maneja el evento del bot�n "Volver al men�"
void FavoritesWindow::OnBackToMain(wxCommandEvent& event) {
    // Seg�n el valor de 'panel_padre', decide a cu�l ventana volver
    if (panel_padre == 'M') {  // Si el panel padre es el men� principal
        wxFrame* mainWindow = new Main_GUI("Main Window", userIsAdmin, ActiveUser);
        mainWindow->Show();
        this->Close();  // Cerrar la ventana actual
    }
    else if (panel_padre == 'B') {  // Si proviene de la ventana de b�squeda
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

// Funci�n que maneja el evento del bot�n "Ver detalles del libro"
void FavoritesWindow::OnViewBookDetails(wxCommandEvent& event) {
    // Llama a la funci�n para seleccionar un libro de la lista
    OnSelectBook();

    // Abre la ventana de detalles del libro seleccionado
    wxFrame* mainWindow = new Ver_Libro("Ver Detalles", userIsAdmin, ActiveUser, BookSelected, 'F');
    mainWindow->Show();
}

// Funci�n que maneja el evento del bot�n "Eliminar de Favoritos"
void FavoritesWindow::OnRemoveFavorite(wxCommandEvent& event) {
    int selection = bookList->GetSelection();  // Obtener el �ndice seleccionado en la lista de favoritos

    if (selection != wxNOT_FOUND) {  // Verifica que haya una selecci�n v�lida
        // Confirmar la eliminaci�n
        int confirm = wxMessageBox("�Est� seguro de que desea eliminar este libro de favoritos?", "Confirmar eliminaci�n", wxYES_NO | wxICON_QUESTION);
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
            SetTitle(wxString::Format("Favoritos (%d)", favorites.size()));  // Actualiza el t�tulo
        }
    }
    else {
        wxMessageBox("No se ha seleccionado ning�n libro.", "Error", wxOK | wxICON_ERROR);
    }
}

// Funci�n para cargar los libros favoritos desde el archivo
void FavoritesWindow::LoadFavoritesFromFile(std::vector<Book>& favorites, const wxString& activeUser) {
    wxString filePath = wxString::Format("Listas/favorites_%s.dat", activeUser);
    std::ifstream file(filePath.ToStdString(), std::ios::binary);

    if (!file) return;  // Si no se puede abrir el archivo, sale de la funci�n

    Book book;
    while (file.read(reinterpret_cast<char*>(&book), sizeof(Book))) {
        favorites.push_back(book);  // Agregar cada libro le�do al vector
    }
    file.close();
}

// Funci�n para guardar la lista actualizada de favoritos
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

// Funci�n que carga todos los libros desde el archivo binario
std::vector<Book> FavoritesWindow::LoadBooks() {
    std::vector<Book> books;
    std::ifstream file("books.dat", std::ios::binary);  // Abrir el archivo en modo binario
    if (!file) return books;  // Si no se puede abrir el archivo, devuelve un vector vac�o

    // Leer los libros desde el archivo binario
    Book book;
    while (file.read(reinterpret_cast<char*>(&book), sizeof(Book))) {
        books.push_back(book);  // Agregar cada libro le�do al vector
    }
    file.close();
    return books;  // Devuelve el vector con los libros cargados
}

// Funci�n que selecciona un libro de la lista
void FavoritesWindow::OnSelectBook() {
    int selection = bookList->GetSelection();  // Obtener el �ndice seleccionado en la lista de favoritos

    if (selection != wxNOT_FOUND) {  // Verifica que haya una selecci�n v�lida
        std::vector<Book> books = LoadBooks();  // Carga todos los libros disponibles

        // Recorre los libros y selecciona el que corresponde a la selecci�n en la lista
        for (size_t i = 0; i < books.size(); ++i) {
            if (i == selection) {
                set_BookSelected(i);  // Almacena el �ndice del libro seleccionado
                break;
            }
        }
    }
}
