#include "Books.h"
#include <wx/sizer.h>
#include <fstream>
#include <iostream>
#include "Main_GUI.h"

// Identificadores de eventos
enum {
    ID_AddBook = 1,       // Identificador para el bot�n de a�adir libro
    ID_DeleteBook,        // Identificador para el bot�n de eliminar libro
    ID_ModifyBook,        // Identificador para el bot�n de modificar libro
    ID_BackToMain,        // Identificador para el bot�n de volver a la ventana principal
    ID_BookList           // Identificador para la lista de libros
};

// Tabla de eventos para manejar eventos de los botones y la lista
wxBEGIN_EVENT_TABLE(Books, wxFrame)
EVT_BUTTON(ID_AddBook, Books::OnAddBook)
EVT_BUTTON(ID_DeleteBook, Books::OnDeleteBook)
EVT_BUTTON(ID_ModifyBook, Books::OnModifyBook)
EVT_BUTTON(ID_BackToMain, Books::OnBackToMain)
EVT_LISTBOX(ID_BookList, Books::OnSelectBook)  // Evento de selecci�n de libro
wxEND_EVENT_TABLE()

// Constructor de la clase Books
Books::Books(const wxString& title, bool isAdmin, const wxString& activeUser)
    : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(800, 600)),
    userIsAdmin(isAdmin), ActiveUser(activeUser) {

    // Establecer el color de fondo de la ventana
    SetBackgroundColour(wxColour(242, 230, 214));

    // Establecer el �cono de la ventana
    wxIcon icon;
    icon.LoadFile("Icono.ico", wxBITMAP_TYPE_ICO);
    SetIcon(icon);

    // Crear un panel y un sizer vertical
    wxPanel* panel = new wxPanel(this, wxID_ANY);
    wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);

    // Sizer para organizar los campos del libro en una cuadr�cula
    wxFlexGridSizer* gridSizer = new wxFlexGridSizer(4, 2, 10, 10);

    // Agregar etiquetas y campos de texto para los detalles del libro
    gridSizer->Add(new wxStaticText(panel, wxID_ANY, wxT("T�tulo:")), 0, wxALIGN_RIGHT);
    titleTextCtrl = new wxTextCtrl(panel, wxID_ANY);
    gridSizer->Add(titleTextCtrl, 1, wxEXPAND);

    gridSizer->Add(new wxStaticText(panel, wxID_ANY, wxT("Autor:")), 0, wxALIGN_RIGHT);
    authorTextCtrl = new wxTextCtrl(panel, wxID_ANY);
    gridSizer->Add(authorTextCtrl, 1, wxEXPAND);

    gridSizer->Add(new wxStaticText(panel, wxID_ANY, wxT("G�nero:")), 0, wxALIGN_RIGHT);
    genreTextCtrl = new wxTextCtrl(panel, wxID_ANY);
    gridSizer->Add(genreTextCtrl, 1, wxEXPAND);

    gridSizer->Add(new wxStaticText(panel, wxID_ANY, wxT("A�o:")), 0, wxALIGN_RIGHT);
    yearTextCtrl = new wxTextCtrl(panel, wxID_ANY);
    gridSizer->Add(yearTextCtrl, 1, wxEXPAND);

    gridSizer->AddGrowableCol(1, 1);  // Hacer que la segunda columna sea expansiva
    vbox->Add(gridSizer, 0, wxEXPAND | wxALL, 10); // A�adir el sizer al sizer vertical

    // Crear la lista de libros
    bookList = new wxListBox(panel, ID_BookList);
    vbox->Add(bookList, 1, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 10);

    // Sizer horizontal para los botones de control
    wxBoxSizer* hbox = new wxBoxSizer(wxHORIZONTAL);
    wxButton* addButton = new wxButton(panel, ID_AddBook, wxT("A�adir libro"));       // Bot�n para a�adir libro
    wxButton* modifyButton = new wxButton(panel, ID_ModifyBook, wxT("Modificar libro")); // Bot�n para modificar libro
    wxButton* deleteButton = new wxButton(panel, ID_DeleteBook, wxT("Eliminar libro"));  // Bot�n para eliminar libro
    wxButton* backButton = new wxButton(panel, ID_BackToMain, wxT("Volver a la ventana principal")); // Bot�n para volver

    // Agregar botones al sizer horizontal
    hbox->Add(addButton, 0, wxRIGHT, 5);
    hbox->Add(modifyButton, 0, wxRIGHT, 5);
    hbox->Add(deleteButton, 0, wxRIGHT, 5);
    hbox->Add(backButton, 0, wxRIGHT, 5);

    vbox->Add(hbox, 0, wxALIGN_CENTER | wxALL, 10); // A�adir el sizer de botones al sizer vertical

    // Texto de estado para mostrar mensajes al usuario
    statusText = new wxStaticText(panel, wxID_ANY, wxT(""));
    vbox->Add(statusText, 0, wxALIGN_CENTER | wxBOTTOM, 10);

    panel->SetSizer(vbox); // Establecer el sizer en el panel

    // Cargar los libros desde el archivo y mostrarlos en la lista
    std::vector<Book> books = LoadBooks();
    for (const auto& book : books) {
        bookList->Append(wxString(book.title)); // Agregar cada libro a la lista
    }

    // Centrar la ventana en la pantalla
    Centre();
}

