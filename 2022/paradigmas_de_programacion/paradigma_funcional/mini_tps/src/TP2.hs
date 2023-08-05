module TP2 where

------------------------------------------
-- Modelo inicial
------------------------------------------

data Celular = Celular {
  linea :: (String, String),
  saldo :: Int,
  proveedor :: String
} deriving (Show, Eq)

------------------------------------------

aumentarSaldo :: Int -> Celular -> Celular
aumentarSaldo monto (Celular linea saldo proveedor) = Celular linea (saldo + monto) proveedor

plus :: Int -> Int
plus montoPagado = min montoPagado 100

aumentoPorProveedor :: Int -> Celular -> Int
aumentoPorProveedor montoPagado (Celular ("011", _) _ "Movistar") = montoPagado * 2
aumentoPorProveedor montoPagado (Celular _ _ "Personal") = plus montoPagado
aumentoPorProveedor _ _ = 0


promoRecarga :: Int -> Celular -> Celular
promoRecarga montoPagado celular = aumentarSaldo (aumentoPorProveedor montoPagado celular) (aumentarSaldo montoPagado celular)

{-

Funcion inicial que luego fue modificada/adaptada/optimizada
 
promoRecarga montoPagado (Celular linea saldo proveedor)
  | proveedor == "Movistar" && fst linea == "011" = Celular linea (saldo + montoPagado * 3) proveedor
  | proveedor == "Personal" = Celular linea (montoPagado + saldo + min montoPagado 100) proveedor
  | otherwise = Celular linea (saldo + montoPagado) proveedor
   
-}