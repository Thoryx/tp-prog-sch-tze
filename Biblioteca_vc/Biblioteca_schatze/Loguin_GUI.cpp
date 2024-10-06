#include "Loguin_GUI.h"
#include "Main_GUI.h"
#include <fstream>
#include <wx/icon.h>
#include <wx/bitmap.h>
#include <wx/sizer.h>  // Para gestionar el layout

// Identificadores automáticos para gestionar eventos
enum {
    ID_Login = 1,       // ID para el botón de iniciar sesión
    ID_Register         // ID para el botón de registro
};

wxBEGIN_EVENT_TABLE(Loguin_GUI, wxFrame)
EVT_BUTTON(ID_Login, Loguin_GUI::OnLogin)       // Evento para el botón de inicio de sesión
EVT_BUTTON(ID_Register, Loguin_GUI::OnRegister) // Evento para el botón de registro
wxEND_EVENT_TABLE()

// Constructor de la clase Loguin_GUI
Loguin_GUI::Loguin_GUI(const wxString& title)
    : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(600, 350)) {

    wxPanel* panel = new wxPanel(this, wxID_ANY);
    SetBackgroundColour(wxColour(242, 230, 214)); // Establecer el color de fondo de la ventana

    // Establecer el ícono de la ventana
    wxIcon icon;
    icon.LoadFile("Icono.ico", wxBITMAP_TYPE_ICO);
    SetIcon(icon);

    // Sizer principal para organizar elementos verticalmente
    wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);

    // Cargar la imagen original y escalarla
    wxImage image(wxT("Logo2-removebg-preview.png"), wxBITMAP_TYPE_PNG);
    image = image.Scale(100, 100); // Ajustar el tamaño de la imagen

    // Convertir la imagen escalada a wxBitmap
    wxBitmap bitmap(image);
    // Agregar la imagen escalada al panel
    wxStaticBitmap* img = new wxStaticBitmap(panel, wxID_ANY, bitmap);
    vbox->Add(img, 0, wxALIGN_CENTER | wxTOP, 10); // Alinear la imagen al centro

    // Caja de texto para el nombre de usuario
    wxBoxSizer* hbox1 = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText* userLabel = new wxStaticText(panel, wxID_ANY, wxT("Usuario:"));
    userTextCtrl = new wxTextCtrl(panel, wxID_ANY); // Campo para ingresar el nombre de usuario
    hbox1->Add(userLabel, 0, wxRIGHT, 8); // Agregar etiqueta de usuario
    hbox1->Add(userTextCtrl, 1); // Agregar campo de texto de usuario

    vbox->Add(hbox1, 0, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 10); // Añadir el hbox al sizer vertical

    // Caja de texto para la contraseña
    wxBoxSizer* hbox2 = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText* passLabel = new wxStaticText(panel, wxID_ANY, wxT("Contraseña:"));
    passTextCtrl = new wxTextCtrl(panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PASSWORD); // Campo para ingresar la contraseña
    hbox2->Add(passLabel, 0, wxRIGHT, 8); // Agregar etiqueta de contraseña
    hbox2->Add(passTextCtrl, 1); // Agregar campo de texto de contraseña

    vbox->Add(hbox2, 0, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 10); // Añadir el hbox al sizer vertical

    // Botones de login y registro
    wxBoxSizer* hbox3 = new wxBoxSizer(wxHORIZONTAL);
    loginButton = new wxButton(panel, ID_Login, wxT("Iniciar Sesión")); // Botón para iniciar sesión
    registerButton = new wxButton(panel, ID_Register, wxT("Registrarse")); // Botón para registrarse
    hbox3->Add(loginButton, 0, wxRIGHT, 5); // Añadir botón de inicio de sesión
    hbox3->Add(registerButton, 0, wxLEFT, 5); // Añadir botón de registro

    vbox->Add(hbox3, 0, wxALIGN_CENTER | wxTOP, 20); // Añadir hbox de botones al sizer vertical

    // Texto de estado para mostrar mensajes al usuario
    statusText = new wxStaticText(panel, wxID_ANY, wxT(""), wxDefaultPosition, wxSize(250, 25));
    vbox->Add(statusText, 0, wxALIGN_CENTER | wxTOP, 10); // Añadir el texto de estado al sizer

    // Aplicar el sizer al panel
    panel->SetSizer(vbox);

    // Centrar la ventana en la pantalla
    Centre();
}

