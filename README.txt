# Proyecto de Árbol de Expresiones Algebraicas

Este proyecto toma expresiones algebraicas desde un archivo de entrada (`entrada.txt`), construye un árbol de expresión para cada una, evalúa las expresiones y guarda los resultados y los árboles de expresión en archivos separados (`salida.dat` y `arboles.dat`).

## Archivos

- `src/main.c`: Contiene el código fuente del programa.
- `entrada.txt`: Archivo de entrada con las expresiones algebraicas.
- `salida.dat`: Archivo de salida con los resultados de las evaluaciones.
- `arboles.dat`: Archivo de salida con los árboles de expresión.
- `CMakeLists.txt`: Archivo de configuración de CMake.
- `README.md`: Este archivo con instrucciones.

## Instrucciones para Compilar y Ejecutar

### Requisitos

- [CLion](https://www.jetbrains.com/clion/) (Editor y entorno de desarrollo integrado)
- [CMake](https://cmake.org/) (Sistema de construcción)
- [GCC](https://gcc.gnu.org/) (Compilador de C)

### Pasos

#### Usando CLion

1. **Abrir CLion**: Inicia CLion en tu computadora. (Puede utilizar cualquier IDE de preferencia) 
2. **Abrir Proyecto**: Selecciona `Open` en la pantalla de bienvenida y navega hasta la carpeta raíz del proyecto. Abre la carpeta del proyecto.
3. **Construir el Proyecto**:
   - Haz clic en el botón `Build` en la esquina superior derecha de la ventana. Esto compilará tu proyecto y generará un ejecutable.
4. **Ejecutar el Proyecto**:
   - Haz clic en el botón `Run` (icono de una flecha verde) en la esquina superior derecha de la ventana. Esto ejecutará el programa.

### Archivos de entrada y salida

1. Archivo de Entrada (entrada.txt): Debe de crear este archivo en la carpeta raíz del proyecto. Cada línea de este archivo debe contener una expresión algebraica. Ejemplo de entrada.txt:
	3 + 5
	2 * (3 + 4)
	sin(30)

### Archivos de salida 

1. salida.dat: Contendrá los resultados de las evaluaciones de las expresiones.
2. arboles.dat: Contendrá las representaciones de los árboles de expresión.

### Ejemplo de uso 

1. Crea un archivo llamado entrada.txt en la carpeta raíz del proyecto con el siguiente contenido:
3 + 5
2 * (3 + 4)
sin(30)

### Compilar y Ejecutar

1. Sigue las instrucciones anteriores para compilar y ejecutar el programa

### Verificación de resultados

1. Después de ejecutar el programa, revisa los archivos salida.dat y arboles.dat en la carpeta raíz del proyecto.
2. salida.dat debe contener:

	Resultado de la expresión '3 + 5': 8.00
	Resultado de la expresión '2 * (3 + 4)': 14.00
	Resultado de la expresión 'sin(30)': 0.50

### IMPORTANTE 

1. Asegurarse de que los archivos entrada.txt, salida.dat y arboles.dat estén en la carpeta raíz del proyecto.
2. Si hay errores de sintaxis en las expresiones del archivo de entrada, estos se registrarán en los archivos de salida correspondientes.
3. Puede modificar el archivo entrada.txt para probar diferentes expresiones algebraicas.
