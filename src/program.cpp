/* Programa de Ping Pong  */
#include <GL/glut.h>
#include <stdlib.h>
#include <iostream>
#include <cstdlib>
#include <ctime>

/* Variables Globales */
float width = 400; // Ancho de la pantalla
float height = 400; // Alto de la pantalla
int estadoPrograma = 0; // Estado del programa 0 = Menu Principal, 1 = Controles, 2 = Juego PJvPJ, 3 = Terminado
int puntajePJ1 = 0; // Puntaje del jugador 1
int puntajePJ2 = 0; // Puntaje del jugador 2
int ganador = -1; // Quien Gano 0 = Jugador 1, 1 = Jugador 2, -1 = Nadie

/* Variables de las barras y pelota */
float posicionJugador1 = 0.0;
float posicionJugador2 = 0.0;
float posicionPelotaX = 0.0;
float posicionPelotaY = 0.0;
bool jugador1Arriba = false;
bool jugador1Abajo = false;
bool jugador2Arriba = false;
bool jugador2Abajo = false;
float velocidadPelotaInicialX = 0.5;
float velocidadPelotaInicialY = 0.25;
float velocidadPelotaX = 0.0;
float velocidadPelotaY = 0.0;

/* Firmas de metodos */
void menuPrincipal();
void menuControles();
void reiniciarVariables();
void juegoPingPong();
void updateJugador1();
void updateJugador2();
void updatePelota();
void updateJuego();
void finJuego();

/* Metodo para inicializar la vista y el fondo de la pantalla */
void myinit(void)
{
	/* Atributos */
	glClearColor(0.0, 0.0, 0.0, 0.0); // Fondo negro
	/* Configurando la Vista */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	/* Ventana con origen en el centro*/
  glViewport(0, 0, width, height);
	gluOrtho2D(-width/2, width/2, -height/2, height/2);
	glMatrixMode(GL_MODELVIEW);
}

/* Metodo que desplegar las pantallas o el juego */
void display(void)
{
	/* Limpiamos la ventana */
	glClear(GL_COLOR_BUFFER_BIT);
  /* Se establece el origen */
  glLoadIdentity();
  /* Dependiendo el estado del programa se muestra una ventana */
  if (estadoPrograma == 0)
  {
    /* Menu principal */
    menuPrincipal();
  } else if (estadoPrograma == 1)
  {
    /* Menu de controles */
    menuControles();
  } else if (estadoPrograma == 2)
  {
    /* Juego Principal */
    juegoPingPong();
  } else if (estadoPrograma == 3)
  {
    /* Fin del Juego */
    finJuego();
  }
	/* Limpiamos los buffers */
  glFlush();
	glutSwapBuffers();
}

/* Metodo que se ejecuta cuando la ventana cambia de tamaño */
void reshape(int w, int h)
{
  /*Se forza al tamaño especificado inicialmente */
  glutReshapeWindow(width, height);
}

/* Metodo que manejara los eventos del teclado */
void keyboard(unsigned char key, int x, int y)
{
  switch(key)
  {
    /* Salir del juego */
    case 27:
      /* Si estamos en el menu principal se cierra el juego */
      if (estadoPrograma == 0)
      {
        exit(0);
      /* Si no estamos en el menu principal se regresa al menu principal */
      } else
      {
        estadoPrograma = 0;
      }
      break;
    /* Ir a los controles */
    case 'c':
    case 'C':
      if (estadoPrograma == 0)
      {
        estadoPrograma = 1;
      }
      break;
    /* Empezar a jugar */
    case 'j':
    case 'J':
      /* Se comienza a jugar y se reinician las variables de los jugadores */
      if (estadoPrograma == 0)
      {
        reiniciarVariables();
        estadoPrograma = 2;
      }
      break;
    /* Controles del jugador 1 */
    /* Arriba */
    case 'w':
    case 'W':
      /* Se revisa que se este en el estado de jugar */
      if (estadoPrograma == 2)
      {
        /* Se activa la condicion del jugador hacia arriba */
        jugador1Arriba = true;
      }
      break;
    /* Abajo */
    case 's':
    case 'S':
      /* Se revisa que se este en el estado de jugar */
      if (estadoPrograma == 2)
      {
        /* Se activa la condicion del jugador hacia arriba */
        jugador1Abajo = true;
      }
      break;
    default:
      std::cout << "Se presiono la tecla: " << key << std::endl;
  }
}

