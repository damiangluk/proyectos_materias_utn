import tp4.usuario.*

class Publicacion {
	const property usuario
	const fechaDePublicacion
	var property privacidad
	method sigueVigente(fecha) = true
	method visitanteEsCreador(visitante) = usuario == visitante
	method esVisible(visitante, fecha) = self.visitanteEsCreador(visitante) || privacidad.esVisible(self, visitante) && self.sigueVigente(fecha)
}

class Historia inherits Publicacion {
	override method sigueVigente(fecha) = (fecha - fechaDePublicacion).abs() < 2
}

object publica {
	method esVisible(publicacion, visitante) = true
}


class Privada {
	method esVisible(publicacion, visitante) {
		return publicacion.usuario().tieneContacto(visitante) && publica.esVisible(publicacion, visitante)	
	}
}

class Secreta inherits Privada {
	var property usuariosRestringidos = []
	override method esVisible(publicacion, visitante) {
		return !usuariosRestringidos.contains(visitante) && super(publicacion, visitante)
	}
}