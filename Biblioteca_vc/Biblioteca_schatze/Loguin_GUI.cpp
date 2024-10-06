#include "Loguin_GUI.h"
#include "Main_GUI.h"
#include <fstream>
#include <wx/icon.h>
#include <wx/bitmap.h>
#include <wx/sizer.h>  // Para gestionar el layout

// Identificadores autom�ticos para gestionar eventos
enum {
    ID_Login = 1,       // ID para el bot�n de iniciar sesi�n
    ID_Register         // ID para el bot�n de registro
};

wxBEGIN_EVENT_TABLE(Loguin_GUI, wxFrame)
EVT_BUTTON(ID_Login, Loguin_GUI::OnLogin)       // Evento para el bot�n de inicio de sesi�n
EVT_BUTTON(ID_Register, Loguin_GUI::OnRegister) // Evento para el bot�n de registro
wxEND_EVENT_TABLE()

// Constructor de la clase Loguin_GUI
Loguin_GUI::Loguin_GUI(const wxString& title)
    : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(600, 350)) {

    wxPanel* panel = new wxPanel(this, wxID_ANY);
    SetBackgroundColour(wxColour(242, 230, 214)); // Establecer el color de fondo de la ventana

    // Establecer el �cono de la ventana
    wxIcon icon;
    icon.LoadFile("Icono.ico", wxBITMAP_TYPE_ICO);
    SetIcon(icon);

    // Sizer principal para organizar elementos verticalmente
    wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);

    // Cargar la imagen original y escalarla
    wxImage image(wxT("Logo2-removebg-preview.png"), wxBITMAP_TYPE_PNG);
    image = image.Scale(100, 100); // Ajustar el tama�o de la imagen

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

    vbox->Add(hbox1, 0, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 10); // A�adir el hbox al sizer vertical

    // Caja de texto para la contrase�a
    wxBoxSizer* hbox2 = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText* passLabel = new wxStaticText(panel, wxID_ANY, wxT("Contrase�a:"));
    passTextCtrl = new wxTextCtrl(panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PASSWORD); // Campo para ingresar la contrase�a
    hbox2->Add(passLabel, 0, wxRIGHT, 8); // Agregar etiqueta de contrase�a
    hbox2->Add(passTextCtrl, 1); // Agregar campo de texto de contrase�a

    vbox->Add(hbox2, 0, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 10); // A�adir el hbox al sizer vertical

    // Botones de login y registro
    wxBoxSizer* hbox3 = new wxBoxSizer(wxHORIZONTAL);
    loginButton = new wxButton(panel, ID_Login, wxT("Iniciar Sesi�n")); // Bot�n para iniciar sesi�n
    registerButton = new wxButton(panel, ID_Register, wxT("Registrarse")); // Bot�n para registrarse
    hbox3->Add(loginButton, 0, wxRIGHT, 5); // A�adir bot�n de inicio de sesi�n
    hbox3->Add(registerButton, 0, wxLEFT, 5); // A�adir bot�n de registro

    vbox->Add(hbox3, 0, wxALIGN_CENTER | wxTOP, 20); // A�adir hbox de botones al sizer vertical

    // Texto de estado para mostrar mensajes al usuario
    statusText = new wxStaticText(panel, wxID_ANY, wxT(""), wxDefaultPosition, wxSize(250, 25));
    vbox->Add(statusText, 0, wxALIGN_CENTER | wxTOP, 10); // A�adir el texto de estado al sizer

    // Aplicar el sizer al panel
    panel->SetSizer(vbox);

    // Centrar la ventana en la pantalla
    Centre();
}

// M�todo para manejar el evento de inicio de sesi�n
void Loguin_GUI::OnLogin(wxCommandEvent& event) {
    std::string username = userTextCtrl->GetValue().ToStdString(); // Obtener el nombre de usuario
    std::string password = passTextCtrl->GetValue().ToStdString(); // Obtener la contrase�a
    if (Authenticate(username, password)) { // Verificar credenciales
        statusText->SetLabel("�Inicio de sesi�n exitoso!"); // Mensaje de �xito
        wxFrame* mainWindow = new Main_GUI("Home", currentUser.isAdmin, currentUser.username); // Crear la ventana principal
        mainWindow->Show(); // Mostrar la ventana principal
        this->Close(); // Cerrar la ventana de inicio de sesi�n
    }
    else {
        statusText->SetLabel("Credenciales incorrectas."); // Mensaje de error
    }
}

