#include "GestionarUser.h"

#define DATA_FILE "Credenciales.dat"

enum {
    ID_EDIT_USER = wxID_HIGHEST + 1,
    ID_EDIT_PASSWORD,
    ID_TOGGLE_ADMIN,
    ID_DELETE_USER,
    ID_BACK_BUTTON
};

wxBEGIN_EVENT_TABLE(GestionarUser, wxFrame)
EVT_LISTBOX(wxID_ANY, GestionarUser::OnSelectUser)
EVT_BUTTON(ID_EDIT_USER, GestionarUser::OnEditUser)
EVT_BUTTON(ID_EDIT_PASSWORD, GestionarUser::OnEditPassword)
EVT_BUTTON(ID_TOGGLE_ADMIN, GestionarUser::OnToggleAdmin)
EVT_BUTTON(ID_DELETE_USER, GestionarUser::OnDeleteUser)
EVT_BUTTON(ID_BACK_BUTTON, GestionarUser::OnBack)
wxEND_EVENT_TABLE()

GestionarUser::GestionarUser(const wxString& title, const wxString& activeUser)
    : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(400, 400)),
    activeUser(activeUser) {

    userListBox = new wxListBox(this, wxID_ANY, wxPoint(10, 10), wxSize(180, 300));
    editUserButton = new wxButton(this, ID_EDIT_USER, "Editar Usuario", wxPoint(200, 10), wxSize(150, 30));
    editPasswordButton = new wxButton(this, ID_EDIT_PASSWORD, "Editar Contraseña", wxPoint(200, 50), wxSize(150, 30));
    toggleAdminButton = new wxButton(this, ID_TOGGLE_ADMIN, "Cambiar Rol Admin", wxPoint(200, 90), wxSize(150, 30));
    deleteUserButton = new wxButton(this, ID_DELETE_USER, "Eliminar Usuario", wxPoint(200, 130), wxSize(150, 30));
    backButton = new wxButton(this, ID_BACK_BUTTON, "Volver", wxPoint(200, 170), wxSize(150, 30));

    SetBackgroundColour(wxColour(242, 230, 214));
    // Establecer el ícono de la ventana
    wxIcon icon;
    icon.LoadFile("Icono.ico", wxBITMAP_TYPE_ICO);
    SetIcon(icon);

    LoadUsersFromFile();
    UpdateUserListBox();
}

GestionarUser::~GestionarUser() {
    SaveUsersToFile();
}

void GestionarUser::LoadUsersFromFile() {
    std::ifstream file(DATA_FILE, std::ios::binary);
    if (file.is_open()) {
        User tempUser;
        while (file.read(reinterpret_cast<char*>(&tempUser), sizeof(User))) {
            users.push_back(tempUser);
        }
        file.close();
    }
}

void GestionarUser::SaveUsersToFile() {
    std::ofstream file(DATA_FILE, std::ios::binary | std::ios::trunc);
    if (file.is_open()) {
        for (const auto& user : users) {
            file.write(reinterpret_cast<const char*>(&user), sizeof(User));
        }
        file.close();
    }
}

void GestionarUser::UpdateUserListBox() {
    userListBox->Clear();
    for (const auto& user : users) {
        userListBox->Append(user.username);
    }
}

User* GestionarUser::GetSelectedUser() {
    int selection = userListBox->GetSelection();
    if (selection != wxNOT_FOUND) {
        return &users[selection];
    }
    return nullptr;
}

// Verificar si el nombre de usuario ya existe
bool GestionarUser::IsUsernameDuplicate(const wxString& username) {
    for (const auto& user : users) {
        if (username == wxString(user.username)) {
            return true;  // Ya existe un usuario con este nombre
        }
    }
    return false;  // No hay duplicado
}

void GestionarUser::OnSelectUser(wxCommandEvent& event) {
    wxString selectedUser = userListBox->GetStringSelection();
}

