#ifndef __Main_GUI__
#define __Main_GUI__

#include <wx/wx.h>
#include "Books.h" // Incluir la definici�n de la clase Book

// Clase que representa la interfaz gr�fica principal
class Main_GUI : public wxFrame {
public:
    // Constructor de la clase Main_GUI
    Main_GUI(const wxString& title, bool isAdmin, const wxString& activeUser);

private:
    // Lista de libros mostrada en la interfaz
    wxListBox* bookList;

    // M�todo para cargar libros desde un archivo
    std::vector<Book> LoadBooks();

    // Botones para las funcionalidades de los usuarios no administradores
    wxButton* viewBookDetailsBtn;   // Bot�n para ver detalles de un libro
    wxButton* searchBookBtn;        // Bot�n para buscar un libro
    wxButton* addToFavoritesBtn;    // Bot�n para agregar un libro a favoritos
    wxButton* viewFavoritesBtn;     // Bot�n para ver la lista de favoritos
    wxButton* CloseSesionBtn;     // Bot�n para cerrar sesion

    // Botones disponibles solo para usuarios administradores
    wxButton* manageBooksBtn;       // Bot�n para gestionar libros
    wxButton* manageUsersBtn;       // Bot�n para gestionar usuarios

    // Atributo que indica si el usuario es administrador
    bool userIsAdmin;

    // Atributo para almacenar el nombre del usuario activo
    wxString ActiveUser;

    // Atributo para almacenar el �ndice del libro seleccionado
    int BookSelected;

    // Label para mostrar mensajes al usuario
    wxStaticText* statusText;

    // Ruta base para la gesti�n de listas de favoritos
    const wxString basePath = wxT("\Listas");

    // M�todos para manejar eventos de botones
    void OnViewBookDetails(wxCommandEvent& event); // Evento para ver detalles del libro
    void OnSearchBook(wxCommandEvent& event);       // Evento para buscar un libro
    void OnAddToFavorites(wxCommandEvent& event);   // Evento para agregar a favoritos
    void OnViewFavorites(wxCommandEvent& event);    // Evento para ver la lista de favoritos
    void OnManageBooks(wxCommandEvent& event);      // Evento para gestionar libros
    void OnManageUsers(wxCommandEvent& event);      // Evento para gestionar usuarios
    void OnSelectBook();                            // M�todo para seleccionar un libro
    void OnExit(wxCommandEvent& event);             // M�todo para cerrar sesion

    // M�todos para cargar y guardar listas de favoritos
    std::vector<Book> LoadFavorites(const wxString& username); // Cargar libros favoritos de un usuario
    void SaveFavorites(const std::vector<Book>& favorites, const wxString& username); // Guardar libros favoritos

    // Setter para el libro seleccionado
    void set_BookSelected(int selection) {
        BookSelected = selection; // Almacenar el �ndice del libro seleccionado
    }

    // Declaraci�n de la tabla de eventos de wxWidgets
    wxDECLARE_EVENT_TABLE();
};

#endif //__Main_GUI__
