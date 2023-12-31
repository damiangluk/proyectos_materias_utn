module SpecTP1 where

import TP1
import Test.Hspec
import Control.Exception (evaluate)

spec = do
  describe "Es mes" $ do
    it "El número 1 es un mes" $ do
      esMes 1 `shouldBe` True
    it "El número 7 es un mes" $ do
      esMes 7 `shouldBe` True
    it "El número 12 es un mes" $ do
      esMes 12 `shouldBe` True
    it "El número 0 no es un mes" $ do
      esMes 0 `shouldBe` False
    it "El número 13 no es un mes" $ do
      esMes 13 `shouldBe` False
  describe "Cambios de estación" $ do
    it "En enero (1) no hay cambio de estación" $ do
      hayCambioDeEstacion 1 `shouldBe` False
    it "En febrero (2) no hay cambio de estación" $ do
      hayCambioDeEstacion 2 `shouldBe` False
    it "En marzo (3) hay cambio de estación" $ do
      hayCambioDeEstacion 3 `shouldBe` True
    it "En abril (4) no hay cambio de estación" $ do
      hayCambioDeEstacion 4 `shouldBe` False
    it "En mayo (5) no hay cambio de estación" $ do
      hayCambioDeEstacion 5 `shouldBe` False
    it "En junio (6) hay cambio de estación" $ do
      hayCambioDeEstacion 6 `shouldBe` True
    it "En julio (7) no hay cambio de estación" $ do
      hayCambioDeEstacion 7 `shouldBe` False
    it "En agosto (8) no hay cambio de estación" $ do
      hayCambioDeEstacion 8 `shouldBe` False
    it "En septiembre (9) hay cambio de estación" $ do
      hayCambioDeEstacion 9 `shouldBe` True
    it "En octubre (10) no hay cambio de estación" $ do
      hayCambioDeEstacion 10 `shouldBe` False
    it "En noviembre (11) no hay cambio de estación" $ do
      hayCambioDeEstacion 11 `shouldBe` False
    it "En diciembre (12) hay cambio de estación" $ do
      hayCambioDeEstacion 12 `shouldBe` True
    it "No hay cambio de estación para números que son meses" $ do
      hayCambioDeEstacion 15 `shouldBe` False
  describe "Estaciones" $ do
    it "En enero es verano" $ do
      estacion 1 `shouldBe` "verano"
    it "En febrero es verano" $ do
      estacion 2 `shouldBe` "verano"
    it "En marzo es verano y otoño" $ do
      estacion 3 `shouldBe` "verano/otonio"
    it "En abril es otoño" $ do
      estacion 4 `shouldBe` "otonio"
    it "En mayo es otoño" $ do
      estacion 5 `shouldBe` "otonio"
    it "En junio es otoño e invierno" $ do
      estacion 6 `shouldBe` "otonio/invierno"
    it "En julio es invierno" $ do
      estacion 7 `shouldBe` "invierno"
    it "En agosto es invierno" $ do
      estacion 8 `shouldBe` "invierno"
    it "En septiembre es invierno y primavera" $ do
      estacion 9 `shouldBe` "invierno/primavera"
    it "En octubre es primavera" $ do
      estacion 10 `shouldBe` "primavera"
    it "En noviembre es primavera" $ do
      estacion 11 `shouldBe` "primavera"
    it "En diciembre es primavera y verano" $ do
      estacion 12 `shouldBe` "primavera/verano"
    it "La función estacion no está definida para números que no sean meses" $ do
      evaluate (estacion 15) `shouldThrow` anyException