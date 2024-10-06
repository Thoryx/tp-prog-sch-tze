#include "GestionarUser.h"
#include "Main_GUI.h"
#include "Loguin_GUI.h"
#include <fstream>

#define DATA_FILE "Credenciales.dat" // Archivo donde se guardan las credenciales

// Enumeraci�n para gestionar eventos de los botones
enum {
    ID_EDIT_USER = wxID_HIGHEST + 1,
    ID_EDIT_PASSWORD,
    ID_TOGGLE_ADMIN,
    ID_DELETE_USER,
    ID_BACK_BUTTON
};

// Definici�n de la tabla de eventos para el manejo de interacciones
wxBEGIN_EVENT_TABLE(GestionarUser, wxFrame)
EVT_LISTBOX(wxID_ANY, GestionarUser::OnSelectUser) // Evento de selecci�n en la lista de usuarios
EVT_BUTTON(ID_EDIT_USER, GestionarUser::OnEditUser) // Evento para editar el nombre de usuario
EVT_BUTTON(ID_EDIT_PASSWORD, GestionarUser::OnEditPassword) // Evento para editar la contrase�a
EVT_BUTTON(ID_TOGGLE_ADMIN, GestionarUser::OnToggleAdmin) // Evento para cambiar el rol a administrador
EVT_BUTTON(ID_DELETE_USER, GestionarUser::OnDeleteUser) // Evento para eliminar un usuario
EVT_BUTTON(ID_BACK_BUTTON, GestionarUser::OnBack) // Evento para volver a la pantalla anterior
wxEND_EVENT_TABLE()

// Constructor de la clase GestionarUser
GestionarUser::GestionarUser(const wxString& title, bool isAdmin, const wxString& activeUser)
    : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(400, 400)), // Inicializa la ventana
    userIsAdmin(isAdmin), ActiveUser(activeUser) {

    // Inicializa los controles de la interfaz gr�fica
    userListBox = new wxListBox(this, wxID_ANY, wxPoint(10, 10), wxSize(180, 300)); // Lista de usuarios
    editUserButton = new wxButton(this, ID_EDIT_USER, "Editar Usuario", wxPoint(200, 10), wxSize(150, 30)); // Bot�n para editar usuario
    editPasswordButton = new wxButton(this, ID_EDIT_PASSWORD, "Editar Contrase�a", wxPoint(200, 50), wxSize(150, 30)); // Bot�n para editar contrase�a
    toggleAdminButton = new wxButton(this, ID_TOGGLE_ADMIN, "Cambiar Rol Admin", wxPoint(200, 90), wxSize(150, 30)); // Bot�n para cambiar rol a administrador
    deleteUserButton = new wxButton(this, ID_DELETE_USER, "Eliminar Usuario", wxPoint(200, 130), wxSize(150, 30)); // Bot�n para eliminar usuario
    backButton = new wxButton(this, ID_BACK_BUTTON, "Volver", wxPoint(200, 170), wxSize(150, 30)); // Bot�n para volver

    SetBackgroundColour(wxColour(242, 230, 214)); // Establece el color de fondo de la ventana
    // Establecer el �cono de la ventana
    wxIcon icon;
    icon.LoadFile("Icono.ico", wxBITMAP_TYPE_ICO); // Carga el �cono de la ventana
    SetIcon(icon); // Establece el �cono de la ventana

    LoadUsersFromFile(); // Carga los usuarios desde el archivo al iniciar
    UpdateUserListBox(); // Actualiza la lista de usuarios en la interfaz
}

// Destructor de la clase GestionarUser
GestionarUser::~GestionarUser() {
    SaveUsersToFile(); // Guarda los usuarios al cerrar la ventana
}

// Carga los usuarios desde el archivo binario
void GestionarUser::LoadUsersFromFile() {
    std::ifstream file(DATA_FILE, std::ios::binary); // Abre el archivo en modo binario
    if (file.is_open()) { // Verifica si el archivo se abri� correctamente
        User tempUser; // Variable temporal para almacenar datos del usuario
        while (file.read(reinterpret_cast<char*>(&tempUser), sizeof(User))) { // Lee cada usuario del archivo
            users.push_back(tempUser); // Agrega el usuario al vector
        }
        file.close(); // Cierra el archivo
    }
}

