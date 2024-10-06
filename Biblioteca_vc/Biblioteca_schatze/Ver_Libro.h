#ifndef Ver_Libro_H
#define Ver_Libro_H

#include <wx/wx.h>
#include <vector>
#include "Books.h"

// Clase Ver_Libro que hereda de wxFrame, se utiliza para mostrar detalles de un libro
class Ver_Libro : public wxFrame {
public:
    // Constructor: inicializa la ventana con el título, los permisos del usuario y la selección del libro
    Ver_Libro(const wxString& title, bool isAdmin, const wxString& activeUser, const int& selection, const char& panel_p);

private:
    // Componentes gráficos para mostrar los detalles del libro
    wxStaticText* Titulo;   // Texto estático para el título del libro
    wxStaticText* Autor;    // Texto estático para el autor del libro
    wxStaticText* Genero;   // Texto estático para el género del libro
    wxStaticText* Anio;     // Texto estático para el año de publicación del libro
    wxButton* backButton;    // Botón para regresar a la pantalla anterior

    // Variables miembro
    const char panel_padre;   // Identificador del panel padre
    bool userIsAdmin;         // Indica si el usuario actual es administrador
    wxString ActiveUser;      // Almacena el nombre del usuario activo
    int selection;            // Almacena la selección del libro para mostrar detalles

    // Métodos privados
    void SetLabels();                     // Método para establecer los textos de los componentes
    std::vector<Book> LoadBooks();        // Método para cargar los libros desde una fuente
    void OnBack(wxCommandEvent& event);   // Maneja el evento del botón de regreso

    // Declaración de la tabla de eventos para manejar eventos específicos
    wxDECLARE_EVENT_TABLE();
};

#endif
