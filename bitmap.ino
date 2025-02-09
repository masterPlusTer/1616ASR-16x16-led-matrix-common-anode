
// codigo para arduino mega

// Pines de la matriz LED 16x16 (ÁNODO COMÚN)
const int filas[] = {A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, A0};
const int columnas[] = {17, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};

// Bitmap (Dibujo en formato de 16x16)
const bool dibujo[16][16] = {
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,1,1,1,0,0,0,0,0,0,0,0,1,1,1,0},
  {0,1,0,1,0,0,0,0,0,0,0,0,1,0,1,0},
  {0,1,0,1,0,0,0,0,0,0,0,0,1,0,1,0},
  {0,1,1,1,0,0,0,0,0,0,0,0,1,1,1,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0},
  {0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0},
  {0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0},
  {0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0},
  {0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0},
  {0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0},
  {0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};

void setup() {
    Serial.begin(9600);

    // Configurar pines como salida
    for (int i = 0; i < 16; i++) {
        pinMode(filas[i], OUTPUT);
        digitalWrite(filas[i], LOW);  // Todas las filas apagadas inicialmente

        pinMode(columnas[i], OUTPUT);
        digitalWrite(columnas[i], HIGH); // Mantener todas las columnas apagadas inicialmente
    }
}

// Dibujar el bitmap en la matriz LED con mejor apagado
void mostrarDibujo() {
    static int filaAnterior = 15; // Variable para la fila anterior

    // Apagar completamente la fila anterior
    digitalWrite(filas[filaAnterior], LOW);
    for (int i = 0; i < 16; i++) {
        digitalWrite(columnas[i], HIGH); // Desactivar TODAS las columnas antes de cambiar de fila
    }

    // Cambiar a la siguiente fila
    int filaActual = (filaAnterior + 1) % 16;

    // Activar la fila nueva
    digitalWrite(filas[filaActual], HIGH);

    // Encender columnas de acuerdo al bitmap
    for (int j = 0; j < 16; j++) {
        digitalWrite(columnas[j], dibujo[filaActual][j] ? LOW : HIGH);
    }

    // Guardar la fila actual como la anterior para la siguiente iteración
    filaAnterior = filaActual;

    delayMicroseconds(500); // Tiempo optimizado para evitar fugas de corriente
}

void loop() {
    mostrarDibujo(); // Mostrar la imagen en la matriz LED
}