// Guarda la lista de usuarios en el archivo binario
void GestionarUser::SaveUsersToFile() {
    std::ofstream file(DATA_FILE, std::ios::binary | std::ios::trunc); // Abre el archivo en modo binario y trunca
    if (file.is_open()) { // Verifica si el archivo se abri� correctamente
        for (const auto& user : users) { // Itera sobre cada usuario
            file.write(reinterpret_cast<const char*>(&user), sizeof(User)); // Escribe el usuario en el archivo
        }
        file.close(); // Cierra el archivo
    }
}

// Actualiza la lista de usuarios en la interfaz gr�fica
void GestionarUser::UpdateUserListBox() {
    userListBox->Clear(); // Limpia la lista de usuarios
    for (const auto& user : users) { // Itera sobre cada usuario
        userListBox->Append(user.username); // Agrega el nombre de usuario a la lista
    }
}

// Obtiene el usuario seleccionado en la lista
User* GestionarUser::GetSelectedUser() {
    int selection = userListBox->GetSelection(); // Obtiene la selecci�n actual de la lista
    if (selection != wxNOT_FOUND) { // Verifica si hay una selecci�n v�lida
        return &users[selection]; // Retorna el puntero al usuario seleccionado
    }
    return nullptr; // Retorna nullptr si no hay selecci�n
}

// Verifica si el nombre de usuario ya existe en la lista
bool GestionarUser::IsUsernameDuplicate(const wxString& username) {
    for (const auto& user : users) { // Itera sobre los usuarios
        if (username == wxString(user.username)) { // Compara con el nombre de usuario existente
            return true;  // Ya existe un usuario con este nombre
        }
    }
    return false;  // No hay duplicado
}

// Maneja la selecci�n de un usuario en la lista
void GestionarUser::OnSelectUser(wxCommandEvent& event) {
    wxString selectedUser = userListBox->GetStringSelection(); // Obtiene el usuario seleccionado
}

// Editar nombre de usuario
void GestionarUser::OnEditUser(wxCommandEvent& event) {
    User* selectedUser = GetSelectedUser(); // Obtiene el usuario seleccionado
    wxString newUsername; // Variable para almacenar el nuevo nombre de usuario
    if (selectedUser) { // Verifica si hay un usuario seleccionado
        if (selectedUser->isAdmin) { // Si el usuario es admin
            wxString enteredPassword = wxGetPasswordFromUser("Ingrese la supercontrase�a para cambiar el usuario:", "Supercontrase�a");
            if (enteredPassword == superPassword) { // Verifica la supercontrase�a
                newUsername = wxGetTextFromUser("Ingrese el nuevo nombre de usuario:", "Editar Usuario"); // Solicita el nuevo nombre
            }
            else {
                wxMessageBox("Supercontrase�a incorrecta.", "Error"); // Mensaje de error si la contrase�a es incorrecta
            }
        }
        else { // Si el usuario no es admin
            newUsername = wxGetTextFromUser("Ingrese el nuevo nombre de usuario:", "Editar Usuario"); // Solicita el nuevo nombre
        }
        if (!newUsername.IsEmpty()) { // Verifica que el nuevo nombre no est� vac�o
            if (IsUsernameDuplicate(newUsername)) { // Verifica si el nombre ya existe
                wxMessageBox("Este nombre de usuario ya existe. Elige uno diferente.", "Error"); // Mensaje de error si ya existe
            }
            else {
                strncpy(selectedUser->username, newUsername.mb_str(), sizeof(selectedUser->username) - 1); // Actualiza el nombre del usuario
                UpdateUserListBox(); // Actualiza la lista de usuarios en la interfaz
            }
        }
    }
}

// Editar contrase�a
void GestionarUser::OnEditPassword(wxCommandEvent& event) {
    User* selectedUser = GetSelectedUser(); // Obtiene el usuario seleccionado
    wxString newPassword; // Variable para almacenar la nueva contrase�a
    if (selectedUser) { // Verifica si hay un usuario seleccionado
        if (selectedUser->isAdmin) { // Si el usuario es admin
            wxString enteredPassword = wxGetPasswordFromUser("Ingrese la supercontrase�a para cambiar la contrase�a:", "Supercontrase�a");
            if (enteredPassword == superPassword) { // Verifica la supercontrase�a
                newPassword = wxGetPasswordFromUser("Ingrese la nueva contrase�a:", "Editar Contrase�a"); // Solicita la nueva contrase�a
            }
            else {
                wxMessageBox("Supercontrase�a incorrecta.", "Error"); // Mensaje de error si la contrase�a es incorrecta
            }
        }
        else { // Si el usuario no es admin
            newPassword = wxGetPasswordFromUser("Ingrese la nueva contrase�a:", "Editar Contrase�a"); // Solicita la nueva contrase�a
        }
        if (!newPassword.IsEmpty()) { // Verifica que la nueva contrase�a no est� vac�a
            strncpy(selectedUser->password, newPassword.mb_str(), sizeof(selectedUser->password) - 1); // Actualiza la contrase�a
        }
    }
}

