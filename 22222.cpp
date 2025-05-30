#include <iostream>  // Para operaciones de entrada/salida (cout, cin, endl)
#include <fstream>   // Para manejar archivos (lectura y escritura)
#include <string>    // Para trabajar con cadenas de texto (string)
#include <algorithm> // Para usar la función std::transform (cambiar a minúsculas)
#include <cctype>    // Para usar la función std::tolower (convertir caracteres a minúsculas)
#include <windows.h> // Específica para Windows: control de la consola (colores, UTF-8)

// Usamos el namespace std completo para simplificar el código
using namespace std;
// Definición de colores para la consola usando una enumeración para claridad
enum ConsoleTextColors {
    DEFAULT_CONSOLE_COLOR = 7,  // Color de texto predeterminado de la consola
    MATCH_HIGHLIGHT_COLOR = 12  // Código para el color rojo brillante
};

// Función para establecer el color del texto en la consola de Windows
void setConsoleOutputColor(int desiredColorCode) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), desiredColorCode);
}
// Función auxiliar para convertir una cadena completa a minúsculas (útil para búsquedas sin distinción de mayúsculas/minúsculas)
string convertToLowerCase(const string& originalText) {
    string lowercasedText = originalText; // Creamos una copia modificable de la cadena original
    // Aplicamos la función std::tolower a cada carácter de la cadena
    transform(lowercasedText.begin(), lowercasedText.end(), lowercasedText.begin(),
                   [](unsigned char c){ return tolower(c); });
    return lowercasedText; // Devolvemos la cadena convertida
}

// Función principal para procesar una línea, buscar coincidencias, resaltarlas y contarlas
void processLineAndHighlight(string& lineContent, const string& userSearchTerm, int& totalFoundOccurrences) {
    string lowerLine = convertToLowerCase(lineContent);          // La línea actual en minúsculas
    string lowerSearchTerm = convertToLowerCase(userSearchTerm); // El término de búsqueda en minúsculas
    size_t currentMatchPos = lowerLine.find(lowerSearchTerm);    // Buscamos la primera aparición del término
    size_t lineSpecificMatches = 0;                              // Contador para esta línea en particular
// Iteramos mientras se encuentren coincidencias en la línea
    while (currentMatchPos != string::npos) { // string::npos indica que no se encontró el término
        // Imprimimos la porción de la línea que precede a la coincidencia
        cout << lineContent.substr(0, currentMatchPos);

        // Cambiamos el color a rojo, imprimimos la coincidencia y luego restauramos el color predeterminado
        setConsoleOutputColor(MATCH_HIGHLIGHT_COLOR); // Establecemos el color rojo
        cout << lineContent.substr(currentMatchPos, userSearchTerm.length()); // Imprimimos la parte que coincide
        setConsoleOutputColor(DEFAULT_CONSOLE_COLOR); // Reestablecemos el color por defecto
