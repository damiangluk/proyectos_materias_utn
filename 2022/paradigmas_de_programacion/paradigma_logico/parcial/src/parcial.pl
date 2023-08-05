/*
Nombre: Gluk, Damian
Legajo: 2036794
*/

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% Código Inicial
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%% objetivo(Proyecto, Objetivo, TipoDeObjetivo)
objetivo(higiene, almejas, material(playa)).
objetivo(higiene, algas, material(mar)).
objetivo(higiene, grasa, material(animales)).
objetivo(higiene, hidroxidoDeCalcio, quimica([hacerPolvo, diluirEnAgua])).
objetivo(higiene, hidroxidoDeSodio, quimica([mezclarIngredientes])).
objetivo(higiene, jabon, quimica([mezclarIngredientes, dejarSecar])).

%% prerequisito(ObjetivoPrevio, ObjetivoSiguiente)
prerequisito(almejas, hidroxidoDeCalcio).
prerequisito(hidroxidoDeCalcio, hidroxidoDeSodio).
prerequisito(algas, hidroxidoDeSodio).
prerequisito(hidroxidoDeSodio, jabon).
prerequisito(grasa, jabon).

%% conseguido(Objetivo)
conseguido(almejas).
conseguido(algas).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%% Punto 1

%% puedeTrabajar(Persona, TipoDeObjetivo)
puedeTrabajar(senku, quimica(_)).
puedeTrabajar(senku, artesanal(Dificultad)) :- Dificultad < 7.
puedeTrabajar(chrome, material(Naturaleza)) :- (Naturaleza \= animales).
puedeTrabajar(chrome, quimica(Procesos)) :- length(Procesos, Cantidad), Cantidad < 4.
puedeTrabajar(kohaku, material(animales)).
puedeTrabajar(suika, material(playa)).
puedeTrabajar(suika, material(bosque)).
puedeTrabajar(suika, quimica([mezclarIngredientes])).
puedeTrabajar(_, artesanal(Dificultad)) :- Dificultad < 3.

%% Punto 2
esObjetivoFinal(Proyecto, Objetivo) :- 
    objetivo(Proyecto, Objetivo, _),
    not(prerequisito(Objetivo, _)).

%% Punto 3
esIndispensable(Persona, Objetivo) :- 
    objetivo(_, Objetivo, Tipo),
    puedeTrabajar(Persona, Tipo), 
    not((puedeTrabajar(OtraPersona, Tipo), OtraPersona \= Persona)).

%% Punto 4
puedeIniciarse(Objetivo) :-
    objetivo(_ ,Objetivo, _),
    not(conseguido(Objetivo)),
    forall(prerequisito(PreObjetivo, Objetivo), conseguido(PreObjetivo)).

%% Punto 5
tiempoEstimadoObjetivo(Objetivo, 0) :- conseguido(Objetivo).
tiempoEstimadoObjetivo(Objetivo, Tiempo) :- objetivo(_, Objetivo, Tipo), tiempoEstimadoTipo(Tipo, Tiempo).

tiempoEstimadoTipo(material(Naturaleza), 3) :- Naturaleza \= mar, Naturaleza \= cuevas.
tiempoEstimadoTipo(material(mar), 8).
tiempoEstimadoTipo(material(cuevas), 48).
tiempoEstimadoTipo(quimica(Procesos), Tiempo) :- length(Procesos, Cantidad), Tiempo is Cantidad * 2.
tiempoEstimadoTipo(artesanal(Dificultad), Dificultad).

tiempoFaltante(Proyecto, TiempoRestante) :-
    objetivo(Proyecto, _, _),
    findall(
        Tiempo, 
        (
            distinct(Objetivo, objetivo(Proyecto, Objetivo, _)),
            not(conseguido(Objetivo)),
            tiempoEstimadoObjetivo(Objetivo, Tiempo)
        ),
        TiemposLista), sum_list(TiemposLista, TiempoRestante).

%% Punto 6
esCostoso(Objetivo) :- objetivo(_, Objetivo, Tipo), tiempoEstimadoTipo(Tipo, Tiempo), Tiempo > 5.

bloqueaObjetivo(Objetivo, OtroObjetivo) :- prerequisito(Objetivo, OtroObjetivo).
bloqueaObjetivo(Objetivo, OtroObjetivo) :- prerequisito(Objetivo, Otro), bloqueaObjetivo(Otro, OtroObjetivo).

esCritico(Proyecto, Objetivo) :- 
    objetivo(Proyecto, Objetivo, _),
    bloqueaObjetivo(Objetivo, OtroObjetivo), 
    esCostoso(OtroObjetivo).

%% Punto 7
convieneTrabajar(Persona, Objetivo, Proyecto) :-
    distinct(Objetivo, objetivo(Proyecto, Objetivo, Tipo)),
    puedeIniciarse(Objetivo),
    puedeTrabajar(Persona, Tipo), 
    necesidadTrabajarCon(Persona, Objetivo, Proyecto).

necesidadTrabajarCon(Persona, Objetivo, _) :- 
    esIndispensable(Persona, Objetivo).
necesidadTrabajarCon(_, Objetivo, Proyecto) :- 
    tiempoEstimadoObjetivo(Objetivo, TiempoObj),
    tiempoFaltante(Proyecto, TiempoProy),
    TiempoObj > (TiempoProy / 2).
necesidadTrabajarCon(Persona, Objetivo, Proyecto) :-
    not((
        objetivo(Proyecto, OtroObjetivo, _),
        OtroObjetivo \= Objetivo,
        esIndispensable(Persona, OtroObjetivo)
    )).