// Cambiar rol de administrador
void GestionarUser::OnToggleAdmin(wxCommandEvent& event) {
    User* selectedUser = GetSelectedUser(); // Obtiene el usuario seleccionado
    if (selectedUser) { // Verifica si hay un usuario seleccionado
        if (selectedUser->isAdmin) { // Si el usuario es admin
            wxString enteredPassword = wxGetPasswordFromUser("Ingrese la supercontrase�a para cambiar el rol:", "Supercontrase�a");
            if (enteredPassword == superPassword) { // Verifica la supercontrase�a
                selectedUser->isAdmin = false; // Cambia el rol a usuario regular
                wxMessageBox("El usuario ahora es un usuario regular.", "Cambio de Rol");
            }
            else {
                wxMessageBox("Supercontrase�a incorrecta.", "Error"); // Mensaje de error si la contrase�a es incorrecta
            }
        }
        else { // Si el usuario no es admin
            selectedUser->isAdmin = true; // Cambia el rol a administrador
            wxMessageBox("El usuario ahora es Administrador.", "Cambio de Rol");
        }
    }
}

// Eliminar usuario
void GestionarUser::OnDeleteUser(wxCommandEvent& event) {
    User* selectedUser = GetSelectedUser(); // Obtiene el usuario seleccionado
    if (selectedUser) { // Verifica si hay un usuario seleccionado
        wxString selectedUsername = wxString(selectedUser->username); // Almacena el nombre del usuario seleccionado
        if (selectedUsername == ActiveUser) { // Verifica si el usuario seleccionado es el que ha iniciado sesi�n
            wxMessageBox("No puedes eliminar el usuario con el que has iniciado sesi�n.", "Error"); // Mensaje de error
            return;
        }
        if (selectedUser->isAdmin) { // Si el usuario es admin
            wxString enteredPassword = wxGetPasswordFromUser("Ingrese la supercontrase�a para eliminar este usuario:", "Supercontrase�a");
            if (enteredPassword == superPassword) { // Verifica la supercontrase�a
                int confirm = wxMessageBox("�Est� seguro de que desea eliminar este usuario?", "Confirmar eliminaci�n", wxYES_NO | wxICON_QUESTION); // Confirma eliminaci�n
                if (confirm == wxYES) { // Si se confirma
                    users.erase(users.begin() + userListBox->GetSelection()); // Elimina el usuario del vector
                    UpdateUserListBox(); // Actualiza la lista de usuarios en la interfaz
                    wxMessageBox("Usuario eliminado.", "Eliminado"); // Mensaje de confirmaci�n
                }
            }
            else {
                wxMessageBox("Supercontrase�a incorrecta.", "Error"); // Mensaje de error si la contrase�a es incorrecta
            }
        }
        else { // Si el usuario no es admin
            int confirm = wxMessageBox("�Est� seguro de que desea eliminar este usuario?", "Confirmar eliminaci�n", wxYES_NO | wxICON_QUESTION); // Confirma eliminaci�n
            if (confirm == wxYES) { // Si se confirma
                users.erase(users.begin() + userListBox->GetSelection()); // Elimina el usuario del vector
                UpdateUserListBox(); // Actualiza la lista de usuarios en la interfaz
                wxMessageBox("Usuario eliminado.", "Eliminado"); // Mensaje de confirmaci�n
            }
        }
    }
}

// Maneja el evento de volver a la ventana anterior
void GestionarUser::OnBack(wxCommandEvent& event) {
    wxFrame* mainWindow = new Main_GUI("Gestor Usuarios", userIsAdmin, ActiveUser); // Crea una nueva instancia de Main_GUI
    mainWindow->Show(); // Muestra la ventana principal
    this->Close(); // Cierra la ventana actual
}
