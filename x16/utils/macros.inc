%ifndef __X16_UTILS_MACROS_INC_INCLUDED__
%define __X16_UTILS_MACROS_INC_INCLUDED__

; %macro push_args 1-*
;	%rep %0
;		push %1
;		%rotate 1
;	%endrep
; %endmacro

%macro call_func_16 1-*
	%rep (%0 - 1)
		push %2
		%rotate 1
	%endrep
	%rotate 1								; rotate one more so the function arg stay in place
	call %1
	add sp, ((%0 - 1) * 2)
%endmacro

%endif                                      ; __X16_UTILS_MACROS_INC_INCLUDED__
