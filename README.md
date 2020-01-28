# Desconecta4Boom
Diseño e implementación de técnicas de búsqueda con adversario en un entorno de juegos.
El entorno de simulación se ha adaptado para simular el juego “DESCONECTA-4 BOOM”.
“DESCONECTA-4 BOOM” se basa en el juego CONECTA-4 (también conocido como 4 en Raya en algunas versiones).

-El objetivo de DESCONECTA-4 BOOM es alinear cuatro fichas sobre un tablero formado por siete filas y
siete columnas (en el juego original, el tablero es de seis filas). Cada jugador dispone de 25 fichas de un color
(en nuestro caso, verdes y azules). Por turnos, los jugadores deben introducir una ficha en la columna que
prefieran (de la 1 a la 7, numeradas de izquierda a derecha, siempre que no esté completa) y ésta caerá a la
posición más baja. Pierde la partida el primero que consiga alinear cuatro fichas consecutivas de un mismo
color en horizontal, vertical o diagonal. Si todas las columnas están ocupadas se produce un empate.

-DESCONECTA-4 BOOM mantiene todas las normas del juego habitual del 4 en raya con una
variante: cada cinco movimientos el jugador coloca una ficha de su color especial que llamaremos
“ficha bomba” (es decir, en las jugadas, 5, 10, 15, 20,...), pudiendo tener como máximo cada jugador
una ficha de este tipo en el tablero (es decir, que si llega la jugada 10 y el jugador que le toca poner
tiene ya una ficha bomba, la ficha que se pone en el mapa es una ficha normal). La ficha bomba, al
igual que el resto de las fichas del jugador, sirven para confeccionar una posible alineación de 4 fichas
para perder el juego, pero tiene la peculiaridad de que el jugador la puede “explotar” en una jugada en
su turno.
¿Cómo se explota una ficha? El jugador en su turno y si tiene una ficha bomba colocada en el tablero
tiene una acción adicional que consiste en explotarla. Al aplicar esta acción, el jugador con el turno, lo
pasa al adversario sin situar ninguna ficha en el tablero.
¿Qué efecto produce la explosión? La explosión elimina la propia ficha bomba y las fichas que están
en la misma fila que son del jugador que explota la bomba. Las fichas situadas encima de las casillas
afectadas caerían por gravedad hasta situarse en sus posiciones estables.

-USO:
Hacer "make" para generar el ejecutable. Ejecutar Desconecta4Boom para abrir la interfaz gráfica.
