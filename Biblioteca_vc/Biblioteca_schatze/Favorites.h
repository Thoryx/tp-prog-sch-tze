#ifndef FAVORITES_WINDOW_H
#define FAVORITES_WINDOW_H

#include <wx/wx.h>
#include <wx/listbox.h>
#include <vector>
#include "Books.h"

class FavoritesWindow : public wxFrame {
public:
    FavoritesWindow(const wxString& title, bool isAdmin, const wxString& activeUser, const char& panel_p);

private:
    // M�todos
    void LoadFavorites(const wxString& username);               // Cargar favoritos
    void OnBackToMain(wxCommandEvent& event);                   // Manejar evento de volver al men�
    void OnViewBookDetails(wxCommandEvent& event);              // Manejar evento de ver detalles del libro
    void OnRemoveFavorite(wxCommandEvent& event);               // Manejar evento de eliminar de favoritos
    void LoadFavoritesFromFile(std::vector<Book>& favorites, const wxString& activeUser);  // Cargar favoritos desde archivo
    void SaveFavoritesToFile(const std::vector<Book>& favorites, const wxString& activeUser);  // Guardar favoritos en archivo
    std::vector<Book> LoadBooks();                               // Cargar libros desde archivo
    void OnSelectBook();                                         // Seleccionar un libro de la lista
    void set_BookSelected(int selection) { BookSelected = selection; }  // Establecer el libro seleccionado

    // Componentes de la interfaz
    wxButton* viewBookDetailsBtn;                               // Bot�n para ver detalles del libro
    wxListBox* bookList;                                        // wxListBox para mostrar los t�tulos de los libros

    // Atributos
    bool userIsAdmin;                                           // Indica si el usuario es administrador
    wxString ActiveUser;                                       // Nombre del usuario activo
    int BookSelected;                                          // �ndice del libro seleccionado
    const char panel_padre;                                   // Identificador del panel padre

    wxDECLARE_EVENT_TABLE();                                   // Declaraci�n de la tabla de eventos
};

#endif // FAVORITES_WINDOW_H
