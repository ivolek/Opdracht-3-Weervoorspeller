/*
 * VisueelScherm.cpp
 *
 *  Created on: 6 juni 2012
 *      Author: Ivo Lek
 */

#include "VisueelScherm.hpp"

#include <conprint.h>

VisueelScherm::VisueelScherm( WeerData* weerData )
{
	//bepaal grootte van het scherm
	MAExtent screenSize = maGetScrSize();
	screenWidth = EXTENT_X( screenSize );
	screenHeight = EXTENT_Y( screenSize );

	//sla de weerdata op in het attribuut
	this->weerData = weerData;

	//ken font en skin toe
	this->font = new MAUI::Font(RES_FONT);
	skin = new WidgetSkin( RES_SELECTED, RES_UNSELECTED, 16, 32, 16, 32, false, false );

	//maak een achtergrond label om alle andere widgets in op te slaan, en te tonen
	Label* achtergrond = new Label(0,0,0,0,NULL);
	achtergrond->setBackgroundColor(0x000000);

	//maak een listbox met update en textueelknop
//	this->listBox = new Label ( screenWidth/2-50, 250, 80, 30, achtergrond, "ListBox", 0, font );
//	this->listBox->setSkin( this->skin );
//	this->listBox->setPaddingLeft(5);
//	this->listBox->setPaddingTop(5);

	//knop om data te updaten
	this->updateKnop = new Label ( screenWidth/2-50, 350, 80, 30, achtergrond, "Update", 0, font );
	this->updateKnop->setSkin( this->skin );
	this->updateKnop->setPaddingLeft(5);
	this->updateKnop->setPaddingTop(5);

	//knop om naar visueel te schakelen
	this->textueelKnop = new Label ( screenWidth/2-50, 385, 80, 30, achtergrond, "Textueel", 0, font );
	this->textueelKnop->setSkin( this->skin );
	this->textueelKnop->setPaddingLeft(5);
	this->textueelKnop->setPaddingTop(5);



	//staafdiagram

	//maak eerst een placeholder
	this->diagramTekening = maCreatePlaceholder();

	//laat de placeholder tekenbaar zijn
	maCreateDrawableImage( this->diagramTekening, EXTENT_X( maGetScrSize()-10 ), EXTENT_Y( screenHeight/2+60 ));


	//maak een nieuwe image met de placeholder
	this->diagramImage = new Image( 5, 5, EXTENT_X( maGetScrSize()-10 ), EXTENT_Y( screenHeight/2+60 ) , achtergrond, true, true, this->diagramTekening );


	this->setMain( achtergrond );
}


VisueelScherm::~VisueelScherm()
{
}


