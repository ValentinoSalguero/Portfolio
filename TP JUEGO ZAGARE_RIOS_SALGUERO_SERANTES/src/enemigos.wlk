import wollok.game.*
import world.*
import graphics.*
import player.*
import objects.*


class Enemigo {
	const property entityType = "enemy"
	var property vivo = true
	var property position = game.at(0,0)
	var posicionOriginal = null
	//var armaduraSumar = 0 
	
	method initialize(){
		posicionOriginal = position
	}
	
	method defensa(danio){}	
	
	method estaVivo() = vivo
	
	method perseguirJugador() {
		if (not game.hasVisual(self)) {return 0} //Por seguridad si justo es llamado cuando no tiene visual
		
		var player = world.player()
		var positioncand = null
		
		if (player.position().x() < position.x() and not self.mismoTipoEnPosicion(position.left(1)) ) {
			position = position.left(1)
		}
		if (player.position().x() > position.x() and not self.mismoTipoEnPosicion(position.right(1)) ) {
			position = position.right(1)
		}
		if (player.position().y() < position.y() and not self.mismoTipoEnPosicion(position.down(1)) ) {
			position = position.down(1)
		}
		if (player.position().y() > position.y() and not self.mismoTipoEnPosicion(position.up(1)) ) {
			position = position.up(1)
		}
		
		//Colision con el jugador
		if (player.position() == position) {
			self.ataque(player)
		}
		
		return 0
	}
	
	method mismoTipoEnPosicion(pos) {
		var o = game.getObjectsIn(pos)
		o = o.filter({obj => 
			return obj.toString() == self.toString()
		})
		return not o.isEmpty()
	}
	
	method activar() {
		if (not vivo) return 0
		
		if (posicionOriginal == null) posicionOriginal = position
		position = posicionOriginal
		game.onTick(500, self.identity().toString()+"_perseguir", {=>self.perseguirJugador()})
		game.onTick(50, self.identity().toString()+"_colisionBala", {=>self.colisionBala()})
		game.addVisual(self)
		return 0
	}
	
	//El enemigo ve si toca una bala cada 50 ms, si toca una bala la elimina y resta vida
	method colisionBala() {
		var col = game.colliders(self)
		col.forEach({col =>
			if (bulletManager.balas().contains(col)){
				self.defensa(col.danio())
				bulletManager.removeBullet(col)
			}
		})
	}
	
	method desactivar() {
		game.removeTickEvent(self.identity().toString()+"_perseguir")
		game.removeTickEvent(self.identity().toString()+"_colisionBala")
		game.removeVisual(self)
	}
	method collide(p) {
		self.ataque(p)
	}
	
	method ataque(p) {}
	
	method sumaEscudo(){
		var player = world.player()
		var sumar = player.armadura() + self.armaduraSumar()
		
		player.armadura(sumar)
	}
	
	method morir() {
		if (vivo) {
			vivo = false
			self.sumaEscudo()
			game.removeVisual(self)
			world.removeObjetoHabitacionActual(self)
			game.removeTickEvent(self.identity().toString()+"_perseguir")
			game.removeTickEvent(self.identity().toString()+"_colisionBala")
		}
	}

}

class Minions inherits Enemigo{
	var vida = 5 
	const ataque = 5		
	var property armaduraSumar = 1

	
	override method sumaEscudo(){
		var player = world.player()
		var sumar = player.armadura() + 1		
		player.armadura(sumar)}
	
	override method defensa(danio){
		vida -= danio
		if(vida <= 0){
			self.morir()
		}
	}
	
	override method ataque(jugador){
		game.say(self, "AAAAAA")
		jugador.danio(ataque)
	}
	
	method image() = "sprites/monsters/minion.png"
	
}

class Soldado inherits Enemigo{
	var vida = 50 
	const ataque = 25	
	var armadura = 50
	
	var property armaduraSumar = 5
	
	
	override method defensa(danio){
		if(armadura >= 0){
			armadura -= danio
		} else {
			vida -= danio
			if (vida <= 0) {
				self.morir()
			}
		}
	}
	
	override method ataque(jugador){
		game.say(self, "AAAAAA")
		jugador.danio(ataque)
	}
	
	method image()= "sprites/monsters/soldado.png"
}

class Demonio inherits Enemigo{
	var vida = 100 
	const ataque = 75	
	var armadura = 100
	
	
	var property armaduraSumar = 30
	

	override method defensa(danio){
		if(armadura >= 0){
			armadura -= danio
		} else {
			vida -= danio
			if (vida <= 0){
				//llamas al metodo que te de no se 20 escudo y listo
				self.morir()
			}
		}
	}
	
	override method ataque(jugador){
		game.say(self, "AAAAAA")
		jugador.danio(ataque)
	}
	
	method image()= "sprites/monsters/demonio.png"
}

class Jefe inherits Enemigo {
	var vida = 1 
	const ataque = 100	
	var armadura = 1
	
	var property armaduraSumar = 0

	override method defensa(danio){
		if(armadura >= 0){
			armadura -= danio
		} else {
			vida -= danio
			if(vida <= 0){
				self.morir()
				game.addVisual(win)
			}
		}
	}
	
	override method ataque(jugador){
		game.say(self, "AAAAAA")
		jugador.danio(ataque)
	}
	
	method image()= "sprites/monsters/jefe.png"
}

