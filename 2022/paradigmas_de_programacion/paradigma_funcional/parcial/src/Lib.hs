{-
Nombre: Gluk, Damian
Legajo: 203679-4
-}

module Lib where
import Text.Show.Functions

----------------------------------------------
-- Código base provisto en el enunciado
----------------------------------------------

maximoSegun :: Ord a => (b -> a) -> [b] -> b
maximoSegun f = foldl1 (mayorSegun f)

mayorSegun :: Ord a => (p -> a) -> p -> p -> p
mayorSegun f a b
  | f a > f b = a
  | otherwise = b

----------------------------------------------
-- DEFINICION DE LOS TIPOS DE DATOS
----------------------------------------------

data Rol = Rol {
  aptitud :: Int
} deriving (Show, Eq)

data Participante = Participante {
  nombre :: String,
  experiencia :: Int,
  inteligencia :: Int,
  destrezaFisica :: Int,
  rol :: Rol
} deriving (Show, Eq)

data Desafio = Desafio {
  rolesDisponibles :: [Rol],
  pruebaASuperar :: Participante -> Bool
}

data Arma = Arma {
  valorCombate :: Int,
  experienciaMinima :: Int
} deriving (Show, Eq)

----------------------------------------------
-- DEFINICION DE FUNCIONES
----------------------------------------------


-- PUNTO 1
-- inteligencia y destreza fisica
indeterminado :: Int -> Int -> Rol
indeterminado inteligencia = Rol . (inteligencia +)

-- inteligencia y experiencia
soporte :: Int -> Int -> Rol
soporte inteligencia = Rol . (inteligencia * 7 +)

-- potencia, destrezaFisica y experiencia
primeraLinea :: Int -> Int -> Int -> Rol
primeraLinea potencia destreza = Rol . ((potencia + destreza) *) . (`div` 100)

part1 :: Participante
part1 = Participante "participante 1" 1000 20 12 (indeterminado 20 12)

poderParticipante :: Participante -> Int
poderParticipante participante = experiencia participante * (aptitud (rol participante))



-- PUNTO 2
elegirNuevoRol :: Participante -> [Rol] -> Participante
elegirNuevoRol participante roles = participante {rol = maximoSegun aptitud roles}

calcularPotencia :: Arma -> Int -> Int
calcularPotencia arma experienciaReal
  | experienciaReal >= experienciaMinima arma = valorCombate arma
  | otherwise = div (valorCombate arma) 2

puedeUsarApropiadamente :: Int -> Arma -> Bool
puedeUsarApropiadamente experiencia = (experiencia >=) . experienciaMinima

-- La siguiente es la consulta que haria para poder obtener el poder del participante
listaRoles = [
              indeterminado (inteligencia part1) (destrezaFisica part1),
              soporte (inteligencia part1) (experiencia part1),
              primeraLinea (destrezaFisica part1) (experiencia part1) (calcularPotencia (Arma 20 750) (experiencia part1))
             ]
consulta = poderParticipante (elegirNuevoRol part1 listaRoles)

maestroDeArmas :: Int -> [Arma] -> Rol
maestroDeArmas experiencia = Rol . sum . map (`calcularPotencia` experiencia) . take 3 . filter (puedeUsarApropiadamente experiencia)

{-
  Si, seria posible ya que haskell utiliza la evaluacion perezosa (lazy), que se basa en resolver las funciones desde afuera hacia
  adentro (o desde la ultima en ejecutar hasta la primera en ejecutar), por lo que en este caso, cuando tendria que evaluar la lista
  infinita, ya sabria que solo tiene que tomar los primeros 3 elementos
-}



-- PUNTO 3
estaEntreParticipantes :: Participante -> [Participante] -> Bool
estaEntreParticipantes participante = elem (nombre participante) . map nombre

recompensaDeVencer :: [Participante] -> [Participante] -> Int
recompensaDeVencer ganadores = experiencia . maximoSegun (\p -> max (experiencia p) (inteligencia p)) . filter (not . flip elem ganadores) 



-- PUNTO 4
incrementarExperiencia :: [Participante] -> [Participante] -> [Participante]
incrementarExperiencia participantes ganadores = ((\valor -> map (\g -> g {experiencia = experiencia g + valor}) ganadores) . (recompensaDeVencer participantes)) ganadores

encararDesafio :: [Participante] -> Desafio -> [Participante]
encararDesafio participantes desafio = (incrementarExperiencia participantes . filter (pruebaASuperar desafio) . map (flip elegirNuevoRol (rolesDisponibles desafio))) participantes



-- PUNTO 5
competirEnTorneo :: [Participante] -> [Desafio] -> [Participante]
competirEnTorneo participantes = foldl encararDesafio participantes
-- foldl :: (b -> a -> b) -> b -> [a] - b
-- foldl :: ([Participante] -> Desafio -> [Participante]) -> [Participante] -> [Desafio] -> [Participantes]