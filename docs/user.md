# Unicorn

Este pequeño ejecutable permite cargar datos de League of Legends almacenados en un archivo de texto
local llamado `data.txt` que no es necesario que este presente, sin embargo, esto permite tener data
pre cargada al iniciar el programa.

Mas sobre el formato del datafile [aquí](./datafile.md).

__Nota__ : Ya se incluye un datafile en las releases de Github

# Interfaz

## Menus
La interfaz está constituida solamente por texto la navegación en los menus principales se puede
realizar usando las flechas izquierda, derecha, arriba, abajo en su teclado.
Esta no es la única forma, ya que también existen sus correspondientes mapeos con las letras:
- Arriba: W, w
- Abajo: S, s
- Izquierda: A, a
- Derecha: D, d

__Nota__ los mapeos a letras no funcionan en menus donde deba ingresa datos.

## Sub Menus
Al igual que los menus principales estos se pueden navegar usando las flechas izquierda, derecha, arriba,
abajo en su teclado, aunque los sub menus tienen las opciones en forma horizontal solamente por lo que
flechas arriba y abajo no realizan ninguna acción.

Otra forma de navegar en sub menus es usando las teclas `WASD` nuevamente reconocidas como:
- Arriba: W, w
- Abajo: S, s
- Izquierda: A, a
- Derecha: D, d

por razones que ya explique `WS` no harán nada en sub menus.

Adicionalmente, si el menu contiene números como indices es posible presionar el carácter del número
en el teclado y activar directamente la opción, esto es equivalente a usar `WASD` para navegar y luego presionar
`Enter` para activar la opción seleccionada.

## Combination de teclas
Los menus también soportan combinaciones de teclas especificas, por ejemplo `Ctrl` + `E` resulta en entrar en modo de edición
contextual de ese menu y realizar  `Ctrl` + `E` ya estando en estado de edición la cancelará regresándolo al estado neutro

Estas combinaciones especiales se le mostrarán al pie de la consola con una breve descripción sobre sus efectos

El único caso especial es `Ctrl` + `Q` ya que esta combinación terminara el programa inmediatamente
independientemente de en que estado se encuentre el programa.