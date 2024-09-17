#include "Loguin_GUI.h"
#include "Main_GUI.h"
#include <fstream>
#include <wx/icon.h>
#include <wx/bitmap.h>
#include <wx/sizer.h>  // Para gestionar el layout

//auto id para gestionar eventos
enum {
    ID_Login = 1,
    ID_Register
};

wxBEGIN_EVENT_TABLE(Loguin_GUI, wxFrame)
EVT_BUTTON(ID_Login, Loguin_GUI::OnLogin)
EVT_BUTTON(ID_Register, Loguin_GUI::OnRegister)
wxEND_EVENT_TABLE()

Loguin_GUI::Loguin_GUI(const wxString& title)
    : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(600, 350)) {

    wxPanel* panel = new wxPanel(this, wxID_ANY);
    SetBackgroundColour(wxColour(242, 230, 214));
    // Establecer el ícono de la ventana
    wxIcon icon;
    icon.LoadFile("Icono.ico", wxBITMAP_TYPE_ICO);
    SetIcon(icon);

    // Sizer principal para organizar elementos
    wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);

    // Cargar la imagen original y escalarla
    wxImage image(wxT("Logo2-removebg-preview.png"), wxBITMAP_TYPE_PNG);

    // Ajustar el tamaño de la imagen 
    image = image.Scale(100, 100);

    // Convertir la imagen escalada a wxBitmap
    wxBitmap bitmap(image);

    // Agregar la imagen escalada al panel
    wxStaticBitmap* img = new wxStaticBitmap(panel, wxID_ANY, bitmap);
    vbox->Add(img, 0, wxALIGN_CENTER | wxTOP, 10);

    // Caja de texto para el nombre de usuario
    wxBoxSizer* hbox1 = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText* userLabel = new wxStaticText(panel, wxID_ANY, wxT("Usuario:"));
    userTextCtrl = new wxTextCtrl(panel, wxID_ANY);
    hbox1->Add(userLabel, 0, wxRIGHT, 8);
    hbox1->Add(userTextCtrl, 1);

    vbox->Add(hbox1, 0, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 10);

    // Caja de texto para la contraseña
    wxBoxSizer* hbox2 = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText* passLabel = new wxStaticText(panel, wxID_ANY, wxT("Contraseña:"));
    passTextCtrl = new wxTextCtrl(panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PASSWORD);
    hbox2->Add(passLabel, 0, wxRIGHT, 8);
    hbox2->Add(passTextCtrl, 1);

    vbox->Add(hbox2, 0, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 10);

    // Botones de login y registro
    wxBoxSizer* hbox3 = new wxBoxSizer(wxHORIZONTAL);
    loginButton = new wxButton(panel, ID_Login, wxT("Iniciar Sesión"));
    registerButton = new wxButton(panel, ID_Register, wxT("Registrarse"));
    hbox3->Add(loginButton, 0, wxRIGHT, 5);
    hbox3->Add(registerButton, 0, wxLEFT, 5);

    vbox->Add(hbox3, 0, wxALIGN_CENTER | wxTOP, 20);

    // Texto de estado para mostrar mensajes
    statusText = new wxStaticText(panel, wxID_ANY, wxT(""), wxDefaultPosition, wxSize(250, 25));
    vbox->Add(statusText, 0, wxALIGN_CENTER | wxTOP, 10);

    // Aplicar el Sizer al panel
    panel->SetSizer(vbox);

    // Centrar la ventana
    Centre();
}

void Loguin_GUI::OnLogin(wxCommandEvent& event) {
    std::string username = userTextCtrl->GetValue().ToStdString();
    std::string password = passTextCtrl->GetValue().ToStdString();
    if (Authenticate(username, password)) {
        statusText->SetLabel("¡Inicio de sesión exitoso!");
        wxFrame* mainWindow = new Main_GUI("Home", currentUser.isAdmin, currentUser.username);
        mainWindow->Show();
        this->Close();
    }
    else {
        statusText->SetLabel("Credenciales incorrectas.");
    }
}

bool Loguin_GUI::ContainsSpaces(const std::string& str) {
    return std::find_if(str.begin(), str.end(), ::isspace) != str.end();
}

void Loguin_GUI::OnRegister(wxCommandEvent& event) {
    std::string username = userTextCtrl->GetValue().ToStdString();
    std::string password = passTextCtrl->GetValue().ToStdString();

    // Verificar si los campos están vacíos o contienen espacios
    if (username.empty() || ContainsSpaces(username) || password.empty() || ContainsSpaces(password)) {
        statusText->SetLabel("Nombre de usuario y contraseña no pueden estar vacíos ni contener espacios.");
        return;
    }

    // Verificar la longitud de los campos
    if (username.length() > 20) {
        statusText->SetLabel("Nombre de usuario demasiado largo (máx. 20 caracteres).");
        return;
    }
    if (password.length() > 8) {
        statusText->SetLabel("Contraseña demasiado larga (máx. 8 caracteres).");
        return;
    }

    // Verificar si el nombre de usuario ya existe
    if (IsUsernameDuplicate(userTextCtrl->GetValue())) {
        statusText->SetLabel("Nombre de usuario ya registrado.");
        return;
    }

    User newUser;
    strncpy(newUser.username, username.c_str(), sizeof(newUser.username));
    strncpy(newUser.password, password.c_str(), sizeof(newUser.password));
    newUser.isAdmin = false;  // Aquí aseguramos explícitamente que no sea admin

    if (SaveUser(newUser)) {
        statusText->SetLabel("¡Usuario registrado con éxito!");
    }
    else {
        statusText->SetLabel("Error al registrar usuario.");
    }
}

bool Loguin_GUI::Authenticate(const std::string& username, const std::string& password) {
    std::vector<User> users = LoadUsers();
    for (const auto& user : users) {
        if (username == user.username && password == user.password) {
            currentUser = user;  // Asigna el usuario autenticado
            return true;
        }
    }
    return false;
}

bool Loguin_GUI::SaveUser(const User& user) {
    std::ofstream file("Credenciales.dat", std::ios::app | std::ios::binary);
    if (!file) {
        statusText->SetLabel("Error al abrir el archivo para guardar.");
        return false;
    }

    file.write(reinterpret_cast<const char*>(&user), sizeof(User));
    file.close();

    return true;
}

std::vector<User> Loguin_GUI::LoadUsers() {
    std::vector<User> users;
    std::ifstream file("Credenciales.dat", std::ios::binary);

    if (!file) return users;  // Retorna lista vacía si no existe el archivo

    User user;
    while (file.read(reinterpret_cast<char*>(&user), sizeof(User))) {
        users.push_back(user);
    }

    file.close();
    return users;
}

// Ahora verifica los usuarios cargados directamente desde el archivo
bool Loguin_GUI::IsUsernameDuplicate(const wxString& username) {
    std::vector<User> users = LoadUsers();
    for (const auto& user : users) {
        if (username == wxString(user.username)) {
            return true;  // Ya existe un usuario con este nombre
        }
    }
    return false;  // No hay duplicado
}
