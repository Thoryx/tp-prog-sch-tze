#include "Busqueda.h"
#include <wx/wx.h>
#include <fstream>
#include "Books.h"
#include "Main_GUI.h"
#include "Favorites.h"

// Identificadores de eventos
enum {
    ID_SEARCH = 1,        // ID para el botón de búsqueda
    ID_Agregar_F,         // ID para el botón de agregar a favoritos
    ID_Ver_Favs,          // ID para el botón de ver favoritos
    ID_EXIT               // ID para el botón de salir
};

// Mapa de eventos: conecta los eventos (botones) con sus respectivos manejadores (funciones)
wxBEGIN_EVENT_TABLE(Busqueda, wxFrame)
EVT_BUTTON(ID_SEARCH, Busqueda::OnSearch)          // Evento del botón de búsqueda
EVT_BUTTON(ID_Agregar_F, Busqueda::OnAddToFavorites)  // Evento del botón de agregar a favoritos
EVT_BUTTON(ID_Ver_Favs, Busqueda::verFavs)         // Evento del botón de ver favoritos
EVT_BUTTON(ID_EXIT, Busqueda::OnExit)              // Evento del botón de salir
wxEND_EVENT_TABLE()

// Constructor de la ventana de búsqueda
Busqueda::Busqueda(const wxString& title, bool isAdmin, const wxString& activeUser)
    : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(600, 400)),
    userIsAdmin(isAdmin), ActiveUser(activeUser) {  // Inicializa la ventana con el título y propiedades del usuario

    // Crear panel principal para contener los controles
    wxPanel* panel = new wxPanel(this, -1);

    // Configuración del ícono de la ventana
    wxIcon icon;
    icon.LoadFile("Icono.ico", wxBITMAP_TYPE_ICO);
    SetIcon(icon);
    SetBackgroundColour(wxColour(242, 230, 214));  // Color de fondo

    // *** Crear controles para la búsqueda ***
    wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);     // Sizer principal vertical
    wxBoxSizer* hbox1 = new wxBoxSizer(wxHORIZONTAL);  // Sizer horizontal para los controles de búsqueda

    // Opciones de filtro para buscar por título, autor, género o año
    wxArrayString filterChoices;
    filterChoices.Add("Title");
    filterChoices.Add("Author");
    filterChoices.Add("Genre");
    filterChoices.Add("Year");

    filterChoice = new wxChoice(panel, wxID_ANY, wxDefaultPosition, wxSize(100, 25), filterChoices);  // Filtro de búsqueda
    searchCtrl = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(200, 25));              // Campo de texto de búsqueda

    searchButton = new wxButton(panel, ID_SEARCH, "Search");         // Botón de búsqueda
    addfav = new wxButton(panel, ID_Agregar_F, "Agregar a Favoritos");  // Botón para añadir a favoritos
    verfav = new wxButton(panel, ID_Ver_Favs, "Ver Favoritos");      // Botón para ver favoritos
    exitButton = new wxButton(panel, ID_EXIT, "Volver al Menu");     // Botón para volver al menú principal

    // Añadir los controles de búsqueda al sizer horizontal
    hbox1->Add(filterChoice, 0);
    hbox1->Add(searchCtrl, 1, wxEXPAND);  // Expandir el campo de búsqueda
    hbox1->Add(searchButton, 0);
    vbox->Add(hbox1, 0, wxEXPAND | wxALL, 10);  // Añadir el sizer horizontal al sizer vertical

    // *** Lista para mostrar resultados de búsqueda ***
    resultList = new wxListBox(panel, wxID_ANY);  // Lista donde se muestran los libros
    vbox->Add(resultList, 1, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 10);  // Añadir la lista al sizer

    // *** Sizer horizontal para los botones de acciones adicionales ***
    wxBoxSizer* hbox2 = new wxBoxSizer(wxHORIZONTAL);

    // Añadir botones de acción (Agregar a favoritos, Ver favoritos, Salir)
    hbox2->Add(addfav, 1, wxEXPAND | wxALL, 5);
    hbox2->Add(verfav, 1, wxEXPAND | wxALL, 5);
    hbox2->Add(exitButton, 1, wxEXPAND | wxALL, 5);

    // Añadir el sizer de botones al sizer principal
    vbox->Add(hbox2, 0, wxEXPAND | wxALL, 10);

    // *** Texto para mostrar mensajes de estado ***
    statusText = new wxStaticText(panel, wxID_ANY, "", wxDefaultPosition, wxSize(400, 20));  // Texto para mensajes al usuario
    vbox->Add(statusText, 0, wxALIGN_LEFT | wxLEFT | wxRIGHT | wxBOTTOM, 10);

    panel->SetSizer(vbox);  // Establecer el sizer principal del panel

    // *** Cargar libros desde el archivo y mostrarlos en la lista al inicio ***
    books = LoadBooks();          // Cargar libros desde archivo binario
    DisplayBooks(books);          // Mostrar los libros cargados en la lista

    Centre();  // Centrar la ventana en la pantalla
}

// Función para cargar libros desde el archivo binario
std::vector<Book> Busqueda::LoadBooks() {
    std::vector<Book> books;  // Vector para almacenar los libros
    std::ifstream file("books.dat", std::ios::binary);  // Abrir archivo en modo binario

    // Verificar si el archivo se abrió correctamente
    if (!file) {
        wxMessageBox("Error al abrir el archivo de libros", "Error", wxOK | wxICON_ERROR);  // Mostrar error si no se abre
        return books;  // Retornar vector vacío en caso de error
    }

    Book book;
    while (file.read(reinterpret_cast<char*>(&book), sizeof(Book))) {  // Leer cada libro del archivo
        books.push_back(book);  // Añadir libro al vector
    }

    file.close();  // Cerrar archivo
    return books;  // Devolver la lista de libros cargados
}

