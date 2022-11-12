Grupo #22 (turno T)
Nombre del grupo: kevinramis
Repositorio: https://gitlab.com/EzequielRamis/algo2-2022c2-grupal.git
Integrantes:
    469/17 Guberman Diego Andrés <diego98g@hotmail.com>
    881/21 Ramis Folberg Ezequiel Leonel <ezequielramis.hello@gmail.com>
    476/16 Sabetay Kevin Damian <kevin_sabetay@hotmail.com>

diego98g@hotmail.com,ezequielramis.hello@gmail.com,kevin_sabetay@hotmail.com

Ojo: pueden faltar integrantes.
Revisar si los datos de la carátula coinciden con los de este listado.


Nota: Aprobado


Comentario General:
- En aliasing, cuando dicen por ejemplo en JugadaValida? "se pasa o: ocurrencia como referencia no modificable" eso ya esta claro de que a. ocurrencia no es un tipo primitivo, siempre se pasa por referencia; y b. el argumento tiene el modificador `in`. Lo que uno espera tener en aspectos de aliasing es que se espera de esa referencia, por ejemplo, en `NuevoJuego` esperaria algo como, la variante no debe ser modificada por fuera, sino invalida el funcionamiento del juego.
- Tal vez el tablero podria ser un modulo auxiliar, pero OK
- Suele ser una buena idea organizar el Rep en sub reps. Y explicar las ideas en prosa.
- No me calculan complejidades y me pone mal.
- Faltan los servicios usados

Comentarios Puntuales:
## Juego
### Rep
- Acuerdense de desreferenciar los punteros
- `e.jugadores[i].cantFichasPorLetra[f] = #fichas(e.variante)` creo que esta mal
- `historialSinVacias` me da vuelta la lista, esta bien eso?
- Por que me guardo todo el historial y no solo lo que no calcule?
- `OcurrenciasValidas` solo chequea que no esten ocupadas, deberia chequear `jugadaValida`?
- En Abs, creo que les falta una parte de puntaje, todo el no calculado, pero podian utilizar las funciones que axiomatizaron arriba
### Algos
- Repartir fichas seguro se puede mover a una auxiliar
- Linea 29 de jugadaValida, creo que no hace falta pedir que los rangos sean distintos. Chequeenlo contra la especificacion del TAD. Similar linea 49
- Como ejercicio mental, piensen como abstraer el codigo de los dos branches del if en jugadavalida
- JugadaValida deberia chequear que el jugador tiene las fichas que dice tener. Creo que quedo afuera del TAD
- A veces el nombre del parametro es `j` pero usan `e`. Typo
- Puntaje la hicieron antes que jugadaValida? Podian reutilizar todas las funciones tipo `esHorizontal` o `rangoDePalabraHorizontal`. Ah, va sumando puntaje, por ahi no. Por ahi pueden generalizar eso en C++
- Linea 26 y 47 de puntaje, revisen el TAD, creo que se suman dos veces.

## Servidor
### Interfaz
- Conectar, en TP2 les va a ser muy util que devuelva el IdCliente
- Recibir depende de K, mal. Van a tener que pensar otra solucion para el TP2
### Algos
- La complejidad de Conectar esta mal calculada
- En Consultar, de donde sale que copiar una notificacion es constante? y por que las copian?
- No me calcularon la complejidad de Recibir, :(
- Me hace un poco de ruido que Recibir tenga que hacer toda la logica de reponer fichas, si en definitiva invoca a Ubicar que hacer exactamente lo mismo.
- El servidor no tiene `configuracion` en su estructura, y lo usan en varios lados

## Variante
### Rep
- #palabraMasLarge deberia ser Nat
- Esta bien lo que dicen que no existe p que bla bla bla, pero falta decir que existe alguno que es igual, sino pongo un num enorme en e.#palabraMasLarga y listo

## Ocurrencia
### Interfaz
- Ejercicio mental, mejoren las complejidades de las operaciones a O(n*log(n)). Si pudiesen pedir algo en el invariante de `conj` que pedirian para que esas operaciones fuesen O(n). En ambos casos n = #o
### Algoritmos
- Por lo general, como los algoritmos no toman la estructura (son externos en algun sentido), no los prefijamos con `i-`

## Trie
### Interfaz
- Esta ok, pero el Trie puede servir más allá del juego. Intenten definir complejidades en base a sus propios inputs y no a inputs del dominio del ejercicio
### Rep
- Bien el rep, pero me deberian decir algo de que los punteros, por ejemplo, no forman ciclos.
### Algos
- Definir no avanza `pIt` en el primer while ni corta si ya lo recorrio todo (Imaginen definir "Holas" y despues "Hol") 
- Es necesario el primer if de `Definida`? Intenten hacer todo en el mismo while (ejercicio mental)


