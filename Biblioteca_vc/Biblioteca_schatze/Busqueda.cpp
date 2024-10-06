#include "Busqueda.h"
#include <wx/wx.h>
#include <fstream>
#include "Books.h"
#include "Main_GUI.h"
#include "Favorites.h"

// Identificadores de eventos
enum {
    ID_SEARCH = 1,        // ID para el bot�n de b�squeda
    ID_Agregar_F,         // ID para el bot�n de agregar a favoritos
    ID_Ver_Favs,          // ID para el bot�n de ver favoritos
    ID_EXIT               // ID para el bot�n de salir
};

// Mapa de eventos: conecta los eventos (botones) con sus respectivos manejadores (funciones)
wxBEGIN_EVENT_TABLE(Busqueda, wxFrame)
EVT_BUTTON(ID_SEARCH, Busqueda::OnSearch)          // Evento del bot�n de b�squeda
EVT_BUTTON(ID_Agregar_F, Busqueda::OnAddToFavorites)  // Evento del bot�n de agregar a favoritos
EVT_BUTTON(ID_Ver_Favs, Busqueda::verFavs)         // Evento del bot�n de ver favoritos
EVT_BUTTON(ID_EXIT, Busqueda::OnExit)              // Evento del bot�n de salir
wxEND_EVENT_TABLE()

// Constructor de la ventana de b�squeda
Busqueda::Busqueda(const wxString& title, bool isAdmin, const wxString& activeUser)
    : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(600, 400)),
    userIsAdmin(isAdmin), ActiveUser(activeUser) {  // Inicializa la ventana con el t�tulo y propiedades del usuario

    // Crear panel principal para contener los controles
    wxPanel* panel = new wxPanel(this, -1);

    // Configuraci�n del �cono de la ventana
    wxIcon icon;
    icon.LoadFile("Icono.ico", wxBITMAP_TYPE_ICO);
    SetIcon(icon);
    SetBackgroundColour(wxColour(242, 230, 214));  // Color de fondo

    // *** Crear controles para la b�squeda ***
    wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);     // Sizer principal vertical
    wxBoxSizer* hbox1 = new wxBoxSizer(wxHORIZONTAL);  // Sizer horizontal para los controles de b�squeda

    // Opciones de filtro para buscar por t�tulo, autor, g�nero o a�o
    wxArrayString filterChoices;
    filterChoices.Add("Title");
    filterChoices.Add("Author");
    filterChoices.Add("Genre");
    filterChoices.Add("Year");

    filterChoice = new wxChoice(panel, wxID_ANY, wxDefaultPosition, wxSize(100, 25), filterChoices);  // Filtro de b�squeda
    searchCtrl = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(200, 25));              // Campo de texto de b�squeda

    searchButton = new wxButton(panel, ID_SEARCH, "Search");         // Bot�n de b�squeda
    addfav = new wxButton(panel, ID_Agregar_F, "Agregar a Favoritos");  // Bot�n para a�adir a favoritos
    verfav = new wxButton(panel, ID_Ver_Favs, "Ver Favoritos");      // Bot�n para ver favoritos
    exitButton = new wxButton(panel, ID_EXIT, "Volver al Menu");     // Bot�n para volver al men� principal

    // A�adir los controles de b�squeda al sizer horizontal
    hbox1->Add(filterChoice, 0);
    hbox1->Add(searchCtrl, 1, wxEXPAND);  // Expandir el campo de b�squeda
    hbox1->Add(searchButton, 0);
    vbox->Add(hbox1, 0, wxEXPAND | wxALL, 10);  // A�adir el sizer horizontal al sizer vertical

    // *** Lista para mostrar resultados de b�squeda ***
    resultList = new wxListBox(panel, wxID_ANY);  // Lista donde se muestran los libros
    vbox->Add(resultList, 1, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 10);  // A�adir la lista al sizer

    // *** Sizer horizontal para los botones de acciones adicionales ***
    wxBoxSizer* hbox2 = new wxBoxSizer(wxHORIZONTAL);

    // A�adir botones de acci�n (Agregar a favoritos, Ver favoritos, Salir)
    hbox2->Add(addfav, 1, wxEXPAND | wxALL, 5);
    hbox2->Add(verfav, 1, wxEXPAND | wxALL, 5);
    hbox2->Add(exitButton, 1, wxEXPAND | wxALL, 5);

    // A�adir el sizer de botones al sizer principal
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

