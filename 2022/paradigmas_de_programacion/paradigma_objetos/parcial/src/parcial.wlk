/*
* Nombre: Gluk, Damian
* Legajo: 2036794
*/

class Imperio {
	var dinero
	const property ciudades
	
	method estaEndeudado() = dinero < 0
	method pagar(cantidad) {
		dinero -= cantidad
	}
	method cobrar(cantidad) {
		dinero += cantidad
	}
	method evolucionar() {
		ciudades.forEach({c => c.evolucionar()})
	}
}

class Ciudad {
	var property sistemaImpositivo
	var edificios
	var tanques
	const baseConstruccion
	const imperio
	var property poblacion
	
	method esFeliz() = !imperio.estaEndeudado() && self.tranquilidadTotal() > self.disconformidadHabitantes() 
	method tranquilidadTotal() = edificios.sum({e => e.tranquilidadQueAporta()})
	method culturaTotal() = edificios.sum({e => e.culturaQueIrradia()})
	method disconformidadHabitantes() = poblacion / 10000 + tanques.min(30)
	method costoDeConstruccion(edificio) = sistemaImpositivo.costoConstruccion(self, edificio, baseConstruccion)
	method costoMantenimiento(edificio) = self.costoDeConstruccion(edificio) / 100
	method construirEdificio(edificio) {
		const costo = self.costoDeConstruccion(edificio)
		if(costo > imperio.dinero())
			throw new NoAlcanzanPepinesException(message = "El costo es mayor al dinero del imperio")
		edificios.add(edificio)
		imperio.pagar(costo)
		
	}
	method CrecerPoblacionPorcentaje(porcentaje) {
		poblacion += poblacion * porcentaje / 100
	}
	method tanquesRecaudados() = edificios.sum({e => e.aportaTanques()})
	method dineroRecaudado() = edificios.sum({e => e.aportaDinero()})
	method evolucionar() {
		if(self.esFeliz())
			self.CrecerPoblacionPorcentaje(2)
		edificios.forEach({e => imperio.pagar(self.costoMantenimiento(e))})
		tanques += self.tanquesRecaudados()
		imperio.cobrar(self.dineroRecaudado())
		self.ajustarSistemaImpositivo()
	}
	method ajustarSistemaImpositivo() {
		if(!self.esFeliz()) self.sistemaImpositivo(apaciguador)
		if(self.estaEntreLasFelicesMenosCulturales()) self.sistemaImpositivo(incentivoCultural)
		self.sistemaImpositivo(new Citadino(incrementoPorHabitantes = 25000))
	}
	method estaEntreLasFelicesMenosCulturales() {
		const culturaTotal = self.culturaTotal()
		return imperio.ciudades().filter({c => c.esFeliz()}).count({c => culturaTotal > c.culturaTotal()}) < 3
	}
}

class Capital inherits Ciudad {
	override method disconformidadHabitantes() = super() / 2
	override method costoDeConstruccion(edificio) {
		const costo = super(edificio)
		return costo + costo * 10 / 100
	}
	override method dineroRecaudado() = super() * 3
}

class Edificio {
	method tranquilidadQueAporta()
	method culturaQueIrradia()
	method aportaDinero() = 0
	method aportaTanques() = 0
}

class Economico inherits Edificio {
	const dineroGenerado
	override method tranquilidadQueAporta() = 3
	override method culturaQueIrradia() = 0
	override method aportaDinero() = dineroGenerado
}

class Cultural inherits Edificio {
	const cultura
	override method tranquilidadQueAporta() = cultura * 3
	override method culturaQueIrradia() = cultura 
}

class Militar inherits Edificio {
	const tanquesGenerados
	override method tranquilidadQueAporta() = 0
	override method culturaQueIrradia() = 0
	override method aportaTanques() = tanquesGenerados
}

class SistemaImpositivo {
	method costoConstruccion(ciudad, edificio, base) = base + self.costo(ciudad, edificio, base)
	method costo(ciudad, edificio, base)
}

class Citadino inherits SistemaImpositivo {
	const incrementoPorHabitantes
	method hayIncremento() {
		if(incrementoPorHabitantes < 1) 
			throw new IncrementoPorHabitantesException(message = "El incremento por cantidad de habitantes no puede ser menor a 1")
	}
	override method costo(ciudad, edificio, base){
		self.hayIncremento()
		return ciudad.poblacion() / incrementoPorHabitantes * base * 5 / 100
	}
}

object incentivoCultural inherits SistemaImpositivo {
	override method costo(ciudad, edificio, base){
		return - edificio.culturaQueIrradia() / 3
	}
}

object apaciguador inherits SistemaImpositivo {
	override method costo(ciudad, edificio, base){
		if(ciudad.esFeliz())return 0
		return - edificio.tranquilidadQueGenera()
	}
}

class IncrementoPorHabitantesException inherits DomainException {}
class NoAlcanzanPepinesException inherits DomainException {}