// Editar nombre de usuario
void GestionarUser::OnEditUser(wxCommandEvent& event) {
    User* selectedUser = GetSelectedUser();
    wxString newUsername;
    if (selectedUser) {
        if (selectedUser->isAdmin) {
            wxString enteredPassword = wxGetPasswordFromUser("Ingrese la supercontraseña para cambiar el usuario:", "Supercontraseña");
            if (enteredPassword == superPassword) {
                wxString newUsername = wxGetTextFromUser("Ingrese el nuevo nombre de usuario:", "Editar Usuario");
            }
            else {
                wxMessageBox("Supercontraseña incorrecta.", "Error");
            }
        }
        else {
             newUsername = wxGetTextFromUser("Ingrese el nuevo nombre de usuario:", "Editar Usuario");
        }
        if (!newUsername.IsEmpty()) {
            if (IsUsernameDuplicate(newUsername)) {
                wxMessageBox("Este nombre de usuario ya existe. Elige uno diferente.", "Error");
            }
            else {
                strncpy(selectedUser->username, newUsername.mb_str(), sizeof(selectedUser->username) - 1);
                UpdateUserListBox();
            }
        }
    }
}

// Editar contraseña
void GestionarUser::OnEditPassword(wxCommandEvent& event) {
    User* selectedUser = GetSelectedUser();
    wxString newPassword;
    if (selectedUser) {
        if (selectedUser->isAdmin) {
            wxString enteredPassword = wxGetPasswordFromUser("Ingrese la supercontraseña para cambiar la contraseña:", "Supercontraseña");
            if (enteredPassword == superPassword) {

                 newPassword = wxGetPasswordFromUser("Ingrese la nueva contraseña:", "Editar Contraseña");

            }
            else {
                wxMessageBox("Supercontraseña incorrecta.", "Error");
            }
        }
        else {
           newPassword = wxGetPasswordFromUser("Ingrese la nueva contraseña:", "Editar Contraseña");
        }
        if (!newPassword.IsEmpty()) {
            strncpy(selectedUser->password, newPassword.mb_str(), sizeof(selectedUser->password) - 1);
        }
    }
}

// Cambiar rol de administrador
void GestionarUser::OnToggleAdmin(wxCommandEvent& event) {
    User* selectedUser = GetSelectedUser();
    if (selectedUser) {
        if (selectedUser->isAdmin) {
            wxString enteredPassword = wxGetPasswordFromUser("Ingrese la supercontraseña para cambiar el rol:", "Supercontraseña");
            if (enteredPassword == superPassword) {
                selectedUser->isAdmin = false;
                wxMessageBox("El usuario ahora es un usuario regular.", "Cambio de Rol");
            }
            else {
                wxMessageBox("Supercontraseña incorrecta.", "Error");
            }
        }
        else {
            selectedUser->isAdmin = true;
            wxMessageBox("El usuario ahora es Administrador.", "Cambio de Rol");
        }
    }
}

// Eliminar usuario
void GestionarUser::OnDeleteUser(wxCommandEvent& event) {
    User* selectedUser = GetSelectedUser();
    if (selectedUser) {
        wxString selectedUsername = wxString(selectedUser->username);
        if (selectedUsername == activeUser) {
            wxMessageBox("No puedes eliminar el usuario con el que has iniciado sesión.", "Error");
            return;
        }
        if (selectedUser->isAdmin) {
            wxString enteredPassword = wxGetPasswordFromUser("Ingrese la supercontraseña para cambiar el rol:", "Supercontraseña");
            if (enteredPassword == superPassword) {
                int confirm = wxMessageBox("¿Está seguro de que desea eliminar este usuario?", "Confirmar eliminación", wxYES_NO | wxICON_QUESTION);
                if (confirm == wxYES) {
                    users.erase(users.begin() + userListBox->GetSelection());
                    UpdateUserListBox();
                    wxMessageBox("Usuario eliminado.", "Eliminado");
                }
            }
            else {
                wxMessageBox("Supercontraseña incorrecta.", "Error");
            }
        }
        else {
            int confirm = wxMessageBox("¿Está seguro de que desea eliminar este usuario?", "Confirmar eliminación", wxYES_NO | wxICON_QUESTION);
            if (confirm == wxYES) {
                users.erase(users.begin() + userListBox->GetSelection());
                UpdateUserListBox();
                wxMessageBox("Usuario eliminado.", "Eliminado");
            }
        }
    }
}

void GestionarUser::OnBack(wxCommandEvent& event) {
    Close();
}
