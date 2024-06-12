import wollok.game.*
import world.*
import graphics.*
import enemigos.*
import objects.*

class Player {
	var property vida = 150
	var vivo = true
	var lastPosition = game.at(1,2)
	var property position = game.at(1, 2)
	var property armaEquipada = new Espada(tomado = true)
	var property armadura = 100
	var puedeMoverse = true
	var termino = false
	
	method image() {
		if (armaEquipada.playerSprite() != null) {
			return armaEquipada.playerSprite()
		}
		return "sprites/player/player_2.png"
	}
	
	method encontrarCuracion(curacion) {
			self.curacion(curacion)
		}

	method ataque(dir) {
        if(puedeMoverse){
        	armaEquipada.usar(position, dir)
        }else {
        	null
        }
	}

	method saberArma(){
		var arma = self.armaEquipada()
		return arma.danio()
	}
	
	
	method defensa(danio){}
	
	method dropArmaEquipada() {
		armaEquipada.position(lastPosition)
		armaEquipada.tomado(false)
		armaEquipada.activar()
		world.addObjetoHabitacionActual(armaEquipada)
		armaEquipada = null
	}
	
	method recargar(arma) = arma.recargar()
	
	method danio(danio) {
		if(armadura > 0){
			armadura -= danio
			if (armadura < danio){
				var resto = -(armadura - danio)
				armadura = 0
				vida -= resto
			}
		} else {
			vida -= danio
			if (vida <= 0) {
				puedeMoverse = false
				vida = 0
				self.morir()
			}
		}
	}
	
	method curacion(curacion) {
		if (vida + curacion.efecto() > 150) vida += (150 - vida)
		
		else vida += curacion.efecto()
	}
	
	/*method armadura(escudo) {
		if (armadura + escudo.efecto() > 100) armadura += (100 - armadura)
		else armadura += escudo.efecto() 
	}*/
	
	method estaVivo() = vivo
	
	method morir() {
		vivo = false
		return vivo
	}
	
	method move(dir){
		if(puedeMoverse){
			lastPosition = position
		
		if (dir == 0 and position.y() < game.height() -1) position = position.up(1)
		if (dir == 1 and position.x() < game.width() -1) position = position.right(1)
		if (dir == 2 and position.y() > 0) position = position.down(1)
		if (dir == 3 and position.x() > 0) position = position.left(1)
		
		var col = game.colliders(self)
		col.forEach({col => col.collide(self)})
		} else{
			if (termino == false){
				game.addVisual(gameOver)
				termino = true
				gameOver.animacionGameOver()
			}else{
				return 0
			}
		}
	}
	
	method revivir(){
		if(not vivo){
			vida = 150
		vivo = true
		armadura = 100
		puedeMoverse = true
		termino = false
		position = game.at(1, 2)
		game.removeVisual(gameOver)
		} else {
			null
		}
	}
	
	method collide(cosa){}
	
	method initialize() {
		keyboard.w().onPressDo({self.move(0)})
		keyboard.d().onPressDo({self.move(1)})
		keyboard.s().onPressDo({self.move(2)})
		keyboard.a().onPressDo({self.move(3)})	
    	keyboard.up().onPressDo({self.ataque(0)}) 
    	keyboard.right().onPressDo({self.ataque(1)}) 
    	keyboard.down().onPressDo({self.ataque(2)}) 
    	keyboard.left().onPressDo({self.ataque(3)}) 
    	keyboard.space().onPressDo({self.revivir()})
    	
	}

}