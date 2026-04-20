# PARCIAL II

**Nombre del Proyecto:** Parqueadero  
**Estudiantes:** Paula Noguera - Julián Rojas  
**Grupo:** G02 Pensamiento Algoritmico  
**Lenguaje:** C++  
**Tipo:** Aplicación de Consola

- **Listado de explicación de funciones generales**:

1. *Generar archivo*: Crea el archivo parqueadero.txt que define la distribución física del parqueadero en una cuadrícula de 25×25. Establece los bordes como paredes (W), marca la entrada (E) y salida (S), coloca vías de circulación (V) cada 4 filas/columnas, y rellena el resto con espacios de parqueo (C).
2. *Cargar el mapa*: Lee el archivo generado y construye la matriz Mapa en memoria. Cada celda queda como un objeto Casilla con su tipo y estado inicial ocupado = false. También cuenta los cupos disponibles totales. *Uso de getline() para recorrer la cadena de texto del archivo parqueadero.txt por el tamaño de la linea para para cada casilla que se recorre en [j] (las columnas) y asignar el tipo de elemento*
3. *Mostar el mapa*: Imprime la cuadrícula en consola mostrando C para espacios libres y X para ocupados, junto con los demás símbolos del mapa y sus referencias.
4. *Registrar ingreso*: Verifica que haya cupos libres, solicita placa y modelo del vehículo, valida que no esté ya registrado, y asigna el primer espacio libre disponible. Registra la hora de entrada y genera un ticket único de 10 caracteres alfanuméricos. *Recorre con variables para identificar si el vehiculo ya está registrado, en caso contrario, se vuelve a recorrer para asignar el "Parkingspot" dentro del mapa, junto con la fecha y hora de registro y la asignación de su ticket, mostrando en pantalla dicha información junto con las credenciales del vehiculo.*
5. *Registrar salida*: Busca el vehículo por placa, valida el ticket, calcula el tiempo transcurrido en minutos (redondeado hacia arriba) y cobra a razón de $150 por minuto. Guarda el registro en historial.txt y libera el espacio. *Usa un recorrido similar al ingreso, identifica si el numero de ticket es el correcto y hace el calculo de el costo total con base al tiempo dentro del parqueadero. Registra los datos de salida mostrando el valor calculado, tiempo y la hora de salida.*
6. *Menú*: Imprime la interfaz del menú con 6 opciones junto con sus colores y atributos en consola, se le pide al usuario que seleccione una de las opciones mostradas.
7. *Main*: Muestra el inicio del sistema del parqueadero cargando el archivo del mapa y generando el archivo a escribir. Uso de switch para llamar a cada función que el usuario requiera cuando marque un número de opción.

- **Listado de funciones extras (innovación)**:

1. *Generador del ticket*: Genera un código alfanumérico aleatorio de 10 caracteres, garantizando que sea único revisando todos los espacios ocupados del mapa antes de retornarlo. *Se de la libreria random, el generador de codigo seudo-random std::mt19937 para la distribución de caracteres aleatorios de todas las letras del abecedario en mayúsculas y minúsculas junto con los números del 0 al 9, generando un ticket unico por cada registro. La función retorna el ticket cuando se hace el resgistro del vehiculo*

**Referencia**:
GeeksforGeeks. (2021, March 30). std::mt19937 class in C++.
    https://www.geeksforgeeks.org/cpp/stdmt19937-class-in-cpp/


2. *Ubicar vehiculo*: Recorre el mapa buscando la placa ingresada y muestra la fila y columna donde está parqueado el vehículo. *Pide la placa del vehiculo del que se desea conocer la ubicación. Recorre el mapa de acuerdo a su tamañno real como Mapa.size para fila y columna, una vez reconozca en fila y columna el número de placa en carro.placa, va a imprimir un mensaje con la fila y la colmuna con las variables que recorrieron el mapa, en caso de no encontrar la placa, se imprime el mensaje de error.*

3. *Colores*: Designación especifica del color verde (\033) para titulos y subtitulos dentro de la interfaz del menú y las divisiones o resaltados de las opciones del menú, usando secuencias de escape ANSI y la forma de sintaxis "\033[x;xx;xxm".

**Referencia**:
Carceler, V. (2020, March 31). Secuencias de escape ANSI: Colores y atributos en la consola.
    https://elpuig.xeill.net/Members/vcarceler/articulos/escape-ansi
