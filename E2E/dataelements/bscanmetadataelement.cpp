#include "bscanmetadataelement.h"

#include "../streamhelper.h"
#include "../datadict/e2emdbdata.h"

#include "../e2e_packhelper.h"


#include <iostream>

namespace
{
	PACKSTRUCT(
	struct MetaDataStruct
	{
		uint32_t unknown1;
		uint32_t imgSizeX;
		uint32_t imgSizeY;
		float    posX1;
		float    posY1;
		float    posX2;
		float    posY2;
		uint32_t zero1;
		float    unknown2;
		float    scaleY; // ?
		float    unknown3One;
		uint32_t zero2;
		float    unknown4[2];
		uint32_t zero3;
		uint32_t imgSizeWidth; // redunanz?
		uint32_t numImages;
		uint32_t aktImage;
		uint32_t unknown5[4];
		uint64_t acquisitionTime;
		uint32_t unknown6[6];
		uint32_t numAve;
		uint32_t unknown7[8];
		float    imageQuality;
	});

	void copyBScansData(const MetaDataStruct& mds, E2E::BScanMetaDataElement::BScanData& bsd)
	{
		bsd.x1              = mds.posX1          ;
		bsd.y1              = mds.posY1          ;
		bsd.x2              = mds.posX2          ;
		bsd.y2              = mds.posY2          ;

		bsd.aktImage        = mds.aktImage       ;
		bsd.imgSizeWidth    = mds.imgSizeWidth   ;
		bsd.imgSizeX        = mds.imgSizeX       ;
		bsd.imgSizeY        = mds.imgSizeY       ;
		bsd.numImages       = mds.numImages      ;
		bsd.scaleY          = mds.scaleY         ;
		bsd.acquisitionTime = mds.acquisitionTime;
		bsd.numAve          = mds.numAve         ;
		bsd.imageQuality    = mds.imageQuality   ;
	}
}


namespace E2E
{

	BScanMetaDataElement::BScanMetaDataElement(std::istream& stream, MDbData& data)
	: BaseElement(stream, data)
	{
		// TODO size check

		MetaDataStruct header;
		StreamHelper::readFStream(stream, &header);

		copyBScansData(header, bscanData);

	}

	BScanMetaDataElement::~BScanMetaDataElement()
	{

	}


}