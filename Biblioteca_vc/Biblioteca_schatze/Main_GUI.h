#ifndef __Main_GUI__
#define __Main_GUI__

#include <wx/wx.h>
#include "Books.h"


class Main_GUI : public wxFrame {
public:
    Main_GUI(const wxString& title, bool isAdmin, const wxString& activeUser);

private:
    wxListBox* bookList;
    std::vector<Book> LoadBooks();

    // Botones para los usuarios no admin
    wxButton* viewBookDetailsBtn;
    wxButton* searchBookBtn;
    wxButton* addToFavoritesBtn;
    wxButton* viewFavoritesBtn;

    // Botones solo para admins
    wxButton* manageBooksBtn;
    wxButton* manageUsersBtn;

    // Atributo para determinar si el usuario es administrador
    bool userIsAdmin;
    //atributo para guardarme el usuario
    wxString ActiveUser;
    //atributo para pasar el nombre del libro a mostrar detalles
    int BookSelected;
    //label para mensajes
    wxStaticText* statusText;
    //Ruta para listas de favoritos
    const wxString basePath = wxT("\Listas");

    // M�todos para manejar eventos
    void OnViewBookDetails(wxCommandEvent& event);
    void OnSearchBook(wxCommandEvent& event);
    void OnAddToFavorites(wxCommandEvent& event);
    void OnViewFavorites(wxCommandEvent& event);
    void OnManageBooks(wxCommandEvent& event);
    void OnManageUsers(wxCommandEvent& event);
    void OnSelectBook();
   
    std::vector<Book> LoadFavorites(const wxString& username);
    void SaveFavorites(const std::vector<Book>& favorites, const wxString& username);
    void set_BookSelected(int selection) {

        BookSelected = selection;
    }

    //declaracion tabla de eventos
    wxDECLARE_EVENT_TABLE();
};
#endif //__Main_GUI__