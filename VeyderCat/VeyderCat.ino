/*Nyan Cat
  with Bass
  Uses Arduino tone library pitches.h [http://arduino.cc/en/Tutorial/tone ]
       by electricmango
  https://electricmango.github.io

  Thanks to Sean for posting the sheet music on
  http://junket.tumblr.com/post/4776023022/heres-the-nyan-cat-sheet-music

  Version 1.0.3
  -------------------------------------------------------------------------
  Nyan Cat with Bass is licensed under the

  Creative Commons Attribution-ShareAlike 4.0 International (CC BY-SA 4.0)

  You are free to:
  Share — copy and redistribute the material in any medium or format
  Adapt — remix, transform, and build upon the material
  for any purpose, even commercially.
  The licensor cannot revoke these freedoms as long as you follow the license terms.
  Under the following terms:
  Attribution — You must give appropriate credit, provide a link to the license, and indicate if changes were made. You may do so in any reasonable manner, but not in any way that suggests the licensor endorses you or your use.
  ShareAlike — If you remix, transform, or build upon the material, you must distribute your contributions under the same license as the original.
  No additional restrictions — You may not apply legal terms or technological measures that legally restrict others from doing anything the license permits.
  The full license is available at https://creativecommons.org/licenses/by-sa/4.0/legalcode

  Copyright (c) 2012 ~ 2015 electricmango

  Edit by Amperka.ru in 2016

  -------------------------------------------------------------------------
  Nyan_Cat.ino
  -------------------------------------------------------------------------
*/

//Ноты

#define REST  0

#define c  261
#define d  294
#define e  329
#define f  349
#define g  391
#define gS  415
#define a  440
#define aS  455
#define b  466
#define cH  523
#define cSH  554
#define dH  587
#define dSH  622
#define eH  659
#define fH  698
#define fSH  740
#define gH  784
#define gSH  830
#define aH  880

#define LED_R 10
#define LED_Y 3
#define LED_G 9
#define LED_B 4
#define BUZZER 2
#define BUTTON 8


// Массив с нотами мелодии

int melody[] = {
  a, a, a, f, cH, a, f, cH, a, REST,
  eH, eH, eH, fH, cH, gS, f, cH, a, REST,
  aH, a, a, aH, gSH, gH, fSH, fH, fSH, REST,
  aS, dSH, dH, cSH, cH, b, cH, REST,
  f, gS, f, a, cH, a, cH, eH,
  aH, a, a, aH, gSH, gH, fSH, fH, fSH, REST,
  aS, dSH, dH, cSH, cH, b, cH, REST,
  f, gS, f, cH, a, f, cH, a, REST
};

// Массив длительности нот в мелодии: 4 = четвертная нота,
// 8 = восьмая нота, и так далее...

int noteDurations[] = {
  500, 500, 500, 350, 150, 500, 350, 150, 650, 150,
  500, 500, 500, 350, 150, 500, 350, 150, 650, 150,
  500, 300, 150, 400, 200, 200, 125, 125, 250, 250,
  250, 400, 200, 200, 125, 125, 250, 250,
  125, 500, 375, 125, 500, 375, 125, 650,
  500, 300, 150, 400, 200, 200, 125, 125, 250, 250,
  250, 400, 200, 200, 125, 125, 250, 250,
  250, 500, 375, 125, 500, 375, 125, 650, 10000
};

void setup() {
  //iterate over the notes of the melody:
  pinMode(LED_R, OUTPUT);
  pinMode(LED_Y, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);

}

void loop() {
  // Если была нажата кнопка, играем мелодию
  if (checkClick())
    nya();
  
  // Гасим светодиоды
  digitalWrite(LED_R, LOW);
  digitalWrite(LED_G, LOW);
  digitalWrite(LED_Y, LOW);
  digitalWrite(LED_B, LOW);
}

void nya()
{
  // Вычисляем количество нот
  int noteCount = sizeof(melody) / sizeof(int);

  // Переменная для хранения состояния светодиодов
  bool toggleLeds = true;
  
  // Играем мелодию
  for (int thisNote = 0; thisNote < noteCount; thisNote++) {
  
  // Если была нажата клавиша - останавливаем мелодию
    if (checkClick())
      return;
      
    // Каждую новую ноту меняем состояние светодиодов
    digitalWrite(LED_R, toggleLeds);
    digitalWrite(LED_Y, toggleLeds);
    digitalWrite(LED_G, !toggleLeds);
    digitalWrite(LED_B, !toggleLeds);
    toggleLeds = !toggleLeds;
    
    noTone(BUZZER); //останавливаем воспроизведение предыдущей ноты

    /*
     Вычислим длительность ноты. Разделим секунду на длительность ноты из массива
     Четвертная нота = 1000/4, восьмая нота 1000/8
     Скорость можно увеличить, увеличив числитель. Больше подошло 1200
    */

    int noteDuration = noteDurations[thisNote];
    
    // Можно увеличить высоту мелодии, умножая ноты на 2, 4, 8
    int octaveMul = 2;
    
    // воспроизведём ноту
    tone(BUZZER, octaveMul * melody[thisNote], noteDuration);

    /*
      Чтобы отделить ноты друг от друга, добавим небольшую паузу между ними
      30% от длины ноты звучат неплохо
    */
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);

  }
}
// Функция для проверки клика кнопки
bool checkClick()
{
  // Переменная для хранения предыдущего состояния кнопки
  static bool buttonWasUp = true;
  bool result = false;
  
  // Читаем текущее состояние кнопки
  bool buttonIsUp = digitalRead(BUTTON);
  
  // Если кнопка была не нажата, а теперь нажата
  // значит был клик
  if (buttonWasUp && !buttonIsUp) {
    delay(50);
    result = true;
  }
  buttonWasUp = buttonIsUp;
  return result;
}