/* Metodo para manejar cuando se levanta una tecla del teclado*/
void keyboardUp(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'w':
    case 'W':
        /* Se revisa que se este en el estado de jugar */
        if (estadoPrograma == 2)
        {
          /* Se desactiva la condicion del jugador hacia arriba */
          jugador1Arriba = false;
        }
        break;
    case 's':
    case 'S':
        /* Se revisa que se este en el estado de jugar */
        if (estadoPrograma == 2)
        {
          /* Se desactiva la condicion del jugador hacia abajo */
          jugador1Abajo = false;
        }
        break;
    }
}

/* Metodo que manejara los eventos del teclas especiales */
void special(int key, int x, int y)
{
  switch(key)
  {
    /* Controles del jugador 2 */
    /* Arriba */
    case GLUT_KEY_UP:
      /* Se revisa que se este en el estado de jugar */
      if (estadoPrograma == 2)
      {
        /* Se activa la condicion del jugador hacia arriba */
        jugador2Arriba = true;
      }
      break;
    case GLUT_KEY_DOWN:
      /* Se revisa que se este en el estado de jugar */
      if (estadoPrograma == 2)
      {
        /* Se activa la condicion del jugador hacia abajo */
        jugador2Abajo = true;
      }
      break;
    default:
      std::cout << "Se presiono la tecla: " << key << std::endl;
  }
}

/* Metodo que manejara los eventos del teclas especiales cuando se levantan */
void specialUp(int key, int x, int y)
{
  switch(key)
  {
    /* Controles del jugador 2 */
    /* Arriba */
    case GLUT_KEY_UP:
      /* Se revisa que se este en el estado de jugar */
      if (estadoPrograma == 2)
      {
        /* Se desactiva la condicion del jugador hacia arriba */
        jugador2Arriba = false;
      }
      break;
    case GLUT_KEY_DOWN:
      /* Se revisa que se este en el estado de jugar */
      if (estadoPrograma == 2)
      {
        /* Se desactiva la condicion del jugador hacia abajo */
        jugador2Abajo = false;
      }
      break;
    default:
      std::cout << "Se presiono la tecla: " << key << std::endl;
  }
}

/* Funcion para actualizar cualquier movimiento del jugador 1 */
void updateJugador1(int valor)
{
  if (estadoPrograma == 2)
  {
    /* Movimiento del Jugador */
    /* Movimiento hacia arriba */
    if (jugador1Arriba && !jugador1Abajo)
    {
      /* Se mueve de 5 en 5 */
      if (posicionJugador1 < height/2 -30)
      {
        posicionJugador1 += 5;
      }
    }

    /* Movimiento hacia abajo */
    if (jugador1Abajo && !jugador1Arriba)
    {
      /* Se mueve de 5 en 5 */
      if (posicionJugador1 > -height/2 +30)
      {
        posicionJugador1 -= 5;
      }
    }

    /* Se actualiza la pantalla */
    glutPostRedisplay();
  }
  /* Se llama nuevamente al metodo */
  glutTimerFunc(10, updateJugador1, 0);
}

/* Funcion para actualizar cualquier movimiento del jugador 2 */
void updateJugador2(int valor)
{
  if (estadoPrograma == 2)
  {
    /* Movimiento del Jugador */
    /* Movimiento hacia arriba */
    if (jugador2Arriba && !jugador2Abajo)
    {
      /* Se mueve de 5 en 5 */
      if (posicionJugador2 < height/2 -30)
      {
        posicionJugador2 += 5;
      }
    }

    /* Movimiento hacia abajo */
    if (jugador2Abajo && !jugador2Arriba)
    {
      /* Se mueve de 5 en 5 */
      if (posicionJugador2 > -height/2 +30)
      {
        posicionJugador2 -= 5;
      }
    }

    /* Se actualiza la pantalla */
    glutPostRedisplay();
  }
  /* Se llama nuevamente al metodo */
  glutTimerFunc(10, updateJugador2, 0);
}

