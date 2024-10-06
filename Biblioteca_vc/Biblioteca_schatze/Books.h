#ifndef BOOKS_H
#define BOOKS_H

#include <wx/wx.h> // Incluye la biblioteca wxWidgets
#include <vector>  // Incluye la biblioteca para utilizar vectores

// Estructura que representa un libro
struct Book {
    char title[100];  // Título del libro (máximo 99 caracteres + terminador nulo)
    char author[100]; // Autor del libro (máximo 99 caracteres + terminador nulo)
    char genre[100];  // Género del libro (máximo 99 caracteres + terminador nulo)
    int year;         // Año de publicación del libro
};

// Clase Books que hereda de wxFrame (ventana principal)
class Books : public wxFrame {
public:
    // Constructor de la clase Books que inicializa la ventana
    Books(const wxString& title, bool isAdmin, const wxString& activeUser);

private:
    // Controles de la interfaz de usuario
    wxListBox* bookList;          // Lista que muestra los libros
    wxTextCtrl* titleTextCtrl;    // Campo de texto para el título del libro
    wxTextCtrl* authorTextCtrl;   // Campo de texto para el autor del libro
    wxTextCtrl* genreTextCtrl;    // Campo de texto para el género del libro
    wxTextCtrl* yearTextCtrl;     // Campo de texto para el año de publicación
    wxStaticText* statusText;      // Texto estático para mostrar mensajes al usuario

    wxString ActiveUser; // Nombre del usuario actualmente registrado
    bool userIsAdmin;    // Indica si el usuario es administrador

    // Métodos para cargar y guardar libros
    std::vector<Book> LoadBooks(); // Carga la lista de libros desde un archivo
    void SaveBooks(const std::vector<Book>& books); // Guarda la lista de libros en un archivo

    // Métodos para manejar eventos de la interfaz
    void OnAddBook(wxCommandEvent& event);     // Maneja el evento para añadir un libro
    void OnDeleteBook(wxCommandEvent& event);  // Maneja el evento para eliminar un libro
    void OnModifyBook(wxCommandEvent& event);  // Maneja el evento para modificar un libro
    void OnBackToMain(wxCommandEvent& event);  // Maneja el evento para volver a la ventana principal
    void OnSelectBook(wxCommandEvent& event);  // Maneja el evento de selección de un libro

    wxDECLARE_EVENT_TABLE(); // Declaración de la tabla de eventos para esta clase
};

#endif // BOOKS_H
