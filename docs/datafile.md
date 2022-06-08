# Datafile

El __Datafile__ es un archivo de texto plano estructurado que usa Unicorn
para descerializar los datos y agregarlas a las estructuras de datos en memoria.
Para que el archivo funcione debe estar en el mismo directorio que el ejecutable

__Nota__ : Ya se incluye un datafile en las releases de Github

## Especificaciones
* El archivo debe estar guardado en codification UTF-8
* Debe contener una linea adicional al final vacía
* Debe comenzar con una línea de nodo o si no los datos serán ignorados

# Importante
Muchas de las limitaciones impuestas desde consola como:
- Largo máximo
- Maxima cantidad de dígitos
- Números no negativos

Se pueden saltar en el datafile, sin embargo, es recomendable mantener las mismas
reglas en el archivo para asegurar una deserealizacón correcta y evitar potenciales
errores del programa.

Además, si se desea se pueden agregar espacios para tener un formato más legible en la data
estos espacios adicionales entre las columnas serán eliminados al leer el archivo.

## Estructura
De forma general existen dos tipos de líneas en el archivo
1) Línea nodo: Se transformará a un nodo de grafo y debe contener en el order
   1) Id del nodo: Numero no negativo (de preferencia)
   2) Nombre del nodo (uno o más caracteres)
2) Línea campeón y debe contener en el order
   1) Prefijo `Tab`
   2) Nombre del campeón (uno o más caracteres)
   3) Edad: Solamente dígitos (uno o más dígitos)
   4) Clase del campeón (uno o más caracteres)

Todas las partes de Línea deben de estar separadas por comas __EXCEPTO__
el prefijo `Tab`

En otras palabras es un archivo `CSV` pero agregando el prefijo `Tab`
se interpretará como un tipo de Línea o la otra.