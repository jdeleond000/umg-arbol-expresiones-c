#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

// Definición de la estructura de un nodo del árbol
typedef struct Nodo {
    char dato[10]; // Dato almacenado en el nodo
    struct Nodo *izquierdo, *derecho; // Punteros a los nodos hijo izquierdo y derecho
} Nodo;

// Función para crear un nuevo nodo con un dato específico
Nodo* nuevoNodo(char* dato) {
    Nodo* nodo = (Nodo*) malloc(sizeof(Nodo)); // Reservar memoria para el nuevo nodo
    strcpy(nodo->dato, dato); // Copiar el dato al nodo
    nodo->izquierdo = nodo->derecho = NULL; // Inicializar los hijos como NULL
    return nodo;
}

// Función para determinar la precedencia de un operador
int precedencia(char* operador) {
    if (strcmp(operador, "+") == 0 || strcmp(operador, "-") == 0) return 1;
    if (strcmp(operador, "*") == 0 || strcmp(operador, "/") == 0) return 2;
    if (strcmp(operador, "^") == 0) return 3; // Añadir precedencia para ^
    return 0;
}

// Función para verificar si un carácter es válido en una expresión
int esCaracterValido(char c) {
    return isdigit(c) || isalpha(c) || c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == '(' || c == ')' || isspace(c);
}

// Función para validar una expresión algebraica
int validarExpresion(char* expr) {
    int parensAbiertas = 0;

    for (int i = 0; expr[i] != '\0'; i++) {
        if (!esCaracterValido(expr[i])) {
            printf("Error: Carácter inválido '%c' en la expresión.\n", expr[i]);
            return 0;
        }
        if (expr[i] == '(') parensAbiertas++;
        if (expr[i] == ')') parensAbiertas--;
        if (parensAbiertas < 0) {
            printf("Error: Paréntesis desbalanceados.\n");
            return 0;
        }
    }
    if (parensAbiertas != 0) {
        printf("Error: Paréntesis desbalanceados.\n");
        return 0;
    }
    return 1;
}

