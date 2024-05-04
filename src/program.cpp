/* Programa de Ping Pong  */
#include <GL/glut.h>
#include <stdlib.h>
#include <iostream>

/* Variables Globales */
float width = 400; // Ancho de la pantalla
float height = 400; // Alto de la pantalla
int estadoPrograma = 0; // Estado del programa 0 = Menu Principal, 1 = Controles, 2 = Juego PJvPJ, 4 = Terminado

/* Firmas de metodos */
void menuPrincipal();
void menuControles();
void reiniciarVariables();

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
    default:
      std::cout << "Se presiono la tecla: " << key << std::endl;
  }
}

/* Metodo que manejara los eventos del teclas especiales */
void special(int key, int x, int y)
{
  switch(key)
  {
    default:
      std::cout << "Se presiono la tecla: " << key << std::endl;
  }
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
  glutSpecialFunc(special); // Funcion que manejara los eventos de teclas especiales
	myinit(); // Se ponen los argumentos
	glutMainLoop(); // Se ingresar a ciclo de eventos
}

/* Metodos auxiliares */

/* Metodo para mostrar las letras de los ejes */
void menuPrincipal()
{
  /* Cuadro del titulo */
  glColor3f(1.0, 1.0, 1.0);
  glBegin(GL_QUADS);
  glVertex2f(65, 150);
  glVertex2f(-60, 150);
  glVertex2f(-60, 105);
  glVertex2f(65, 105);
  glEnd();

	/* Color de las letras del titulo */
	glColor3f(0.0, 0.0, 0.0);
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
	glColor3f(1.0, 1.0, 1.0);

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
  glColor3f(1.0, 1.0, 1.0);
  glBegin(GL_QUADS);
  glVertex2f(55, 150);
  glVertex2f(-60, 150);
  glVertex2f(-60, 105);
  glVertex2f(55, 105);
  glEnd();

  /* Jugador 1 */
  glColor3f(1.0, 1.0, 1.0);
  glBegin(GL_QUADS);
  glVertex2f(-100, 100);
  glVertex2f(-150, 100);
  glVertex2f(-150, 55);
  glVertex2f(-100, 55);
  glEnd();

  /* Jugador 2 */
  glColor3f(1.0, 1.0, 1.0);
  glBegin(GL_QUADS);
  glVertex2f(100, 100);
  glVertex2f(150, 100);
  glVertex2f(150, 55);
  glVertex2f(100, 55);
  glEnd();

	/* Color de las letras del titulo */
	glColor3f(0.0, 0.0, 0.0);
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
	glColor3f(1.0, 1.0, 1.0);

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
  glBegin(GL_TRIANGLES);
  glVertex2f(160, 20);
  glVertex2f(170, 5);
  glVertex2f(150, 5);
  glEnd();
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
  glBegin(GL_TRIANGLES);
  glVertex2f(160, -80);
  glVertex2f(170, -65);
  glVertex2f(150, -65);
  glEnd();
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

/* Metodo que representa la limpieza de las variables del juego */
void reiniciarVariables()
{

}