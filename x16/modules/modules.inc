%ifndef __X16_MODULES_INC_INCLUDED__
%define __X16_MODULES_INC_INCLUDED__

[bits 16]
[org 0x500]

%include "x16/modules/disk/disk.inc"
%include "x16/modules/keyboard/keyboard.inc"
%include "x16/modules/system/system.inc"
%include "x16/modules/time/time.inc"
%include "x16/modules/video/video.inc"


%endif                              ; %ifndef __X16_MODULES_INC_INCLUDED__
