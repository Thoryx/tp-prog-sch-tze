#ifndef Favorites_WINDOW_H
#define Favorites_WINDOW_H

#include <wx/wx.h>
#include <wx/listbox.h>
#include <vector>
#include "Books.h"  

class FavoritesWindow : public wxFrame {
public:
    FavoritesWindow(const wxString& title, bool isAdmin, const wxString& activeUser);

private:
    void LoadFavorites(const wxString& username);
    void OnBackToMain(wxCommandEvent& event);
    void OnViewBookDetails(wxCommandEvent& event);
    std::vector<Book> LoadBooks();
    void OnSelectBook();
    void set_BookSelected(int selection) {

        BookSelected = selection;
    }

    wxButton* viewBookDetailsBtn;
    wxListBox* bookList;  // wxListBox para mostrar los títulos de los libros
    // Atributo para determinar si el usuario es administrador
    bool userIsAdmin;
    //atributo para guardarme el usuario
    wxString ActiveUser;
    //atributo para pasar el nombre del libro a mostrar detalles
    int BookSelected;

    wxDECLARE_EVENT_TABLE();
};

#endif // FAVORITES_WINDOW_H
