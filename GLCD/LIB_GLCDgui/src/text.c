/*
   ********************* Authors *********************
   ***** Laboratorio de Sistemas Embebidos (LSE) *****
   *****    http://laboratorios.fi.uba.ar/lse    *****
   ******************* 20/12/2011 ********************
     Ezequiel Espósito <ezequiel.esposito@gmail.com>
         Alan Kharsansky <akharsa@gmail.com>
       Federico Roasio <federoasio@gmail.com>
     Daniel Schermuk <daniel.schermuk@gmail.com>
   ***************************************************
*/

#include <string.h>
#include "text.h"
#include "object.h"
#include "window.h"
#include "GLCDFonts.h"
#include "SystemFont5x7.h"
#include "GLCDgui.h"

TText* GUI_Text_Create ( const char* const _windowName, const char* const _name,
						   uint16_t _xPos, uint16_t _yPos, uint8_t _color,
						   const char* const _fontName, uint8_t _fontColor,
						   const char* const _text )
{
	TText* auxText;

	TNode* pNode;
	TWindow* pWindow;
	TObject* pObject;

	auxText = (TText*) GUI_Malloc ( sizeof(TText) );

	auxText->windowName = (char*) GUI_Malloc ( sizeof(char) * 12 );
	strcpy (auxText->windowName, _windowName);

	auxText->name = (char*) GUI_Malloc ( sizeof(char) * 12 );
	strcpy (auxText->name, _name);

	auxText->xPos = _xPos;
	auxText->yPos = _yPos;

	auxText->color = _color;

	auxText->fontName = _fontName;
	auxText->fontColor = _fontColor;

	auxText->text = (char*) GUI_Malloc ( sizeof(char) * strlen(_text) );
	strncpy (auxText->text, _text, strlen(_text));

	// Busco el nodo que tiene la información de la ventana
	pNode = List_SearchNode (&(windowsList), auxText->windowName);

	// Obtengo la ventana
	pWindow = (TWindow*) pNode->data;

	// Creo el objeto que voy a agregar en la lista de objetos de la ventana
	pObject = (TObject*) GUI_Malloc ( sizeof(TObject) );
	pObject->objectType = TEXT;
	pObject->objectData = (void*) auxText;

	// Agrego el objeto a la lista de objetos de la ventana
	List_AddNode (&(pWindow->objectsList), _name, pObject);

	return auxText;
}

void GUI_Text_Draw ( TText* pText )
{
	// Draw button name
	GLCD_SelectFont(System5x7, pText->fontColor);
	GLCD_CursorFreeTo(pText->xPos, pText->yPos);
	GLCD_FreePuts( pText->text );
}
