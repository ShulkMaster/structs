# Instrucciones de compilado

## Usando Linux o Linux en WSL

__Nota__ _Este ejecutable es solo compatible con linux_

### Instalacion de herramientas de building

Si es una instalación nueva de ubuntu es posible que no tenga todas las herramientas para
hacer build de proyectos de *c++*. Ejecutar este comando para instalar las tools mas usadas
>sudo apt-get install build-essential libssl-dev

Aunque probablemente no instale nada ya que ubuntu casi siempre tiene estas pre instaldas.

Se debe primero ensamblar el proyecto usando la herramienta Cmake en la version 3.16 o superior

podria ser que ya ente instalado, revisar con:
>cmake --version

en caso que no este instalado, instalarlo en ubuntu o el gestor de paquetes de la distribution
>sudo apt install cmake

Adicional a *Cmake* es necesario tener un Generator, en este caso usando _ninja build_

revisar si no esta instalado junto a Cmake (lo mas probable)
>ninja --version

si no esta instalado, se puede instalar en ubuntu con
>sudo apt install ninja-build

### compilar el proyecto

1) Primero ir al directorio de código fuente

2) Luego crear el build con Cmake
   >   cmake -DCMAKE_BUILD_TYPE=Debug -G Ninja . -B ./build

    - como funciona el comando
   >   cmake -DCMAKE_BUILD_TYPE=Debug -G Ninja . -B ./build

   This command will build the project in debug mode with the Ninja build tool in the current directory
   cmake -DCMAKE_BUILD_TYPE=*[Debug|Release]* -G *[Generator Tool]* *[Source directory]* -B *[output directory]*
   *the point* with the *-B* build flag and the output directory *build*


3) Una vez que el proyecto se haya generado se podra compilar con 😎

   >cmake --build ./build --target data unicorn

   El comando se estructura
   cmake --build *[Generated directory]* --target *[target names]*


4) Si no hay errores de compilación significa que hay un ejecutable en la carpeta *[Generated directory]*llamado __unicorn__
   para el caso debería ser la carpeta build

5) Ejecutar el código
   >./build/unicorn