// M�todo para verificar si una cadena contiene espacios
bool Loguin_GUI::ContainsSpaces(const std::string& str) {
    return std::find_if(str.begin(), str.end(), ::isspace) != str.end(); // Retorna verdadero si hay espacios
}

// M�todo para manejar el evento de registro
void Loguin_GUI::OnRegister(wxCommandEvent& event) {
    std::string username = userTextCtrl->GetValue().ToStdString(); // Obtener el nombre de usuario
    std::string password = passTextCtrl->GetValue().ToStdString(); // Obtener la contrase�a

    // Verificar si los campos est�n vac�os o contienen espacios
    if (username.empty() || ContainsSpaces(username) || password.empty() || ContainsSpaces(password)) {
        statusText->SetLabel("Nombre de usuario y contrase�a no pueden estar vac�os ni contener espacios."); // Mensaje de error
        return; // Salir de la funci�n
    }

    // Verificar la longitud de los campos
    if (username.length() > 20) {
        statusText->SetLabel("Nombre de usuario demasiado largo (m�x. 20 caracteres)."); // Mensaje de error
        return; // Salir de la funci�n
    }
    if (password.length() > 8) {
        statusText->SetLabel("Contrase�a demasiado larga (m�x. 8 caracteres)."); // Mensaje de error
        return; // Salir de la funci�n
    }

    // Verificar si el nombre de usuario ya existe
    if (IsUsernameDuplicate(userTextCtrl->GetValue())) {
        statusText->SetLabel("Nombre de usuario ya registrado."); // Mensaje de error
        return; // Salir de la funci�n
    }

    User newUser; // Crear un nuevo usuario
    strncpy(newUser.username, username.c_str(), sizeof(newUser.username)); // Copiar nombre de usuario
    strncpy(newUser.password, password.c_str(), sizeof(newUser.password)); // Copiar contrase�a
    newUser.isAdmin = false; // Asegurar que no sea admin

    // Guardar el nuevo usuario
    if (SaveUser(newUser)) {
        statusText->SetLabel("�Usuario registrado con �xito!"); // Mensaje de �xito
    }
    else {
        statusText->SetLabel("Error al registrar usuario."); // Mensaje de error
    }
}

// M�todo para autenticar al usuario
bool Loguin_GUI::Authenticate(const std::string& username, const std::string& password) {
    std::vector<User> users = LoadUsers(); // Cargar la lista de usuarios
    for (const auto& user : users) { // Iterar sobre los usuarios
        if (username == user.username && password == user.password) { // Verificar credenciales
            currentUser = user; // Asigna el usuario autenticado
            return true; // Autenticaci�n exitosa
        }
    }
    return false; // Autenticaci�n fallida
}

// M�todo para guardar un usuario en el archivo
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

// M�todo para cargar usuarios desde el archivo
std::vector<User> Loguin_GUI::LoadUsers() {
    std::vector<User> users; // Vector para almacenar usuarios
    std::ifstream file("Credenciales.dat", std::ios::binary); // Abrir archivo en modo binario

    if (!file) return users;  // Retornar lista vac�a si no existe el archivo

    User user;
    while (file.read(reinterpret_cast<char*>(&user), sizeof(User))) { // Leer usuarios del archivo
        users.push_back(user); // Agregar usuario al vector
    }

    file.close(); // Cerrar el archivo
    return users; // Retornar lista de usuarios
}

// M�todo para verificar si el nombre de usuario ya existe
bool Loguin_GUI::IsUsernameDuplicate(const wxString& username) {
    std::vector<User> users = LoadUsers(); // Cargar usuarios
    for (const auto& user : users) { // Iterar sobre los usuarios
        if (username == wxString(user.username)) { // Comparar nombres de usuario
            return true;  // Ya existe un usuario con este nombre
        }
    }
    return false;  // No hay duplicado
}
