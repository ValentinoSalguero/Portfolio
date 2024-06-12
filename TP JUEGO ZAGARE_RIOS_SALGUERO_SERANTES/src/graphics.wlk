import wollok.game.*

///////CLASES DE SPRITES/////////
//Cada objeto/mob/como se llame debe tener varios objetos AnimatedSprite que definen las animaciones
//Y un objeto AnimatedSpriteManager el cual maneja el sprite actual y hace los cambios de sprite
//Clase de sprite animado. Puede reproducir y parar la animacion, y obtener el frame actual
class AnimatedSprite {

	const property animationId = self.identity().toString() + "_animation"
	var frame = 0
	var frame_duration = 10
	var property images = [ "null.png" ]

	method initialize() {
	// No se realiza ninguna acción en la inicialización
	}

	// Arranca la animación
	method play() {
		game.onTick(frame_duration, animationId, { => self.next_frame()})
	}

	// Detiene la animación
	method stop() {
		try {
			game.removeTickEvent(animationId)
		} catch e : Exception {
		// No se realiza ninguna acción si la animación no existe
		}
		frame = 0
	}

	// Avanza al próximo frame. Si no hay más frames, vuelve al inicial.
	method next_frame() {
		frame = (frame + 1) % images.size()
	}

	// Retorna la imagen actual del sprite
	method image() = images.get(frame)

}

// Manager de sprites animados para simplificar las cosas
// Todas las acciones relacionadas con el sprite (reproducir, detener, cambiar) se deben hacer desde este objeto.
class AnimatedSpriteManager {

	var sprite = null
	var playing = false

	method image() {
		if (sprite != null) {
			return sprite.image()
		} else {
			return "null.png"
		}
	}

	method setSprite(newSprite) {
		sprite.stop() // Detiene el sprite actual
		sprite = newSprite // Cambia al nuevo sprite
		if (playing) sprite.play() // Si estaba reproduciendo, inicia el nuevo sprite
	}

	method play() {
		playing = true
		if (sprite != null) sprite.play() // Inicia la reproducción del sprite actual
	}

	method stop() {
		playing = false
		if (sprite != null) sprite.stop() // Detiene la reproducción del sprite actual
	}

	method currentSprite() = sprite

	method currentSpriteAnimationId() = sprite.animationId()

}

// Ejemplo de objeto usando AnimatedSprite y AnimatedSpriteManager
object TestAnimatedObject {

	var property position = game.at(4, 5)
	var sprFlyingDown = new AnimatedSprite(images = [ "sprites/test/testsprite_0.png", "sprites/test/testsprite_1.png", "sprites/test/testsprite_2.png" ], frame_duration = 200)
	var sprFlyingUp = new AnimatedSprite(images = [ "sprites/test/testsprite_4.png", "sprites/test/testsprite_6.png", "sprites/test/testsprite_7.png" ], frame_duration = 200)
	var sprite = new AnimatedSpriteManager(sprite = sprFlyingDown)

	method image() = sprite.image()

	method initialize() {
		sprite.play() // Inicia la reproducción del sprite
		game.onTick(5000, "TestChangeSprite", { => self.testChangeSprite()})
	}

	method testChangeSprite() {
		console.println(sprite.currentSpriteAnimationId())
		if (sprite.currentSpriteAnimationId() == sprFlyingUp.animationId()) {
			sprite.setSprite(sprFlyingDown) // Cambia al sprite "FlyingDown"
		} else if (sprite.currentSpriteAnimationId() == sprFlyingDown.animationId()) {
			sprite.setSprite(sprFlyingUp) // Cambia al sprite "FlyingUp"
		}
	}

}