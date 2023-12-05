# ESP8266 Web Server Projesi

Bu proje, ESP8266 mikrodenetleyici kartını kullanarak basit bir web sunucusu oluşturan ve bir dizi özellik ekleyen bir Arduino projedir.

## Özellikler
- Web sunucusu üzerinden uzaktan LED kontrolü
- DHT11 sensörü ile sıcaklık ve nem ölçümü
- Sabit IP adresi kullanma
- Otomatik sayfa yenileme

## Gereksinimler
- [Arduino IDE](https://www.arduino.cc/en/software) yüklü olmalıdır.
- ESP8266 kartlarını Arduino IDE'ye entegre etmek için [ESP8266 Arduino Core](https://github.com/esp8266/Arduino) kullanılmalıdır.
- DHT sensörünüzün kütüphanesi Arduino IDE'ye yüklenmelidir.

## Bağlantılar
- ESP8266 kartınızın DHT sensörüne ve LED'lere bağlantılarını kontrol edin.

## Kurulum
1. Arduino IDE'yi açın.
2. Arduino kartınızı ve portunuzu seçin.
3. Gerekli kütüphaneleri yükleyin.
4. Kodu Arduino kartınıza yükleyin.

## Kullanım
1. Arduino kartınızı bilgisayarınıza bağlayın.
2. Arduino IDE'de kodu yükleyin.
3. Arduino kartınızı güç kaynağına bağlayın.
4. Arduino'nun seri monitörünü açın ve IP adresini kontrol edin.
5. Tarayıcınızdan Arduino'nun IP adresine giderek web arayüzüne erişin.

## Katkıda Bulunma
1. Bu depoyu forklayın.
2. Yeni bir özellik ekleyin veya hata düzeltmeleri yapın.
3. Değişikliklerinizi test edin.
4. Pull request oluşturun.
