INCLUDE Irvine32.inc
INCLUDE Macros.inc
;=========================
;=========================
.data
	setHour BYTE "Set Hour : ", 0
	setMinute BYTE "Set Minute : ", 0
	setMode BYTE "0 for am, 1 for pm : ", 0
	reset BYTE "Press R to reset : ", 0
	mode1 BYTE "AM", 0
	mode2 BYTE "PM", 0
	invalidH BYTE "Invalid Hour ", 0dh, 0ah, 0
	invalidM BYTE "Invalid Minute", 0dh, 0ah, 0
	
	flg BYTE 1
	
	h2 BYTE ?
	h1 BYTE ?
	m2 BYTE ?
	m1 BYTE ?
	s2 BYTE ?
	s1 BYTE ?
	
	l BYTE ?
	r BYTE ?
	mid BYTE ?
;===========================
;===========================
.code
main PROC
xor eax, eax
mov eax, 0Ah
	call setTextColor
	call setTime
	mov s1, 0
top:	call clrscr
		mov eax, 0Ah
		call setTextColor
	call printH2
	call printH1
		mov eax, 0Ch
		call setTextColor
	call colon1
		mov eax, 0Ah
		call setTextColor
	call printM2
	call printM1
		mov eax, 0Ch
		call setTextColor
	call colon2
		mov eax, 0Ah
		call setTextColor
	call printS2
	call printS1
		mov eax, 0Ah
		call setTextColor
	call am_pm
	mGotoxy 30,14
	mWriteStr offset reset
	call incS1
	mov eax, 1000
	call delay
	jmp top
exit
main ENDP
;===========================
	setTime PROC
		mov bl, 10
		up1:
		
		mGotoxy 30, 14
		mWriteStr offset setHour
		call readInt
		.if al>12 || al<1
		call clrscr
		mGotoxy 30, 15
		mWriteStr offset invalidH
		jmp up1
		.endif
		div bl
		mov h2, al
		mov h1, ah
		call clrscr
		
		up2:
		mGotoxy 30, 14
		mWriteStr offset setMinute
		call readInt
		.if al>59 || al<0
		call clrscr
		mGotoxy 30, 15
		mWriteStr offset invalidM
		jmp up2
		.endif
		div bl
		mov m2, al
		mov m1, ah
		call clrscr
		
		mGotoxy 30, 14
		mWriteStr offset setMode
		call readInt
		.if al==0
		mov flg, 0
		.else
		mov flg, 1
		.endif
		ret
	setTime ENDP
;===========================
	am_pm PROC
		.if flg==0
		mGotoxy 64, 12
		mWriteStr offset mode1

		.else
		mGotoxy 64, 12
		mwritestr offset mode2
		.endif
		ret
	am_pm ENDP
;===========================
	colon1 PROC
		mov al, ':'
		mGotoxy 30, 8
		call writechar
		mGotoxy 30, 9
		call WriteChar
		ret
	colon1 ENDP
;===========================
	colon2 PROC
		mov al, ':'
		mGotoxy 47, 8
		call writechar
		mGotoxy 47, 9
		call WriteChar
		ret
	colon2 ENDP
;===========================
;===========================
;	Following 10 procedures are for digits 0-9
;===========================
;===========================
	zero PROC
		
		mov al, '-'
		mGotoxy mid, 5
		call writechar
		add mid, 2
		mGotoxy mid, 5
		call writechar
		add mid, 2
		mGotoxy mid, 5
		call writechar
		sub mid, 4
		
		
		
		mov al, '|'
		mGotoxy l, 11
		call writeChar
		mGotoxy r,11
		call writechar
		
		mGotoxy l, 6
		call writeChar
		mGotoxy r,6
		call writechar
		
		mGotoxy l, 7
		call writeChar
		mGotoxy r,7
		call writechar
		
		mGotoxy l, 8
		call writeChar
		mGotoxy r,8
		call writechar
		
		mGotoxy l, 9
		call writeChar
		mGotoxy r,9
		call writechar
		
		mGotoxy l, 10
		call writeChar
		
		
		mov al, '-'
		mGotoxy mid, 12
		call writechar
		add mid, 2
		mGotoxy mid, 12
		call writechar
		add mid, 2
		mGotoxy mid, 12
		call writechar
		
		mov al, '|'
		mGotoxy r, 10
		call writechar
		ret
	zero ENDP
