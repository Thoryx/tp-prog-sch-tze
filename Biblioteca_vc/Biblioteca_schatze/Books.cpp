#include "Books.h"
#include <wx/sizer.h>

#include <fstream>
#include <iostream>

#include "Main_GUI.h"

// Identificadores de eventos
enum {
    ID_AddBook = 1,
    ID_DeleteBook,
    ID_ModifyBook,
    ID_BackToMain,
    ID_BookList
};

wxBEGIN_EVENT_TABLE(Books, wxFrame)
EVT_BUTTON(ID_AddBook, Books::OnAddBook)
EVT_BUTTON(ID_DeleteBook, Books::OnDeleteBook)
EVT_BUTTON(ID_ModifyBook, Books::OnModifyBook)
EVT_BUTTON(ID_BackToMain, Books::OnBackToMain)
EVT_LISTBOX(ID_BookList, Books::OnSelectBook)  // Evento de selección
wxEND_EVENT_TABLE()

Books::Books(const wxString& title, bool isAdmin, const wxString& activeUser)
    : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(800, 600)),
    userIsAdmin(isAdmin), ActiveUser(activeUser) {

    SetBackgroundColour(wxColour(242, 230, 214));
    // Establecer el ícono de la ventana
    wxIcon icon;
    icon.LoadFile("Icono.ico", wxBITMAP_TYPE_ICO);
    SetIcon(icon);
    wxPanel* panel = new wxPanel(this, wxID_ANY);
    wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);

    // Sizer para organizar los campos del libro
    wxFlexGridSizer* gridSizer = new wxFlexGridSizer(4, 2, 10, 10);
    gridSizer->Add(new wxStaticText(panel, wxID_ANY, wxT("Título:")), 0, wxALIGN_RIGHT);
    titleTextCtrl = new wxTextCtrl(panel, wxID_ANY);
    gridSizer->Add(titleTextCtrl, 1, wxEXPAND);

    gridSizer->Add(new wxStaticText(panel, wxID_ANY, wxT("Autor:")), 0, wxALIGN_RIGHT);
    authorTextCtrl = new wxTextCtrl(panel, wxID_ANY);
    gridSizer->Add(authorTextCtrl, 1, wxEXPAND);

    gridSizer->Add(new wxStaticText(panel, wxID_ANY, wxT("Género:")), 0, wxALIGN_RIGHT);
    genreTextCtrl = new wxTextCtrl(panel, wxID_ANY);
    gridSizer->Add(genreTextCtrl, 1, wxEXPAND);

    gridSizer->Add(new wxStaticText(panel, wxID_ANY, wxT("Año:")), 0, wxALIGN_RIGHT);
    yearTextCtrl = new wxTextCtrl(panel, wxID_ANY);
    gridSizer->Add(yearTextCtrl, 1, wxEXPAND);

    gridSizer->AddGrowableCol(1, 1);  // Hacer que la segunda columna sea expansiva.
    vbox->Add(gridSizer, 0, wxEXPAND | wxALL, 10);

    // Lista de libros
    bookList = new wxListBox(panel, ID_BookList);
    vbox->Add(bookList, 1, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 10);

    // Botones de control
    wxBoxSizer* hbox = new wxBoxSizer(wxHORIZONTAL);
    wxButton* addButton = new wxButton(panel, ID_AddBook, wxT("Añadir libro"));
    wxButton* modifyButton = new wxButton(panel, ID_ModifyBook, wxT("Modificar libro"));
    wxButton* deleteButton = new wxButton(panel, ID_DeleteBook, wxT("Eliminar libro"));
    wxButton* backButton = new wxButton(panel, ID_BackToMain, wxT("Volver a la ventana principal"));

    hbox->Add(addButton, 0, wxRIGHT, 5);
    hbox->Add(modifyButton, 0, wxRIGHT, 5);
    hbox->Add(deleteButton, 0, wxRIGHT, 5);
    hbox->Add(backButton, 0, wxRIGHT, 5);

    vbox->Add(hbox, 0, wxALIGN_CENTER | wxALL, 10);

    // Texto de estado para mensajes
    statusText = new wxStaticText(panel, wxID_ANY, wxT(""));
    vbox->Add(statusText, 0, wxALIGN_CENTER | wxBOTTOM, 10);

    panel->SetSizer(vbox);

    // Cargar los libros desde el archivo
    std::vector<Book> books = LoadBooks();
    for (const auto& book : books) {
        bookList->Append(wxString(book.title));
    }

    // Centrar la ventana
    Centre();
}

