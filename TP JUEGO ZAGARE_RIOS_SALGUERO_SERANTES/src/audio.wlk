import wollok.game.*

object audioManager {

	// Archivos de música disponibles
	var songFiles = [ "music/fight.wav", "music/tienda.mp3", "music/bossfight.mp3" ]
	var songs = [] // Lista de canciones cargadas
	var songPlaying = 0 // Índice de la canción actualmente en reproducción

	method initialize() {
		// Inicialización de las canciones
		songFiles.forEach({ f =>
			var nSong = new Sound(file = f) // Crea una instancia de Sound con el archivo especificado
			nSong.shouldLoop(true) // Configura la reproducción en bucle
			songs.add(nSong) // Agrega la canción a la lista
		})
		console.println(songs) // Muestra las canciones cargadas en la consola
	}

	method play(song) {
		var oldSong = songs.get(songPlaying) // Obtiene la canción actualmente en reproducción
		if (oldSong.played()) {
			if (not oldSong.paused()) oldSong.pause() // Pausa la canción actual si ya se ha reproducido
		}
		if (song == -1) {
			return 0
		} // Si se proporciona -1, no se reproduce ninguna canción
		var newSong = songs.get(song) // Obtiene la nueva canción según el índice proporcionado
		if (newSong.paused()) {
			newSong.resume() // Si está en pausa, reanuda la reproducción
		} else {
			newSong.play() // Si no está en pausa, inicia la reproducción
		}
		songPlaying = song // Actualiza el índice de la canción actual
		return 0
	}

}

