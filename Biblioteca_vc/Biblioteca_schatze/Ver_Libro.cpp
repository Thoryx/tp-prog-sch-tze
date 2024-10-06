#include "Ver_Libro.h"
#include "Main_GUI.h"
#include "Favorites.h"
#include "Books.h"
#include "Busqueda.h"
#include <fstream>
#include <vector>

// Definición de ID para el botón "Volver"
enum {
    ID_Back = wxID_HIGHEST + 1
};

// Macro para definir la tabla de eventos de wxWidgets
wxBEGIN_EVENT_TABLE(Ver_Libro, wxFrame)
EVT_BUTTON(ID_Back, Ver_Libro::OnBack)  // Asignación del evento de clic del botón "Volver"
wxEND_EVENT_TABLE()

// Constructor de la clase Ver_Libro
Ver_Libro::Ver_Libro(const wxString& title, bool isAdmin, const wxString& activeUser, const int& seleccion, const char& panel_p)
    : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(400, 400)),
    userIsAdmin(isAdmin),
    ActiveUser(activeUser),
    selection(seleccion),
    panel_padre(panel_p) {

    wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);  // Creador de sizer vertical para organizar los controles

    // Ajustar estilo de fuente y tamaño
    wxFont fontTitulo(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);  // Fuente para el título
    wxFont fontNormal(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);  // Fuente normal

    // Crear los controles como miembros de la clase
    Titulo = new wxStaticText(this, wxID_ANY, wxT(""));  // Control para mostrar el título del libro
    Titulo->SetFont(fontTitulo);  // Aumentar tamaño de fuente del título

    Autor = new wxStaticText(this, wxID_ANY, wxT(""));  // Control para mostrar el autor del libro
    Autor->SetFont(fontNormal);  // Establecer fuente normal

    Genero = new wxStaticText(this, wxID_ANY, wxT(""));  // Control para mostrar el género del libro
    Genero->SetFont(fontNormal);  // Establecer fuente normal

    Anio = new wxStaticText(this, wxID_ANY, wxT(""));  // Control para mostrar el año de publicación
    Anio->SetFont(fontNormal);  // Establecer fuente normal

    backButton = new wxButton(this, ID_Back, "Volver", wxDefaultPosition, wxSize(150, 40));  // Botón "Volver"

    SetLabels();  // Llamar a la función para establecer las etiquetas de los controles

    // Establecer color de fondo
    SetBackgroundColour(wxColour(242, 230, 214));  // Color de fondo personalizado

    // Establecer el ícono de la ventana
    wxIcon icon;
    icon.LoadFile("Icono.ico", wxBITMAP_TYPE_ICO);  // Cargar ícono desde archivo
    SetIcon(icon);  // Establecer el ícono en la ventana

    // Añadir los controles al sizer con margen y centrado
    vbox->Add(Titulo, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 20);  // Añadir título al sizer
    vbox->Add(Autor, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 10);  // Añadir autor al sizer
    vbox->Add(Genero, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 10);  // Añadir género al sizer
    vbox->Add(Anio, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 10);  // Añadir año al sizer
    vbox->Add(backButton, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 20);  // Añadir botón "Volver" al sizer

    SetSizer(vbox);  // Establecer el sizer para la ventana
}

// Función para cargar los libros desde un archivo binario
std::vector<Book> Ver_Libro::LoadBooks() {
    std::vector<Book> books;  // Vector para almacenar los libros
    std::ifstream file("books.dat", std::ios::binary);  // Abrir el archivo en modo binario
    if (!file) return books;  // Si no se puede abrir el archivo, retornar vector vacío

    Book book;  // Objeto temporal para almacenar los datos de un libro
    while (file.read(reinterpret_cast<char*>(&book), sizeof(Book))) {  // Leer datos de cada libro en el archivo
        books.push_back(book);  // Agregar libro al vector
    }
    file.close();  // Cerrar el archivo
    return books;  // Retornar el vector de libros
}

// Función para establecer las etiquetas de los controles
void Ver_Libro::SetLabels() {
    if (selection != wxNOT_FOUND) {  // Verificar si la selección es válida
        std::vector<Book> books = LoadBooks();  // Cargar libros
        if (!books.empty() && selection < books.size()) {  // Verificar si hay libros y si la selección es válida
            const Book& selectedBook = books[selection];  // Obtener el libro seleccionado
            Titulo->SetLabel("Titulo: " + wxString(selectedBook.title));  // Establecer etiqueta para el título
            Autor->SetLabel("Autor: " + wxString(selectedBook.author));  // Establecer etiqueta para el autor
            Genero->SetLabel("Genero: " + wxString(selectedBook.genre));  // Establecer etiqueta para el género
            Anio->SetLabel("Año de publicacion: " + wxString::Format(wxT("%d"), selectedBook.year));  // Establecer etiqueta para el año
        }
        else {
            // Si no se encuentra el libro, muestra un mensaje por defecto
            Titulo->SetLabel("Título no encontrado");  // Mensaje por defecto para título
            Autor->SetLabel("Autor no encontrado");  // Mensaje por defecto para autor
            Genero->SetLabel("Género no encontrado");  // Mensaje por defecto para género
            Anio->SetLabel("Año no encontrado");  // Mensaje por defecto para año
        }
    }
}

// Evento que maneja el clic en el botón "Volver"
void Ver_Libro::OnBack(wxCommandEvent& event) {
    if (panel_padre == 'M') {  // Verificar si el panel padre es el principal
      
        this->Close();  // Cerrar la ventana actual
    }
    else if (panel_padre == 'F') {  // Verificar si el panel padre es de favoritos
       
        this->Close();  // Cerrar la ventana actual
    }
}
