object carrito {
	const listaDeProductos = new List()
	
	method agregar(producto) {
		listaDeProductos.add(producto)
	}

	method estaVacio() {
		return listaDeProductos.isEmpty()
	}
	
	method cantidadDeProductos() {
		return listaDeProductos.size()
	}
	
	method totalAAbonar() {
		return listaDeProductos.sum({prod => prod.precioTotal()})
	}
	
	method productoMasCaro() {
		return listaDeProductos.max({prod => prod.precioTotal()})
	}
	
	method detalleDeCompra() {
		return listaDeProductos.map({prod => prod.descripcion()}).asSet().sortedBy({x, y => x < y})
	}
}

class ProductoUnitario {
	var property nombre
	var property precioUnitario
	
	method precioTotal() = precioUnitario
	method descripcion() = nombre
}

class ProductoPorPeso {
	var property nombre
	var property precioPorKilo
	var property peso
	
	method precioTotal() = precioPorKilo * peso
	method descripcion() = nombre + " x " + peso.toString() + " kg"
}