;===========================
	one PROC
		mov al, '|'
		mGotoxy r, 6
		call writechar
		
		mGotoxy r, 7
		call writechar
		mGotoxy r, 8
		call writechar
		mGotoxy r, 9
		call writechar
		mGotoxy r, 10
		call writechar
		mGotoxy r, 11
		call writechar
		ret
	one ENDP
;===========================
	two PROC
		mov al, '-'
		mGotoxy mid, 5
		call writechar
		add mid, 2
		mGotoxy mid, 5
		call writechar
		add mid,2 
		mGotoxy mid, 5
		call writechar
		sub mid, 4
		
		
		
		mov al, '|'
		mGotoxy r, 6
		call writechar
		mGotoxy r, 7
		call writechar
		mGotoxy r, 8
		call writechar
		
		mov al, '_'
		mGotoxy mid, 8
		call writechar
		add mid, 2
		mGotoxy mid, 8
		call writechar
		add mid, 2
		mGotoxy mid, 8
		call writechar
		sub mid, 4
		
		
		
		mov al, '|'
		mGotoxy l, 9
		call writechar
		mov al, '|'
		mGotoxy l, 10
		call writechar
		mov al, '|'
		mGotoxy l, 11
		call writechar
		
		
		mov al, '-'
		mGotoxy mid, 12
		call writechar
		add mid, 2
		mGotoxy mid, 12
		call writechar
		add mid, 2
		mGotoxy mid, 12
		call writechar

		ret
	two ENDP
;==========================
	three PROC
		mov al, '-'
		mGotoxy mid, 5
		call writechar
		add mid, 2
		mGotoxy mid, 5
		call writechar
		add mid, 2
		mGotoxy mid, 5
		call writechar
		sub mid, 4
		
		
		
		mov al, '|'
		mGotoxy r, 6
		call writechar
		mGotoxy r, 7
		call writechar
		mGotoxy r, 8
		call writechar
		
		mov al, '_'
		mGotoxy mid, 8
		call writechar
		add mid,2
		mGotoxy mid, 8
		call writechar
		add mid, 2
		mGotoxy mid, 8
		call writechar
		sub mid, 4
		
		mov al, '|'
		mGotoxy r, 9
		call writechar
		mGotoxy r, 10
		call writechar
		mGotoxy r, 11
		call writechar

		
		mov al, '-'
		mGotoxy mid, 12
		call writechar
		add mid,2
		mGotoxy mid, 12
		call writechar
		add mid, 2
		mGotoxy mid, 12
		call writechar
		
		
		ret
	three ENDP
;==========================
	four PROC
		mov al, '|'
		mGotoxy l, 6
		call writechar
		mGotoxy l, 7
		call writechar
		mGotoxy l, 8
		call writechar
		
		
		
		mov al, '_'
		mGotoxy mid, 8
		call writechar
		add mid, 2
		mGotoxy mid, 8
		call writechar
		add mid, 2
		mGotoxy mid, 8
		call writechar
	
		mov al, '|'
		mGotoxy r, 6
		call writechar
		mGotoxy r, 7
		call writechar
		mGotoxy r, 8
		call writechar
		mGotoxy r, 9
		call writechar
		mGotoxy r, 10
		call writechar
		mGotoxy r, 11
		call writechar
		
		
		ret
	four ENDP
;===========================
	five PROC
		mov al, '-'
		mGotoxy mid, 5
		call writechar
		add mid, 2
		mGotoxy mid, 5
		call writechar
		add mid, 2
		mGotoxy mid, 5
		call writechar
		sub mid, 4
		
		
		mov al, '|'
		mGotoxy l, 6
		call writechar
		mGotoxy l, 7
		call writechar
		mGotoxy l, 8
		call writechar
		
		mov al, '_'
		mGotoxy mid, 8
		call writechar
		add mid, 2
		mGotoxy mid, 8
		call writechar
		add mid, 2
		mGotoxy mid, 8
		call writechar
		sub mid, 4
		
		
		mov al, '|'
		mGotoxy r, 9
		call writechar
		mGotoxy r, 10
		call writechar
		mGotoxy r, 11
		call writechar
		
		mov al, '-'
		mGotoxy mid, 12
		call writechar
		add mid, 2
		mGotoxy mid, 12
		call writechar
		add mid, 2
		mGotoxy mid, 12
		call writechar
		ret
	five ENDP
