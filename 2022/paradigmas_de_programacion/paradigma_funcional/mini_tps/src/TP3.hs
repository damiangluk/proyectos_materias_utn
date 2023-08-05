module TP3 where
import Cafe

-- Utilizar composicion y aplicacion parcial

prepararFrapuccino :: Gramos -> Cafe
prepararFrapuccino = servirEnVaso 400 . licuar 60 120 . agregarHielo 6 . prepararCafe 80 . molerGranos

prepararCafeDeFiltro :: Vaso -> Gramos -> Cafe
prepararCafeDeFiltro vaso = servirEnVaso vaso . prepararCafe 1000 . molerGranos