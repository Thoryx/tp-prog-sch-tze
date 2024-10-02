#ifndef __GestionarUser__
#define __GestionarUser__
#include <wx/wx.h>
// Definir la estructura de usuario
struct User {
    char username[20];
    char password[8];
    bool isAdmin;

    User() : isAdmin(false) {}
};


class Loguin_GUI : public wxFrame {
public:
   
    Loguin_GUI(const wxString& title);

private:
    // Controles de la interfaz
    wxTextCtrl* userTextCtrl;
    wxTextCtrl* passTextCtrl;
    wxButton* loginButton;
    wxButton* registerButton;
    wxStaticText* statusText;
    User currentUser;
   

    // Métodos para manejar eventos
    void OnLogin(wxCommandEvent& event);
    void OnRegister(wxCommandEvent& event);
    bool Authenticate(const std::string& username, const std::string& password);
    bool SaveUser(const User& user);
    bool IsUsernameDuplicate(const wxString& username);
    // Método helper para cargar usuarios desde archivo
    std::vector<User> LoadUsers();

    bool ContainsSpaces(const std::string& str);
    

    wxDECLARE_EVENT_TABLE();
};

#endif