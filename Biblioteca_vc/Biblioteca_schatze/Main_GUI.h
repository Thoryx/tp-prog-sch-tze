#ifndef __Main_GUI__
#define __Main_GUI__
#include <wx/wx.h>


class Main_GUI : public wxFrame {
public:
    Main_GUI(const wxString& title, bool isAdmin);

private:
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

    // Métodos para manejar eventos
    void OnViewBookDetails(wxCommandEvent& event);
    void OnSearchBook(wxCommandEvent& event);
    void OnAddToFavorites(wxCommandEvent& event);
    void OnViewFavorites(wxCommandEvent& event);
    void OnManageBooks(wxCommandEvent& event);
    void OnManageUsers(wxCommandEvent& event);

    //declaracion tabla de eventos
    wxDECLARE_EVENT_TABLE();
};
#endif //__Main_GUI__