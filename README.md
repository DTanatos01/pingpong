# Ping Pong

Juego de Ping Pong creado con C++ para Windows

## Documento de Apoyo

Para obtener más detalles sobre como instalar o configurar OpenGL en Windows [Guía de Instalación](https://www.sumantaguha.com/wp-content/uploads/2022/06/installGuideWindows.pdf).

## Características

- **Género:** Deportes
- **Modo:** Dos jugadores.
- **Periféricos:** Teclado, Pantalla.
- **Plataforma:** Windows PC.
- **Versión:** V-1.5
- **Controles:**
    - **Jugador 1:**
		- W: Arriba.
		- S: Abajo,
	- **Jugador 2:**
		- Flecha Arriba: Arriba,
		- Flecha Abajo: Abajo.
	- ESC: Salir o Ir al Menú Principal


## Funcionalidades

- **Pantalla de Inicio:** ![PantallaInicial](https://progress-bar.dev/100/?title=Completado)

- **Pantalla de Juego:** ![PantallaJuego](https://progress-bar.dev/100/?title=Completado)

- **Pantall Final:** ![PantallaFinal](https://progress-bar.dev/100/?title=Completado)

- **Movilidad Barras:** ![MovilidadBarra](https://progress-bar.dev/100/?title=Completado)

- **Movilidad Pelota:** ![MovilidadPelota](https://progress-bar.dev/100/?title=Completado)

- **Jugabilidad:** ![Jugabilidad](https://progress-bar.dev/100/?title=Completado)

## Requisitos

- Compilador de C++
- En este caso se uso g++ (MinGW.org GCC-6.3.0-1) 6.3.0
- [Descargar MinGW](https://sourceforge.net/projects/mingw/)
- Del material de apoyo solo seguir los pasos 2, 3, 4 para la descarga librerias.
- Del material de apoyo solo seguir los pasos 5, 6, 7 para poder ejecutar los .exe generados.

## Uso

Para el uso del programa seguir los siguientes pasos:

1. Abre la carpeta pingpong con una terminal.

2. Ingresar a la carpeta build.

3. Ejecutar el siguiente comando:

```
g++ ../src/program.cpp -o programa -I"C:\Users\Bryan Gonzalez\Documents\pingpong\includes\freeglut" -I"C:\Users\Bryan Gonzalez\Documents\pingpong\includes\glm" -I"C:\Users\Bryan Gonzalez\Documents\pingpong\includes\glew" -L"C:\Users\Bryan Gonzalez\Documents\pingpong\libs\freeglut" -L"C:\Users\Bryan Gonzalez\Documents\pingpong\libs\glew" -lopengl32 -lfreeglut -lglu32
```

4. Se generara en la carpeta de build programa.exe

5. Ejecuta el programa.exe y a disfrutar el juego.