;==========================
	six PROC
		mov al, '-'
		mGotoxy mid, 5
		call writechar
		add mid, 2
		mGotoxy mid, 5
		call writechar
		add mid, 2
		mGotoxy mid, 5
		call writechar
		sub mid, 4
		
		
		mov al, '|'
		mGotoxy l, 6
		call writechar
		mGotoxy l, 7
		call writechar
		mGotoxy l, 8
		call writechar
		mGotoxy l, 9
		call writechar
		mGotoxy l, 10
		call writechar
		mGotoxy l, 11
		call writechar
		
		mov al, '_'
		mGotoxy mid, 8
		add mid, 2
		call writechar
		mGotoxy mid, 8
		add mid, 2
		call writechar
		mGotoxy mid, 8
		call writechar
		sub mid, 4
		
		
		mov al, '-'
		mGotoxy mid, 12
		call writechar
		add mid, 2
		mGotoxy mid, 12
		call writechar
		add mid, 2
		mGotoxy mid, 12
		call writechar
		
		mov al, '|'
		mGotoxy r, 9
		call writechar
		mGotoxy r, 10
		call writechar
		mGotoxy r, 11
		call writechar
		ret
	six ENDP
;==========================
	seven PROC
		mov al, '-'
		mGotoxy mid, 5
		call writechar
		add mid, 2
		mGotoxy mid, 5
		call writechar
		add mid, 2
		mGotoxy mid, 5
		call writechar
		
		
		mov al, '|'
		mGotoxy r, 6
		call writechar
		
		mGotoxy r, 7
		call writechar
		mGotoxy r, 8
		call writechar
		mGotoxy r, 9
		call writechar
		mGotoxy r, 10
		call writechar
		mGotoxy r, 11
		call writechar
		
		ret
	seven ENDP
;==========================
	eight PROC
		mov al, '-'
		mGotoxy mid, 5
		call writechar
		add mid, 2
		mGotoxy mid, 5
		call writechar
		add mid, 2
		mGotoxy mid, 5
		call writechar
		sub mid, 4

		mov al, '|'
		mGotoxy l, 6
		call writeChar
		mGotoxy l, 7
		call writeChar
		mGotoxy l, 8
		call writeChar
		mGotoxy l, 9
		call writeChar
		mGotoxy l, 10
		call writeChar
		mGotoxy l, 11
		call writeChar

		mov al, '_'
		mGotoxy mid, 8
		call writechar
		add mid, 2
		mGotoxy mid, 8
		call writechar
		add mid, 2
		mGotoxy mid, 8
		call writechar
		sub mid, 4
		
		
		mov al, '|'
		mGotoxy r,6
		call writechar
		mGotoxy r,7
		call writechar
		mGotoxy r,8
		call writechar
		mGotoxy r,9
		call writechar
		mGotoxy r,10
		call writechar
		mGotoxy r,11
		call writechar

		mov al, '-'
		mGotoxy mid ,12
		call writechar
		add mid, 2
		mGotoxy mid ,12
		call writechar
		add mid, 2
		mGotoxy mid ,12
		call writechar		
		ret
	eight ENDP
;==========================
	nine PROC
		mov al, '-'
		mGotoxy mid, 5
		call writechar
		add mid, 2
		mGotoxy mid, 5
		call writechar
		add mid, 2
		mGotoxy mid, 5
		call writechar
		sub mid, 4

		mov al, '|'
		mGotoxy l, 6
		call writeChar
		mGotoxy l, 7
		call writeChar
		mGotoxy l, 8
		call writeChar

		mov al, '_'
		mGotoxy mid, 8
		call writechar
		add mid, 2
		mGotoxy mid, 8
		call writechar
		add mid, 2
		mGotoxy mid, 8
		call writechar
		sub mid, 4
		
		mov al, '|'
		mGotoxy r,9
		call writechar
		mGotoxy r,10
		call writechar
		mGotoxy r,11
		call writechar
		mGotoxy r,8
		call writechar
		mGotoxy r,7
		call writechar
		mGotoxy r,6
		call writechar

		mov al, '-'
		mGotoxy mid ,12
		call writechar
		add mid, 2
		mGotoxy mid ,12
		call writechar
		add mid, 2
		mGotoxy mid ,12
		call writechar

		
		ret
	nine ENDP