/* Funcion para actualizar cualquier movimiento de la pelota */
void updatePelota(int valor)
{
  /* Se revisa que se este en el estado de juego */
  if (estadoPrograma == 2)
  {
    /* Movimiento de la pelota */
    posicionPelotaX += velocidadPelotaX;
    posicionPelotaY += velocidadPelotaY;

    /* Se revisan las colisiones con los jugadores */
    /* Colision con el jugador 1 */
    if (posicionPelotaX <= -width/2 + 23 && posicionPelotaY <= posicionJugador1 + 21.0 && posicionPelotaY >= posicionJugador1 - 21.0)
    {
        /* Se aumenta la velocida en cada golpe */
        velocidadPelotaX = -velocidadPelotaX * 1.15;
        /* La velocidad tiene limites */
        if (velocidadPelotaX > 1.5)
        {
          velocidadPelotaX = 1.5;
        }
        if (velocidadPelotaX < -1.5)
        {
          velocidadPelotaX = -1.25;
        }
    }

    /* Colision con el jugador 2 */
    if (posicionPelotaX >= width/2 - 23 && posicionPelotaY <= posicionJugador2 + 21.0 && posicionPelotaY >= posicionJugador2 - 21.0)
    {
        /* Se aumenta la velocida en cada golpe */
        velocidadPelotaX = -velocidadPelotaX * 1.15;
        /* La velocidad tiene limites */
        if (velocidadPelotaX > 1.25)
        {
          velocidadPelotaX = 1.25;
        }
        if (velocidadPelotaX < -1.25)
        {
          velocidadPelotaX = -1.25;
        }
    }

    /* Se revisan las colisiones con los bordes */

    /* Bordes superiores e infiores*/
    if (posicionPelotaY > height/2 -7 || posicionPelotaY < -height/2 + 7)
    {
      /* Se cambia la direccion de la pelota en y */
      /* Se aumenta ademas la velocidad en y */
      velocidadPelotaY = -velocidadPelotaY * 1.05;
      /* Se mantiene la velocidad en limites */
      if (velocidadPelotaY > 1.0)
      {
        velocidadPelotaY = 1.0;
      }
      if (velocidadPelotaY < -1.0)
      {
        velocidadPelotaY = 1.0;
      }
    }

    /* Borde izquierdo */
    if (posicionPelotaX < -width/2 + 7)
    {
      /* Se le añade un punto al jugador 2*/
      puntajePJ2 += 1; 
      /* Se reinicia la posicion de la pelota */
      posicionPelotaX = 0.0;
      posicionPelotaY = 0.0;
      /* Se decide la direccion de la pelota de manera aleatoria por cada juego */
      std::srand(std::time(nullptr)); // Semilla para la generación de números aleatorios
      bool direccionXBooleana = std::rand() % 2 == 1; // Generar valor booleano aleatorio
      bool direccionYBooleana = std::rand() % 2 == 1; // Generar valor booleano aleatorio
      /* Dependiendo el booleano generado, la direccion puede ser positiva o negativa */
      velocidadPelotaX = direccionXBooleana ? velocidadPelotaInicialX : -velocidadPelotaInicialX; 
      velocidadPelotaY = direccionYBooleana ? velocidadPelotaInicialY : -velocidadPelotaInicialY;
    }

    /* Borde derecho */
    if (posicionPelotaX > width/2 - 7)
    {
      /* Se le añade un punto al jugador 1*/
      puntajePJ1 += 1; 
      /* Se reinicia la posicion de la pelota */
      posicionPelotaX = 0.0;
      posicionPelotaY = 0.0;
      /* Se decide la direccion de la pelota de manera aleatoria por cada juego */
      std::srand(std::time(nullptr)); // Semilla para la generación de números aleatorios
      bool direccionXBooleana = std::rand() % 2 == 1; // Generar valor booleano aleatorio
      bool direccionYBooleana = std::rand() % 2 == 1; // Generar valor booleano aleatorio
      /* Dependiendo el booleano generado, la direccion puede ser positiva o negativa */
      velocidadPelotaX = direccionXBooleana ? velocidadPelotaInicialX : -velocidadPelotaInicialX; 
      velocidadPelotaY = direccionYBooleana ? velocidadPelotaInicialY : -velocidadPelotaInicialY;
    }

    /* Se actualiza la pantalla */
    glutPostRedisplay();
  }
  /* Se llama nuevamente al metodo */
  glutTimerFunc(5, updatePelota, 0);
}

