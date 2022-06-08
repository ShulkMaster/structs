# League Of Legends project
Este proyecto es el rework del primer proyecto de técnicas de simulación
ciclo 01 2022

## Estructura
La estructura se define como un [Grafo](./data/Graph.h) implementado con listas de adyacencia
donde cada nodo del grafo tiene un ID numérico entero único y no soporta repetidos.
El grafo contendrá entre mínimo `0` y máximo `25` nodos. 
Cada nodo contiene
- Id del nodo _(editable solo al crear y máximo 6 dígitos no negativo en consola)_
- Nombre del nodo _(editable)_
- Árbol binario de Campeones _(editable)_

Cada nodo del grafo representa una region geográfica de Runaterra (El mundo de Liga de las leyendas)
teniendo el nombre de esta.

Dentro de cada nodo del grafo existe un [árbol binario](./data/Tree.h) ordenando según el orden alfanumérico
que le corresponda al objeto `std::wstring` que representa su nombre. Este arbol contendra `N`
nodos y cada nodo contiene un objeto de la clase `Champion`

La clase [Champion](./entities/Champion.h) contiene algunos datos de interés como
- Nombre del campeon _(editable máximo 50 caracteres en consola)_
- Edad del campeon _(editable máximo 6 dígitos no negativo en consola)_
- Clase del campeon _(editable máximo 60 caracteres en consola)_

# Otros enlaces

- [Manual de usuario](./docs/user.md)
- [Guia de compilación](./docs/compile.md): __NO__ es necesario compilarlo manual ya que esta 
un ejecutable ya compilado en la parte de releases de Github favor descargar de ahi.