// Método para manejar el evento de inicio de sesión
void Loguin_GUI::OnLogin(wxCommandEvent& event) {
    std::string username = userTextCtrl->GetValue().ToStdString(); // Obtener el nombre de usuario
    std::string password = passTextCtrl->GetValue().ToStdString(); // Obtener la contraseña
    if (Authenticate(username, password)) { // Verificar credenciales
        statusText->SetLabel("¡Inicio de sesión exitoso!"); // Mensaje de éxito
        wxFrame* mainWindow = new Main_GUI("Home", currentUser.isAdmin, currentUser.username); // Crear la ventana principal
        mainWindow->Show(); // Mostrar la ventana principal
        this->Close(); // Cerrar la ventana de inicio de sesión
    }
    else {
        statusText->SetLabel("Credenciales incorrectas."); // Mensaje de error
    }
}

// Método para verificar si una cadena contiene espacios
bool Loguin_GUI::ContainsSpaces(const std::string& str) {
    return std::find_if(str.begin(), str.end(), ::isspace) != str.end(); // Retorna verdadero si hay espacios
}

// Método para manejar el evento de registro
void Loguin_GUI::OnRegister(wxCommandEvent& event) {
    std::string username = userTextCtrl->GetValue().ToStdString(); // Obtener el nombre de usuario
    std::string password = passTextCtrl->GetValue().ToStdString(); // Obtener la contraseña

    // Verificar si los campos están vacíos o contienen espacios
    if (username.empty() || ContainsSpaces(username) || password.empty() || ContainsSpaces(password)) {
        statusText->SetLabel("Nombre de usuario y contraseña no pueden estar vacíos ni contener espacios."); // Mensaje de error
        return; // Salir de la función
    }

    // Verificar la longitud de los campos
    if (username.length() > 20) {
        statusText->SetLabel("Nombre de usuario demasiado largo (máx. 20 caracteres)."); // Mensaje de error
        return; // Salir de la función
    }
    if (password.length() > 8) {
        statusText->SetLabel("Contraseña demasiado larga (máx. 8 caracteres)."); // Mensaje de error
        return; // Salir de la función
    }

    // Verificar si el nombre de usuario ya existe
    if (IsUsernameDuplicate(userTextCtrl->GetValue())) {
        statusText->SetLabel("Nombre de usuario ya registrado."); // Mensaje de error
        return; // Salir de la función
    }

    User newUser; // Crear un nuevo usuario
    strncpy(newUser.username, username.c_str(), sizeof(newUser.username)); // Copiar nombre de usuario
    strncpy(newUser.password, password.c_str(), sizeof(newUser.password)); // Copiar contraseña
    newUser.isAdmin = false; // Asegurar que no sea admin

    // Guardar el nuevo usuario
    if (SaveUser(newUser)) {
        statusText->SetLabel("¡Usuario registrado con éxito!"); // Mensaje de éxito
    }
    else {
        statusText->SetLabel("Error al registrar usuario."); // Mensaje de error
    }
}

// Método para autenticar al usuario
bool Loguin_GUI::Authenticate(const std::string& username, const std::string& password) {
    std::vector<User> users = LoadUsers(); // Cargar la lista de usuarios
    for (const auto& user : users) { // Iterar sobre los usuarios
        if (username == user.username && password == user.password) { // Verificar credenciales
            currentUser = user; // Asigna el usuario autenticado
            return true; // Autenticación exitosa
        }
    }
    return false; // Autenticación fallida
}

// Método para guardar un usuario en el archivo
bool Loguin_GUI::SaveUser(const User& user) {
    std::ofstream file("Credenciales.dat", std::ios::app | std::ios::binary); // Abrir archivo en modo append
    if (!file) {
        statusText->SetLabel("Error al abrir el archivo para guardar."); // Mensaje de error
        return false; // No se pudo abrir el archivo
    }

    file.write(reinterpret_cast<const char*>(&user), sizeof(User)); // Escribir el usuario en el archivo
    file.close(); // Cerrar el archivo

    return true; // Guardado exitoso
}

// Método para cargar usuarios desde el archivo
std::vector<User> Loguin_GUI::LoadUsers() {
    std::vector<User> users; // Vector para almacenar usuarios
    std::ifstream file("Credenciales.dat", std::ios::binary); // Abrir archivo en modo binario

    if (!file) return users;  // Retornar lista vacía si no existe el archivo

    User user;
    while (file.read(reinterpret_cast<char*>(&user), sizeof(User))) { // Leer usuarios del archivo
        users.push_back(user); // Agregar usuario al vector
    }

    file.close(); // Cerrar el archivo
    return users; // Retornar lista de usuarios
}

// Método para verificar si el nombre de usuario ya existe
bool Loguin_GUI::IsUsernameDuplicate(const wxString& username) {
    std::vector<User> users = LoadUsers(); // Cargar usuarios
    for (const auto& user : users) { // Iterar sobre los usuarios
        if (username == wxString(user.username)) { // Comparar nombres de usuario
            return true;  // Ya existe un usuario con este nombre
        }
    }
    return false;  // No hay duplicado
}