/* Funcion para revisar el desarrollo del juego */
void updateJuego(int valor)
{
  /* Se revisa que se este en el estado de juego */
  if (estadoPrograma == 2)
  {
    /* Se revisan puntajes */
    if (puntajePJ1 == 5)
    {
      ganador = 0;
    }
    if (puntajePJ2 == 5)
    {
      ganador = 1;
    }

    /* Si ganador es distinto de -1 hay un ganador */
    if (ganador != -1)
    {
      estadoPrograma = 3;
    }


    /* Se actualiza la pantalla */
    glutPostRedisplay();
  }
  /* Se llama nuevamente al metodo */
  glutTimerFunc(5, updateJuego, 0);
}

/* Metodo principal */
int main(int argc, char** argv)
{
	// Inicializacion estandar de Glut
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // Por defecto, no necesario
	glutInitWindowSize(width, height); // Ventana de width x height
	glutInitWindowPosition(0, 0); // Se coloca la ventana en la parte superior izquierda de la pantalla
	glutCreateWindow("Ping Pong"); // Titulo de la ventana
	glutDisplayFunc(display); // Se invoca al metodo display cuando la ventana es abierta
  glutReshapeFunc(reshape); // Funcion que se llama cuando la ventana cambia de tamaño
  glutKeyboardFunc(keyboard); // Funcion que manejara los eventos del teclado
  glutKeyboardUpFunc(keyboardUp); // Funcion que manejara los eventos del teclado cuando se levanta una tecla
  glutSpecialFunc(special); // Funcion que manejara los eventos de teclas especiales
  glutSpecialUpFunc(specialUp); // Funcion que manejara los eventos de teclas especiales cuando se levanta una tecla
  glutTimerFunc(10, updateJugador1, 0); // Funcion encargada de cada movimiento del jugador 1 en pantalla
  glutTimerFunc(10, updateJugador2, 0); // Funcion encargada de cada movimiento del jugador 2 en pantalla
	glutTimerFunc(5, updatePelota, 0); // Funcion encargada de cada movimiento de la pelota en pantalla
  glutTimerFunc(5, updateJuego, 0); // Funcion encargada de revisar los puntajes del juego y decidir un ganador
  myinit(); // Se ponen los argumentos
	glutMainLoop(); // Se ingresar a ciclo de eventos
}

/* Metodos auxiliares */

/* Metodo principal que reprensenta la logica del juego */
void juegoPingPong()
{
  /* Se dibuja la pelota */
  glColor3f(1.0, 1.0, 1.0); // Color blanco
  glPointSize(10);
  glBegin(GL_POINTS);
  glVertex2f(posicionPelotaX, posicionPelotaY);
  glEnd();

  /* Se dibuja las barras */
  /* Jugador 1 */
  glColor3f(1.0, 0.0, 0.0); // Color Rojo
  glBegin(GL_POLYGON);
  glVertex2f(-width/2 + 10, posicionJugador1 + 20);
  glVertex2f(-width/2 + 20, posicionJugador1 + 20);
  glVertex2f(-width/2 + 20, posicionJugador1 - 20);
  glVertex2f(-width/2 + 10, posicionJugador1 - 20);
  glEnd();

  /* Jugador 2 */
  glColor3f(0.0, 0.0, 1.0); // Color Azul
  glBegin(GL_POLYGON);
  glVertex2f(width/2 - 10, posicionJugador2 + 20);
  glVertex2f(width/2 - 20, posicionJugador2 + 20);
  glVertex2f(width/2 - 20, posicionJugador2 - 20);
  glVertex2f(width/2 - 10, posicionJugador2 - 20);
  glEnd();

  /* Se dibuja el puntaje*/
  glColor3f(0.0, 1.0, 0.0); // Color Verde
  /* Posicion del del puntaje */
	glRasterPos2f(0, -height/2 + 20);
  glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ':');
  /* Posicion del del puntaje Jugador 1 */
	glRasterPos2f(-20, -height/2 + 20);
  glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '0' + puntajePJ1);
  /* Posicion del del puntaje Jugador 2 */
	glRasterPos2f(15, -height/2 + 20);
  glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '0' + puntajePJ2);
  glColor3f(1.0, 1.0, 1.0); // Color Blanco
}

