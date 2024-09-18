#ifndef BOOKS_H
#define BOOKS_H

#include <wx/wx.h>
#include <vector>
#include <fstream>

// Estructura de libro
struct Book {
    char title[100];  // Título del libro
    char author[100]; // Autor del libro
    char genre[100];  // Género
    int year;         // Año de publicación
};

class Books : public wxFrame {
public:
    Books(const wxString& title, bool isAdmin, const wxString& activeUser);

private:
    wxListBox* bookList;
    wxTextCtrl* titleTextCtrl;
    wxTextCtrl* authorTextCtrl;
    wxTextCtrl* genreTextCtrl;
    wxTextCtrl* yearTextCtrl;
    wxStaticText* statusText;

    wxString ActiveUser; // Nombre del usuario actualmente registrado
    bool userIsAdmin;
    std::vector<Book> LoadBooks();
    void SaveBooks(const std::vector<Book>& books);

    void OnAddBook(wxCommandEvent& event);
    void OnDeleteBook(wxCommandEvent& event);
    void OnModifyBook(wxCommandEvent& event);
    void OnBackToMain(wxCommandEvent& event);
    void OnSelectBook(wxCommandEvent& event);

    wxDECLARE_EVENT_TABLE();
};

#endif // BOOKS_H