// Mostrar libros en la lista de resultados
void Busqueda::DisplayBooks(const std::vector<Book>& booksToDisplay) {
    resultList->Clear();  // Limpiar la lista antes de mostrar nuevos resultados
    for (const auto& book : booksToDisplay) {
        // Formatear cada libro en el formato "Título por Autor (Año) - Género"
        wxString item = wxString::Format("%s by %s (%d) - %s",
            book.title, book.author, book.year, book.genre);
        resultList->Append(item);  // Añadir cada libro a la lista de resultados
    }
}

// Función para realizar la búsqueda según el filtro seleccionado
void Busqueda::OnSearch(wxCommandEvent& event) {
    wxString searchTerm = searchCtrl->GetValue().Lower();  // Obtener el término de búsqueda en minúsculas
    int selectedFilter = filterChoice->GetSelection();     // Obtener el filtro seleccionado (título, autor, etc.)

    // Verificar si se seleccionó un filtro válido
    if (selectedFilter < 0 || selectedFilter > 3) {
        wxMessageBox("Seleccione un filtro válido", "Error", wxOK | wxICON_ERROR);  // Mostrar error si no hay filtro válido
        return;
    }

    // Filtrar los libros según el filtro y término de búsqueda
    std::vector<Book> filteredBooks;
    for (const auto& book : books) {
        wxString bookData;
        switch (selectedFilter) {
        case 0: bookData = book.title; break;  // Buscar por título
        case 1: bookData = book.author; break;  // Buscar por autor
        case 2: bookData = book.genre; break;  // Buscar por género
        case 3: bookData = wxString::Format("%d", book.year); break;  // Buscar por año
        }
        bookData = bookData.Lower();  // Convertir el dato del libro a minúsculas
        if (bookData.Contains(searchTerm)) {  // Si el dato contiene el término de búsqueda, añadirlo a la lista filtrada
            filteredBooks.push_back(book);
        }
    }

    // Mostrar los libros filtrados
    DisplayBooks(filteredBooks);
}

// Función para salir y volver al menú principal
void Busqueda::OnExit(wxCommandEvent& event) {
    wxFrame* mainWindow = new Main_GUI("Main Window", userIsAdmin, ActiveUser);  // Crear instancia de la ventana principal
    mainWindow->Show();  // Mostrar la ventana principal
    this->Close();       // Cerrar la ventana actual
}

// Cargar favoritos del usuario desde archivo binario
std::vector<Book> Busqueda::LoadFavorites(const wxString& username) {
    std::vector<Book> favorites;  // Vector de libros favoritos
    wxString filePath = wxString::Format("Listas/favorites_%s.dat", username);  // Ruta del archivo de favoritos
    std::ifstream file(filePath.ToStdString(), std::ios::binary);  // Abrir archivo en modo binario

    if (!file) return favorites;  // Si no se puede abrir, devolver vector vacío

    Book favorite;
    while (file.read(reinterpret_cast<char*>(&favorite), sizeof(Book))) {  // Leer favoritos del archivo
        favorites.push_back(favorite);  // Añadir cada favorito al vector
    }

    file.close();  // Cerrar archivo
    return favorites;  // Devolver lista de favoritos cargados
}

// Guardar lista de favoritos en archivo binario
void Busqueda::SaveFavorites(const std::vector<Book>& favorites, const wxString& username) {
    wxString filePath = wxString::Format("Listas/favorites_%s.dat", username);  // Ruta del archivo de favoritos
    std::ofstream file(filePath.ToStdString(), std::ios::binary);  // Abrir archivo en modo binario

    for (const auto& favorite : favorites) {
        file.write(reinterpret_cast<const char*>(&favorite), sizeof(Book));  // Escribir cada favorito en el archivo
    }

    file.close();  // Cerrar archivo
}

// Función para agregar un libro seleccionado a favoritos
void Busqueda::OnAddToFavorites(wxCommandEvent& event) {
    int selectionIndex = resultList->GetSelection();  // Obtener el índice del libro seleccionado en la lista

    if (selectionIndex == wxNOT_FOUND) {  // Verificar si se ha seleccionado un libro
        statusText->SetLabel("Seleccione un libro para agregar a favoritos.");  // Mostrar mensaje de error
        return;
    }

    // Cargar los favoritos actuales del usuario
    std::vector<Book> favorites = LoadFavorites(ActiveUser);

    // Verificar si el libro ya está en favoritos
    const Book& selectedBook = books[selectionIndex];
    bool alreadyInFavorites = false;
    for (const auto& favorite : favorites) {
        if (favorite.title == selectedBook.title && favorite.author == selectedBook.author) {
            alreadyInFavorites = true;  // Si el libro ya está en favoritos, marcarlo
            break;
        }
    }

    if (!alreadyInFavorites) {
        favorites.push_back(selectedBook);  // Añadir libro a favoritos si no está
        SaveFavorites(favorites, ActiveUser);  // Guardar la lista de favoritos actualizada
        statusText->SetLabel("Libro agregado a favoritos.");  // Mostrar mensaje de éxito
    }
    else {
        statusText->SetLabel("El libro ya está en favoritos.");  // Mostrar mensaje de que ya está en favoritos
    }
}

// Función para ver los favoritos
void Busqueda::verFavs(wxCommandEvent& event) {
    wxFrame* favoritesWindow = new FavoritesWindow("Favoritos", userIsAdmin, ActiveUser, 'B'); // Mostrar la ventana de favoritos
    favoritesWindow->Show(); 
    this->Close();
}