void VisueelScherm::update()
{
	//update waarden vam weerdata
	this->weerData->update();

	//stel draw target in op onze tekening
	maSetDrawTarget( this->diagramTekening );

	//teken een staaf diagram
	//dag 1
	int i = weerData->zonneschijn[0];
	char zonneschijn1 [25];
	itoa (i, zonneschijn1, 10);

	int i2 = weerData->neerslag[0];
	char neerslag1 [25];
	itoa (i2, neerslag1, 10);

	int i3 = weerData->minimumtemperatuur[0];
	char temperatuur1 [25];
	itoa (i3, temperatuur1, 10);

	//dag 2
	int i4 = weerData->zonneschijn[1];
	char zonneschijn2 [25];
	itoa (i4, zonneschijn2, 10);

	int i5 = weerData->neerslag[1];
	char neerslag2 [25];
	itoa (i5, neerslag2, 10);

	int i6 = weerData->minimumtemperatuur[1];
	char temperatuur2 [25];
	itoa (i6, temperatuur2, 10);

	//dag 3
	int i7 = weerData->zonneschijn[2];
	char zonneschijn3 [25];
	itoa (i7, zonneschijn3, 10);

	int i8 = weerData->neerslag[2];
	char neerslag3 [25];
	itoa (i8, neerslag3, 10);

	int i9 = weerData->minimumtemperatuur[2];
	char temperatuur3 [25];
	itoa (i9, temperatuur3, 10);

	//legenda
	maSetColor(0xffffff);
	maDrawText(5,10,"Legenda:");
	maSetColor(0xffbc47);
	maDrawText(10,35,"Zonneschijn %");
	maSetColor(0x6078f4);
	maDrawText(10,50,"Neerslag %");
	maSetColor(0xff8ee8);
	maDrawText(10,65,"Minimum temp.");
	maSetColor(0xffffff);
	maDrawText(10,280,"vandaag");
	maDrawText(70,280,"Morgen");
	maDrawText(130,280,"Overmorgen");
	//teken blokje en text met zonneschijn, neerslag en temperatuur

	//teken 10-stap lijnen

	//teken de staven van zonneschijn, neerslag en minimum temperatuur
	//Vandaag
	maSetColor(0xffffff);
	maDrawText(10, screenHeight/2+40-weerData->zonneschijn[0]-15, zonneschijn1);
	maDrawText(30, screenHeight/2+40-weerData->neerslag[0]-15, neerslag1);
	maDrawText(50, screenHeight/2+40-weerData->minimumtemperatuur[0]-15, temperatuur1);
	maSetColor(0xffbc47);
	maFillRect(10, screenHeight/2+40-weerData->zonneschijn[0], 15, weerData->zonneschijn[0]);
	maSetColor(0x6078f4);
    maFillRect(30, screenHeight/2+40-weerData->neerslag[0], 15, weerData->neerslag[0]);
	maSetColor(0xff8ee8);
	maFillRect(50, screenHeight/2+40-weerData->minimumtemperatuur[0],15,weerData->minimumtemperatuur[0]);

	//Morgen
	maSetColor(0xffffff);
	maDrawText(70, screenHeight/2+40-weerData->zonneschijn[1]-15, zonneschijn2);
	maDrawText(90, screenHeight/2+40-weerData->neerslag[1]-15, neerslag2);
	maDrawText(110, screenHeight/2+40-weerData->minimumtemperatuur[1]-15, temperatuur2);
	maSetColor(0xffbc47);
	maFillRect(70, screenHeight/2+40-weerData->zonneschijn[1], 15, weerData->zonneschijn[1]);
	maSetColor(0x6078f4);
    maFillRect(90, screenHeight/2+40-weerData->neerslag[1], 15, weerData->neerslag[1]);
	maSetColor(0xff8ee8);
	maFillRect(110, screenHeight/2+40-weerData->minimumtemperatuur[1],15,weerData->minimumtemperatuur[1]);

	//Overmorgen
	maSetColor(0xffffff);
	maDrawText(130, screenHeight/2+40-weerData->zonneschijn[2]-15, zonneschijn3);
	maDrawText(150, screenHeight/2+40-weerData->neerslag[2]-15, neerslag3);
	maDrawText(170, screenHeight/2+40-weerData->minimumtemperatuur[2]-15, temperatuur3);
	maSetColor(0xffbc47);
	maFillRect(130, screenHeight/2+40-weerData->zonneschijn[2], 15, weerData->zonneschijn[2]);
	maSetColor(0x6078f4);
    maFillRect(150, screenHeight/2+40-weerData->neerslag[2], 15, weerData->neerslag[2]);
	maSetColor(0xff8ee8);
	maFillRect(170, screenHeight/2+40-weerData->minimumtemperatuur[2],15,weerData->minimumtemperatuur[2]);


	//altijd draw target na tekenen teruggeven naar scherm!
	maSetDrawTarget( HANDLE_SCREEN );

	//update de image met de nieuwe tekening
	this->diagramImage->setResource( this->diagramTekening );
}



void VisueelScherm::setToggleScherm( Screen* toggleScherm )
{
	//switch naar andere scherm (textueel scherm)
	this->toggleScherm = toggleScherm;
}




void VisueelScherm::pointerPressEvent( MAPoint2d maPoint )
{
	Point point;
	point.x = maPoint.x;
	point.y = maPoint.y;

	//update knop is ingedrukt
	if( this->updateKnop->contains( point ) )
	{
		this->updateKnop->setSelected( true );
		this->update();
	}
	else
	{
		this->updateKnop->setSelected( false );
	}


	//textueel knop is ingedrukt
	if( this->textueelKnop->contains( point ) )
	{
		this->textueelKnop->setSelected( true );
		this->hide();
		this->toggleScherm->show();
	}
	else
	{
		this->textueelKnop->setSelected( false );
	}
}