// Función para construir un árbol de expresión a partir de una expresión algebraica
Nodo* construirArbolExpresion(char* expr) {
    Nodo* pilaNodos[100];
    char pilaOperadores[100][10];
    int topeNodo = -1, topeOperador = -1;

    for (int i = 0; expr[i] != '\0';) {
        if (isspace(expr[i])) {
            i++;
            continue;
        }

        if (isdigit(expr[i])) {
            char num[10];
            int j = 0;
            while (isdigit(expr[i])) {
                num[j++] = expr[i++];
            }
            num[j] = '\0';
            pilaNodos[++topeNodo] = nuevoNodo(num);
        } else if (isalpha(expr[i])) {
            char func[10];
            int j = 0;
            while (isalpha(expr[i])) {
                func[j++] = expr[i++];
            }
            func[j] = '\0';
            if (expr[i] == '(') {
                pilaOperadores[++topeOperador][0] = '\0';
                strcpy(pilaOperadores[topeOperador], func);
            } else {
                pilaNodos[++topeNodo] = nuevoNodo(func);
            }
        } else if (expr[i] == '(') {
            pilaOperadores[++topeOperador][0] = expr[i++];
            pilaOperadores[topeOperador][1] = '\0';
        } else if (expr[i] == ')') {
            while (topeOperador != -1 && strcmp(pilaOperadores[topeOperador], "(") != 0) {
                Nodo* nodo = nuevoNodo(pilaOperadores[topeOperador--]);
                if (strcmp(nodo->dato, "sin") == 0 || strcmp(nodo->dato, "cos") == 0 || strcmp(nodo->dato, "tan") == 0 || strcmp(nodo->dato, "ln") == 0) {
                    nodo->izquierdo = pilaNodos[topeNodo--];
                } else {
                    nodo->derecho = pilaNodos[topeNodo--];
                    nodo->izquierdo = pilaNodos[topeNodo--];
                }
                pilaNodos[++topeNodo] = nodo;
            }
            if (topeOperador == -1) {
                printf("Error: Paréntesis desbalanceados.\n");
                return NULL;
            }
            topeOperador--; // Sacar '(' de la pila
            if (topeOperador != -1 && (strcmp(pilaOperadores[topeOperador], "sin") == 0 || strcmp(pilaOperadores[topeOperador], "cos") == 0 || strcmp(pilaOperadores[topeOperador], "tan") == 0 || strcmp(pilaOperadores[topeOperador], "ln") == 0)) {
                Nodo* nodo = nuevoNodo(pilaOperadores[topeOperador--]);
                nodo->izquierdo = pilaNodos[topeNodo--];
                pilaNodos[++topeNodo] = nodo;
            }
            i++;
        } else {
            char op[2] = { expr[i], '\0' };
            while (topeOperador != -1 && precedencia(pilaOperadores[topeOperador]) >= precedencia(op)) {
                Nodo* nodo = nuevoNodo(pilaOperadores[topeOperador--]);
                nodo->derecho = pilaNodos[topeNodo--];
                nodo->izquierdo = pilaNodos[topeNodo--];
                pilaNodos[++topeNodo] = nodo;
            }
            pilaOperadores[++topeOperador][0] = expr[i++];
            pilaOperadores[topeOperador][1] = '\0';
        }
    }

    while (topeOperador != -1) {
        Nodo* nodo = nuevoNodo(pilaOperadores[topeOperador--]);
        if (topeNodo < 1) {
            printf("Error: Expresión inválida.\n");
            return NULL;
        }
        nodo->derecho = pilaNodos[topeNodo--];
        nodo->izquierdo = pilaNodos[topeNodo--];
        pilaNodos[++topeNodo] = nodo;
    }

    if (topeNodo != 0) {
        printf("Error: Expresión inválida.\n");
        return NULL;
    }

    return pilaNodos[topeNodo];
}

// Función para imprimir el árbol de expresión en un archivo
void imprimirArbolUtil(Nodo *raiz, int espacio, FILE *archivo) {
    if (raiz == NULL) return;

    int nivelEspacio = 10;
    espacio += nivelEspacio;
    imprimirArbolUtil(raiz->derecho, espacio, archivo);

    fprintf(archivo, "\n");
    for (int i = nivelEspacio; i < espacio; i++)
        fprintf(archivo, " ");
    fprintf(archivo, "(%s)\n", raiz->dato);

    imprimirArbolUtil(raiz->izquierdo, espacio, archivo);
}

// Función para imprimir el árbol de expresión
void imprimirArbol(Nodo *raiz, FILE *archivo) {
    imprimirArbolUtil(raiz, 0, archivo);
}

