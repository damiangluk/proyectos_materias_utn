import tp4.usuario.*
import tp4.redSocial.*

const privada = new Privada()

object fabrica {
	const property creador = new Usuario(nombre = "Tito")
	
	method fechaPublicacion() = new Date()
	method crearPublicacionPublica() {
		return new Publicacion(
			usuario = self.creador(),
			privacidad = publica,
			fechaDePublicacion = self.fechaPublicacion()
		)
	}
	method crearPublicacionPrivada() {
		return new Publicacion(
			usuario = self.creador(),
			privacidad = privada,
			fechaDePublicacion = self.fechaPublicacion()
		)
	}
	method crearHistoriaPublica() {
		return new Historia(
			usuario = self.creador(),
			privacidad = publica,
			fechaDePublicacion = self.fechaPublicacion()
		)
	}
	method crearHistoriaPrivada() {
		return new Historia(
			usuario = self.creador(),
			privacidad = privada,
			fechaDePublicacion = self.fechaPublicacion()
		)
	}
	method crearPublicacionSecreta(restringidos) {
		return new Publicacion(
			usuario = self.creador(),
			privacidad = new Secreta(usuariosRestringidos = restringidos),
			fechaDePublicacion = self.fechaPublicacion()
		)
	}
	method crearHistoriaSecreta(restringidos) {
		return new Historia(
			usuario = self.creador(),
			privacidad = new Secreta(usuariosRestringidos = restringidos),
			fechaDePublicacion = self.fechaPublicacion()
		)
	}
	
	// Otros métodos convenientes que se usan desde las pruebas
	// No se espera que los cambies
	
	method fechaLejanaAPublicacion() = self.fechaPublicacion().plusDays(10)
	method diaSiguienteAPublicacion() = self.fechaPublicacion().plusDays(1)
	
	method configurarContactos(){
		creador.agregarContacto(new Usuario(nombre = "Ana"))
		creador.agregarContacto(new Usuario(nombre = "Fito"))
	}
	
	method desconocido() = new Usuario(nombre = "Anónimo")
	method contactoDelCreador() = self.creador().contactos().anyOne()
	
	method usuariosDePrueba() 
		= #{creador, self.desconocido()} + creador.contactos()
}