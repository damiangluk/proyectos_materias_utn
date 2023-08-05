object jardin {
	var property malezas = 30
	
	method image()
	  = if(not self.desprolijo()) "arbusto.png"
	    else "arbusto-desprolijo.png"
	
	method crecerMalezas() {
		malezas += 5
	}
	
	method desprolijo() = malezas > 20
	
	method emprolijar(nivelProlijidad) {
		if (nivelProlijidad >= 10)
			malezas = 0
		else if (nivelProlijidad >= 3)
			malezas /= 2
	}
}

object spa {
	method image() = "spa.png"
	
	method atender(persona) {
		persona.seDaBanioDeVapor(5)
		persona.recibeMasajes()
		persona.seDaBanioDeVapor(15)
	}
}

object olivia {
	var property relax = 4
	
	method image() = "jardinera.png"
	
	method seEstresa(num){
		relax = (relax - num).max(1)
	}
	
	method trabajarEnJardin(unJardin){
		if(unJardin.desprolijo()){
			self.seEstresa(2)
		}
		
		unJardin.emprolijar(relax * 2)
		self.seEstresa(1)
	}
	
	method seDaBanioDeVapor(minutos){
		relax += (minutos / 5)
	}
	
	method recibeMasajes(){
		relax += 3
	}
}

object adriano {
	var property contracturas = 0
	
	method image() = "jardinero.png"
	
	method estaLastimado() = contracturas > 10
	
	method nivelProlijidad() {
		if(self.estaLastimado())
			return 1
		return 5
	}
	
	method trabajarEnJardin(unJardin){
		const malezasIniciales = unJardin.malezas()
		unJardin.emprolijar(self.nivelProlijidad())
		contracturas += 7.min(malezasIniciales)
	}

	method disminuirContracturas(num){
		contracturas = (contracturas - num).max(0)
	}
	
	method seDaBanioDeVapor(_){
		if(self.estaLastimado())
			self.disminuirContracturas(2)
	}
	
	method recibeMasajes(){
		self.disminuirContracturas(5)
	}
}