;===========================
;===========================
;	following are updating procedures
;===========================
;===========================
	incS1 PROC
		inc s1
		.if s1>9
		mov s1, 0
		call incS2
		.endif
		ret
	incS1 ENDP
;===========================
	incS2 PROC
		inc s2
		.if s2>5
		mov s2, 0
		call incM1
		.endif
		ret
	incs2 ENDP
;===========================
	incM1 PROC
		inc m1
		.if m1>9
		mov m1, 0
		call incM2
		.endif
		ret
	incM1 ENDP
;===========================
	incM2 PROC
		inc m2
		.if m2>5
		mov m2, 0
		call incH1
		.endif
	ret
	incM2 ENDP
;===========================
	incH1 PROC
		inc h1
		.if h2==1 && h1>2 && flg==0
		mov h1, 1
		mov h2, 0
		mov flg, 1
		.elseif h2==1 && h1>2 && flg==1
		mov h1, 1
		mov h2, 0
		mov flg, 0
		.elseif h2==0 && h1>9
		mov h1, 0
		call incH2
		.endif
		ret
	incH1 ENDP
;============================
	incH2 PROC
		inc h2
		.if h2>1
		mov h2, 0
		.endif
		ret
	incH2 ENDP
;============================
;============================
;	below are the printing Procecures
;============================
;============================
	printH2 PROC
	;call clrscr
		mov l, 15
		mov mid, 16
		mov r, 21
		
		.if h2==0
		call zero
		.elseif h2==1
		call one
		.elseif h2==2
		call two
		.elseif h2==3
		call three
		.elseif h2==4
		call four
		.elseif h2==5
		call five
		.elseif h2==6
		call six
		.elseif h2==7
		call seven
		.elseif h2==8
		call eight
		.elseif h2==9
		call nine
		.endif
		ret
	printH2 ENDP
;=============================
printH1 PROC
		mov l, 22
		mov mid, 23
		mov r, 28
		
		.if h1==0
		call zero
		.elseif h1==1
		call one
		.elseif h1==2
		call two
		.elseif h1==3
		call three
		.elseif h1==4
		call four
		.elseif h1==5
		call five
		.elseif h1==6
		call six
		.elseif h1==7
		call seven
		.elseif h1==8
		call eight
		.elseif h1==9
		call nine
		.endif
		ret
	printH1 ENDP
;============================
	printM2 PROC
		mov l, 32
		mov mid, 33
		mov r, 38
		
		.if m2==0
		call zero
		.elseif m2==1
		call one
		.elseif m2==2
		call two
		.elseif m2==3
		call three
		.elseif m2==4
		call four
		.elseif m2==5
		call five
		.elseif m2==6
		call six
		.elseif m2==7
		call seven
		.elseif m2==8
		call eight
		.elseif m2==9
		call nine
		.endif
		ret
	printM2 ENDP
;==============================
	printM1 PROC
		mov l, 39
		mov mid, 40
		mov r, 45
		
		.if m1==0
		call zero
		.elseif m1==1
		call one
		.elseif m1==2
		call two
		.elseif m1==3
		call three
		.elseif m1==4
		call four
		.elseif m1==5
		call five
		.elseif m1==6
		call six
		.elseif m1==7
		call seven
		.elseif m1==8
		call eight
		.elseif m1==9
		call nine
		.endif
		ret
	printM1 ENDP
;==============================
	printS2 PROC
		mov l, 49
		mov mid, 50
		mov r, 55

		.if s2==0
		call zero
		.elseif s2==1
		call one
		.elseif s2==2
		call two
		.elseif s2==3
		call three
		.elseif s2==4
		call four
		.elseif s2==5
		call five
		.elseif s2==6
		call six
		.elseif s2==7
		call seven
		.elseif s2==8
		call eight
		.elseif s2==9
		call nine
		.endif
		ret
	printS2 ENDP
;==============================
	printS1 PROC
		mov l, 56
		mov mid, 57
		mov r, 62

		.if s1==0
		call zero
		.elseif s1==1
		call one
		.elseif s1==2
		call two
		.elseif s1==3
		call three
		.elseif s1==4
		call four
		.elseif s1==5
		call five
		.elseif s1==6
		call six
		.elseif s1==7
		call seven
		.elseif s1==8
		call eight
		.elseif s1==9
		call nine
		.endif
		
		ret
	printS1 ENDP
END main