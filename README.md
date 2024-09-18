# IntelHex_to_Bin

Program IntelHex formatındaki dosyayı .Bin dosyasına çevirerek kaydeder.

## Asciinema 

<script id="asciicast-embed" src="https://asciinema.org/a/DlxgERwFdLkRPSzM5ugNzfX8k" async></script>



## Kullanım

İlk önce .c dosyası derlenir.

```bash
$ gcc -o IntelHextoBin IntelHEX_to_bin.c
```
Daha sonra oluşan .o dosyası 2 parametreyle çalıştırılır.

```bash
$ ./IntelHextoBin example.hex output.bin 
acildi
Hex Dosyasi Bin dosyasina Cevrildi !
```

en son aşamada hexdump yardımıyla oluşan dosya okunabilir.

```bash
$ hexdump -C output.bin 
```
