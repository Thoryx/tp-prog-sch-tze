#include "Ver_Libro.h"
#include "Main_GUI.h"
#include "Favorites.h"
#include "Books.h"
#include "Busqueda.h"
#include <fstream>
#include <vector>

// Definici�n de ID para el bot�n "Volver"
enum {
    ID_Back = wxID_HIGHEST + 1
};

// Macro para definir la tabla de eventos de wxWidgets
wxBEGIN_EVENT_TABLE(Ver_Libro, wxFrame)
EVT_BUTTON(ID_Back, Ver_Libro::OnBack)  // Asignaci�n del evento de clic del bot�n "Volver"
wxEND_EVENT_TABLE()

// Constructor de la clase Ver_Libro
Ver_Libro::Ver_Libro(const wxString& title, bool isAdmin, const wxString& activeUser, const int& seleccion, const char& panel_p)
    : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(400, 400)),
    userIsAdmin(isAdmin),
    ActiveUser(activeUser),
    selection(seleccion),
    panel_padre(panel_p) {

    wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);  // Creador de sizer vertical para organizar los controles

    // Ajustar estilo de fuente y tama�o
    wxFont fontTitulo(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);  // Fuente para el t�tulo
    wxFont fontNormal(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);  // Fuente normal

    // Crear los controles como miembros de la clase
    Titulo = new wxStaticText(this, wxID_ANY, wxT(""));  // Control para mostrar el t�tulo del libro
    Titulo->SetFont(fontTitulo);  // Aumentar tama�o de fuente del t�tulo

    Autor = new wxStaticText(this, wxID_ANY, wxT(""));  // Control para mostrar el autor del libro
    Autor->SetFont(fontNormal);  // Establecer fuente normal

    Genero = new wxStaticText(this, wxID_ANY, wxT(""));  // Control para mostrar el g�nero del libro
    Genero->SetFont(fontNormal);  // Establecer fuente normal

    Anio = new wxStaticText(this, wxID_ANY, wxT(""));  // Control para mostrar el a�o de publicaci�n
    Anio->SetFont(fontNormal);  // Establecer fuente normal

    backButton = new wxButton(this, ID_Back, "Volver", wxDefaultPosition, wxSize(150, 40));  // Bot�n "Volver"

    SetLabels();  // Llamar a la funci�n para establecer las etiquetas de los controles

    // Establecer color de fondo
    SetBackgroundColour(wxColour(242, 230, 214));  // Color de fondo personalizado

    // Establecer el �cono de la ventana
    wxIcon icon;
    icon.LoadFile("Icono.ico", wxBITMAP_TYPE_ICO);  // Cargar �cono desde archivo
    SetIcon(icon);  // Establecer el �cono en la ventana

    // A�adir los controles al sizer con margen y centrado
    vbox->Add(Titulo, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 20);  // A�adir t�tulo al sizer
    vbox->Add(Autor, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 10);  // A�adir autor al sizer
    vbox->Add(Genero, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 10);  // A�adir g�nero al sizer
    vbox->Add(Anio, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 10);  // A�adir a�o al sizer
    vbox->Add(backButton, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 20);  // A�adir bot�n "Volver" al sizer

    SetSizer(vbox);  // Establecer el sizer para la ventana
}

// Funci�n para cargar los libros desde un archivo binario
std::vector<Book> Ver_Libro::LoadBooks() {
    std::vector<Book> books;  // Vector para almacenar los libros
    std::ifstream file("books.dat", std::ios::binary);  // Abrir el archivo en modo binario
    if (!file) return books;  // Si no se puede abrir el archivo, retornar vector vac�o

    Book book;  // Objeto temporal para almacenar los datos de un libro
    while (file.read(reinterpret_cast<char*>(&book), sizeof(Book))) {  // Leer datos de cada libro en el archivo
        books.push_back(book);  // Agregar libro al vector
    }
    file.close();  // Cerrar el archivo
    return books;  // Retornar el vector de libros
}

// Funci�n para establecer las etiquetas de los controles
void Ver_Libro::SetLabels() {
    if (selection != wxNOT_FOUND) {  // Verificar si la selecci�n es v�lida
        std::vector<Book> books = LoadBooks();  // Cargar libros
        if (!books.empty() && selection < books.size()) {  // Verificar si hay libros y si la selecci�n es v�lida
            const Book& selectedBook = books[selection];  // Obtener el libro seleccionado
            Titulo->SetLabel("Titulo: " + wxString(selectedBook.title));  // Establecer etiqueta para el t�tulo
            Autor->SetLabel("Autor: " + wxString(selectedBook.author));  // Establecer etiqueta para el autor
            Genero->SetLabel("Genero: " + wxString(selectedBook.genre));  // Establecer etiqueta para el g�nero
            Anio->SetLabel("A�o de publicacion: " + wxString::Format(wxT("%d"), selectedBook.year));  // Establecer etiqueta para el a�o
        }
        else {
            // Si no se encuentra el libro, muestra un mensaje por defecto
            Titulo->SetLabel("T�tulo no encontrado");  // Mensaje por defecto para t�tulo
            Autor->SetLabel("Autor no encontrado");  // Mensaje por defecto para autor
            Genero->SetLabel("G�nero no encontrado");  // Mensaje por defecto para g�nero
            Anio->SetLabel("A�o no encontrado");  // Mensaje por defecto para a�o
        }
    }
}

// Evento que maneja el clic en el bot�n "Volver"
void Ver_Libro::OnBack(wxCommandEvent& event) {
    if (panel_padre == 'M') {  // Verificar si el panel padre es el principal
      
        this->Close();  // Cerrar la ventana actual
    }
    else if (panel_padre == 'F') {  // Verificar si el panel padre es de favoritos
       
        this->Close();  // Cerrar la ventana actual
    }
}
