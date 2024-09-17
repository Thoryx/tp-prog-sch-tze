#ifndef GESTIONARUSER_H
#define GESTIONARUSER_H

#include <wx/wx.h>
#include <wx/listbox.h>
#include <vector>
#include <fstream>

// Estructura de usuario que contiene el nombre, contrase�a y si es administrador o no
struct User {
    char username[20];
    char password[8];
    bool isAdmin;

    User() : isAdmin(false) {}
};

// Clase que maneja la ventana de gesti�n de usuarios
class GestionarUser : public wxFrame {
public:
    // Constructor: Se inicializa con el t�tulo y el nombre del usuario activo
    GestionarUser(const wxString& title, const wxString& activeUser);

    // Destructor: Libera los recursos utilizados
    ~GestionarUser();

private:
    // Componentes gr�ficos
    wxListBox* userListBox;  // Lista de usuarios
    wxButton* editUserButton;
    wxButton* editPasswordButton;
    wxButton* toggleAdminButton;
    wxButton* deleteUserButton;
    wxButton* backButton;

    // Datos y almacenamiento
    std::vector<User> users; // Vector que almacena los usuarios cargados del archivo binario
    const wxString superPassword = "SuperAdmin123"; // Supercontrase�a para cambiar roles de administrador
    wxString activeUser; // Nombre del usuario actualmente registrado

    // Funciones para gestionar usuarios y la interfaz gr�fica
    void LoadUsersFromFile();   // Carga los usuarios desde el archivo binario
    void SaveUsersToFile();     // Guarda los usuarios en el archivo binario
    void UpdateUserListBox();   // Actualiza la lista de usuarios en la interfaz gr�fica

    // Eventos asociados a la selecci�n y los botones
    void OnSelectUser(wxCommandEvent& event);        // Evento al seleccionar un usuario de la lista
    void OnEditUser(wxCommandEvent& event);          // Evento al presionar el bot�n de editar usuario
    void OnEditPassword(wxCommandEvent& event);      // Evento al presionar el bot�n de editar contrase�a
    void OnToggleAdmin(wxCommandEvent& event);       // Evento al presionar el bot�n para cambiar el rol de administrador
    void OnDeleteUser(wxCommandEvent& event);        // Evento al presionar el bot�n de eliminar usuario
    void OnBack(wxCommandEvent& event);              // Evento al presionar el bot�n para volver a la pantalla principal

    // Funciones auxiliares
    User* GetSelectedUser();       // Obtiene el usuario seleccionado de la lista
    bool IsUsernameDuplicate(const wxString& username);  // Verifica si un nombre de usuario ya existe en la lista

    wxDECLARE_EVENT_TABLE();
};

#endif // GESTIONARUSER_H
