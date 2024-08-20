#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
using namespace std;

struct User {
	char username[50];
	char password[50];
	char role[4];
};

bool AddUser(const std::string& filename, const std::string& newUsername, const std::string& newPassword, const std::string& newRole) {
	std::vector<User> users;
	User newUser;
	
	// Copia el nuevo usuario a la estructura
	std::strncpy(newUser.username, newUsername.c_str(), sizeof(newUser.username) - 1);
	newUser.username[sizeof(newUser.username) - 1] = '\0';
	std::strncpy(newUser.password, newPassword.c_str(), sizeof(newUser.password) - 1);
	newUser.password[sizeof(newUser.password) - 1] = '\0';
	std::strncpy(newUser.role, newRole.c_str(), sizeof(newUser.role) - 1);
	newUser.role[sizeof(newUser.role) - 1] = '\0';
	
	// Abre el archivo en modo lectura para leer los usuarios existentes
	std::ifstream infile(filename, std::ios::binary);
	if (infile) {
		User temp;
		while (infile.read(reinterpret_cast<char*>(&temp), sizeof(User))) {
			users.push_back(temp);
		}
		infile.close();
	}
	
	// Añade el nuevo usuario a la lista
	users.push_back(newUser);
	
	// Abre el archivo en modo escritura para guardar todos los usuarios
	std::ofstream outfile(filename, std::ios::binary | std::ios::trunc);
	if (!outfile) {
		std::cerr << "Error opening file for writing" << std::endl;
		return false;
	}
	
	for (const auto& user : users) {
		outfile.write(reinterpret_cast<const char*>(&user), sizeof(User));
	}
	
	outfile.close();
	return true;
}

int main() {
	std::string filename = "users.dat";
	std::string username = "newuser";
	std::string password = "newpassword";
	std::string role = "admin";  // Role example
	
	if (AddUser(filename, username, password, role)) {
		std::cout << "User added successfully." << std::endl;
	} else {
		std::cerr << "Failed to add user." << std::endl;
	}
	
	return 0;
}
