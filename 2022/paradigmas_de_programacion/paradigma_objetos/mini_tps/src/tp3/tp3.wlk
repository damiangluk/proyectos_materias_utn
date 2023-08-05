class EstiloDeCruza {	
	method AnalizarExitoDelCruce(perro1, perro2) {
		if(!perro1.esCompatibleCon(perro2)) self.errorCruzaNoExitosa()
	}
	
	method errorCruzaNoExitosa() {
		throw new NoSePudieronCruzarException(message="Se intentaron cruzar dos perros no compatibles")
	}
	
	method cruzar(perro1, perro2) 
	{	
		self.AnalizarExitoDelCruce(perro1,perro2)
		return self.crearCria(perro1, perro2)
	}
	
	method crearCria(perro1, perro2) {
		return new Perro(
			velocidad = self.calculoDeFuerzaYVelocidad(perro1.velocidad(), perro2.velocidad(), perro1.esHembra()),
			fuerza = self.calculoDeFuerzaYVelocidad(perro1.fuerza(), perro2.fuerza(), perro1.esHembra())
		)
	}
	
	method calculoDeFuerzaYVelocidad(dato1, dato2, elPrimeroEsHembra)
} 

object cruzaPareja inherits EstiloDeCruza {
	method calculoDeFuerzaYVelocidad(dato1, dato2, _) {
		return (dato1 + dato2) / 2
	}
}

object hembraDominante inherits EstiloDeCruza {
	override method cruzar(perro1, perro2) 
	{
		if(!self.laHembraEsMasFuerte(perro1, perro2))
			throw new NoSePudieronCruzarException(message="Se intento cruzar un macho con un hembra mas debil que el")
		return super(perro1, perro2)
	}
	
	method calculoDeFuerzaYVelocidad(dato1, dato2, elPrimeroEsHembra) {
		if(elPrimeroEsHembra) {
			return (dato1 + 5 * dato2 / 100)			
		}
		return dato2 + 5 * dato1 / 100
	}
	
	method laHembraEsMasFuerte(perro1, perro2) {
		return 
			perro1.esHembra() && perro1.esMasFuerteQue(perro2) ||
			perro2.esHembra() && perro2.esMasFuerteQue(perro1)
	}
}

object underdog inherits EstiloDeCruza {
	method calculoDeFuerzaYVelocidad(dato1, dato2, _) {
		return dato1.min(dato2) * 2
	}
}

class Criadero {
	const property perros
	
	method cruzar(estiloDeCruza, perroACruzar) {
		const listaPerros = self.perros().asList()
		const perrosPotencialesOrdenados = self.potencialesParejas(estiloDeCruza, perroACruzar, listaPerros)
		perrosPotencialesOrdenados.sortBy({p1, p2 => p1.status() > p2.status()})

		return self.intentarCruce(estiloDeCruza, perroACruzar, perrosPotencialesOrdenados, 1)
	}
	
	method intentarCruce(estiloDeCruza, perro1, perrosPotencialesOrdenados, numeroDeIntento) {
		
		if (numeroDeIntento > 3) 
			return throw new IntentosDeCruzaAgotadosException(message="Se agotaron los intentos de cruzar perros")
			
		if(perrosPotencialesOrdenados.size() < numeroDeIntento)
			return throw new NecesitaMasPerrosException(message="La cantidad de perros no es suficiente para encontrar una cria")		
			
		try {
			return estiloDeCruza.cruzar(perro1, perrosPotencialesOrdenados.get(numeroDeIntento - 1))
		} catch ex : NoSePudieronCruzarException 
		{
			return self.intentarCruce(estiloDeCruza, perro1, perrosPotencialesOrdenados, numeroDeIntento + 1)
		}
	}
	
	method potencialesParejas(estiloDeCruza, perroACruzar, lista) = lista.filter({p => p.esCompatibleCon(perroACruzar)})
}

////////////////////
/// Excepciones
////////////////////
class NoSePudieronCruzarException inherits DomainException {}
class IntentosDeCruzaAgotadosException inherits DomainException {}
class NecesitaMasPerrosException inherits DomainException {}

/////////////////////////////////////////////////////////////////////////////////////////

class Perro {
	const property esHembra = 0.randomUpTo(2).roundUp() > 1
	var property velocidad
	var property fuerza
	var property adulto = false

	method status() = self.fuerza() + self.velocidad()
	method tienenSexosDistintos(otroPerro) = otroPerro.esHembra() != self.esHembra()
	method esCompatibleCon(otroPerro) = self.adulto() && otroPerro.adulto() && self.tienenSexosDistintos(otroPerro)
	method esMasFuerteQue(otroPerro) = self.fuerza() > otroPerro.fuerza()
}

