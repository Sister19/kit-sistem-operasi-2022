; bootloader.asm
; Michael Black, 2007
; Modified by Asisten Sister '19, 2022

; This is a simple bootloader that loads and
;   executes a kernel located in drive sector 1


bits 16
KSEG    equ 0x1000    ; Lokasi segment eksekusi kernel pada memory = 0x1000
KSIZE   equ 15        ; Ukuran kernel                              = 15 sektor
KSTART  equ 1         ; Lokasi sektor kernel pada drive            = sektor 1


; Boot loader starts at 0 in segment 0x7c00
org 0h
bootloader:
    ; -- Kode bootloader --
    ; Ekuivalen dengan readSector() ke memory KSEG:0x0000
    ; Read kernel from disk with INT 13h
    mov ch, 0            ; CH -> Track
    mov cl, KSTART + 1   ; CL -> Sector number
    mov dh, 0            ; DH -> Head
    mov dl, 0            ; Read from drive A

    mov ax, KSEG
    mov es, ax           ; Buffer location     = ES:BX
    mov bx, 0            ; Set buffer location = KSEG:0x0000

    mov ah, 0x02         ; Disk read from drive
    mov al, KSIZE        ; Read KSIZE sectors
    int 13h              ; Call BIOS INT 13h

    ; Ekuivalen dengan launchProgram()
    ; Setup segment registers
    mov ax, KSEG
    mov ds, ax
    mov ss, ax
    mov es, ax
    ; Set stack pointer at KSEG:0xFFF0
    mov ax, 0xfff0
    mov sp, ax
    mov bp, ax
    ; Lompat ke kernel
    jmp KSEG:0x0000



    ; -- Bagian padding & bootloader signature --
    ; Kalkulasi dan buat padding hingga byte setelah "times" adalah byte ke 510
    times 510-($-$$) db 0x00

    ; Tuliskan 2 byte 0xAA55 yang merupakan signature bootloader yang valid
    ; Signature tersebut wajib terletak pada 2 byte terakhir pada 512 bytes
    ; https://en.wikipedia.org/wiki/Bootloader
    ; https://en.wikipedia.org/wiki/Master_boot_record#Programming_considerations
    dw 0xAA55
