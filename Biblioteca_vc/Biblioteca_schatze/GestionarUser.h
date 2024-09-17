#ifndef GESTIONARUSER_H
#define GESTIONARUSER_H

#include <wx/wx.h>
#include <wx/listbox.h>
#include <vector>
#include <fstream>

// Estructura de usuario que contiene el nombre, contraseña y si es administrador o no
struct User {
    char username[20];
    char password[8];
    bool isAdmin;

    User() : isAdmin(false) {}
};

// Clase que maneja la ventana de gestión de usuarios
class GestionarUser : public wxFrame {
public:
    // Constructor: Se inicializa con el título y el nombre del usuario activo
    GestionarUser(const wxString& title, const wxString& activeUser);

    // Destructor: Libera los recursos utilizados
    ~GestionarUser();

private:
    // Componentes gráficos
    wxListBox* userListBox;  // Lista de usuarios
    wxButton* editUserButton;
    wxButton* editPasswordButton;
    wxButton* toggleAdminButton;
    wxButton* deleteUserButton;
    wxButton* backButton;

    // Datos y almacenamiento
    std::vector<User> users; // Vector que almacena los usuarios cargados del archivo binario
    const wxString superPassword = "SuperAdmin123"; // Supercontraseña para cambiar roles de administrador
    wxString activeUser; // Nombre del usuario actualmente registrado

    // Funciones para gestionar usuarios y la interfaz gráfica
    void LoadUsersFromFile();   // Carga los usuarios desde el archivo binario
    void SaveUsersToFile();     // Guarda los usuarios en el archivo binario
    void UpdateUserListBox();   // Actualiza la lista de usuarios en la interfaz gráfica

    // Eventos asociados a la selección y los botones
    void OnSelectUser(wxCommandEvent& event);        // Evento al seleccionar un usuario de la lista
    void OnEditUser(wxCommandEvent& event);          // Evento al presionar el botón de editar usuario
    void OnEditPassword(wxCommandEvent& event);      // Evento al presionar el botón de editar contraseña
    void OnToggleAdmin(wxCommandEvent& event);       // Evento al presionar el botón para cambiar el rol de administrador
    void OnDeleteUser(wxCommandEvent& event);        // Evento al presionar el botón de eliminar usuario
    void OnBack(wxCommandEvent& event);              // Evento al presionar el botón para volver a la pantalla principal

    // Funciones auxiliares
    User* GetSelectedUser();       // Obtiene el usuario seleccionado de la lista
    bool IsUsernameDuplicate(const wxString& username);  // Verifica si un nombre de usuario ya existe en la lista

    wxDECLARE_EVENT_TABLE();
};

#endif // GESTIONARUSER_H