/* Metodo para mostrar las letras de los ejes */
void menuPrincipal()
{
  /* Cuadro del titulo */
  glColor3f(1.0, 1.0, 1.0); // Color blanco
  /* Se dibuja cuadrado */
  glBegin(GL_QUADS);
  glVertex2f(65, 150);
  glVertex2f(-60, 150);
  glVertex2f(-60, 105);
  glVertex2f(65, 105);
  glEnd();

	/* Color de las letras del titulo */
	glColor3f(0.0, 0.0, 0.0); // Color negro
  /* Se muestra el titulo */
  /* Posicion del titulo */
	glRasterPos2f(-50.0, 120.0);
  /* Se imprimen en pantalla las letras de Ping Pong y su tipo de letra */
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'P');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'i');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'n');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'g');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ' ');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'P');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'o');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'n');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'g');

	/* Color de las letras del titulo */
	glColor3f(1.0, 1.0, 1.0); // Color blanco

  /* Se muestra el menu */
  /* Se genera un cuadrado para contener una letra */
  glBegin(GL_LINE_LOOP);
  glVertex2f(-20, 40);
  glVertex2f(-60, 40);
  glVertex2f(-60, 0);
  glVertex2f(-20, 0);
  glEnd();

  /* Se muestra la letra para iniciar el juego */
  glRasterPos2f(-46, 12);
  glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'J');

  /* Se muestra el texto*/
  glRasterPos2f(0, 12);
  glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'J');
  glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'u');
  glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'g');
  glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'a');
  glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'r');

  /* Se genera otro cuadrado para contener una letra */
  glBegin(GL_LINE_LOOP);
  glVertex2f(-20, -30);
  glVertex2f(-60, -30);
  glVertex2f(-60, -70);
  glVertex2f(-20, -70);
  glEnd();

  /* Se muestra la letra para mostrar los controles */
  glRasterPos2f(-48, -58);
  glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'C');

  /* Se muestra el texto*/
  glRasterPos2f(0, -58);
  glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'C');
  glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'o');
  glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'n');
  glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 't');
  glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'r');
  glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'o');
  glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'l');
  glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'e');
  glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 's');
  
  /* Se genera otro cuadrado para contener una letra */
  glBegin(GL_LINE_LOOP);
  glVertex2f(-20, -100);
  glVertex2f(-60, -100);
  glVertex2f(-60, -140);
  glVertex2f(-20, -140);
  glEnd();

  /* Se muestra la letra para salir del juego */
  glRasterPos2f(-58, -128);
  glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'E');
  glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 's');
  glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'c');

  /* Se muestra el texto*/
  glRasterPos2f(0, -128);
  glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'S');
  glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'a');
  glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'l');
  glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'i');
  glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'r');
}