// Funci�n para cargar libros desde el archivo binario
std::vector<Book> Busqueda::LoadBooks() {
    std::vector<Book> books;  // Vector para almacenar los libros
    std::ifstream file("books.dat", std::ios::binary);  // Abrir archivo en modo binario

    // Verificar si el archivo se abri� correctamente
    if (!file) {
        wxMessageBox("Error al abrir el archivo de libros", "Error", wxOK | wxICON_ERROR);  // Mostrar error si no se abre
        return books;  // Retornar vector vac�o en caso de error
    }

    Book book;
    while (file.read(reinterpret_cast<char*>(&book), sizeof(Book))) {  // Leer cada libro del archivo
        books.push_back(book);  // A�adir libro al vector
    }

    file.close();  // Cerrar archivo
    return books;  // Devolver la lista de libros cargados
}

// Mostrar libros en la lista de resultados
void Busqueda::DisplayBooks(const std::vector<Book>& booksToDisplay) {
    resultList->Clear();  // Limpiar la lista antes de mostrar nuevos resultados
    for (const auto& book : booksToDisplay) {
        // Formatear cada libro en el formato "T�tulo por Autor (A�o) - G�nero"
        wxString item = wxString::Format("%s by %s (%d) - %s",
            book.title, book.author, book.year, book.genre);
        resultList->Append(item);  // A�adir cada libro a la lista de resultados
    }
}

// Funci�n para realizar la b�squeda seg�n el filtro seleccionado
void Busqueda::OnSearch(wxCommandEvent& event) {
    wxString searchTerm = searchCtrl->GetValue().Lower();  // Obtener el t�rmino de b�squeda en min�sculas
    int selectedFilter = filterChoice->GetSelection();     // Obtener el filtro seleccionado (t�tulo, autor, etc.)

    // Verificar si se seleccion� un filtro v�lido
    if (selectedFilter < 0 || selectedFilter > 3) {
        wxMessageBox("Seleccione un filtro v�lido", "Error", wxOK | wxICON_ERROR);  // Mostrar error si no hay filtro v�lido
        return;
    }

    // Filtrar los libros seg�n el filtro y t�rmino de b�squeda
    std::vector<Book> filteredBooks;
    for (const auto& book : books) {
        wxString bookData;
        switch (selectedFilter) {
        case 0: bookData = book.title; break;  // Buscar por t�tulo
        case 1: bookData = book.author; break;  // Buscar por autor
        case 2: bookData = book.genre; break;  // Buscar por g�nero
        case 3: bookData = wxString::Format("%d", book.year); break;  // Buscar por a�o
        }
        bookData = bookData.Lower();  // Convertir el dato del libro a min�sculas
        if (bookData.Contains(searchTerm)) {  // Si el dato contiene el t�rmino de b�squeda, a�adirlo a la lista filtrada
            filteredBooks.push_back(book);
        }
    }

    // Mostrar los libros filtrados
    DisplayBooks(filteredBooks);
}

// Funci�n para salir y volver al men� principal
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

    if (!file) return favorites;  // Si no se puede abrir, devolver vector vac�o

    Book favorite;
    while (file.read(reinterpret_cast<char*>(&favorite), sizeof(Book))) {  // Leer favoritos del archivo
        favorites.push_back(favorite);  // A�adir cada favorito al vector
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

// Funci�n para agregar un libro seleccionado a favoritos
void Busqueda::OnAddToFavorites(wxCommandEvent& event) {
    int selectionIndex = resultList->GetSelection();  // Obtener el �ndice del libro seleccionado en la lista

    if (selectionIndex == wxNOT_FOUND) {  // Verificar si se ha seleccionado un libro
        statusText->SetLabel("Seleccione un libro para agregar a favoritos.");  // Mostrar mensaje de error
        return;
    }

    // Cargar los favoritos actuales del usuario
    std::vector<Book> favorites = LoadFavorites(ActiveUser);

    // Verificar si el libro ya est� en favoritos
    const Book& selectedBook = books[selectionIndex];
    bool alreadyInFavorites = false;
    for (const auto& favorite : favorites) {
        if (favorite.title == selectedBook.title && favorite.author == selectedBook.author) {
            alreadyInFavorites = true;  // Si el libro ya est� en favoritos, marcarlo
            break;
        }
    }

    if (!alreadyInFavorites) {
        favorites.push_back(selectedBook);  // A�adir libro a favoritos si no est�
        SaveFavorites(favorites, ActiveUser);  // Guardar la lista de favoritos actualizada
        statusText->SetLabel("Libro agregado a favoritos.");  // Mostrar mensaje de �xito
    }
    else {
        statusText->SetLabel("El libro ya est� en favoritos.");  // Mostrar mensaje de que ya est� en favoritos
    }
}

// Funci�n para ver los favoritos
void Busqueda::verFavs(wxCommandEvent& event) {
    wxFrame* favoritesWindow = new FavoritesWindow("Favoritos", userIsAdmin, ActiveUser, 'B'); // Mostrar la ventana de favoritos
    favoritesWindow->Show(); 
    this->Close();
}
