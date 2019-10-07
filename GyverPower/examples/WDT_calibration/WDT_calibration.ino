#include <GyverPower.h>

void setup() {
  Serial.begin(9600);
  // WDT будит МК ото сна, его таймер не очень точный (с завода) и нуждается в калибровке.
  // Калибровка таймаутов для максимальной точности sleepDelay

  // === ВАРИАНТ 1 ===
  Serial.println(getMaxTimeout()); // вывести реальный макс. период (выполняется ~8 секунд)
  // допустим вывело 8321
  calibrate(8321); 			// калибруем по реальному периоду
  // можно жёстко задать в скетче (как выше) или пихнуть в EEPROM

  // === ВАРИАНТ 2 ===
  // автоматически посчитать и откалибровать (выполняется ~8 секунд)
  // каждый раз при запуске скетча
  calibrate(getMaxTimeout());

  // === ВАРИАНТ 3 ===
  autoCalibrate(); // автоматическая калибровка ~2 секунды
  // калибрует менее точно, чем вариант с 8-ю секундами. Можно оставить "на каждый запуск"
  
  pinMode(13, OUTPUT);
}

void loop() {
  // пример циклического сна
  sleepDelay(1500); // спим ровно 1.5 секунды (мы откалиброваны!)
  digitalWrite(13, !digitalRead(13)); // инвертируем состояние на пине
}