/* Metodo que representa el menu de los controles */
void menuControles()
{
  /* Cuadro del titulo */
  glColor3f(1.0, 1.0, 1.0); // Color blanco
  /* Se dibuja el cuadrado */
  glBegin(GL_QUADS);
  glVertex2f(55, 150);
  glVertex2f(-60, 150);
  glVertex2f(-60, 105);
  glVertex2f(55, 105);
  glEnd();

  /* Jugador 1 */
  glColor3f(1.0, 1.0, 1.0); // Color blanco
  /* Se dibuja el cuadrado */
  glBegin(GL_QUADS);
  glVertex2f(-100, 100);
  glVertex2f(-150, 100);
  glVertex2f(-150, 55);
  glVertex2f(-100, 55);
  glEnd();

  /* Jugador 2 */
  glColor3f(1.0, 1.0, 1.0); // Color blanco
  /* Se dibuja el cuadrado */
  glBegin(GL_QUADS);
  glVertex2f(100, 100);
  glVertex2f(150, 100);
  glVertex2f(150, 55);
  glVertex2f(100, 55);
  glEnd();

	/* Color de las letras del titulo */
	glColor3f(0.0, 0.0, 0.0); // Color negro
  /* Se muestra el titulo */
  /* Posicion del titulo */
	glRasterPos2f(-50.0, 120.0);
  /* Se imprimen en pantalla las letras de Ping Pong y su tipo de letra */
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'C');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'o');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'n');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 't');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'r');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'o');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'l');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'e');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 's');
  
  /* Posicion del jugador */
	glRasterPos2f(-144.0, 70.0);
  /* Se imprimen en pantalla las letras de Ping Pong y su tipo de letra */
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'P');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'J');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '1');
  
  /* Posicion del jugador 2 */
	glRasterPos2f(106.0, 70.0);
  /* Se imprimen en pantalla las letras de Ping Pong y su tipo de letra */
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'P');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'J');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '2');

	/* Color de las letras del titulo */
	glColor3f(1.0, 1.0, 1.0); // Color blanco

  /* Se muestra el menu */
  /* Se genera un cuadrado para contener una letra */
  glBegin(GL_LINE_LOOP);
  glVertex2f(-140, 25);
  glVertex2f(-180, 25);
  glVertex2f(-180, -15);
  glVertex2f(-140, -15);
  glEnd();

  /* Se muestra la letra para iniciar el juego */
  glRasterPos2f(-172, -3);
  glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'W');

  /* Se muestra el texto*/
  glRasterPos2f(-120, -3);
  glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'A');
  glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'r');
  glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'r');
  glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'i');
  glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'b');
  glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'a');

  /* Se genera un cuadrado para contener una flecha */
  glBegin(GL_LINE_LOOP);
  glVertex2f(140, 25);
  glVertex2f(180, 25);
  glVertex2f(180, -15);
  glVertex2f(140, -15);
  glEnd();
  
  /* Se dibuja la flecha */
  /* Se dibuja triangulo */
  glBegin(GL_TRIANGLES);
  glVertex2f(160, 20);
  glVertex2f(170, 5);
  glVertex2f(150, 5);
  glEnd();
  /* Se dibuja la linea */
  glBegin(GL_LINES);
  glVertex2f(160, 5);
  glVertex2f(160, -10);
  glEnd();

  /* Se muestra el texto*/
  glRasterPos2f(55, -3);
  glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'A');
  glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'r');
  glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'r');
  glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'i');
  glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'b');
  glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'a');

  /* Se genera otro cuadrado para contener una letra */
  glBegin(GL_LINE_LOOP);
  glVertex2f(-140, -45);
  glVertex2f(-180, -45);
  glVertex2f(-180, -85);
  glVertex2f(-140, -85);
  glEnd();

  /* Se muestra la letra para mostrar los controles */
  glRasterPos2f(-166, -73);
  glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'S');

  /* Se muestra el texto*/
  glRasterPos2f(-120, -73);
  glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'A');
  glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'b');
  glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'a');
  glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'j');
  glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'o');

  /* Se genera otro cuadrado para contener una flecha */
  glBegin(GL_LINE_LOOP);
  glVertex2f(140, -45);
  glVertex2f(180, -45);
  glVertex2f(180, -85);
  glVertex2f(140, -85);
  glEnd();

  /* Se dibuja la flecha */
  /* Se dibuja el triangulo */
  glBegin(GL_TRIANGLES);
  glVertex2f(160, -80);
  glVertex2f(170, -65);
  glVertex2f(150, -65);
  glEnd();
  /* Se dibuja linea */
  glBegin(GL_LINES);
  glVertex2f(160, -65);
  glVertex2f(160, -50);
  glEnd();

  /* Se muestra el texto*/
  glRasterPos2f(58, -73);
  glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'A');
  glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'b');
  glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'a');
  glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'j');
  glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'o');
  
  /* Se genera otro cuadrado para contener una letra */
  glBegin(GL_LINE_LOOP);
  glVertex2f(-100, -120);
  glVertex2f(-140, -120);
  glVertex2f(-140, -160);
  glVertex2f(-100, -160);
  glEnd();

  /* Se muestra la letra para salir del juego */
  glRasterPos2f(-138, -148);
  glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'E');
  glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 's');
  glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'c');

  /* Se muestra el texto*/
  glRasterPos2f(-80, -148);
  glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'S');
  glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'a');
  glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'l');
  glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'i');
  glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'r');
  glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ' ');
  glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'o');
  glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ' ');
  glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'M');
  glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'e');
  glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'n');
  glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'u');
  glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ' ');
  glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'P');
  glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'r');
  glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'i');
  glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'n');
  glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'c');
  glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'i');
  glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'p');
  glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'a');
  glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'l');
}

