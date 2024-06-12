import wollok.game.*

// Objeto que maneja la interfaz gráfica (GUI)
object gui {

	var property player = null // Referencia al jugador
	var healthLabel = new guiLabel() // Etiqueta para mostrar la salud y la armadura

	method init() {
		game.addVisual(healthLabel) // Agrega la etiqueta al juego
		game.addVisual(caraGui) // Agrega el objeto caraGui al juego
		game.onTick(50, "UpdateGuiEvent", { => self.update()}) // Actualiza la GUI cada 50 ms
	}

	method update() {
		healthLabel.update("SALUD: " + player.vida().toString() + "\nARMADURA: " + player.armadura().toString())
	// Actualiza el texto de la etiqueta con la salud y la armadura del jugador
	}

}

// Objeto para mostrar una cara en la GUI
object caraGui {

	var property position = game.at(0, 0)
	var img = "ui/cara_mid.png" // Imagen inicial

	method initialize() {
		game.schedule(250.randomUpTo(1000), { => self.randFace()}) // Programa cambios aleatorios de imagen
	}

	method image() = img // Retorna la imagen actual

	method randFace() {
		img = [ "ui/cara_der.png", "ui/cara_mid.png", "ui/cara_izq.png" ].get(0.randomUpTo(2))
			// Cambia la imagen a una aleatoria entre las disponibles
		game.schedule(250.randomUpTo(1000), { => self.randFace()}) // Programa el próximo cambio
	}

	method collide(p) {
	}

}

// Etiqueta de la GUI para mostrar texto
class guiLabel {

	var property position = game.at(2, 0)
	var txt = "TEST" // Texto inicial

	method text() = txt // Retorna el texto actual

	method textColor() = "FFFFFFFF" // Color del texto (blanco)

	method update(t) {
		txt = t // Actualiza el texto con el valor proporcionado
	}

	method collide(p) {
	}

}

// Clase para manejar dígitos en la GUI 
class guiLabelNumberDigit {

}