void Books::OnAddBook(wxCommandEvent& event) {
    // Implementa la lógica para añadir un libro
    Book newBook;
    strncpy(newBook.title, titleTextCtrl->GetValue().ToStdString().c_str(), sizeof(newBook.title));
    strncpy(newBook.author, authorTextCtrl->GetValue().ToStdString().c_str(), sizeof(newBook.author));
    strncpy(newBook.genre, genreTextCtrl->GetValue().ToStdString().c_str(), sizeof(newBook.genre));
    newBook.year = wxAtoi(yearTextCtrl->GetValue());

    // Añadir el libro a la lista y guardarlo en el archivo
    std::vector<Book> books = LoadBooks();
    books.push_back(newBook);
    SaveBooks(books);

    bookList->Append(wxString(newBook.title));
    statusText->SetLabel("¡Libro añadido!");
}

void Books::OnDeleteBook(wxCommandEvent& event) {
    int selection = bookList->GetSelection();
    if (selection != wxNOT_FOUND) {
        std::vector<Book> books = LoadBooks();
        books.erase(books.begin() + selection);
        SaveBooks(books);

        bookList->Delete(selection);
        statusText->SetLabel("¡Libro eliminado!");
    }
    else {
        statusText->SetLabel("No se ha seleccionado ningún libro.");
    }
}

void Books::OnModifyBook(wxCommandEvent& event) {
    int selection = bookList->GetSelection();
    if (selection != wxNOT_FOUND) {
        Book modifiedBook;
        strncpy(modifiedBook.title, titleTextCtrl->GetValue().ToStdString().c_str(), sizeof(modifiedBook.title));
        strncpy(modifiedBook.author, authorTextCtrl->GetValue().ToStdString().c_str(), sizeof(modifiedBook.author));
        strncpy(modifiedBook.genre, genreTextCtrl->GetValue().ToStdString().c_str(), sizeof(modifiedBook.genre));
        modifiedBook.year = wxAtoi(yearTextCtrl->GetValue());

        std::vector<Book> books = LoadBooks();
        books[selection] = modifiedBook;
        SaveBooks(books);

        bookList->SetString(selection, wxString(modifiedBook.title));
        statusText->SetLabel("¡Libro modificado!");
    }
    else {
        statusText->SetLabel("No se ha seleccionado ningún libro.");
    }
}

void Books::OnBackToMain(wxCommandEvent& event) {
    wxFrame* mainWindow = new Main_GUI("Main Window",userIsAdmin,ActiveUser);  // Crear instancia de Main_GUI
    mainWindow->Show();
    this->Close();  // Cerrar la ventana actual (Books)
}

void Books::OnSelectBook(wxCommandEvent& event) {
    int selection = bookList->GetSelection();
    if (selection != wxNOT_FOUND) {
        std::vector<Book> books = LoadBooks();
        if (selection < books.size()) {
            const Book& selectedBook = books[selection];
            titleTextCtrl->SetValue(wxString(selectedBook.title));
            authorTextCtrl->SetValue(wxString(selectedBook.author));
            genreTextCtrl->SetValue(wxString(selectedBook.genre));
            yearTextCtrl->SetValue(wxString::Format(wxT("%d"), selectedBook.year));
        }
    }
}

std::vector<Book> Books::LoadBooks() {
    std::vector<Book> books;
    std::ifstream file("books.dat", std::ios::binary);
    if (!file) return books;

    Book book;
    while (file.read(reinterpret_cast<char*>(&book), sizeof(Book))) {
        books.push_back(book);
    }
    file.close();
    return books;
}

void Books::SaveBooks(const std::vector<Book>& books) {
    std::ofstream file("books.dat", std::ios::binary | std::ios::trunc);
    if (!file) {
        wxLogError("Error al abrir el archivo para guardar.");
        return;
    }

    for (const auto& book : books) {
        file.write(reinterpret_cast<const char*>(&book), sizeof(Book));
    }
    file.close();
}