/* Metodo que representa el fin del juego */
void finJuego()
{
  /* Cuadro del titulo */
  glColor3f(1.0, 1.0, 1.0); // Color blanco
  /* Se dibuja el cuadrado */
  glBegin(GL_QUADS);
  glVertex2f(55, 150);
  glVertex2f(-60, 150);
  glVertex2f(-60, 105);
  glVertex2f(55, 105);
  glEnd();

  /* Jugador Ganador */
  glColor3f(1.0, 1.0, 1.0); // Color blanco
  /* Se dibuja el cuadrado */
  glBegin(GL_QUADS);
  glVertex2f(-25, 100);
  glVertex2f(25, 100);
  glVertex2f(25, 55);
  glVertex2f(-25, 55);
  glEnd();

	/* Color de las letras del titulo */
	glColor3f(0.0, 0.0, 0.0); // Color negro
  /* Se muestra el titulo */
  /* Posicion del titulo */
	glRasterPos2f(-45.0, 120.0);
  /* Se imprimen en pantalla las letras de Ping Pong y su tipo de letra */
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'G');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'a');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'n');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'a');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'd');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'o');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'r');
  
  /* Posicion del jugador */
	glRasterPos2f(-18, 70.0);
  /* Se imprimen en pantalla las letras de Ping Pong y su tipo de letra */
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'P');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'J');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ganador == 0 ? '1' : '2');

  /* Se genera otro cuadrado para contener una letra */
  glColor3f(1.0, 1.0, 1.0); // Color blanco
  glBegin(GL_LINE_LOOP);
  glVertex2f(-100, -120);
  glVertex2f(-140, -120);
  glVertex2f(-140, -160);
  glVertex2f(-100, -160);
  glEnd();

  /* Se muestra la letra para salir del juego */
  glRasterPos2f(-138, -148);
  glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'E');
  glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 's');
  glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'c');

  /* Se muestra el texto*/
  glRasterPos2f(-80, -148);
  glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'M');
  glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'e');
  glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'n');
  glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'u');
  glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ' ');
  glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'P');
  glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'r');
  glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'i');
  glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'n');
  glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'c');
  glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'i');
  glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'p');
  glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'a');
  glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'l');
}

/* Metodo que representa la limpieza de las variables del juego */
void reiniciarVariables()
{
  /* Se reinician los puntajes */
  puntajePJ1 = 0;
  puntajePJ2 = 0;
  /* Se reinician las posiciones del jugador y pelota*/
  posicionJugador1 = 0.0;
  posicionJugador2 = 0.0;
  posicionPelotaX = 0.0;
  posicionPelotaY = 0.0;
  /* Se reinicia el ganador */
  ganador = -1;
  /* Se decide la direccion de la pelota de manera aleatoria por cada juego */
  std::srand(std::time(nullptr)); // Semilla para la generación de números aleatorios
  bool direccionXBooleana = std::rand() % 2 == 1; // Generar valor booleano aleatorio
  bool direccionYBooleana = std::rand() % 2 == 1; // Generar valor booleano aleatorio
  /* Dependiendo el booleano generado, la direccion puede ser positiva o negativa */
  velocidadPelotaX = direccionXBooleana ? velocidadPelotaInicialX : -velocidadPelotaInicialX; 
  velocidadPelotaY = direccionYBooleana ? velocidadPelotaInicialY : -velocidadPelotaInicialY;
  std::cout << "VelocidadX " << velocidadPelotaX << " VelocidadY " << velocidadPelotaY << std::endl; 
}