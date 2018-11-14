# Defuse the bomb
Juego de desactivar la bomba con Arduino. 
## Explicación del juego:
El jugador deberá de insertar un número de 5 cifras hasta acertar, para ello tendrá un teclado numérico con el que podrá introducir los números, borrar los números introducidos y comprobar si ha acertado. Como pista, contara con 5 leds los cuales se iluminaran si ha acertado alguna cifra. Y por último en un panel de digital de 4 números como el de un reloj, saldrá una cuenta atrás. 
## Desarrollo:
El desarrollo que he realizado a sido por partes:
1. He instalado el lcd, con la librería liquidCrystal es muy fácil, ya que tiene métodos simples para poder mostrar en el lcd lo que quiera
2. El teclado numérico también viene con una librería, es una librería sencilla ya que el teclado es simplemente una matriz de 4x4 botones, gracias a la librería simplemente tenemos que declarar que valor tendrá cada botón
3. El panel de la cuenta atrás viene sin librería, por lo que para escribir un número tengo que ir diciéndole a arduino que pines quiero activar cada vez que cambio de número.
4.  Una vez que ya todo funciona por separado he realizado un contador que cuente los milisegundos, así poder hacer la cuenta atrás.
5.  He metido casi todo el programa en un if que se vuelve true al presionar una tecla , y así ya poder iniciar la cuenta atrás y dejar al jugador que pruebe números, mientras que cuando los comprueba los 5 leds se irán iluminando o no.
6. Una vez que el juego termina, se puede volver a jugar tantas veces como se quiera.
