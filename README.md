stm32f411ret6보드를 이용한 BLDC모터 제어 코드입니다.
TI사의 DRV8313을 사용하며 iPower GM4108 모터를 사용합니다.
모터는 11폴이며 전원은 8V이상을 공급합니다.

모터에 인가되는 전압은 setVoltage()함수를 이용하며 100으로 설정시 전원 전압의 100%를 인가합니다.
실험에서는 무부하로 10이상부터 동작하지만 흔들림이 발생하고 30부터는 흔들림이 발생되지 않습니다.

기타 문의는 coffeedust@gmail.com으로 연락바랍니다.
