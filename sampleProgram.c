void configurar() {
	definirTitulo(variableTitulo)
	CajaTexto cajaTextoNombre
	cajaTextoNombre = generarCajaTexto(variableNombreCaja, variableEsObligatorioCaja, 
		variableEsAlfanumericoCaja, variableClaseCaja)

	Boton botonEnviar
	botonEnviar = generarBoton(variableNombreBoton, variableClaseCaja)

	definirHojaDeEstilos(variableHojaEstilos)
	definirPosicion(variablePosicion)
	agregarElemento(cajaTextoNombre)
	agregarElemento(botonEnviar)
}
generarFormulario()

