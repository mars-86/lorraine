;*******************************************************
;
;	All interrupts reference were extracted from 
;	Ralf Brown's Interrupt List
;	http://www.ctyme.com/rbrown.htm
;
;*******************************************************

%ifndef __X16_ERROR_INC_INCLUDED__
%define __X16_ERROR_INC_INCLUDED__

[bits 16]

; Values for disk operation status:
; 00h    successful completion
; 01h    invalid function in AH or invalid parameter
; 02h    address mark not found
; 03h    disk write-protected
; 04h    sector not found/read error
; 05h    reset failed (hard disk)
; 05h    data did not verify correctly (TI Professional PC)
; 06h    disk changed (floppy)
; 07h    drive parameter activity failed (hard disk)
; 08h    DMA overrun
; 09h    data boundary error (attempted DMA across 64K boundary or >80h sectors)
; 0Ah    bad sector detected (hard disk)
; 0Bh    bad track detected (hard disk)
; 0Ch    unsupported track or invalid media
; 0Dh    invalid number of sectors on format (PS/2 hard disk)
; 0Eh    control data address mark detected (hard disk)
; 0Fh    DMA arbitration level out of range (hard disk)
; 10h    uncorrectable CRC or ECC error on read
; 11h    data ECC corrected (hard disk)
; 20h    controller failure
; 31h    no media in drive (IBM/MS INT 13 extensions)
; 32h    incorrect drive type stored in CMOS (Compaq)
; 40h    seek failed
; 80h    timeout (not ready)
; AAh    drive not ready (hard disk)
; B0h    volume not locked in drive (INT 13 extensions)
; B1h    volume locked in drive (INT 13 extensions)
; B2h    volume not removable (INT 13 extensions)
; B3h    volume in use (INT 13 extensions)
; B4h    lock count exceeded (INT 13 extensions)
; B5h    valid eject request failed (INT 13 extensions)
; B6h    volume present but read protected (INT 13 extensions)
; BBh    undefined error (hard disk)
; CCh    write fault (hard disk)
; E0h    status register error (hard disk)
; FFh    sense operation failed (hard disk)

jmp .lib

;*******************************************************
;	Preprocessor directives
;*******************************************************


;*******************************************************
;	Data section
;*******************************************************


.lib:

floppy_errors_array_addr:
floppy_status_00 db "Successful completion", 0x0A, 0x0D, 0
floppy_status_01 db "Invalid function in AH or invalid parameter", 0x0A, 0x0D, 0
floppy_status_02 db "Address mark not found", 0x0A, 0x0D, 0
floppy_status_03 db "Disk write-protected", 0x0A, 0x0D, 0
floppy_status_04 db "Sector not found/read error", 0x0A, 0x0D, 0
floppy_status_05 db "Reset failed (hard disk)", 0x0A, 0x0D, 0
floppy_status_06 db "Disk changed (floppy)", 0x0A, 0x0D, 0
floppy_status_07 db "Drive parameter activity failed (hard disk)", 0x0A, 0x0D, 0
floppy_status_08 db "DMA overrun", 0x0A, 0x0D, 0
floppy_status_09 db "Data boundary error (attempted DMA across 64K boundary or >80h sectors)", 0x0A, 0x0D, 0
floppy_status_0A db "Bad sector detected (hard disk)", 0x0A, 0x0D, 0
floppy_status_0B db "Bad track detected (hard disk)", 0x0A, 0x0D, 0
floppy_status_0C db "Unsupported track or invalid media", 0x0A, 0x0D, 0
floppy_status_0D db "Invalid number of sectors on format (PS/2 hard disk)", 0x0A, 0x0D, 0
floppy_status_0E db "Control data address mark detected (hard disk)", 0x0A, 0x0D, 0
floppy_status_0F db "DMA arbitration level out of range (hard disk)", 0x0A, 0x0D, 0
floppy_status_10 db "Uncorrectable CRC or ECC error on read", 0x0A, 0x0D, 0
floppy_status_11 db "Data ECC corrected (hard disk)", 0x0A, 0x0D, 0
db 0
db 0
db 0
db 0
db 0
db 0
db 0
db 0
db 0
db 0
db 0
db 0
db 0
db 0
floppy_status_20 db "Controller failure", 0x0A, 0x0D, 0

%endif									; __X16_ERROR_INC_INCLUDED__