// Función para derivar una expresión algebraica
void derivarExpresion(const char* expr, char* derivada) {
    char resultado[1000] = "";
    int i = 0;
    int longitud = strlen(expr);

    while (i < longitud) {
        if (expr[i] == ' ') {
            i++;
            continue;
        }

        if (isdigit(expr[i])) {
            // Coeficiente numérico
            int coef = 0;
            while (isdigit(expr[i])) {
                coef = coef * 10 + (expr[i] - '0');
                i++;
            }

            if (expr[i] == '*') {
                i++;
                if (isalpha(expr[i])) {
                    // Variable
                    char variable = expr[i];
                    i++;

                    if (expr[i] == '^') {
                        i++;
                        int exponente = 0;
                        while (isdigit(expr[i])) {
                            exponente = exponente * 10 + (expr[i] - '0');
                            i++;
                        }

                        // Aplicar la regla del exponente
                        coef = coef * exponente;
                        exponente--;

                        char term[50];
                        if (exponente == 1) {
                            snprintf(term, sizeof(term), "%d*%c", coef, variable);
                        } else {
                            snprintf(term, sizeof(term), "%d*%c^%d", coef, variable, exponente);
                        }
                        strcat(resultado, term);
                    } else {
                        // Caso lineal
                        char term[50];
                        snprintf(term, sizeof(term), "%d", coef);
                        strcat(resultado, term);
                    }
                }
            }
        } else if (isalpha(expr[i])) {
            if (strncmp(&expr[i], "sin", 3) == 0) {
                strcat(resultado, "cos(x)");
                i += 3;
            } else if (strncmp(&expr[i], "cos", 3) == 0) {
                strcat(resultado, "-sin(x)");
                i += 3;
            } else if (strncmp(&expr[i], "tan", 3) == 0) {
                strcat(resultado, "sec^2(x)");
                i += 3;
            } else if (strncmp(&expr[i], "ln", 2) == 0) {
                strcat(resultado, "1/x");
                i += 2;
            } else {
                // Variable
                char term[10];
                snprintf(term, sizeof(term), "%c", expr[i]);
                strcat(resultado, term);
                i++;
            }
        } else if (expr[i] == '+') {
            strcat(resultado, " + ");
            i++;
        } else if (expr[i] == '-') {
            strcat(resultado, " - ");
            i++;
        } else {
            i++;
        }
    }

    strcpy(derivada, resultado);
}

// Función principal
int main() {
    // Abrir el archivo de entrada para leer las expresiones
    FILE* archivoEntrada = fopen("C:\\Users\\jairo\\CLionProjects\\untitled\\entrada.txt", "r");
    if (!archivoEntrada) {
        printf("Error: No se pudo abrir el archivo 'entrada.txt'.\n");
        return 1;
    }

    // Abrir el archivo de salida para escribir los resultados
    FILE* archivoSalida = fopen("C:\\Users\\jairo\\CLionProjects\\untitled\\salida.dat", "w");
    if (!archivoSalida) {
        printf("Error: No se pudo abrir el archivo 'salida.dat'.\n");
        fclose(archivoEntrada);
        return 1;
    }

    // Abrir el archivo para escribir los árboles de expresión
    FILE* archivoArboles = fopen("C:\\Users\\jairo\\CLionProjects\\untitled\\arboles.dat", "w");
    if (!archivoArboles) {
        printf("Error: No se pudo abrir el archivo 'arboles.dat'.\n");
        fclose(archivoEntrada);
        fclose(archivoSalida);
        return 1;
    }

    char expr[100];
    char derivada[1000];
    // Leer cada línea del archivo de entrada
    while (fgets(expr, sizeof(expr), archivoEntrada)) {
        // Eliminar el carácter de nueva línea
        expr[strcspn(expr, "\n")] = '\0';

        // Validar la expresión
        if (!validarExpresion(expr)) {
            fprintf(archivoSalida, "Error: Expresión inválida '%s'.\n", expr);
            fprintf(archivoArboles, "Error: Expresión inválida '%s'.\n", expr);
            continue;
        }

        // Construir el árbol de expresión
        Nodo* raiz = construirArbolExpresion(expr);
        if (raiz == NULL) {
            fprintf(archivoSalida, "Error: No se pudo construir el árbol de expresión para '%s'.\n", expr);
            fprintf(archivoArboles, "Error: No se pudo construir el árbol de expresión para '%s'.\n", expr);
            continue;
        }

        // Imprimir el árbol de expresión en el archivo correspondiente
        fprintf(archivoArboles, "Árbol de expresión para '%s':\n", expr);
        imprimirArbol(raiz, archivoArboles);

        // Derivar la expresión
        derivarExpresion(expr, derivada);
        fprintf(archivoSalida, "Derivada de la expresión '%s': %s\n", expr, derivada);
    }

    // Cerrar los archivos
    fclose(archivoEntrada);
    fclose(archivoSalida);
    fclose(archivoArboles);
    return 0;
}
