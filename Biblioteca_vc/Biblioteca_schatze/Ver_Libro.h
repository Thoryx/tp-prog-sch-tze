#ifndef Ver_Libro_H
#define Ver_Libro_H

#include <wx/wx.h>
#include <vector>
#include "Books.h"

// Clase Ver_Libro que hereda de wxFrame, se utiliza para mostrar detalles de un libro
class Ver_Libro : public wxFrame {
public:
    // Constructor: inicializa la ventana con el t�tulo, los permisos del usuario y la selecci�n del libro
    Ver_Libro(const wxString& title, bool isAdmin, const wxString& activeUser, const int& selection, const char& panel_p);

private:
    // Componentes gr�ficos para mostrar los detalles del libro
    wxStaticText* Titulo;   // Texto est�tico para el t�tulo del libro
    wxStaticText* Autor;    // Texto est�tico para el autor del libro
    wxStaticText* Genero;   // Texto est�tico para el g�nero del libro
    wxStaticText* Anio;     // Texto est�tico para el a�o de publicaci�n del libro
    wxButton* backButton;    // Bot�n para regresar a la pantalla anterior

    // Variables miembro
    const char panel_padre;   // Identificador del panel padre
    bool userIsAdmin;         // Indica si el usuario actual es administrador
    wxString ActiveUser;      // Almacena el nombre del usuario activo
    int selection;            // Almacena la selecci�n del libro para mostrar detalles

    // M�todos privados
    void SetLabels();                     // M�todo para establecer los textos de los componentes
    std::vector<Book> LoadBooks();        // M�todo para cargar los libros desde una fuente
    void OnBack(wxCommandEvent& event);   // Maneja el evento del bot�n de regreso

    // Declaraci�n de la tabla de eventos para manejar eventos espec�ficos
    wxDECLARE_EVENT_TABLE();
};

#endif
