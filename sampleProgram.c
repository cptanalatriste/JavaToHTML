void configurar() {
	definirTitulo("Titulo del formulario")
	definirHojaDeEstilos("style.css")

	Parrafo parrafo 
	parrafo = generarParrafo("Este parrafo contiene las instrucciones del formulario")

	CajaTexto cajaTextoNombre
	cajaTextoNombre = generarCajaTexto("idTexto", "Caja de Texto")

	Boton botonEnviar
	botonEnviar = generarBoton("Enviar")

	agregarElemento(parrafo)
	agregarElemento(cajaTextoNombre)
	agregarElemento(botonEnviar)
}
generarFormulario()

