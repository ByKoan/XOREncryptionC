#include <stdio.h>
#include <string.h>

void XOR(char *input, char *key, char *output) {
    int input_length = strlen(input);
    int key_length = strlen(key);

    for (int i = 0; i < input_length; i++) {
        // Aplica la operación XOR entre el carácter de entrada y el de la clave

        /*
            * Tabla de la verdad de operacion XOR
            * A = 0 B = 0 = OUTPUT = 0
            * A = 0 B = 1 = OUTPUT = 1
            * A = 1 B = 0 = OUTPUT = 1
            * A = 1 B = 1 = OUTPUT = 0
        */

        output[i] = input[i] ^ key[i % key_length];
    }
    output[input_length] = '\0'; // Asegura que el resultado sea una cadena válida
}

void TextExportEncrypted(char *output) {
    FILE *file = fopen("Encryptedtext.txt", "w");  // Creamos el archivo Encryptedtext.txt
    if (file == NULL) {
        printf("Error al abrir el archivo para escribir.\n");
        return;
    }

    fprintf(file, "Texto encriptado: %s\n", output);

    fclose(file); // Cerramos el archivo
    printf("Texto encriptado exportado a Encryptedtext.txt\n");
}

void TextExportDecrypted(char *output) {
    FILE *file = fopen("Decryptedtext.txt", "w");  // Creamos el archivo Decryptedtext.txt
    if (file == NULL) {
        printf("Error al abrir el archivo para escribir.\n");
        return;
    }

    fprintf(file, "Texto desencriptado: %s\n", output);

    fclose(file); // Cerramos el archivo
    printf("Texto exportado a Decryptedtext.txt\n");
}

int main() {
    char input[32];
    char key[32];
    char output[32];

    printf("Introduce el texto a cifrar: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0'; // Eliminar carácter de nueva línea

    printf("Introduce la clave: ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = '\0'; // Eliminar carácter de nueva línea

    XOR(input, key, output); // Ejecutamos el cifrado XOR

    printf("Texto cifrado: %s\n", output);
    TextExportEncrypted(output); // Exportamos el texto encriptado

    printf("Quieres desencriptar el texto? (s/n): ");
    char respuesta[2]; // Creamos variable respuesta que la usaremos en el if para comparar si quiere desencriptarlo o no
    fgets(respuesta, sizeof(respuesta), stdin);

    if (respuesta[0] == 's' || respuesta[0] == 'S') {
        char decrypted[32]; // Variable en la que guardaremos el texto desencriptado
        XOR(output, key, decrypted); // Desencripta el texto
        printf("Texto descifrado: %s\n", decrypted);
        TextExportDecrypted(decrypted); // Exportar el texto desencriptado 
    } else if (respuesta[0] == 'n' || respuesta[0] == 'N') {
        return 1;
    } else {
        printf("No has introducido una opción válida.\n");
    }

    return 0;
}