// M�todo para a�adir un libro
void Books::OnAddBook(wxCommandEvent& event) {
    Book newBook; // Crear un nuevo libro

    // Obtener los valores de los campos de texto y almacenarlos en el nuevo libro
    strncpy(newBook.title, titleTextCtrl->GetValue().ToStdString().c_str(), sizeof(newBook.title));
    strncpy(newBook.author, authorTextCtrl->GetValue().ToStdString().c_str(), sizeof(newBook.author));
    strncpy(newBook.genre, genreTextCtrl->GetValue().ToStdString().c_str(), sizeof(newBook.genre));
    newBook.year = wxAtoi(yearTextCtrl->GetValue());

    // Cargar los libros existentes, agregar el nuevo libro y guardarlos
    std::vector<Book> books = LoadBooks();
    books.push_back(newBook);
    SaveBooks(books);

    // A�adir el t�tulo del nuevo libro a la lista
    bookList->Append(wxString(newBook.title));
    statusText->SetLabel("�Libro a�adido!"); // Mensaje de �xito
}

// M�todo para eliminar un libro
void Books::OnDeleteBook(wxCommandEvent& event) {
    int selection = bookList->GetSelection(); // Obtener la selecci�n actual de la lista
    if (selection != wxNOT_FOUND) { // Verificar si hay un libro seleccionado
        std::vector<Book> books = LoadBooks(); // Cargar los libros
        books.erase(books.begin() + selection); // Eliminar el libro seleccionado
        SaveBooks(books); // Guardar la lista actualizada

        bookList->Delete(selection); // Eliminar el libro de la lista
        statusText->SetLabel("�Libro eliminado!"); // Mensaje de �xito
    }
    else {
        statusText->SetLabel("No se ha seleccionado ning�n libro."); // Mensaje de advertencia
    }
}

// M�todo para modificar un libro
void Books::OnModifyBook(wxCommandEvent& event) {
    int selection = bookList->GetSelection(); // Obtener la selecci�n actual de la lista
    if (selection != wxNOT_FOUND) { // Verificar si hay un libro seleccionado
        Book modifiedBook; // Crear un libro modificado

        // Obtener los valores de los campos de texto y almacenarlos en el libro modificado
        strncpy(modifiedBook.title, titleTextCtrl->GetValue().ToStdString().c_str(), sizeof(modifiedBook.title));
        strncpy(modifiedBook.author, authorTextCtrl->GetValue().ToStdString().c_str(), sizeof(modifiedBook.author));
        strncpy(modifiedBook.genre, genreTextCtrl->GetValue().ToStdString().c_str(), sizeof(modifiedBook.genre));
        modifiedBook.year = wxAtoi(yearTextCtrl->GetValue());

        std::vector<Book> books = LoadBooks(); // Cargar los libros existentes
        books[selection] = modifiedBook; // Actualizar el libro seleccionado con los nuevos valores
        SaveBooks(books); // Guardar la lista actualizada

        bookList->SetString(selection, wxString(modifiedBook.title)); // Actualizar la lista visualmente
        statusText->SetLabel("�Libro modificado!"); // Mensaje de �xito
    }
    else {
        statusText->SetLabel("No se ha seleccionado ning�n libro."); // Mensaje de advertencia
    }
}

// M�todo para volver a la ventana principal
void Books::OnBackToMain(wxCommandEvent& event) {
    wxFrame* mainWindow = new Main_GUI("Main Window", userIsAdmin, ActiveUser); // Crear instancia de Main_GUI
    mainWindow->Show(); // Mostrar la ventana principal
    this->Close(); // Cerrar la ventana actual (Books)
}

// M�todo para manejar la selecci�n de un libro en la lista
void Books::OnSelectBook(wxCommandEvent& event) {
    int selection = bookList->GetSelection(); // Obtener la selecci�n actual de la lista
    if (selection != wxNOT_FOUND) { // Verificar si hay un libro seleccionado
        std::vector<Book> books = LoadBooks(); // Cargar los libros
        if (selection < books.size()) { // Verificar que la selecci�n sea v�lida
            const Book& selectedBook = books[selection]; // Obtener el libro seleccionado
            // Rellenar los campos de texto con los detalles del libro seleccionado
            titleTextCtrl->SetValue(wxString(selectedBook.title));
            authorTextCtrl->SetValue(wxString(selectedBook.author));
            genreTextCtrl->SetValue(wxString(selectedBook.genre));
            yearTextCtrl->SetValue(wxString::Format(wxT("%d"), selectedBook.year));
        }
    }
}

// M�todo para cargar los libros desde un archivo
std::vector<Book> Books::LoadBooks() {
    std::vector<Book> books; // Vector para almacenar los libros
    std::ifstream file("books.dat", std::ios::binary); // Abrir el archivo en modo binario
    if (!file) return books; // Retornar vac�o si no se puede abrir el archivo

    Book book;
    // Leer los libros del archivo y almacenarlos en el vector
    while (file.read(reinterpret_cast<char*>(&book), sizeof(Book))) {
        books.push_back(book);
    }
    file.close(); // Cerrar el archivo
    return books; // Retornar el vector de libros
}

// M�todo para guardar los libros en un archivo
void Books::SaveBooks(const std::vector<Book>& books) {
    std::ofstream file("books.dat", std::ios::binary | std::ios::trunc); // Abrir el archivo en modo binario y truncar
    if (!file) {
        wxLogError("Error al abrir el archivo para guardar."); // Mensaje de error si no se puede abrir
        return; // Salir del m�todo
    }

    // Escribir cada libro en el archivo
    for (const auto& book : books) {
        file.write(reinterpret_cast<const char*>(&book), sizeof(Book));
    }
    file.close(); // Cerrar el archivo
}
