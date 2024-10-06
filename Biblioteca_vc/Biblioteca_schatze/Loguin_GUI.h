#ifndef __GestionarUser__
#define __GestionarUser__

#include <wx/wx.h> // Incluye la biblioteca wxWidgets

// Definir la estructura de usuario
struct User {
    char username[20]; // Nombre de usuario (máximo 19 caracteres + terminador nulo)
    char password[8];  // Contraseña (máximo 7 caracteres + terminador nulo)
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
    wxTextCtrl* passTextCtrl;      // Campo de texto para la contraseña
    wxButton* loginButton;          // Botón para iniciar sesión
    wxButton* registerButton;       // Botón para registrarse
    wxStaticText* statusText;       // Texto estático para mostrar mensajes al usuario
    User currentUser;               // Usuario actual que está intentando iniciar sesión o registrarse

    // Métodos para manejar eventos de la interfaz
    void OnLogin(wxCommandEvent& event);       // Maneja el evento de inicio de sesión
    void OnRegister(wxCommandEvent& event);    // Maneja el evento de registro
    bool Authenticate(const std::string& username, const std::string& password); // Autenticación del usuario
    bool SaveUser(const User& user);            // Guarda el usuario en un archivo
    bool IsUsernameDuplicate(const wxString& username); // Verifica si el nombre de usuario ya existe
    std::vector<User> LoadUsers();              // Carga los usuarios desde un archivo

    bool ContainsSpaces(const std::string& str); // Verifica si una cadena contiene espacios

    wxDECLARE_EVENT_TABLE(); // Declaración de la tabla de eventos para esta clase
};

#endif // __GestionarUser__
