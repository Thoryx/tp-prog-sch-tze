#ifndef __GestionarUser__
#define __GestionarUser__

#include <wx/wx.h> // Incluye la biblioteca wxWidgets

// Definir la estructura de usuario
struct User {
    char username[20]; // Nombre de usuario (m�ximo 19 caracteres + terminador nulo)
    char password[8];  // Contrase�a (m�ximo 7 caracteres + terminador nulo)
    bool isAdmin;      // Indica si el usuario tiene privilegios de administrador

    // Constructor por defecto que inicializa isAdmin a false
    User() : isAdmin(false) {}
};

// Clase Loguin_GUI que hereda de wxFrame (ventana principal)
class Loguin_GUI : public wxFrame {
public:
    // Constructor de la clase Loguin_GUI que inicializa la ventana
    Loguin_GUI(const wxString& title);

private:
    // Controles de la interfaz de usuario
    wxTextCtrl* userTextCtrl;      // Campo de texto para el nombre de usuario
    wxTextCtrl* passTextCtrl;      // Campo de texto para la contrase�a
    wxButton* loginButton;          // Bot�n para iniciar sesi�n
    wxButton* registerButton;       // Bot�n para registrarse
    wxStaticText* statusText;       // Texto est�tico para mostrar mensajes al usuario
    User currentUser;               // Usuario actual que est� intentando iniciar sesi�n o registrarse

    // M�todos para manejar eventos de la interfaz
    void OnLogin(wxCommandEvent& event);       // Maneja el evento de inicio de sesi�n
    void OnRegister(wxCommandEvent& event);    // Maneja el evento de registro
    bool Authenticate(const std::string& username, const std::string& password); // Autenticaci�n del usuario
    bool SaveUser(const User& user);            // Guarda el usuario en un archivo
    bool IsUsernameDuplicate(const wxString& username); // Verifica si el nombre de usuario ya existe
    std::vector<User> LoadUsers();              // Carga los usuarios desde un archivo

    bool ContainsSpaces(const std::string& str); // Verifica si una cadena contiene espacios

    wxDECLARE_EVENT_TABLE(); // Declaraci�n de la tabla de eventos para esta clase
};

#endif // __GestionarUser__
