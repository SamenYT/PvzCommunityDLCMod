#define EACH_ROW\
	for (int y = 0; y < aDestRect.mHeight - 1; y++, aDestPixelsRow += aDestPixelsPitch)\
	{\
		float aBaseX = roundf(((int)aDestRect.mX) + 0 - theRotCenterX - theX);\
        float aBaseY = roundf(((int)aDestRect.mY) + y - theRotCenterY - theY);\
		\
		int aU = (int) ((aCos*(aBaseX) - aSin*(aBaseY) + theRotCenterX) * 0x10000);\
		int aV = (int) ((aCos*(aBaseY) + aSin*(aBaseX) + theRotCenterY) * 0x10000);\
		\
		DEST_PIXEL_TYPE* aDestPixels = aDestPixelsRow;\
		\
		int aLeft = 0;\
		int aRight = aDestRect.mWidth;\
		\
		int aUInt = (aU >> 16);\
		int aVInt = (aV >> 16);\
		\
		if (aCosLong <= -0x0001)\
		{\
			if (aUInt<0)\
				continue;\
		\
			int anEdgeLeft = (((theSrcRect.mWidth + 1) << 16) - 0x27FFF - aU) / aCosLong;\
			if (anEdgeLeft >= aLeft)\
				aLeft = anEdgeLeft;\
\
			int anEdgeRight = (0x07FFF - aU - 1) / aCosLong;\
			if (anEdgeRight < aRight)\
				aRight = anEdgeRight;\
		}\
		else if (aCosLong >= 0x0001)\
		{\
			if (aUInt >= theSrcRect.mWidth-1)\
				continue;\
	\
			int anEdgeLeft = (0x10000 - aU - 1) / aCosLong;\
			if (anEdgeLeft > aLeft)\
				aLeft = anEdgeLeft;\
\
			int anEdgeRight = (((theSrcRect.mWidth + 1) << 16) - 0x17FFF - aU) / aCosLong;\
			if (anEdgeRight < aRight)\
				aRight = anEdgeRight;\
		}\
		else if ((aU < 0) || (aU >= (theSrcRect.mWidth - 1) << 16))\
			continue;\
\
		if (aSinLong <= -0x0001)\
		{\
			if (aVInt<0)\
				continue;\
	\
			int anEdgeLeft = ((theSrcRect.mHeight << 16) - 0x27FFF - aV) / aSinLong;\
			if (anEdgeLeft > aLeft)\
				aLeft = anEdgeLeft;\
\
			int anEdgeRight = (0x0000 - aV) / aSinLong;\
			if (anEdgeRight < aRight)\
				aRight = anEdgeRight;\
		}\
		else if (aSinLong >= 0x0001)\
		{\
			if (aVInt >= theSrcRect.mHeight)\
				continue;\
	\
			int anEdgeLeft = (0x10000 - aV) / aSinLong;\
			if (anEdgeLeft > aLeft)\
				aLeft = anEdgeLeft;\
\
			int anEdgeRight = ((theSrcRect.mHeight << 16) - 0x17FFF - aV) / aSinLong;\
			if (anEdgeRight < aRight)\
				aRight = anEdgeRight;\
		}\
		else if ((aV < 0) || (aV >= theSrcRect.mHeight << 16))\
			continue;\
\
		aU += aLeft * aCosLong;\
		aV += aLeft * aSinLong;\
		aDestPixels += aLeft;\
\
		int aWidth = theImage->mWidth;
#define END_ROW }
{
#if defined(OPTIMIZE_SOFTWARE_DRAWING) && defined(WRITE_PIXEL_OPTIMIZED)
	if (gOptimizeSoftwareDrawing)
	{
		if (aNumBits == 16)
		{
#ifdef WRITE_PIXEL_OPTIMIZED_565
			if (aGMask == 0x7E0) // 5-6-5
			{
				EACH_ROW
				for (int x = aLeft; x <= aRight; x++)
				{
					int aUInt = (aU >> 16);
					int aVInt = (aV >> 16);
								
					SRC_TYPE* srcptr = aSrcBits + 
						(aVInt * aWidth) + aUInt;

					int aUFactor = (aU & 0xFFFE) + 1; // aUFactor needs to be between 1 and 0xFFFF to avoid overflow
					int aVFactor = (aV & 0xFFFE) + 1; // ditto for aVFactor

					ulong src1 = READ_COLOR(srcptr);
					ulong src2 = READ_COLOR(srcptr+1);
					ulong src3 = READ_COLOR(srcptr+theImage->mWidth);
					ulong src4 = READ_COLOR(srcptr+1+theImage->mWidth);
					
					int a1 = ((src1 >> 24) * ((ulong) ((0x10000  - aUFactor) * (0x10000  - aVFactor)) >> 16)) >> 16;
					int a2 = ((src2 >> 24) * ((ulong) ((           aUFactor) * (0x10000  - aVFactor)) >> 16)) >> 16;
					int a3 = ((src3 >> 24) * ((ulong) ((0x10000  - aUFactor) * (           aVFactor)) >> 16)) >> 16;
					int a4 = ((src4 >> 24) * ((ulong) ((           aUFactor) * (           aVFactor)) >> 16)) >> 16;

					WRITE_PIXEL_OPTIMIZED_565;

					aU += aCosLong;
					aV += aSinLong;
				}
				END_ROW
			}
#endif
#ifdef WRITE_PIXEL_OPTIMIZED_555
#ifdef WRITE_PIXEL_OPTIMIZED_565
			else
#endif
			if (aGMask == 0x3E0) // 5-5-5
			{
				EACH_ROW
				for (int x = aLeft; x <= aRight; x++)
				{
					int aUInt = (aU >> 16);
					int aVInt = (aV >> 16);
								
					SRC_TYPE* srcptr = aSrcBits + 
						(aVInt * aWidth) + aUInt;

					int aUFactor = (aU & 0xFFFE) + 1; // aUFactor needs to be between 1 and 0xFFFF to avoid overflow
					int aVFactor = (aV & 0xFFFE) + 1; // ditto for aVFactor

					ulong src1 = READ_COLOR(srcptr);
					ulong src2 = READ_COLOR(srcptr+1);
					ulong src3 = READ_COLOR(srcptr+theImage->mWidth);
					ulong src4 = READ_COLOR(srcptr+1+theImage->mWidth);
					
					int a1 = ((src1 >> 24) * ((ulong) ((0x10000  - aUFactor) * (0x10000  - aVFactor)) >> 16)) >> 16;
					int a2 = ((src2 >> 24) * ((ulong) ((           aUFactor) * (0x10000  - aVFactor)) >> 16)) >> 16;
					int a3 = ((src3 >> 24) * ((ulong) ((0x10000  - aUFactor) * (           aVFactor)) >> 16)) >> 16;
					int a4 = ((src4 >> 24) * ((ulong) ((           aUFactor) * (           aVFactor)) >> 16)) >> 16;

					WRITE_PIXEL_OPTIMIZED_555;

					aU += aCosLong;
					aV += aSinLong;
				}
				END_ROW
			}
#endif
#if defined(WRITE_PIXEL_OPTIMIZED_555) || defined(WRITE_PIXEL_OPTIMIZED_565)
			else
#endif
			{
				EACH_ROW
				for (int x = aLeft; x <= aRight; x++)
				{
					int aUInt = (aU >> 16);
					int aVInt = (aV >> 16);
								
					SRC_TYPE* srcptr = aSrcBits + 
						(aVInt * aWidth) + aUInt;

					int aUFactor = (aU & 0xFFFE) + 1; // aUFactor needs to be between 1 and 0xFFFF to avoid overflow
					int aVFactor = (aV & 0xFFFE) + 1; // ditto for aVFactor

					ulong src1 = READ_COLOR(srcptr);
					ulong src2 = READ_COLOR(srcptr+1);
					ulong src3 = READ_COLOR(srcptr+theImage->mWidth);
					ulong src4 = READ_COLOR(srcptr+1+theImage->mWidth);
					
					int a1 = ((src1 >> 24) * ((ulong) ((0x10000  - aUFactor) * (0x10000  - aVFactor)) >> 16)) >> 16;
					int a2 = ((src2 >> 24) * ((ulong) ((           aUFactor) * (0x10000  - aVFactor)) >> 16)) >> 16;
					int a3 = ((src3 >> 24) * ((ulong) ((0x10000  - aUFactor) * (           aVFactor)) >> 16)) >> 16;
					int a4 = ((src4 >> 24) * ((ulong) ((           aUFactor) * (           aVFactor)) >> 16)) >> 16;
					
					WRITE_PIXEL;

					aU += aCosLong;
					aV += aSinLong;
				}
				END_ROW
			}
		}
		else if (aNumBits == 32)
		{
			EACH_ROW
			for (int x = aLeft; x <= aRight; x++)
			{
				int aUInt = (aU >> 16);
				int aVInt = (aV >> 16);
							
				SRC_TYPE* srcptr = aSrcBits + 
					(aVInt * aWidth) + aUInt;

				int aUFactor = (aU & 0xFFFE) + 1; // aUFactor needs to be between 1 and 0xFFFF to avoid overflow
				int aVFactor = (aV & 0xFFFE) + 1; // ditto for aVFactor

				ulong src1 = READ_COLOR(srcptr);
				ulong src2 = READ_COLOR(srcptr+1);
				ulong src3 = READ_COLOR(srcptr+theImage->mWidth);
				ulong src4 = READ_COLOR(srcptr+1+theImage->mWidth);
				
				int a1 = ((src1 >> 24) * ((ulong) ((0x10000  - aUFactor) * (0x10000  - aVFactor)) >> 16)) >> 16;
				int a2 = ((src2 >> 24) * ((ulong) ((           aUFactor) * (0x10000  - aVFactor)) >> 16)) >> 16;
				int a3 = ((src3 >> 24) * ((ulong) ((0x10000  - aUFactor) * (           aVFactor)) >> 16)) >> 16;
				int a4 = ((src4 >> 24) * ((ulong) ((           aUFactor) * (           aVFactor)) >> 16)) >> 16;
				
				WRITE_PIXEL_OPTIMIZED;

				aU += aCosLong;
				aV += aSinLong;
			}
			END_ROW
		}
	}
	else
	{
#endif
		EACH_ROW
		for (int x = aLeft; x <= aRight; x++)
		{
			int aUInt = (aU >> 16);
			int aVInt = (aV >> 16);
						
			SRC_TYPE* srcptr = aSrcBits + 
				(aVInt * aWidth) + aUInt;

			int aUFactor = (aU & 0xFFFE) + 1; // aUFactor needs to be between 1 and 0xFFFF to avoid overflow
			int aVFactor = (aV & 0xFFFE) + 1; // ditto for aVFactor

			ulong src1 = READ_COLOR(srcptr);
			ulong src2 = READ_COLOR(srcptr+1);
			ulong src3 = READ_COLOR(srcptr+theImage->mWidth);
			ulong src4 = READ_COLOR(srcptr+1+theImage->mWidth);
			
			int a1 = ((src1 >> 24) * ((ulong) ((0x10000  - aUFactor) * (0x10000  - aVFactor)) >> 16)) >> 16;
			int a2 = ((src2 >> 24) * ((ulong) ((           aUFactor) * (0x10000  - aVFactor)) >> 16)) >> 16;
			int a3 = ((src3 >> 24) * ((ulong) ((0x10000  - aUFactor) * (           aVFactor)) >> 16)) >> 16;
			int a4 = ((src4 >> 24) * ((ulong) ((           aUFactor) * (           aVFactor)) >> 16)) >> 16;
			
			WRITE_PIXEL;
	
			aU += aCosLong;
			aV += aSinLong;
		}
		END_ROW
#if defined(OPTIMIZE_SOFTWARE_DRAWING) && defined(WRITE_PIXEL_OPTIMIZED)
	}
#endif
}