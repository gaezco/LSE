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
   *****************  Modificacion  ******************
   ******************* 22/02/2013 ********************
			Gaston Conessa <gaezco@gmail.com>
		Hernan Barrios <barrioshernan@hotmail.com>
   ***************************************************
*/

#include <string.h>
#include "window.h"
#include "Check.h"
#include "GLCDgui.h"
#include "GLCDPrimitives.h"
#include "GLCDLowLevel.h"
#include "GLCDColor.h"
#include "SystemFont5x7.h"
#include "GLCDFonts.h"
#include "object.h"

#define FALSE 	0
#define TRUE 	1
#define ON		1
#define OFF		0

#ifndef NULL
#define NULL	0
#endif

TCheck* GUI_Check_Create (const char* const _windowName, const char* const _name, uint16_t _height, uint16_t _width, uint16_t _xPos,
						uint16_t _yPos, uint8_t _color, const char* const _fontName, uint8_t _fontColor,
						uint8_t _status,
						void (*_OnClickHandler) (void* voidPointerParams),
						void (*_OnDoubleClickHandler) (void* voidPointerParams),
						void (*_OnDragHandler) (void* voidPointerParams),
						void (*_OnDropHandler) (void* voidPointerParams) )
{
	TCheck* auxCheck;

	TNode* pNode;
	TWindow* pWindow;
	TObject* pObject;

	auxCheck = (TCheck*) GUI_Malloc ( sizeof(TCheck) );

	auxCheck->windowName = (char*) GUI_Malloc ( sizeof(char) * 12 );
	strcpy (auxCheck->windowName, _windowName);

	auxCheck->name = (char*) GUI_Malloc ( sizeof(char) * 12 );
	strcpy (auxCheck->name, _name);

	auxCheck->height = _height;
	auxCheck->width = _width;
	auxCheck->xPos = _xPos;
	auxCheck->yPos = _yPos;
	auxCheck->color = _color;
	auxCheck->fontName = _fontName;
	auxCheck->fontColor = _fontColor;
	auxCheck->status = _status;

	//auxCheck->text = (char*) GUI_Malloc ( sizeof(char) * 12 );
	//strncpy (auxCheck->text, _text, 12);

	auxCheck->OnClickHandler = _OnClickHandler;
	auxCheck->OnDoubleClickHandler = _OnDoubleClickHandler;
	auxCheck->OnDragHandler = _OnDragHandler;
	auxCheck->OnDropHandler = _OnDropHandler;

	// Busco el nodo que tiene la información de la ventana
	pNode = List_SearchNode (&(windowsList), auxCheck->windowName);

	// Obtengo la ventana
	pWindow = (TWindow*) pNode->data;

	// Creo el objeto que voy a agregar en la lista de objetos de la ventana
	pObject = (TObject*) GUI_Malloc ( sizeof(TObject) );
	pObject->objectType = CHECK;
	pObject->objectData = (void*) auxCheck;

	// Agrego el objeto a la lista de objetos de la ventana
	List_AddNode (&(pWindow->objectsList), _name, pObject);

	return auxCheck;
}

TCheck* GUI_Check_CreateNotInWindowList (const char* const _windowName, const char* const _name,
										   uint16_t _height, uint16_t _width, uint16_t _xPos, uint16_t _yPos,
										   uint8_t _color, const char* const _fontName, uint8_t _fontColor,
										   uint8_t _status,
										   void (*_OnClickHandler) (void* voidPointerParams),
										   void (*_OnDoubleClickHandler) (void* voidPointerParams),
										   void (*_OnDragHandler) (void* voidPointerParams),
										   void (*_OnDropHandler) (void* voidPointerParams) )
{
	TCheck* auxCheck;

	auxCheck = (TCheck*) GUI_Malloc ( sizeof(TCheck) );

	auxCheck->windowName = (char*) GUI_Malloc ( sizeof(char) * 12 );
	strcpy (auxCheck->windowName, _windowName);

	auxCheck->height = _height;
	auxCheck->width = _width;
	auxCheck->xPos = _xPos;
	auxCheck->yPos = _yPos;
	auxCheck->color = _color;
	auxCheck->fontName = _fontName;
	auxCheck->fontColor = _fontColor;
	auxCheck->status = _status;

//	auxCheck->text = (char*) GUI_Malloc ( sizeof(char) * 12 );
//	strncpy (auxCheck->text, _text, 12);

	auxCheck->OnClickHandler = _OnClickHandler;
	auxCheck->OnDoubleClickHandler = _OnDoubleClickHandler;
	auxCheck->OnDragHandler = _OnDragHandler;
	auxCheck->OnDropHandler = _OnDropHandler;

	return auxCheck;
}


void GUI_Check_Draw ( TCheck* pCheck )
{
	uint32_t xi, xf, yi, yf;
	uint8_t state, block;

	xi = pCheck->xPos;
	xf = pCheck->xPos + pCheck->width;
	yi = pCheck->yPos;
	yf = pCheck->yPos + pCheck->height;
	state =  pCheck->status;
	block = 2;


	GLCDPrimitives_DrawLine (xi, yi, xf, yi, BLACK);
	GLCDPrimitives_DrawLine (xf, yi, xf, yf, BLACK);
	GLCDPrimitives_DrawLine (xf, yf, xi, yf, BLACK);
	GLCDPrimitives_DrawLine (xi, yf, xi, yi, BLACK);

	if (state == ON)
	{
		GLCDPrimitives_FillRect (xi+block, yi+block, (pCheck->width)-block -2, (pCheck->height) - block - 2, BLACK);
	}
	else
	{
		GLCDPrimitives_FillRect (xi+block, yi+block, (pCheck->width)-block -2, (pCheck->height) - block - 2, WHITE);
	}

}
