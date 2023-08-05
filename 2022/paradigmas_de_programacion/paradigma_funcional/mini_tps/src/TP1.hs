module TP1 where

esMes :: Int -> Bool
esMes numero = numero > 0 && numero < 13

hayCambioDeEstacion :: Int -> Bool
hayCambioDeEstacion numero = esMes numero && (mod numero 3) == 0

siguienteMes :: Int -> Int
siguienteMes 12 = 1
siguienteMes n = n + 1

anteriorMes :: Int -> Int
anteriorMes 1 = 12
anteriorMes n = n - 1

estacion :: Int -> String
estacion 1 = "verano"
estacion 4 = "otonio"
estacion 7 = "invierno"
estacion 10 = "primavera"
estacion mes
    | hayCambioDeEstacion mes = estacion (anteriorMes mes) ++ "/" ++ estacion (siguienteMes mes)
    | esMes mes = estacion (anteriorMes mes)