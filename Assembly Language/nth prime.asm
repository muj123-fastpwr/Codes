INCLUDE Irvine32.inc
.data
	flag BYTE ?
	i DWORD 3
	counter WORD ?
	limit WORD ?
	msg BYTE "nth prime number : ", 0
.code
main PROC
xor eax, eax
xor ebx, ebx
	mov edx, offset msg
	call writestring
	call readint
	dec ax
	mov limit, ax
mov eax, 2
call writeDec
call crlf
inc eax
	.while i<=1000
	mov ebx, 2
	mov flag, 1
		.while ebx<i
		xor edx, edx		;
		mov eax, i
		div ebx
		.if edx==0
		mov flag, 0
		.endif
		inc ebx
		xor eax, eax
		.endw
	.if flag==1
	inc counter			;
	mov eax, i
	call writedec
	call crlf
	.endif
	mov ax, counter			;
	.if ax==limit			;	
	exit				;optional
	.endif				;optional
	inc i
	.endw
	
exit
main ENDP
END main