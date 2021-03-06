#pragma once
//#include "WinAPIwindow.h"
#include<Windows.h>
#include<gl\GL.h>

//-------------------------------------------------------------------------------------------------------------------
//----------------------------------------CZCIONKI WYŚWIETLANE NA EKRANIE GRY----------------------------------------
//--------------------klasa odpowiadająca za definicję czcionki rastrowej wyświetlanej na ekranie--------------------
//-------------------------------------------------------------------------------------------------------------------

class FONT {
	HDC hDC;																		//uchwyt aktualnego okna dla czcionki

	unsigned int fontSize;															//rozmiar czcionki

	unsigned int listBase;															//identyfikator listy bazowej dla czcionki

	unsigned int CreateBitmapFont(char* fontName, int fontSize);					//stworzenie i zarejestrowanie w systemie czcionki o danej nazwie i rozmiarze

public:
	FONT() { listBase = 0; fontSize = 0; }														//kosntruktor domyślny [domyślna wartość listBase=0 - lista nie została stworzona]
	FONT(char* fontName, unsigned int FontSize):fontSize(FontSize) {									//konstruktor tworzący czcionkę o danej nazwie i rozmiarze
		listBase = CreateBitmapFont(fontName, FontSize);
	}
	~FONT() {																		//destruktor [usuwa wszystkie listy przechowujące czcionki]
		if (listBase != 0)
			glDeleteLists(listBase, 96);											//zwolnienie wszystkich list wyświetlania
	}

	void Initilize(char* fontName, unsigned int fontSize, HDC _hDC);				//inicjalizacja wybranej czcionki

	void PrintString(char* str);													//wypisanie stringa na ekranie

	unsigned int GetFontSize() { return fontSize; }
};